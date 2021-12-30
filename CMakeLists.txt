cmake_minimum_required(VERSION 3.18)
#配置cmake使用的版本号
project(single_source)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-static -DNOSSL")
add_executable(single_source config.cpp config.h libftp/ftplib.cpp libftp/ftplib.h)
