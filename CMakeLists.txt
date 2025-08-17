# SPDX-License-Identifier: Apache-2.0
set(BOARD nucleo_f401re)

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
include(FetchContent)

project(blinky LANGUAGES C CXX)

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h CACHE STRING "" FORCE)

message(STATUS "LV_CONF_PATH set to: ${LV_CONF_PATH}")

set(LV_VERSION "v9.0.0") # this string represents the Tag name of the release desired - Change the GIT_TAG below as well
message("Fetching LVGL " ${LV_VERSION})

# Store the original value of ZEPHYR_BASE
set(ORIGINAL_ZEPHYR_BASE "${ZEPHYR_BASE}")

# Temporarily unset ZEPHYR_BASE
unset(ZEPHYR_BASE CACHE)

# Fetch lvgl
#FetchContent_Declare(
#        lvgl
##        GIT_REPOSITORY https://github.com/lvgl/lvgl
#        GIT_TAG       v9.0.0
#)

#FetchContent_MakeAvailable(
#        lvgl
#)
#message("Fetching LVGL Done")#
#
#message("lvgl " ${lvgl_SOURCE_DIR})
target_sources(app PRIVATE
        src/main.c
#        gp9002a/gp9002a.c
)


# Add LVGL as a static library
#target_include_directories(app PRIVATE ${lvgl_SOURCE_DIR}/src)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#target_link_libraries(app PRIVATE lvgl)


