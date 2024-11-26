#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"


void SpawnBall();
void StepFrame(float elapsed);
void SetupScene();
bool IsColliding(Play::GameObject& ball);
void DrawPaddle();
void UpdatePaddle();
