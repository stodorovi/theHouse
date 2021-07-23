include_directories("${PROJECT_SOURCE_DIR}/src/game")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/game")

set(SRC_FILES "${PROJECT_SOURCE_DIR}/src/main.cpp"
              "${PROJECT_SOURCE_DIR}/src/Actor.h"
              "${PROJECT_SOURCE_DIR}/src/Actor.cpp"
              "${PROJECT_SOURCE_DIR}/src/AudioManager.h"
              "${PROJECT_SOURCE_DIR}/src/AudioManager.cpp"
              "${PROJECT_SOURCE_DIR}/src/Button.h"
              "${PROJECT_SOURCE_DIR}/src/Button.cpp"
              "${PROJECT_SOURCE_DIR}/src/Camera.h"
              "${PROJECT_SOURCE_DIR}/src/Camera.cpp"
              "${PROJECT_SOURCE_DIR}/src/DrawableObject.h"
              "${PROJECT_SOURCE_DIR}/src/DrawableObject.cpp"
              "${PROJECT_SOURCE_DIR}/src/GameException.h"
              "${PROJECT_SOURCE_DIR}/src/GameException.cpp"
              "${PROJECT_SOURCE_DIR}/src/GameObject.h"
              "${PROJECT_SOURCE_DIR}/src/GameObject.cpp"
              "${PROJECT_SOURCE_DIR}/src/Image.h"
              "${PROJECT_SOURCE_DIR}/src/Image.cpp"
              "${PROJECT_SOURCE_DIR}/src/Text.h"
              "${PROJECT_SOURCE_DIR}/src/Text.cpp"
              "${PROJECT_SOURCE_DIR}/src/TextureManager.h"
              "${PROJECT_SOURCE_DIR}/src/TextureManager.cpp"
              "${PROJECT_SOURCE_DIR}/src/Timer.h"
              "${PROJECT_SOURCE_DIR}/src/Timer.cpp"
              ${GAME_FILES}
              PARENT_SCOPE
)