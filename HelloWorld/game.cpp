#define PLAY_USING_GAMEOBJECT_MANAGER
#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "constants.h"
#include "game.h"
#include "Paddle.h"

Paddle paddle = { 320, 20 };

void DrawPaddle()
{
	Play::DrawRect(paddle.topright, paddle.bottomleft, Play::cWhite, false);
};

void UpdatePaddle()
{
	if (Play::KeyDown(Play::KEY_LEFT) && paddle.x > 50)
	{
		paddle.x -= 5;
	}
	if (Play::KeyDown(Play::KEY_RIGHT) && paddle.x < DISPLAY_WIDTH - 50)
	{
		paddle.x += 5;
	}
	paddle.topright.x = paddle.x + (paddle.width), paddle.y + paddle.height;
	paddle.bottomleft.x = paddle.x - (paddle.width), paddle.y;
}

void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 300 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

void SetupScene() 
{
	for (int y = DISPLAY_HEIGHT-150; y < DISPLAY_HEIGHT -15 ; y += 12)
	{
		for (int x = 15; x < DISPLAY_WIDTH - 15; x += 18)
		{
			const int objectId = Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
			GameObject& brick = Play::GetGameObject(objectId);
		}
	}
}

void StepFrame( float elapsed)
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	const std::vector<int> bricksIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = Play::GetGameObject(ballIds[i]);

		Play::DrawObject(ball);
		Play::UpdateGameObject(ball);

		//The colliton for the walls 
		if (ball.pos.y < 0)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (ball.pos.y > DISPLAY_HEIGHT)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (ball.pos.x < 0)
		{
			ball.velocity.x = -ball.velocity.x;
		}
		else if (ball.pos.x > DISPLAY_WIDTH)
		{
			ball.velocity.x = -ball.velocity.x;
		}
		if ( IsColliding(ball))
		{
			ball.velocity.y = -ball.velocity.y;
		}
	}
	for (int i = 0; i < bricksIds.size(); i++) {
		GameObject& brick = Play::GetGameObject(bricksIds[i]);
		for (int y = 0; y < ballIds.size(); y++) {
			GameObject& balls = Play::GetGameObject(ballIds[y]);
			Play::DrawObject(brick);
			Play::UpdateGameObject(brick);
			if (Play::IsColliding(balls, brick)) {
				Play::DestroyGameObject(bricksIds[i]);
				balls.velocity.y = -balls.velocity.y;
			}
		}
	}
}

int Max(int b, int s)
{
	bool max = b > s || b == s;
	return max ? b : s;
}

int Min(int b, int s)
{
	bool min = b < s || b == s;
	return min ? b : s; 
}

bool IsColliding(GameObject& ball)
{
	float dx = ball.pos.x - Max(paddle.bottomleft.x, Min(ball.pos.x, paddle.topright.x));
	float dy = ball.pos.y - Max(paddle.bottomleft.y, Min(ball.pos.y, paddle.topright.y));
	return (dx * dx + dy * dy) < (ball.radius * ball.radius);
}



