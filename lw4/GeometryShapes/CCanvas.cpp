#include "CCanvas.h"
#include "common.h"

void CCanvas::DisplayResult() const
{
	sf::RenderWindow window(sf::RenderWindow(sf::VideoMode(1600, 1000), "My window"));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(BACKGROUND_COLOR);
		for (auto shape : m_shapes)
		{
			window.draw(*shape);
		}
		window.display();
	}
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	auto lineLengh = [](CPoint start, CPoint end)
	{
		double differenceInX = start.x - end.x;
		double differenceInY = start.y - end.y;

		return sqrt(differenceInX * differenceInX + differenceInY * differenceInY);
	};

	double lineToDrawLength = lineLengh(from, to);
	sf::RectangleShape rectangle(sf::Vector2f(lineToDrawLength, 3));
	rectangle.setFillColor(sf::Color(lineColor));

	sf::Vector2f moveToStartVector(from.x, from.y);
	rectangle.setPosition(moveToStartVector);

	CPoint movedEndPoint(rectangle.getPoint(1).x + moveToStartVector.x, rectangle.getPoint(1).y + moveToStartVector.y);
	double fromCurrentToNeededEndDistance = lineLengh(movedEndPoint, to);
	double cornerToRotate = asin(fromCurrentToNeededEndDistance / (2 * lineToDrawLength)) * 2;
	if (to.y < from.y)
	{
		cornerToRotate *= -1;
	}
	rectangle.setRotation(RadToDegree(cornerToRotate));
	m_shapes.push_back(new sf::RectangleShape(rectangle));
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor, uint32_t outlineColor)
{
	sf::ConvexShape polygon;

	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); i++)
	{
		CPoint point = points[i];
		polygon.setPoint(i, sf::Vector2f(point.x, point.y));
	}
	polygon.setFillColor(sf::Color(fillColor));
	polygon.setOutlineThickness(4);
	polygon.setOutlineColor(sf::Color(outlineColor));
	m_shapes.push_back(new sf::ConvexShape(polygon));
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
{
	sf::CircleShape circle(radius);
	double offsetFromCenter = radius;
	circle.setPosition(center.x - offsetFromCenter, center.y - offsetFromCenter);
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineThickness(4);
	circle.setOutlineColor(sf::Color(outlineColor));
	m_shapes.push_back(new sf::CircleShape(circle));
}