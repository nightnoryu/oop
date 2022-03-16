#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return std::abs(m_vertex1.GetY() * (m_vertex2.GetY() - m_vertex3.GetY()) + m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY()) + m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY()));
}

double CTriangle::GetPerimeter() const
{
	auto distance12 = CPoint::Distance(m_vertex1, m_vertex2);
	auto distance23 = CPoint::Distance(m_vertex2, m_vertex3);
	auto distance31 = CPoint::Distance(m_vertex3, m_vertex1);

	return distance12 + distance23 + distance31;
}

std::string CTriangle::ToString() const
{
	return "Triangle";
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
