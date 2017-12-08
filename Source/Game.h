#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include "Vector.h"

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

	int  callback_id = -1;             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */
	ASGE::Sprite* sprite = nullptr; /**< Sprite Object. The background sprite. */
	ASGE::Sprite* paddle_one = nullptr;
	ASGE::Sprite* paddle_two = nullptr;
	ASGE::Sprite* ball = nullptr;


	bool in_menu = true;
	bool in_main_menu = true;
	bool in_leaderboard = false;
	bool in_mode_select = false;
	int menu_option = 0;
	int score_p_one = 0;
	int score_p_two = 0;

	int direction_one = 0;
	int direction_two = 0;
	bool player_one_input = false;
	bool player_two_input = false;

	Vector ball_direction;
	int move_speed;
};

