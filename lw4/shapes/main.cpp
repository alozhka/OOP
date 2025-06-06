#include "include/CCanvas.h"
#include "include/CShapesController.h"

#include <SFML/Graphics.hpp>
#include <iostream>

struct WindowSettings
{
	std::string title = "Shapes";
	sf::Vector2u size = { 800, 800 };
};

static sf::RenderWindow CreateWindow()
{
	sf::ContextSettings settings;
	const WindowSettings windowSettings;
	settings.antiAliasingLevel = 8;

	return sf::RenderWindow{
		sf::VideoMode(
			windowSettings.size,
			1),
		windowSettings.title,
		sf::Style::Default,
		sf::State::Windowed,
		settings
	};
}

int main()
{
	sf::RenderWindow window = CreateWindow();
	CShapesController shapesController(std::cin, std::cout);
	bool inputFinished = false;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		// вынести логику считывания отдельно
		if (!inputFinished)
		{
			shapesController.ProcessShape();
			if (std::cin.eof())
			{
				inputFinished = true;
				shapesController.PrintResults();
			}
		}
		// до сюда

		window.clear(sf::Color::Black);
		shapesController.DrawShapes(window);
		window.display();
	}

	return EXIT_SUCCESS;
}