
cmake_minimum_required(VERSION 3.4.1)
set(PATH_TO_NATIVE ${PATH_TO_MEDIACORE}/src/main/cpp)
set(PATH_TO_PRE_BUILT ${PATH_TO_MEDIACORE}/libs/${ANDROID_ABI})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -s")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--gc-sections,--icf=safe")
include_directories(BEFORE ${PATH_TO_MEDIACORE}/libs/include/)

file(GLOB  FFMPEG_DECODE_SOURCE "*.cpp")#包含当前目录的cpp文件
add_definitions(-DDLIB_PNG_SUPPORT)
add_library(opencv
        SHARED
        ${FFMPEG_DECODE_SOURCE}
        )


target_link_libraries(opencv
                    log
                    z
                    ${PATH_TO_PRE_BUILT}/libopencv_java3.so
                    ${PATH_TO_PRE_BUILT}/libdlib.so
                    )


