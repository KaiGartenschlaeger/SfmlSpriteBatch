#include "SpriteBatch.hpp"

void SpriteBatch::render(sf::RenderTarget & target)
{
	for (SpriteBatchDrawItem & info : m_drawBuffer)
	{
		sf::RenderStates states;
		states.texture = info.texture;

		target.draw(info.vertices, 4, sf::Quads, states);
	}
}

SpriteBatch::SpriteBatch()
	:
	m_beginCalled(false)
{
	m_drawBuffer.reserve(100);
}

void SpriteBatch::begin(SpriteBatchSortMode sortMode)
{
	if (m_beginCalled)
		throw new std::runtime_error("begin has been already called");

	m_beginCalled = true;

	m_sortMode = sortMode;
	m_drawBuffer.clear();
}

void SpriteBatch::drawInternal(sf::Texture & texture, float posX, float posY, int srcX, int srcY, int srcWidth, int srcHeight, float layerDepth)
{
	if (!m_beginCalled)
		throw new std::runtime_error("begin must be called first");

	SpriteBatchDrawItem item;
	item.texture = &texture;

	sf::Vector2u textureSize = texture.getSize();

	if (srcWidth > 0 && srcHeight > 0)
	{
		item.vertices[0].position.x = posX;
		item.vertices[0].position.y = posY;
		item.vertices[0].texCoords.x = srcX;
		item.vertices[0].texCoords.y = srcY;

		item.vertices[1].position.x = posX + srcWidth;
		item.vertices[1].position.y = posY;
		item.vertices[1].texCoords.x = srcX + srcWidth;
		item.vertices[1].texCoords.y = srcY;

		item.vertices[2].position.x = posX + srcWidth;
		item.vertices[2].position.y = posY + srcHeight;
		item.vertices[2].texCoords.x = srcX + srcWidth;
		item.vertices[2].texCoords.y = srcY + srcHeight;

		item.vertices[3].position.x = posX;
		item.vertices[3].position.y = posY + srcHeight;
		item.vertices[3].texCoords.x = srcX;
		item.vertices[3].texCoords.y = srcY + srcHeight;
	}
	else
	{
		item.vertices[0].position.x = posX;
		item.vertices[0].position.y = posY;
		item.vertices[0].texCoords.x = posX;
		item.vertices[0].texCoords.y = posY;

		item.vertices[1].position.x = posX + textureSize.x;
		item.vertices[1].position.y = posY;
		item.vertices[1].texCoords.x = posX + textureSize.x;
		item.vertices[1].texCoords.y = posY;

		item.vertices[2].position.x = posX + textureSize.x;
		item.vertices[2].position.y = posY + textureSize.y;
		item.vertices[2].texCoords.x = posX + textureSize.x;
		item.vertices[2].texCoords.y = posY + textureSize.y;

		item.vertices[3].position.x = posX;
		item.vertices[3].position.y = posY + textureSize.y;
		item.vertices[3].texCoords.x = posX;
		item.vertices[3].texCoords.y = posY + textureSize.y;
	}

	item.layerDepth = layerDepth;

	m_drawBuffer.push_back(item);
}

void SpriteBatch::draw(sf::Texture & sprite, sf::Vector2f pos, float layerDepth)
{
	drawInternal(sprite, pos.x, pos.y, 0, 0, 0, 0, layerDepth);
}

void SpriteBatch::draw(sf::Texture & sprite, sf::Vector2f pos, sf::IntRect source, float layerDepth)
{
	drawInternal(sprite, pos.x, pos.y, source.left, source.top, source.width, source.height, layerDepth);
}

void SpriteBatch::end(sf::RenderTarget & target)
{
	if (!m_beginCalled)
		throw new std::runtime_error("begin must be called first");

	if (!m_drawBuffer.empty())
	{
		switch (m_sortMode)
		{
			case SpriteBatchSortMode::BackToFront:
				std::sort(m_drawBuffer.begin(), m_drawBuffer.end(), std::less<SpriteBatchDrawItem>());
				break;
			case SpriteBatchSortMode::FrontToBack:
				std::sort(m_drawBuffer.begin(), m_drawBuffer.end(), std::greater<SpriteBatchDrawItem>());
				break;
		}

		render(target);
	}

	m_beginCalled = false;
}