cmake_minimum_required(VERSION 3.16)
project(pibot)

set(CMAKE_CXX_STANDARD 17)

add_executable(pibot
    main.cpp
    gpio.cpp
)

# find_library(PIGPIO_LIB pigpio REQUIRED)
# find_library(RT_LIB rt REQUIRED)

# target_link_libraries(pibot
#     ${PIGPIO_LIB}
#     ${RT_LIB}
# )

# websocket のライブラリ紐づけ
target_include_directories(pibot INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/uWebSockets/src
)
