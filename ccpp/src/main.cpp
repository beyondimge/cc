#include "../include/game.hpp"

int main(int argc, char **argv)
{
    ccpp::game::Game game;

    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }

    game.Shutdown();
    return 0;
}