set(SERVER_SOURCE Server.cpp serverApp.cpp)


set(BOOST_INCLUDE_DIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARY_DIR ${BOOST_ROOT}/lib)
set(YAML_INCLUDE_DIR ${YAML_ROOT}/include)
set(YAML_LIBRARY_DIR ${YAML_ROOT}/lib)


find_package(Boost REQUIRED COMPONENTS log log_setup thread)
find_package(yaml-cpp REQUIRED)

set(Boost_USE_MULTITHREADED ON)

add_executable(ServerApp ${SERVER_SOURCE})


target_include_directories(ServerApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../includes ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(ServerApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${BOOST_INCLUDE_DIR} ${YAML_INCLUDE_DIR})


target_link_libraries(ServerApp PRIVATE pthread ${BOOST_LIBRARY_DIR} Boost::log_setup Boost::log)
target_link_libraries(ServerApp PRIVATE -lrt ${YAML_LIBRARY_DIR}/libyaml-cpp.a)
target_link_libraries(ServerApp PRIVATE -lrt ${CMAKE_CURRENT_SOURCE_DIR}/../../build/IPCLibrary/src/libIPCLibrary.a)

