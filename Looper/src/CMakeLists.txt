add_executable(looper_app Looper.cpp)

target_include_directories(looper_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../includes)

target_link_libraries(looper_app PRIVATE -lrt ${CMAKE_CURRENT_SOURCE_DIR}/../../build/IPCLibrary/src/libIPCLibrary.a)
