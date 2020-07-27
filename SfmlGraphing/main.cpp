#include <SFML/Graphics.hpp>
#include <cmath>
#include <future>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Graphing App");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    float theta = 0;
    while (window.isOpen())
    {
        sf::Event event;
        sf::ConvexShape polygon;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    theta += M_PI/20;
                }   
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    polygon.move(sf::Vector2f(30, 30));
                }   
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    polygon.move(sf::Vector2f(-30, -30));
                }   
            }


            const int count = 16;

            polygon.setPointCount(count);
            for(float i = 0, j=0; i < 2*M_PI; i+= 2*M_PI/count, j++)
            {
                int dx = 100*sin(i) * cos(theta) - 100*cos(i) * sin(theta + M_PI);
                int dy = 100*sin(i) * cos(theta) + 100*cos(i) * sin(theta + M_PI);


                polygon.setPoint((int)j, sf::Vector2f(dx, dy));
            }

            polygon.setOutlineColor(sf::Color::Red);
            polygon.setOutlineThickness(5);
            polygon.setPosition(150, 150);
            window.draw(polygon);
            window.display();
            window.clear();
        }

        window.clear();
    }

    return 0;
}
