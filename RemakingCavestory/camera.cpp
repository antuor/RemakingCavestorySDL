#include "camera.h"

static SDL_Rect m_rect;

void Camera::Init()
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = globals::SCREEN_WIDTH;
	m_rect.h = globals::SCREEN_HEIGHT;
}

SDL_Rect Camera::GetRect()
{
	return m_rect;
}

void Camera::Update(float elapsedTime, Player &player)
{
	if ((player.getX() < (m_rect.w) / 3) && (m_rect.x > 0))
	{
		m_rect.x -= 2;
		m_rect.w -= 2;
	}
	else
	{
		if ((player.getX() > (m_rect.w) * 2 / 3) && (m_rect.w < globals::SCREEN_WIDTH))
		{
			m_rect.x += 2;
			m_rect.w += 2;
		}
	}
	if ((player.getY() < (m_rect.h) / 3) && (m_rect.y > 0))
	{
		m_rect.y -= 2;
		m_rect.h -= 2;
	}
	else
	{
		if ((player.getY() > (m_rect.h) * 2 / 3) && (m_rect.h < globals::SCREEN_HEIGHT))
		{
			m_rect.y += 2;
			m_rect.h += 2;
		}
	}
	//m_rect.x = player.getX() - globals::SCREEN_WIDTH / 2;
	//m_rect.y = player.getY() - globals::SCREEN_HEIGHT / 2;
}