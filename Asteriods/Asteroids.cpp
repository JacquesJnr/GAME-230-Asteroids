#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Definintions.h"

using namespace sf;


class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;

   Entity()
   {
     life = 1;
   }

   void settings(int X,int Y,float Angle = 0,int radius = 1)
   {
     x = X; y = Y;
     angle = Angle;
     R = radius;
   }

   virtual void update() {};

   void draw(RenderWindow& app)
   {
     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     app.draw(circle);
   }

   virtual ~Entity() {};
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