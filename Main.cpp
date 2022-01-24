#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Graph2D.h"

using namespace sf;

double SinusDeMesCouilles(double x);

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;

    RenderWindow window(VideoMode(1000, 800), "SFML works!", Style::Default, settings);

    Graph2D sinx;
    sinx.setPosition(Vector2f(50., 50.));
    sinx.setSize(Vector2f(900., 700.));


    sinx.setFunction(&SinusDeMesCouilles);

    window.draw(sinx);

    window.display();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

 /*       window.clear();*/


    }

    return 0;
}

double SinusDeMesCouilles(double x) {
    return sin(x);
}