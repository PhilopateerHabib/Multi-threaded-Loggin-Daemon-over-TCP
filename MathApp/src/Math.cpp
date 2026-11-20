#include <iostream>
#include <cstring>
#include "Math_operations.h"
#include "util.h"
#include "IPCSender.h"

Message my_msg;

// send message using IPCSender
void sendMyMessage(IPCSender *My_Sender, const char *msg, LogLevel log_level)
{
    strcpy(my_msg.msg, msg);
    my_msg.log_level = log_level;
    My_Sender->sendMessage(my_msg);
}

// showing --help or in bad behaviour
void printHelpManual(const char *programName)
{
    std::cout << "Usage: " << programName << " <operation> <operand1> [operand2]" << std::endl;
    std::cout << "Available operations:" << std::endl;
    std::cout << "  add     : Addition       => add  <operand1> <operand2>" << std::endl;
    std::cout << "  mul     : Multiplication => mul  <operand1> <operand2>" << std::endl;
    std::cout << "  sub     : Subtraction    => sub  <operand1> <operand2>" << std::endl;
    std::cout << "  div     : Division       => div  <operand1> <operand2>" << std::endl;
    std::cout << "  mod     : Modulo         => mod  <operand1> <operand2>" << std::endl;
    std::cout << "  pow     : Power          => pow  <operand1> <operand2>" << std::endl;
    std::cout << "  fact    : Factorial      => fact <operand1>" << std::endl;
    std::cout << "  sqrt    : Square Root    => sqrt <operand1>" << std::endl;
    std::cout << "  abs     : Absolute       => abs  <operand1>" << std::endl;
    std::cout << "  max     : Maximum        => max  <operand1> <operand2>" << std::endl;
    std::cout << "  min     : Minimum        => min  <operand1> <operand2>" << std::endl;
}

int main(int argc, char *argv[])
{
    IPCSender My_Sender = IPCSender("/Math_Msg_Que");

    if (My_Sender.connectToMessageQueue() == FAILURE)
    {
        return 1;
    }

    sendMyMessage(&My_Sender, "Just connected to message queue", Info);
    sendMyMessage(&My_Sender, "Checking number of args", Info);

    if (argc < 2)
    {
        std::string argv_0(argv[0]);

        std::string err_msg = "Usage: " + argv_0 + " <operation> <operand1> [operand2]";
        std::string full_msg = "Invalid input => " + err_msg;
        sendMyMessage(&My_Sender, full_msg.c_str(), Error);
        printHelpManual(argv_0.c_str());
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0)
    {
        printHelpManual(argv[0]);
        return 0;
    }

    if (argc < 3)
    {
        std::string argv_0(argv[0]);

        std::string err_msg = "Usage: " + argv_0 + " operation operand1 [operand2]";
        std::string full_msg = "Invalid input => " + err_msg;
        sendMyMessage(&My_Sender, full_msg.c_str(), Error);
        printHelpManual(argv_0.c_str());
        return 1;
    }

    MathOperations *mathInstance = MathOperations::getInstance();
    sendMyMessage(&My_Sender, "Start parsing the input", Info);

    std::string operation = argv[1];
    double operand1 = std::stod(argv[2]);
    double operand2 = 0.0; // Initialize operand2 with a default value

    // Check if the operation requires two operands
    bool requiresTwoOperands = true;
    if (operation == "fact" || operation == "sqrt" || operation == "abs")
    {
        requiresTwoOperands = false;
    }

    if (requiresTwoOperands)
    {
        if (argc < 4)
        {
            sendMyMessage(&My_Sender, "Operation requires two operands", Error);
            printHelpManual(argv[0]);
            return 1;
        }
        operand2 = std::stod(argv[3]);
    }

    sendMyMessage(&My_Sender, "Finish parsing the input", Info);

    double result;

    if (operation == "add")
    {
        sendMyMessage(&My_Sender, "Detecting addition operation", Info);
        sendMyMessage(&My_Sender, "Start adding operation", Info);
        result = mathInstance->add(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed adding operation", Info);
    }
    else if (operation == "mul")
    {
        sendMyMessage(&My_Sender, "Detecting multiplication operation", Info);
        sendMyMessage(&My_Sender, "Start multiplying operation", Info);
        result = mathInstance->multiply(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed multiplying operation", Info);
    }
    else if (operation == "sub")
    {
        sendMyMessage(&My_Sender, "Detecting subtraction operation", Info);
        sendMyMessage(&My_Sender, "Start subtracting operation", Info);
        result = mathInstance->subtract(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed subtracting operation", Info);
    }
    else if (operation == "div")
    {
        sendMyMessage(&My_Sender, "Detecting division operation", Info);
        sendMyMessage(&My_Sender, "Start dividing operation", Info);
        result = mathInstance->divide(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed dividing operation", Info);
    }
    else if (operation == "mod")
    {
        sendMyMessage(&My_Sender, "Detecting modulo operation", Info);
        sendMyMessage(&My_Sender, "Start modulo operation", Info);
        result = mathInstance->modulo(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed modulo operation", Info);
    }
    else if (operation == "pow")
    {
        sendMyMessage(&My_Sender, "Detecting power operation", Info);
        sendMyMessage(&My_Sender, "Start power operation", Info);
        result = mathInstance->power(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed power operation", Info);
    }
    else if (operation == "fact")
    {
        sendMyMessage(&My_Sender, "Detecting factorial operation", Info);
        sendMyMessage(&My_Sender, "Start factorial operation", Info);
        result = mathInstance->factorial(operand1);
        sendMyMessage(&My_Sender, "Finshed factorial operation", Info);
    }
    else if (operation == "sqrt")
    {
        sendMyMessage(&My_Sender, "Detecting square root operation", Info);
        sendMyMessage(&My_Sender, "Start square root operation", Info);
        result = mathInstance->squareRoot(operand1);
        sendMyMessage(&My_Sender, "Finshed square root operation", Info);
    }
    else if (operation == "abs")
    {
        sendMyMessage(&My_Sender, "Detecting absolute operation", Info);
        sendMyMessage(&My_Sender, "Start absolute operation", Info);
        result = mathInstance->absolute(operand1);
        sendMyMessage(&My_Sender, "Finshed absolute operation", Info);
    }
    else if (operation == "max")
    {
        sendMyMessage(&My_Sender, "Detecting maximum operation", Info);
        sendMyMessage(&My_Sender, "Start maximum operation", Info);
        result = mathInstance->max(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed maximum operation", Info);
    }
    else if (operation == "min")
    {
        sendMyMessage(&My_Sender, "Detecting minimum operation", Info);
        sendMyMessage(&My_Sender, "Start minimum operation", Info);
        result = mathInstance->min(operand1, operand2);
        sendMyMessage(&My_Sender, "Finshed minimum operation", Info);
    }
    else
    {
        sendMyMessage(&My_Sender, "Detecting unsupported operation", Error);
        std::cout << "Unsupported operation: " << operation << std::endl;
        return 1;
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
