#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "Game.h"
#include "GameFont.h"


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
	paddle_one->width(30);
	paddle_one->height(200);

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
				in_leaderboard = false;
				menu_option = 0;
				break;

			case 1:
				in_main_menu = false;
				in_mode_select = false;
				in_leaderboard = true;
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
			in_leaderboard = false;
			in_mode_select = false;
		}
	}
	else
	{
		if (key->key == ASGE::KEYS::KEY_W &&
			key->action == ASGE::KEYS::KEY_RELEASED)
			
		{
			
		}

		if (key->key == ASGE::KEYS::KEY_S &&
			key->action == ASGE::KEYS::KEY_RELEASED)
		{
			
		}

		if (key->key == ASGE::KEYS::KEY_UP &&
			key->action == ASGE::KEYS::KEY_RELEASED)
		{
	
		}

		if (key->key == ASGE::KEYS::KEY_DOWN &&
			key->action == ASGE::KEYS::KEY_RELEASED)
		{
			
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
void Pong::update(const ASGE::GameTime &)
{

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
		renderer->renderText(menu_option == 1 ? ">LEADERBOARDS" : "LEADERBOARDS",
			200, 250, 1.0, ASGE::COLOURS::AQUAMARINE);
		renderer->renderText(menu_option == 2 ? ">QUIT" : "QUIT?",
			200, 300, 1.0, ASGE::COLOURS::AQUAMARINE);
	}
	else if (in_leaderboard)
	{
		renderer->renderText("TOP SCORES", 
			200, 200, 1.0, ASGE::COLOURS::AQUAMARINE);
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
	}
}