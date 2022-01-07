cmake_minimum_required(VERSION 3.18)
#配置cmake使用的版本号
project(single_source)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-static -DNOSSL")
add_executable(5g_ssrc main.cpp libftp/ftplib.cpp libftp/ftplib.h Fpga.h zynq7035.cpp
        zynq7035.h ftp.cpp ftp.h)