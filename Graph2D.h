#pragma once

#include <functional> // for function pointer
#include <SFML/Graphics.hpp>

class Graph2D : public sf::Drawable, public sf::Transformable
{
public:
	Graph2D();
	~Graph2D();
	void setFunction(std::function<double(double)> fct);
	
	void setXMin(double xMin);
	void setXMax(double xMax);
	void setYMin(double yMin);
	void setYMax(double yMax);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);

	double getXMin();
	double getXMax();
	double getYMin();
	double getYMax();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
private:

	double m_thickness;
	double m_xMin;
	double m_xMax;
	double m_yMin;
	double m_yMax;

	sf::Vector2f m_position;
	sf::Vector2f m_size;
	
	std::function<double(double)> m_fct;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	double derivative(double x, double h) const;
	double boundsFunction(double x) const;
	double pixelFunction(double x_pixel) const;
};

