#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual u_int32_t GetFilledColor() = 0;

	~ISolidShape() override = default;
};