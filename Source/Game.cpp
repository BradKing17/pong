#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>


#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include <ctime>


/**
*   @brief   Default Constructor.
*/
Pong::Pong()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Pong::~Pong()
{
	this->inputs->unregisterCallback(callback_id);

	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The keyHandler callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool Pong::init()
{
	game_width  = WINDOW_WIDTH;
	game_height = WINDOW_HEIGHT;

	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Pong");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

	paddle_one = renderer->createRawSprite();
	paddle_one->loadTexture(".\\Resources\\Textures\\Paddle.png");
	paddle_one->width(15);
	paddle_one->height(75);
	paddle_one->xPos(10);
	paddle_one->yPos((game_height / 2) - (paddle_one->height()/2));

	paddle_two = renderer->createRawSprite();
	paddle_two->loadTexture(".\\Resources\\Textures\\Paddle.png");
	paddle_two->width(15);
	paddle_two->height(75);
	paddle_two->xPos(game_width - (paddle_two->width() + 10));
	paddle_two->yPos((game_height / 2) - (paddle_one->height() / 2));

	ball = renderer->createRawSprite();
	ball->loadTexture(".\\Resources\\Textures\\Paddle.png");
	ball->width(15);
	ball->height(15);

	std::srand(time(NULL));
	spawn();

	toggleFPS();

	callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);


	// enable noob mode
	inputs->use_threads = false;
	
	return true;
}


