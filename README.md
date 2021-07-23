# The House of Nine
## How To Play
* W - Move Up
* A - Move Left
* S - Move Down
* D - Move Right

* Ctrl - Attack
* Alt - Defend

## Dependencies
This project requires the following SDL2 libraries: \
`SDL2` \
`SDL2-image` \
`SDL2-mixer` \
`SDL2-ttf`

## Building
```
CMake 3.10 minimum required to build.
```
**All libraries should be installed before building the project**
* If the libraries were not found by CMake, add their paths to the `CMAKE_INSTALL_PREFIX`

## Running the game
The compiled binary should be placed inside the root folder, or inside a folder which contains the following folders: \
`sfx` `gfx` & `fonts`.