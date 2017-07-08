#include "Game.hpp"

void Game::startGameLoop()
{
	// do first update/draw before the loop is starting
	handleWindowEvents();

	m_time.total = m_clock.getElapsedTime().asSeconds();
	m_time.elapsed = 0.0f;
	update(m_time);
	draw();

	while (m_window.isOpen())
	{
		handleWindowEvents();
		handleUpdateDraw();
	}
}

void Game::handleWindowEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_handleWindowClose &&
			m_event.type == sf::Event::EventType::Closed)
			//|| (m_event.type == sf::Event::KeyReleased && m_event.key.code == sf::Keyboard::Key::Escape)))
		{
			if (onStop())
			{
				m_window.close();
			}
		}
	}
}

void Game::handleUpdateDraw()
{
	float elapsedFrameTime = m_clock.restart().asSeconds();
	m_clock.restart();

	if (m_fixedTimeStep)
	{
		bool executeDraw = false;

		m_timeSinceLastUpdate += elapsedFrameTime;
		while (m_timeSinceLastUpdate >= m_timePerFrame)
		{
			m_time.elapsed = m_timePerFrame;
			m_time.total += m_timePerFrame;

			update(m_time);
			executeDraw = true;

			m_timeSinceLastUpdate -= m_timePerFrame;
		}

		if (executeDraw)
			draw();
	}
	else
	{
		m_time.elapsed = elapsedFrameTime;
		m_time.total += m_time.elapsed;

		update(m_time);
		draw();
	}
}

void Game::update(GameTime const & time)
{
	onUpdate(m_time);
}

void Game::draw()
{
	m_window.clear(m_backgroundColor);
	onDraw();
	m_window.display();
}

Game::Game()
	: Game("SFML Window", 800, 600)
{
}

Game::Game(std::string windowTitle, unsigned int windowWidth, unsigned int windowHeight)
	:
	m_fixedTimeStep(true),
	m_frameRate(60),
	m_timePerFrame(1.0f / 60),
	m_timeSinceLastUpdate(0.0f),
	m_handleWindowClose(false),
	m_backgroundColor(0, 0, 0, 255)
{
	m_window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle,
		sf::Style::Close | sf::Style::Titlebar);
}

Game::~Game()
{
}

void Game::onUpdate(GameTime const time)
{
}

void Game::onDraw()
{
}

bool Game::onStop()
{
	return true;
}

int Game::Start()
{
	startGameLoop();

	return 0;
}

void Game::Stop()
{
	m_window.close();
}

sf::Window & Game::getWindow()
{
	return m_window;
}

void Game::setFixedTimeStep(bool fixedTimeStep)
{
	m_fixedTimeStep = fixedTimeStep;
}

bool Game::isFixedTimeStep()
{
	return m_fixedTimeStep;
}

void Game::setHandleWindowClose(bool handleWindowClose)
{
	m_handleWindowClose = handleWindowClose;
}

bool Game::isWindowCloseHandled()
{
	return m_handleWindowClose;
}

void Game::setBackgroundColor(sf::Color color)
{
	m_backgroundColor = color;
}

sf::Color Game::getBackgroundColor()
{
	return m_backgroundColor;
}

void Game::setFrameRate(unsigned int framesPerSecond)
{
	m_frameRate = framesPerSecond;
	m_timePerFrame = 1.0f / framesPerSecond;
}

unsigned int Game::getFrameRate()
{
	return m_frameRate;
}
