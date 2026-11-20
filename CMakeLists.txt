cmake_minimum_required(VERSION 3.22)
project(Capstone_Project)


set(GPP_RPI4_CROSS_COMPILER /home/philo/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++)
set(GCC_RPI4_CROSS_COMPILER /home/philo/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc)

set(BOOST_ROOT /home/philo/baw/boost_arm64_install)
set(YAML_ROOT /home/philo/Yaml_build/usr/local)


add_subdirectory(ClientReceiver)
add_subdirectory(IPCLibrary)
add_subdirectory(Daemon)
add_subdirectory(MathApp)
add_subdirectory(Looper)


set(INSTALL_DESTINATION bin)

# Install the executable to the specified directory
set(executables ServerApp math_app looper_app)
install(TARGETS ${executables} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin_rpi)
install(TARGETS client_App DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin_host)



