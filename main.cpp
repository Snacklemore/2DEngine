#include <iostream>
#include "Game.h"
sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

int main() {
    Game game;
    sf::Clock clock;
    while (game.IsRunning())
    {
        sf::Time elapsedTime = clock.restart();
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            game.Update(TIME_PER_FRAME.asSeconds());
        }
        game.CaptureInput();
        game.Update(TIME_PER_FRAME.asSeconds());
        game.LateUpdate();
        game.Draw();
        //game.calculateDeltaTime();
    }
}