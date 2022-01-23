#pragma once

#include <functional> // for function pointer
#include <SFML/Graphics.hpp>

class Graph2D : public sf::Drawable, public sf::Transformable
{
public:
	Graph2D();
	~Graph2D();
	void setFunction(std::function<double(double)> fct);
	
	//void set_xMin(double xMin);
	//void set_xMax(double xMax);
	//void set_yMin(double yMin);
	//void set_yMax(double yMax);
	//double get_xMin();
	//double get_xMax();
	//double get_yMin();
	//double get_yMax();
private:
	double m_xMin;
	double m_xMax;
	double m_yMin;
	double m_yMax;

	double m_xSizePixel;
	double m_ySizePixel;
	double m_thickness;
	
	std::function<double(double)> m_fct;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f parametricToPixel(sf::Vector2f x);
};

