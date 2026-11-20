set(MATH_SOURCE Math.cpp Math_operations.cpp)

add_executable(math_app ${MATH_SOURCE})

target_include_directories(math_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../../includes)

target_link_libraries(math_app PRIVATE -lrt ${CMAKE_CURRENT_SOURCE_DIR}/../../build/IPCLibrary/src/libIPCLibrary.a)
