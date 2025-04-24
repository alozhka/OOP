#pragma once
#include "ICanvasDrawable.h"

#include <string>

// общий ToString в какой-то из классов
class IShape : public ICanvasDrawable
{
public:
	[[nodiscard]] virtual double GetArea() const = 0;
	[[nodiscard]] virtual double GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;

	~IShape() override = default;
};