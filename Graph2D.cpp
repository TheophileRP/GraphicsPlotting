#include "Graph2D.h"

#include <iostream>

#define M_PIOVER2 1.57079632679

Graph2D::Graph2D()
{
	m_xMin = 0;
	m_xMax = 6.28;
	m_yMin = 1;
	m_yMax = -1;
	m_position = sf::Vector2f(0., 0.);
	m_size = sf::Vector2f(100., 100.);
	m_thickness = 20;
}

Graph2D::~Graph2D()
{
}

void Graph2D::setFunction(std::function<double(double)> fct)
{
	m_fct = fct;
}

void Graph2D::setXMin(double xMin)
{
	m_xMin = xMin;
}

void Graph2D::setXMax(double xMax)
{
	m_xMax = xMax;
}

void Graph2D::setYMin(double yMin)
{
	m_yMin = yMin;
}

void Graph2D::setYMax(double yMax)
{
	m_yMax = yMax;
}

void Graph2D::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Graph2D::setSize(sf::Vector2f size)
{
	m_size = size;
}

double Graph2D::getXMin()
{
	return m_xMin;
}

double Graph2D::getXMax()
{
	return m_xMax;
}

double Graph2D::getYMin()
{
	return m_yMin;
}

double Graph2D::getYMax()
{
	return m_yMax;
}

sf::Vector2f Graph2D::getPosition()
{
	return m_position;
}

sf::Vector2f Graph2D::getSize()
{
	return m_size;
}

void Graph2D::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(1., 1.));
	rect.setFillColor(sf::Color::White);

	double x_para = 0.;
	double y_pixel = 0.;
	double a = m_thickness / 2.;
	double delta = 0;
	double x_paraPlus1 = 0.;
	double y_pixelPlus1 = 0.;
	double x_n, y_n = 0.;

	sf::VertexArray normal(sf::Lines, 2); //Store two points to draw the normals
	sf::VertexArray anti_normal(sf::Lines, 2); //Store two points to draw the normals

	for (int i = 0; i <= (m_size.x); i++) {

		x_para = (i * (m_xMax - m_xMin) / m_size.x);
		/*std::cout << x_para << std::endl;*/
		y_pixel = (((m_fct(x_para) - m_yMin) * m_size.y) / (m_yMax - m_yMin));
		//std::cout << x_para << " " << m_fct(x_para) << std::endl;

		rect.setPosition(sf::Vector2f((i + m_position.x), (y_pixel + m_position.y)));

		target.draw(rect);

		//Get the deltaY over deltaX
		x_paraPlus1 = ((i + 1) * (m_xMax - m_xMin) / m_size.x);
		y_pixelPlus1 = (((m_fct(x_paraPlus1) - m_yMin) * m_size.y) / (m_yMax - m_yMin));
		delta = (y_pixelPlus1 - y_pixel);

		x_n = a * (cos(atan(delta) + M_PIOVER2));
		y_n = a * (sin(atan(delta) + M_PIOVER2));

		// Draw the normals
		normal[0].position = sf::Vector2f(i + m_position.x, y_pixel + m_position.y);
		normal[1].position = sf::Vector2f(i + m_position.x + x_n, y_pixel + m_position.y + y_n);
		normal[0].color = sf::Color::Red;
		normal[1].color = sf::Color::Red;

		target.draw(normal);

		x_n = a * (cos(atan(delta) - M_PIOVER2));
		y_n = a * (sin(atan(delta) - M_PIOVER2));

		// Draw the normals
		anti_normal[0].position = sf::Vector2f(i + m_position.x, y_pixel + m_position.y);
		anti_normal[1].position = sf::Vector2f(i + m_position.x + x_n, y_pixel + m_position.y + y_n);
		anti_normal[0].color = sf::Color::Green;
		anti_normal[1].color = sf::Color::Green;

		target.draw(anti_normal);

	}
}

sf::Vector2f Graph2D::parametricToPixel(sf::Vector2f x)
{
	sf::Vector2f result;
	result.x = m_position.x + (x.x * m_size.x / (m_xMax - m_xMin));
	result.y = m_position.y + (x.y * m_size.y / (m_yMax - m_yMin));
	return result;
}

sf::Vector2f Graph2D::pixelToParametric(sf::Vector2f x)
{
	sf::Vector2f result;
	result.x = (x.x * (m_xMax - m_xMin) / m_size.x) - m_position.x;
	result.y = (x.y * (m_yMax - m_yMin) / m_size.y) - m_position.y;
	return result;
}
