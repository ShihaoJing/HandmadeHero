if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    message("Debug output enabled.")
    add_definitions(-DDEBUG_MODE)
else()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(HANDMADE_INTERNAL "Option description" 1)
option(HANDMADE_SLOW "Option description" 1)

if(HANDMADE_INTERNAL)
    add_definitions(-DHANDMADE_INTERNAL)
endif()
if(HANDMADE_SLOW)
    add_definitions(-DHANDMADE_SLOW)
endif()

set(SOURCE_FILES sdl_handmade.cpp handmade.cpp)
add_executable(main ${SOURCE_FILES})

include(FindPkgConfig)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES})
endif()

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES})