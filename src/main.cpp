#include <iostream>
#include <memory>

#include "game/Game.h"
#include "GameException.h"

int main(int argc, char **argv) {
    std::unique_ptr<house::Game> game =
                        std::make_unique<house::Game>("The House of Nine");

    bool gameInitialised = false;
    try {
        gameInitialised = game->init();
    }
    catch (const house::GameException &e) {
        std::cerr << e.what();
        e.writeToLog();
    }

    if (gameInitialised) {
        try{
            game->start();
        }
        catch (const house::GameException &e) {
            std::cerr << e.what();
            e.writeToLog();
        }
    }

    game->unload();
    
    return 0;
}