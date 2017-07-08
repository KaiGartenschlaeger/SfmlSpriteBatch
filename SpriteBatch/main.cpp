#include <SFML\Graphics.hpp>
#include "SpriteBatch.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SpriteBatch Test",
		sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);


	sf::Vector2f viewSize = window.getView().getSize();


	SpriteBatch batch;

	
	sf::Texture grassTexture;
	grassTexture.loadFromFile("Content/grass.png");

	sf::Texture treeTexture;
	treeTexture.loadFromFile("Content/treetop.png");

	
	sf::Font fontFps;
	fontFps.loadFromFile("Content/Miramo.ttf");

	
	sf::Text fpsText;
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setOutlineThickness(1);
	fpsText.setCharacterSize(18);
	fpsText.setPosition(viewSize.x - 100, 10);
	fpsText.setFont(fontFps);

	unsigned int fpsCounter = 0;
	unsigned int fpsCounterTmp = 0;
	float fpsCounterResetTime = 1.0f;
	float fpsCounterTime = 0.0f;

	sf::Clock clock;
	sf::Event event;
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();

		fpsCounterTime += elapsedTime.asSeconds();
		if (fpsCounterTime >= fpsCounterResetTime)
		{
			fpsCounterTime -= fpsCounterResetTime;
			fpsCounter = fpsCounterTmp;
			fpsCounterTmp = 0;
		}
		else
		{
			fpsCounterTmp++;
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		batch.begin(SpriteBatchSortMode::BackToFront);

		for (size_t x = 0; x < viewSize.x / 32; x++)
		{
			for (size_t y = 0; y < viewSize.y / 32; y++)
			{
				batch.draw(grassTexture, sf::Vector2f(x * 32, y * 32), sf::IntRect(64, 160, 32, 32), 0.0f);
			}
		}

		batch.draw(treeTexture, sf::Vector2f(150, 150), sf::IntRect(0, 96, 96, 96), 0.2f);
		batch.draw(treeTexture, sf::Vector2f(110, 110), sf::IntRect(0, 96, 96, 96), 0.1f);

		batch.end(window);

		
		fpsText.setString(std::to_string(fpsCounter));

		window.draw(fpsText);
		window.display();
	}

	return EXIT_SUCCESS;
}
