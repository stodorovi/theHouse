include_directories("${PROJECT_SOURCE_DIR}/src/game/characters"
                    "${PROJECT_SOURCE_DIR}/src/game/levels"
                    "${PROJECT_SOURCE_DIR}/src/game/objects"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/src/game/characters")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/game/levels")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/game/objects")

set(GAME_FILES "${PROJECT_SOURCE_DIR}/src/game/Character.h"
               "${PROJECT_SOURCE_DIR}/src/game/Character.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/Circle.h"
               "${PROJECT_SOURCE_DIR}/src/game/Circle.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/Game.h"
               "${PROJECT_SOURCE_DIR}/src/game/Game.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/Level.h"
               "${PROJECT_SOURCE_DIR}/src/game/Level.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/Mission.h"
               "${PROJECT_SOURCE_DIR}/src/game/Mission.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/PlayerLivesIcon.h"
               "${PROJECT_SOURCE_DIR}/src/game/PlayerLivesIcon.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/TimeOfDayIcon.h"
               "${PROJECT_SOURCE_DIR}/src/game/TimeOfDayIcon.cpp"
               "${PROJECT_SOURCE_DIR}/src/game/Wall.h"
               "${PROJECT_SOURCE_DIR}/src/game/Wall.cpp"
               ${CHARACTERS_FILES}
               ${LEVELS_FILES}
               ${OBJECTS_FILES}
               PARENT_SCOPE
)