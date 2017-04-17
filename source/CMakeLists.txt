if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    message("Debug output enabled.")
    add_definitions(-DDEBUG_MODE)
else()
endif()

add_executable(main main.cpp Systems.h)


