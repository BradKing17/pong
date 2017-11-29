#pragma once
#include <string>
#include <Engine/OGLGame.h>

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


	bool in_menu = true;
	bool in_main_menu = true;
	bool in_leaderboard = false;
	bool in_mode_select = false;
	int menu_option = 0;
	int score_p_one = 0;
	int score_p_two = 0;
};