/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's 
			 keyboard input. For this assignment, calls to this function 
			 are thread safe, so you may alter the game's state as you 
			 see fit. 
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void Pong::keyHandler(ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
	
	if(in_menu)
	{
		if (key->key == ASGE::KEYS::KEY_ENTER &&
			key->action == ASGE::KEYS::KEY_RELEASED &&
			in_main_menu == true)
		{
			switch (menu_option)
			{
			case 0:
				in_main_menu = false;
				in_mode_select = true;
				in_how_to_play = false;
				menu_option = 0;
				break;

			case 1:
				in_main_menu = false;
				in_mode_select = false;
				in_how_to_play = true;
				menu_option = 0;
				break;

			case 2:
				signalExit();
				break;
			}
		}
		else if ((key->key == ASGE::KEYS::KEY_ENTER &&
			key->action == ASGE::KEYS::KEY_RELEASED &&
			in_mode_select == true))
		{
			in_mode_select = false;
			in_menu = false;
		}

		if (key->key == ASGE::KEYS::KEY_W &&
			key->action == ASGE::KEYS::KEY_RELEASED
			&& menu_option != 0)
		{
			menu_option--;
		}

		if (key->key == ASGE::KEYS::KEY_S &&
			key->action == ASGE::KEYS::KEY_RELEASED
			&& menu_option != 2)
		{
			menu_option++;
		}

		if (key->key == ASGE::KEYS::KEY_UP &&
			key->action == ASGE::KEYS::KEY_RELEASED
			&& menu_option != 0)
		{
			menu_option--;
		}

		if (key->key == ASGE::KEYS::KEY_DOWN &&
			key->action == ASGE::KEYS::KEY_RELEASED
			&& menu_option != 2)
		{
			menu_option++;
		}

		if (key->key == ASGE::KEYS::KEY_ESCAPE &&
			key->action == ASGE::KEYS::KEY_RELEASED &&
			in_main_menu == false)
		{
			in_main_menu = true;
			in_mode_select = false;
		}
	}
	else
	{
		if (key->action == ASGE::KEYS::KEY_PRESSED)
		{
			switch (key->key)
			{
				case ASGE::KEYS::KEY_W:
				{
					direction.set_dir_one(-1);
					break;
				}
				case ASGE::KEYS::KEY_S:
				{
					direction.set_dir_one(1);
					break;
				}
				case ASGE::KEYS::KEY_UP:
				{
					direction.set_dir_two(-1);
					break;
				}
				case ASGE::KEYS::KEY_DOWN:
				{
					direction.set_dir_two(1);
					break;
				}
			}
		}
		else if (key->action == ASGE::KEYS::KEY_RELEASED)
		{
			switch (key->key)
			{
				case ASGE::KEYS::KEY_W:
				{
					direction.set_dir_one(0);
					break;
				}
				case ASGE::KEYS::KEY_S:
				{
					direction.set_dir_one(0);
					break;
				}

				case ASGE::KEYS::KEY_UP:
				{
					direction.set_dir_two(0);
					break;
				}
				case ASGE::KEYS::KEY_DOWN:
				{
					direction.set_dir_two(0);
					break;
				}
			}
		}

	}

}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void Pong::update(const ASGE::GameTime & us)
{
	if (!in_menu)
	{
		//get current position of ball
		auto x_pos = ball->xPos();
		auto y_pos = ball->yPos();

		//check if ball is hitting paddles 
		if (isInside(ball, paddle_one, x_pos, y_pos))
		{
			ball_direction.set_x(ball_direction.get_x() * -1);
		}
		else if (isInside(ball, paddle_two, x_pos, y_pos))
		{
			ball_direction.set_x(ball_direction.get_x() * -1);
		}
		//apply speed to ball 
		x_pos += ball_speed * ball_direction.get_x() * (us.delta_time.count() / 1000.f);
		y_pos += ball_speed * ball_direction.get_y() * (us.delta_time.count() / 1000.f);

		// update the position of the ball
		ball->yPos(y_pos);
		ball->xPos(x_pos);

		//check for walls
		if (y_pos >= game_height - ball->height() || y_pos <= 0)
		{
			ball_direction.set_y(ball_direction.get_y() * -1);
		}

		//check for point scoring
		if (x_pos >= game_width - ball->width())
		{
			score_p_one++;
			spawn();
		}
		if (x_pos <= 0)
		{
			score_p_two++;
			spawn();
			
		}

		//paddle movement
		auto y_pos_one = paddle_one->yPos();
		auto y_pos_two = paddle_two->yPos();

		y_pos_one += direction.get_dir_one() * move_speed * (us.delta_time.count() / 1000.f);
		y_pos_two += direction.get_dir_two() * move_speed * (us.delta_time.count() / 1000.f);

		paddle_one->yPos(y_pos_one);
		paddle_two->yPos(y_pos_two);
	}
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
			 Once the current frame is has finished the buffers are 
			 swapped accordingly and the image shown.
*   @return  void
*/
void Pong::render(const ASGE::GameTime &)
{
	if (in_main_menu)
	{
		renderer->renderText(menu_option == 0 ? ">PLAY" : "PLAY",
			200, 200, 1.0, ASGE::COLOURS::AQUAMARINE);
		renderer->renderText(menu_option == 1 ? ">HOW TO PLAY" : "HOW TO PLAY",
			200, 250, 1.0, ASGE::COLOURS::AQUAMARINE);
		renderer->renderText(menu_option == 2 ? ">QUIT" : "QUIT?",
			200, 300, 1.0, ASGE::COLOURS::AQUAMARINE);
	}
	else if (in_how_to_play)
	{
		renderer->renderText("HOW TO PLAY", 
			200, 200, 1.0, ASGE::COLOURS::ORANGE);

		renderer->renderText("PLAYER 1",
			200, 250, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText("W : MOVE YOUR PADDLE UP",
			200, 300, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText("S : MOVE YOUR PADDLE DOWN",
			200, 325, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText("PLAYER 2",
			500, 250, 1.0, ASGE::COLOURS::AQUAMARINE);


		renderer->renderText("UP ARROW : MOVE YOUR PADDLE UP",
			500, 300, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText("DOWN ARROW : MOVE YOUR PADDLE DOWN",
			500, 325, 1.0, ASGE::COLOURS::AQUAMARINE);


		renderer->renderText("SCORE POINTS BY HITTING THE BALL PAST THE\n"
			"OTHER PLAYERS PADDLE INTO THEIR GOAL WHILE DEFENDING YOUR OWN GOAL.",
			200, 400, 1.0, ASGE::COLOURS::AQUAMARINE);
	}
	else if (in_mode_select)
	{
		renderer->renderText("FIRST TO: " ,
			200, 200, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText(menu_option == 0 ? ">5 POINTS" : "5 POINTS",
			350, 200, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText(menu_option == 1 ? ">10 POINTS" : "10 POINTS",
			350, 300, 1.0, ASGE::COLOURS::AQUAMARINE);

		renderer->renderText(menu_option == 2 ? ">20 POINTS" : "20 POINTS",
			350, 400, 1.0, ASGE::COLOURS::AQUAMARINE);
	}
	else
	{
		renderer->renderSprite(*paddle_one);
		renderer->renderSprite(*paddle_two);
		renderer->renderSprite(*ball);

		std::string score_str_one = "SCORE: " + std::to_string(score_p_one);
		renderer->renderText(score_str_one.c_str(), 150, 25, 1.0, ASGE::COLOURS::DARKORANGE);
		std::string score_str_two = "SCORE: " + std::to_string(score_p_two);
		renderer->renderText(score_str_two.c_str(), (game_width - 250), 25, 1.0, ASGE::COLOURS::DARKORANGE);


	}
}

void Pong::spawn()
{
	if (score_p_one == max_score)
	{
		in_menu = true;
		in_main_menu = true;
	}
	else if (score_p_two == max_score)
	{
		in_menu = true;
		in_main_menu = true;
	}
	else
	{
		auto x = (rand() % 10 + 1) - 5;
		auto y = (rand() % 10 + 1) - 5;

		if (x == 0)
		{
			x += 5;
		}
		if (y == 0)
		{
			y += 5;
		}

		ball_direction.set_x(x);
		ball_direction.set_y(y);
		ball_direction.normalise();
		ball->xPos((game_width - ball->width()) / 2);
		ball->yPos((game_height - ball->height()) / 2);
	}
	
}

bool Pong::isInside(const ASGE::Sprite* ball_sprite, const ASGE::Sprite* paddle_sprite, float x, float y) const
{
	float paddle_height = paddle_sprite->height();
	float paddle_width = paddle_sprite->width();
	float pos_x = paddle_sprite->xPos();
	float pos_y = paddle_sprite->yPos();

	if (((x >= pos_x) && (x <= pos_x + paddle_width)) &&
		((y >= pos_y) && (y <= pos_y + paddle_height)))
	{
		return true;
	}
	else
	{
		return false;
	}

}
