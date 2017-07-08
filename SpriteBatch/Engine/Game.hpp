#pragma once

#include <SFML\Graphics.hpp>

struct GameTime
{
	float total = 0.0f;
	float elapsed = 0.0f;
};

class Game
{

private:

	// variables

	GameTime m_time;

	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Clock m_clock;

	unsigned int m_frameRate;
	float m_timePerFrame;
	float m_timeSinceLastUpdate;

	bool m_fixedTimeStep;
	bool m_handleWindowClose;

	sf::Color m_backgroundColor;

	// functions

	void startGameLoop();
	void handleWindowEvents();
	void handleUpdateDraw();

	void update(GameTime const & time);
	void draw();

protected:

	// Called when an update is required.
	virtual void onUpdate(GameTime const time);

	// Called when a refresh is required.
	virtual void onDraw();

	// Called when the game should stop.
	// If false is returned, the stop process is canceled.
	virtual bool onStop();

public:

	Game();
	Game(std::string windowTitle, unsigned int windowWidth, unsigned int windowHeight);

	~Game();

	int Start();
	void Stop();

	sf::Window & getWindow();

	void setFixedTimeStep(bool fixedTimeStep);
	bool isFixedTimeStep();

	void setHandleWindowClose(bool handleWindowClose);
	bool isWindowCloseHandled();

	void setBackgroundColor(sf::Color color);
	sf::Color getBackgroundColor();

	void setFrameRate(unsigned int framesPerSecond);
	unsigned int getFrameRate();

};
