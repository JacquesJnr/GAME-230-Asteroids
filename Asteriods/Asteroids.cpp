#include "Framework.h"
#include "Definintions.h"

enum states{Menu, Play, Reset, Exit};

float DEGTORAD = 0.017453f;

class Player {
    
public:
    bool thrust;
    float angle {0}, radius, xPos, yPos, deltaX, deltaY;
    sf::CircleShape shape;
    sf::Texture texture;

    Player(float X, float Y, float rad) {
        shape.setPosition({ X, Y});
        shape.setRadius(rad);
        shape.setOrigin(rad, rad);
    }

    void Update() {

        shape.setRotation(angle);
        if (angle >= 360) {
            angle = 0;
        }

        if (angle <= -360) {
            angle = 0;
        }
    }
};

int main()
{    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Asteroids!");

    sf::Texture bg, playerimg;
    bg.loadFromFile("images/Background.png");
    playerimg.loadFromFile("images/player.png");
    sf::Sprite background(bg);

    Player player(WIDTH / 2, HEIGHT / 2, 20.f);
    player.shape.setTexture(&playerimg);

    sf::Font font;
    font.loadFromFile("fonts/SourceCodePro.ttf");
    sf::Text someText;
    someText.setPosition(100, 100);
    someText.setFont(font);
    someText.setCharacterSize(16);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) player.angle += 2;
        if (Keyboard::isKeyPressed(Keyboard::Left))  player.angle -= 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) player.thrust = true;
        else player.thrust = false;

        someText.setString(std::to_string(player.angle));

        window.clear();
        window.draw(background);
        window.draw(someText);
        player.Update();
        window.draw(player.shape);
        window.display();
    }

    return 0;
}
