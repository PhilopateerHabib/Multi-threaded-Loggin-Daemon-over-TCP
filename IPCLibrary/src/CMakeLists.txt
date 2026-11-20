add_library(IPCLibrary STATIC 
    IPCReceiver.cpp 
    IPCSender.cpp
)
target_include_directories(IPCLibrary 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../includes
)
