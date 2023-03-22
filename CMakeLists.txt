cmake_minimum_required(VERSION 3.12)

project(Game)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE Game_SOURCES CONFIGURE_DEPENDS "sources/*.cpp")
file(GLOB_RECURSE Game_HEADERS CONFIGURE_DEPENDS "headers/*.hpp")

set(Game_INCLUDE_DIRS "")

foreach(_headerFile ${Game_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND Game_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES Game_INCLUDE_DIRS)

if(WIN32)
    add_executable(Game ${Game_SOURCES})
else()
    add_executable(Game MACOSX_BUNDLE ${Game_SOURCES})
endif()

if(APPLE)
    target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2.framework/Headers ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_image.framework/Headers ${Game_INCLUDE_DIRS})
else()
    target_include_directories(Game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc PRIVATE ${Game_INCLUDE_DIRS})
endif()

if(APPLE)
    find_library(SDL SDL2)
    find_library(SDL_image SDL2_image)
    target_link_libraries(Game PRIVATE ${SDL} ${SDL_image})
else()
    target_link_libraries(Game PRIVATE mingw32 SDL2main SDL2.dll SDL2_image.dll)
endif()

file(GLOB_RECURSE Game_ASSETS CONFIGURE_DEPENDS "assets/*.png")

if(APPLE)
    add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Game.app/Contents/MacOS/assets)
    add_custom_command(
        TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${Game_ASSETS}
        ${CMAKE_CURRENT_BINARY_DIR}/Game.app/Contents/MacOS/assets)
else()
    add_custom_command(TARGET Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets)
    add_custom_command(
        TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${Game_ASSETS}
        ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()