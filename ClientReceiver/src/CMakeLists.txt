set(CMAKE_CXX_STANDARD 17)

set(SERVER_SOURCE Client.cpp ClientReceiver.cpp)
add_executable(client_App ${SERVER_SOURCE})


target_include_directories(client_App PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)


