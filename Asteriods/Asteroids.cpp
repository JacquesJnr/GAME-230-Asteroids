#include "Framework.h"
#include "Definintions.h"

enum states{Menu, Play, Reset, Exit};

float DEGTORAD = 0.017453f;

class Player {
    
public:
    bool thrust;
    float angle{ 0 }, radius, xPos, yPos, speed{ 0 }, moveX, moveY;
    sf::CircleShape shape;
    sf::Texture texture;

    Player(float X, float Y, float rad) {
        xPos = X;
        yPos = Y;
        shape.setPosition({X, Y});
        shape.setRadius(rad);
        shape.setOrigin(rad, rad);
    }

    void Update() {

        if (Keyboard::isKeyPressed(Keyboard::Right))
            angle += 0.5;
        if (Keyboard::isKeyPressed(Keyboard::Left))
            angle -= 0.5;
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            speed = 2.f;
        }
        else
        {
            speed *= 0.99;
            angle *= 0.99;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            speed = -2.f;
        }
        else
        {
            speed *= 0.99;
            angle *= 0.99;
        }



        if (xPos > HEIGHT) xPos = 0; if (xPos < 0) xPos = HEIGHT;
        if (yPos > WIDTH) yPos = 0; if (yPos < 0) yPos = WIDTH;

        shape.setPosition(yPos += (angle / 4 ), xPos -= speed);

        if (angle >= 360)
            angle = 0;
        if (angle <= -360)
            angle = 0;        
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
    sf::Text angleValue, angle, speed, positionX, positionY, X, Y;
    
    std::list<Text> allTexts;

    angleValue.setPosition(110, 60);
    angleValue.setFont(font);
    angleValue.setCharacterSize(16);

    angle.setPosition(50, 60);
    angle.setFont(font);
    angle.setCharacterSize(16);
    angle.setString("Angle: ");
    allTexts.push_back(angle);

    speed.setPosition(50, 80);
    speed.setFont(font);
    speed.setCharacterSize(16);
    speed.setString("Speed: ");
    allTexts.push_back(speed);

    positionX.setPosition(50, 100);
    positionX.setFont(font);
    positionX.setCharacterSize(16);
    positionX.setString("X: ");
    allTexts.push_back(positionX);

    positionY.setPosition(50, 120);
    positionY.setFont(font);
    positionY.setCharacterSize(16);
    positionY.setString("Y: ");
    allTexts.push_back(positionY);

    X.setPosition(80, 100);
    X.setFont(font);
    X.setCharacterSize(16);

    Y.setPosition(80, 120);
    Y.setFont(font);
    Y.setCharacterSize(16);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        angleValue.setString(std::to_string(player.angle));
        X.setString(std::to_string(player.shape.getPosition().x));
        Y.setString(std::to_string(player.shape.getPosition().y));

        window.clear();
        window.draw(background);
        for (auto i : allTexts) window.draw(i); // Draws all the text in one convenient draw call
        window.draw(angleValue);
        window.draw(X);
        window.draw(Y);
        player.Update();
        player.shape.setRotation(player.angle);
        window.draw(player.shape);
        window.display();
    }

    return 0;
}
