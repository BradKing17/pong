#include <Engine/Sprite.h>
#include "Collision.h"


bool Collision::isInside(const ASGE::Sprite* sprite, float x, float y) const
{
	auto paddle_one_min_x = ->xPos();
	auto paddle_one_max_x = sprite->xPos() + sprite->width();
	auto paddle_one_min_y = sprite->yPos();
	auto paddle_one_max_y = sprite->yPos() + sprite->height();

	if ((paddle_one_min_x <= x && x <= paddle_one_max_x) &&
		(paddle_one_min_y <= y && y <= paddle_one_max_y))
	{
		return true;
	}
	else
	{
		return false;
	}
}