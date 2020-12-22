#include "Framework.h"
#include "Definintions.h"

int main()
{
    float playerRadius = 20.0f;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Asteroids!");

    sf::Texture bg, playerimg;
    bg.loadFromFile("images/Background.png");
    playerimg.loadFromFile("images/player.png");
    sf::Sprite background(bg);

    sf::CircleShape player(playerRadius);
    player.setTexture(&playerimg);
    player.setOrigin(playerRadius, playerRadius);
    player.setPosition(WIDTH / 2, HEIGHT / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }

    return 0;
}
