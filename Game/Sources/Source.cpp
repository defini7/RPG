#include "../Include/Game.hpp"

int main()
{
    Game game;

    if (game.Construct(256, 240, 4, 4, false, true))
        game.Run();

    return 0;
}
