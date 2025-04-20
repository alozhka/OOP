#include <SFML/Graphics.hpp>

struct WindowSettings
{
	std::string title = "Shapes";
	sf::Vector2u size = { 800, 800 };
};

static sf::RenderWindow RenderWindow()
{
	sf::ContextSettings settings;
	const WindowSettings windowSettings;
	settings.antiAliasingLevel = 16;

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
	sf::RenderWindow window = RenderWindow();

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
	}
	return 0;
}