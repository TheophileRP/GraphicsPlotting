#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Graph2D.h"

using namespace sf;

double SinusDeMesCouilles(double x);

int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");

    Graph2D sinx;

    sinx.setFunction(&SinusDeMesCouilles);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(sinx);

        window.display();
    }

    return 0;
}

double SinusDeMesCouilles(double x) {
    return sin(x);
}