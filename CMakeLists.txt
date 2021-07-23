cmake_minimum_required(VERSION 3.10)

project(House VERSION 1.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2       REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(SDL2_ttf   REQUIRED)

include_directories("${SDL2_INCLUDE_DIR}"
                    "${SDL2_IMAGE_INCLUDE_DIR}"
                    "${SDL2_MIXER_INCLUDE_DIR}"
                    "${SDL2_TTF_INCLUDE_DIR}"
                    "${PROJECT_SOURCE_DIR}/src"
                    "${PROJECT_SOURCE_DIR}/src/game"
                    "${PROJECT_SOURCE_DIR}/src/game/characters"
                    "${PROJECT_SOURCE_DIR}/src/game/levels"
                    "${PROJECT_SOURCE_DIR}/src/game/objects"
)

set(SDL_LIBS SDL2
SDL2_image
SDL_mixer
SDL_ttf
)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

set(GAME_SOURCES "${SRC_FILES}")

add_executable(${CMAKE_PROJECT_NAME} "${GAME_SOURCES}")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}
                                      ${SDL2_IMAGE_LIBRARIES}
                                      ${SDL2_MIXER_LIBRARIES}
                                      ${SDL2_TTF_LIBRARIES})