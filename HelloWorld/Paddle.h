#pragma once
#include "Play.h"
#include "constants.h"

//position 
struct Paddle
{
	int x = 320;
	int y = 20;
	int width = 50;
	int height = 5;

	Play::Point2D bottomleft = { DISPLAY_WIDTH / 2, y};
	Play::Point2D topright = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 330};
};