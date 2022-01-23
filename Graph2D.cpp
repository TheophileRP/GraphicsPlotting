#include "Graph2D.h"

#include <iostream>

Graph2D::Graph2D()
{
	m_xMin = 0;
	m_xMax = 1;
	m_yMin = 1;
	m_yMax = -1;
}

Graph2D::~Graph2D()
{
}

void Graph2D::setFunction(std::function<double(double)> fct)
{
	m_fct = fct;
}

void Graph2D::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(1., 5.));
	rect.setFillColor(sf::Color::Red);

	for (int i = 0; i < 100; i++) {
		rect.setPosition(i, (m_fct(i) * 10) + 50);

		target.draw(rect);
	}
}

sf::Vector2f Graph2D::parametricToPixel(sf::Vector2f x)
{
	return sf::Vector2f();
}
