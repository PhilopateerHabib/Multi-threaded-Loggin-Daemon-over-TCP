#include "Server.h"
#include <csignal>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <ctime>

int Server::server_socket_fd = -1;
int Server::client_socket_fd = -1;
bool Server::is_closed_socket = true;

std::string getCurrentTimestamp()
{
    std::time_t now = std::time(nullptr);
    char buffer[80];
    struct tm time_info;

    localtime_r(&now, &time_info);
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d__%H:%M:%S]", &time_info);

    return std::string(buffer);
}

std::string formatLogMessage(const boost::log::record_view &rec)
{
    std::ostringstream formatted;
    formatted << "[" << boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec) << "] "
              << "[" << boost::log::extract<boost::log::trivial::severity_level>("Severity", rec) << "] "
              << boost::log::extract<std::string>("Message", rec);
    return formatted.str();
}

std::string Server::writeLogToFile(const std::string &filename, const std::string &message, LogLevel severity)
{
    boost::log::add_common_attributes();

    // Create a sink backend that stores log messages
    struct LogCaptureBackend : public boost::log::sinks::basic_formatted_sink_backend<char>
    {
        boost::log::record_view lastRecord;

        void consume(boost::log::record_view const &rec, string_type const &formatted_message)
        {
            lastRecord = rec;
        }
    };

    // Create the sink and attach it to the logger
    boost::shared_ptr<LogCaptureBackend> captureBackend(new LogCaptureBackend());
    boost::shared_ptr<boost::log::sinks::synchronous_sink<LogCaptureBackend>> captureSink(
        new boost::log::sinks::synchronous_sink<LogCaptureBackend>(captureBackend));
    boost::log::core::get()->add_sink(captureSink);

    boost::log::add_file_log(
        boost::log::keywords::file_name = filename,
        boost::log::keywords::open_mode = std::ios_base::app,
        boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%");

    boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger;
    boost::log::trivial::severity_level boostSeverityLevel;

    switch (severity)
    {
    case LogLevel::Trace:
        boostSeverityLevel = boost::log::trivial::trace;
        break;
    case LogLevel::Debug:
        boostSeverityLevel = boost::log::trivial::debug;
        break;
    case LogLevel::Info:
        boostSeverityLevel = boost::log::trivial::info;
        break;
    case LogLevel::Warning:
        boostSeverityLevel = boost::log::trivial::warning;
        break;
    case LogLevel::Error:
        boostSeverityLevel = boost::log::trivial::error;
        break;
    case LogLevel::Fatal:
        boostSeverityLevel = boost::log::trivial::fatal;
        break;
    }

    BOOST_LOG_SEV(logger, boostSeverityLevel) << message;

    boost::log::core::get()->remove_sink(captureSink);
    boost::log::core::get()->remove_all_sinks();

    return formatLogMessage(captureBackend->lastRecord);
}

Server::Server()
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, signalHandler);
    server_socket_fd = -1;
    client_socket_fd = -1;
    is_closed_socket = true;
}

Server &Server::getInstance()
{
    static Server instance;
    return instance;
}

void Server::signalHandler(int signum)
{
    close(client_socket_fd);
    close(server_socket_fd);
    std::cout << "\nReceived signal " << signum << ". Exiting..." << std::endl;
    exit(signum);
}

SuccessState Server::createServerSocket()
{
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd == -1)
    {
        std::cout << "Failed to create server socket." << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

SuccessState Server::bindSocket(const int socket_port_num)
{
    int flags = fcntl(server_socket_fd, F_GETFL, 0);
    fcntl(server_socket_fd, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(socket_port_num); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;      // Listen on all available interfaces

    if (bind(server_socket_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        close(server_socket_fd);
        std::cout << "Failed To bind Socket" << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

SuccessState Server::listenSocket()
{
    if (listen(server_socket_fd, 1) == -1)
    {
        close(server_socket_fd);
        std::cout << "Failed To Listen" << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

std::string Server::saveLog(const char *file_name, std::string message, LogLevel log_level)
{
    static std::mutex logMutex; // Mutex to protect static variable

    // Lock the mutex before accessing the static variable
    std::lock_guard<std::mutex> lock(logMutex);

    // Increment the static counter
    static int logCount = 0;
    logCount++;

    std::cout << logCount << std::endl;

    if (logCount >= 11)
    {
        std::string old_file_name = std::string(file_name);

        // Remove the ".txt" extension from file_name
        size_t dotPos = old_file_name.find_last_of('.');
        if (dotPos != std::string::npos)
        {
            old_file_name.erase(dotPos);
        }
        std::string timestamp = getCurrentTimestamp();
        std::string new_file_name = old_file_name + " " + timestamp + ".txt";
        std::rename(file_name, new_file_name.c_str());
        logCount = 1;
    }

    return writeLogToFile(file_name, message.c_str(), log_level);
}

void Server::acceptClientConnection()
{
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&clientAddr, &clientAddrSize);
    std::cout << "Accept Connection" << std::endl;
    is_closed_socket = false;
}

SuccessState Server::sendResultToClient(std::string message)
{
    static std::mutex logMutex; // Mutex to protect static variable

    // Lock the mutex before accessing the static variable
    std::lock_guard<std::mutex> lock(logMutex);
    ssize_t sendResult = send(client_socket_fd, message.c_str(), message.size(), 0);
    if (sendResult == -1)
    {
        std::cout << "Failed in Sending" << std::endl;
        is_closed_socket = true;
        return FAILURE;
    }
    return SUCCESS;
}

bool Server::getSocketClosingState()
{
    return is_closed_socket;
}

int Server::getServerSocketFd()
{
    return server_socket_fd;
}

int Server::getClientSocketFd()
{
    return client_socket_fd;
}

void Server::closeAll()
{
    close(server_socket_fd);
}
