#pragma once

#include <vector>
#include <stdexcept>
#include <functional>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Vertex.hpp>

enum class SpriteBatchSortMode
{
	Deffered,
	BackToFront,
	FrontToBack
};

class SpriteBatch
{

private:

	struct SpriteBatchDrawItem
	{
		sf::Texture * texture;
		sf::Vertex vertices[4];
		float layerDepth;

		bool operator<(SpriteBatchDrawItem const & lhs) const
		{
			return layerDepth < lhs.layerDepth;
		}

		bool operator>(SpriteBatchDrawItem const & lhs) const
		{
			return layerDepth > lhs.layerDepth;
		}

	};

	bool m_beginCalled;
	SpriteBatchSortMode m_sortMode;
	std::vector<SpriteBatchDrawItem> m_drawBuffer;

	void render(sf::RenderTarget & target);
	void drawInternal(sf::Texture & texture, float x, float y, int srcX, int srcY, int srcWidth, int srcHeight, float layerDepth);

public:

	SpriteBatch();

	void begin(SpriteBatchSortMode sortMode = SpriteBatchSortMode::Deffered);

	void draw(sf::Texture & texture, sf::Vector2f pos, float layerDepth = 0.0f);
	void draw(sf::Texture & texture, sf::Vector2f pos, sf::IntRect source, float layerDepth = 0.0f);

	void end(sf::RenderTarget & target);

};
