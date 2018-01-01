#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include "Vector.h"
#include "Collision.h"
#include "Paddle.h"

struct GameFont;

/**
*  Pong. An OpenGL Game based on ASGE.
*/

class Pong:
	public ASGE::OGLGame
{
public:
	Pong();
	~Pong();
	virtual bool init() override;

private:
	void keyHandler(ASGE::SharedEventData data);

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	void spawn();
	bool Pong::isInside(const ASGE::Sprite* paddle_sprite, float x, float y) const;

	int  callback_id = -1;             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */
	ASGE::Sprite* sprite = nullptr; /**< Sprite Object. The background sprite. */
	ASGE::Sprite* background = nullptr;
	ASGE::Sprite* paddle_one = nullptr;
	ASGE::Sprite* paddle_two = nullptr;
	ASGE::Sprite* ball = nullptr;


	bool in_menu = true;
	bool in_main_menu = true;
	bool in_how_to_play = false;
	bool in_mode_select = false;
	int menu_option = 0;
	int score_p_one = 0;
	int score_p_two = 0;
	int max_score = 5;

	Paddle direction = 0;
	Vector ball_direction = { 2,3 };
	int ball_speed = 600;
	int move_speed = 450;
};

