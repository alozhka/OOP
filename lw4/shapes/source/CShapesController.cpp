#include "../include/CShapesController.h"

CShapesController::CShapesController(std::istream& input, std::ostream& output)
	: m_action_map{ { { "rectangle", std::bind_front(&CShapesController::AddRectangle, this) } } }
	, m_input(input)
	, m_output(output)
{
}

void CShapesController::AddRectangle(std::string_view args)
{
}
