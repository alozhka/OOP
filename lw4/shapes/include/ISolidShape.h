#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	[[nodiscard]] virtual u_int32_t GetFilledColor() const = 0;

	~ISolidShape() override = default;
};