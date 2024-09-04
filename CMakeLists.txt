cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
# find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

SET(FastNoise FastNoise)
STRING(TOLOWER ${FastNoise} FastNoise)
if (NOT "${FastNoise}_FOUND") # If there's none, fetch and build FastNoise2
  include(FetchContent)
  FetchContent_Declare(
    ${FastNoise}
    GIT_REPOSITORY https://github.com/Auburn/FastNoise2.git
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
  )
  FetchContent_GetProperties(${FastNoise})
  if (NOT "${FastNoise}_POPULATED") # Have we downloaded FastNoise2 yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(${FastNoise})
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory("${${FastNoise}_SOURCE_DIR}" "${${FastNoise}_BINARY_DIR}")
  endif()
endif()

# Our Project
include_directories(./src/)
SET (SRC_DIR ./src/apps/)
CMAKE_PATH(APPEND APPS_SRC_ABS_DIR ${PROJECT_SOURCE_DIR} ${SRC_DIR} )
file( GLOB_RECURSE APP_SOURCES ./src/apps/**.c* )
foreach( appSourceFile ${APP_SOURCES} )
    # Cut off the file extension and directory path

    get_filename_component(appDir ${appSourceFile} REALPATH )
    file(RELATIVE_PATH appDir ${APPS_SRC_ABS_DIR} ${appDir})
    get_filename_component( appDir ${appDir} DIRECTORY)
    
    get_filename_component(appName ${appSourceFile} NAME_WE )

    # MESSAGE( STATUS "----- Folder: ${appDir} App: ${appName} -----" )
    
    add_executable( ${appName} ${appSourceFile} )

    set_target_properties( ${appName}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${appDir}"
  )
    # Make sure YourLib is linked to each app
    target_link_libraries( ${appName} raylib )
    target_link_libraries( ${appName} m )
    target_link_libraries( ${appName} FastNoise )
endforeach( appSourceFile ${APP_SOURCES} )


#set(raylib_VERBOSE 1)
# target_link_libraries(${PROJECT_NAME} raylib)
# target_link_libraries(${PROJECT_NAME} m)

# Web Configurations
# if (${PLATFORM} STREQUAL "Web")
#     # Tell Emscripten to build an example.html file.
#     set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
# endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()