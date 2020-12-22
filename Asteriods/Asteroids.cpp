#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Definintions.h"

using namespace sf;


class GameObject
{
   public:
   float xPos,yPos,deltaX,deltaY,radius,angle;
   bool life;
   std::string name;

   GameObject()
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

   virtual ~GameObject() {};
};

class Asteroid : public GameObject
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

class Player : public GameObject
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

bool isCollide(GameObject* a, GameObject* b)
{
    return (b->xPos - a->xPos) * (b->xPos - a->xPos) +
        (b->yPos - a->yPos) * (b->yPos - a->yPos) <
        (a->radius + b->radius) * (a->radius + b->radius);
}


class Bullet : public GameObject
{
public:
    Bullet()
    {
        name = "bullet";
    }

    void  update()
    {
        deltaX = cos(angle * degsToRad) * 6;
        deltaY = sin(angle * degsToRad) * 6;
        // angle+=rand()%7-3;  /*try this*/
        xPos += deltaX;
        yPos += deltaY;

        if (xPos > WIDTH || xPos<0 || yPos>HEIGHT || yPos < 0) life = 0;
    }

};

int main() {

    srand(time(0));

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML Asteroids!");
    window.setFramerateLimit(60);

    std::list<GameObject*> entities;

    for (int i = 0; i < 15; i++)
    {
        Asteroid* a = new Asteroid();
        a->settings(rand() % WIDTH, rand() % HEIGHT, rand() % 360, 25);
    }

    Player* p = new Player();
    p->settings(200, 200, 0, 20);
    entities.push_back(p);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space)
                {
                    Bullet* b = new Bullet();
                    b->settings(p->xPos, p->yPos, p->angle, 10);
                    entities.push_back(b);
                }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust = true;
        else p->thrust = false;


        for (auto a : entities)
            for (auto b : entities)
            {
                if (a->name == "asteroid" && b->name == "bullet")
                    if (isCollide(a, b))
                    {
                        a->life = false;
                        b->life = false;

                        GameObject* e = new GameObject();
                        e->settings(a->xPos, a->yPos);
                        e->name = "explosion";
                        entities.push_back(e);


                        for (int i = 0; i < 2; i++)
                        {
                            if (a->radius == 15) continue;
                            GameObject* e = new Asteroid();
                            e->settings(a->xPos, a->yPos, rand() % 360, 15);
                            entities.push_back(e);
                        }

                    }

                if (a->name == "player" && b->name == "asteroid")
                    if (isCollide(a, b))
                    {
                        b->life = false;

                        GameObject* e = new GameObject();
                        e->settings(sExplosion_ship, a->xPos, a->yPos);
                        e->name = "explosion";
                        entities.push_back(e);

                        p->settings( WIDTH / 2, HEIGHT / 2, 0, 20);
                        p->deltaX = 0; p->deltaY = 0;
                    }
            }

        for (auto e : entities)
            if (e->name == "explosion")
                e->life = 0;

        if (rand() % 150 == 0)
        {
            Asteroid* a = new Asteroid();
            a->settings(0, rand() % WIDTH, rand() % 360, 25);
            entities.push_back(a);
        }

        for (auto i = entities.begin(); i != entities.end();)
        {
            GameObject* e = *i;

            e->update();

            if (e->life == false) { i = entities.erase(i); delete e; }
            else i++;
        }

        //////draw//////
        window.draw(background);
        for (auto i : entities) i->draw(window);
        window.display();
    }
}