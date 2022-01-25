#include "Graph2D.h"

#include <iostream>

#define M_PIOVER2 1.57079632679
#define H 1.

Graph2D::Graph2D()
{
	m_xMin = 0.;
	m_xMax = 2.;
	m_yMin = -1.;
	m_yMax = 1.;
	m_position = sf::Vector2f(50., 50.);
	m_size = sf::Vector2f(900., 700.);
	m_thickness = 100;
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

	double y_pixel = 0.;
	double a = m_thickness / 2.;
	double localDerivative = 0;
	double secondDerivative = 0;
	double x_n, y_n = 0.;

	double radius = 0;

	int interval = 15;
	int j = 0;

	sf::VertexArray normal(sf::Lines, 2); //Store two points to draw the normals & anti-normals
	sf::CircleShape normalCircle(a, 50);
	normalCircle.setFillColor(sf::Color::Transparent);
	normalCircle.setOutlineThickness(1.);
	normalCircle.setOutlineColor(sf::Color::White);
	normalCircle.setOrigin(a, a);

	for (int i = 0; i <= (m_size.x); i++) {

		// Get the y value (in pixel) for current pixel
		y_pixel = pixelFunction(i);

		//Get the local derivative
		localDerivative = derivative(i, H);

		rect.setPosition(i + m_position.x, y_pixel);
		
		// draw only if it's in the frame
		if(rect.getPosition().y >= m_position.y && rect.getPosition().y < (m_position.y + m_size.y))
		target.draw(rect);

		// Process the second derivative
		secondDerivative = (derivative(i + H, H) - localDerivative) / H;

		// Process the radius of the curvature circle
		radius = pow((1 + pow(localDerivative, 2)), (3./2.)) / secondDerivative;
		std::cout << radius << std::endl;

		if (j == interval) {

			// Process the x & y coordinates of the normal vector
			x_n = a * (cos(atan(localDerivative) + M_PIOVER2));
			y_n = a * (sin(atan(localDerivative) + M_PIOVER2));

			// Draw the normals
			normal[0].position = sf::Vector2f(i + m_position.x, y_pixel);
			normal[1].position = sf::Vector2f(i + m_position.x + x_n, y_pixel + y_n);
			normal[0].color = sf::Color::Red;
			normal[1].color = sf::Color::Red;

			// Draw the normal circle
			normalCircle.setPosition(i + m_position.x + x_n, y_pixel + y_n);

			if ((radius > 0. && radius > a) || radius < 0.) {
				target.draw(normalCircle);
				target.draw(normal);
			}

			// Process the x & y coordinates of the anti-normal vector
			x_n = a * (cos(atan(localDerivative) - M_PIOVER2));
			y_n = a * (sin(atan(localDerivative) - M_PIOVER2));

			// Draw the normals
			normal[0].position = sf::Vector2f(i + m_position.x, y_pixel);
			normal[1].position = sf::Vector2f(i + m_position.x + x_n, y_pixel + y_n);
			normal[0].color = sf::Color::Green;
			normal[1].color = sf::Color::Green;

			//if(radius < 0. && radius > a)
			target.draw(normal);
			
			j = 0;
		}
		else{
			j++;
		}
	}
}

double Graph2D::derivative(double x, double h) const
{
	//std::cout << pixelFunction(x) << " " << pixelFunction(x + h) << std::endl;
	return (pixelFunction(x + h) - pixelFunction(x)) / h;
	//return (m_fct(x + h) - m_fct(x)) / h;
}

double Graph2D::boundsFunction(double x) const
{
	// bounds function = 1 / Y_size * (f(x * X_size + X_offset) + Y_offset)
	return (1. / (m_yMax - m_yMin) * (m_fct(x * (m_xMax - m_xMin) + m_xMin) - m_yMin));
}

double Graph2D::pixelFunction(double x_pixel) const
{
	// pixel function = (Y_size_pixel / Y_size_para) * f(x_pixel * X_size_para / X_size_pixel + X_offset_pixel) + Y_offset_pixel
	return (m_size.y * (1. - (boundsFunction(x_pixel / m_size.x))) + m_position.y);
}
