#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Definintions.h"

using namespace sf;


class Entity
{
   public:
   float xPos,yPos,deltaX,deltaY,radius,angle;
   bool life;
   std::string name;

   Entity()
   {
     life = 1;
   }

   void settings(int X,int Y,float Angle = 0,int radius = 1)
   {
     xPos = X; yPos = Y;
     angle = Angle;
     radius = radius;
   }

   virtual void update() {};

   void draw(RenderWindow& app)
   {
     CircleShape circle(radius);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(xPos,yPos);
     circle.setOrigin(radius,radius);
     app.draw(circle);
   }

   virtual ~Entity() {};
};

class Asteroid : public Entity
{
public:
    Asteroid()
    {
        deltaX = rand() % 8 - 4;
        deltaY = rand() % 8 - 4;
        name = "asteroid";
    }

    void Update()
    {
        xPos += deltaX;
        yPos += deltaY;

        if (xPos > WIDTH) xPos = 0;  if (xPos < 0) xPos = WIDTH;
        if (yPos > HEIGHT) yPos = 0;  if (yPos < 0) yPos = HEIGHT;
    }
};

class Player : public Entity
{
public:
    bool thrust;

    Player()
    {
        name = "player";
    }

    void Update()
    {
        if (thrust)
        {
            deltaX += cos(angle * degsToRad) * 0.2f;
            deltaY += sin(angle * degsToRad) * 0.2f;
        }
        else
        {
            deltaX *= 0.99;
            deltaY *= 0.99;
        }

        int maxSpeed = 15;
        float speed = sqrt(deltaX * deltaX + deltaY * deltaY);
        if (speed > maxSpeed)
        {
            deltaX *= maxSpeed / speed;
            deltaY *= maxSpeed / speed;
        }

        xPos += deltaX;
        yPos += deltaY;

        if (xPos > WIDTH) xPos = 0; if (xPos < 0) xPos = WIDTH;
        if (yPos > HEIGHT) yPos = 0; if (yPos < 0) yPos = HEIGHT;
    }

};

int main() {

    srand(time(0));

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML Asteroids!");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

}