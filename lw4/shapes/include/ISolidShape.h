#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	[[nodiscard]] virtual uint32_t GetInlineColor() const = 0;

	~ISolidShape() override = default;
};