cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PraticaTesteUnitario C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# ----------------------------------------
# Main executable (application)

add_executable(PraticaTesteUnitario
    app/main.c
    drivers/temp_sensor.c
    hal/hal_temp_sensor.c
)

pico_set_program_name(PraticaTesteUnitario "PraticaTesteUnitario")
pico_set_program_version(PraticaTesteUnitario "0.1")

pico_enable_stdio_uart(PraticaTesteUnitario 0)
pico_enable_stdio_usb(PraticaTesteUnitario 1)

target_link_libraries(PraticaTesteUnitario
    pico_stdlib
    hardware_adc
)

target_include_directories(PraticaTesteUnitario PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/lib/unity
)

pico_add_extra_outputs(PraticaTesteUnitario)

