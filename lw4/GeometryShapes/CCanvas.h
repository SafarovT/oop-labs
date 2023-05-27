#pragma once
#include "ICanvas.h"
#include "ICanvasDrawable.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	void DisplayResult() const;
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor, uint32_t outlineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor) override;
private:
	const sf::Color BACKGROUND_COLOR = sf::Color::White;
	std::vector<sf::Shape*> m_shapes;
};