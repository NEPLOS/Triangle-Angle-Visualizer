
#include <iostream>
#include <cmath>
#include "raylib.h"

bool holdSometing = false;

class circle
{

private:
	bool holding = false;
	char radius;
	Vector2 position;
	Color colour;
public:
	circle(Vector2 a, Color cl, char c = 5)
	{
		position = a;
		colour = cl;
		radius = c;
	}
	bool Collision(Vector2 m)
	{

		return CheckCollisionPointCircle(m, position, radius);

	}
	void draw()
	{
		Vector2 m = GetMousePosition();

		if(holdSometing == true && holding == false)
		{
			DrawCircle(position.x, position.y, radius, colour);
			return;
		}

		if ((Collision(m) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON) && holding) && holdSometing == false)
		{
			// position.x = m.x;
			// position.y = m.y;
			holding = true;
			holdSometing = true;
		}

		if (Collision(m) && IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON) && holding)
		{
			position.x = m.x;
			position.y = m.y;
		}
		

		if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			holding = false;
			holdSometing = false;
		}

		DrawCircle(position.x, position.y, radius, colour);
	}

	Vector2 get_cord()
	{
		return position;
	}

	friend void cal_angle(circle* f);

};

void cal_angle(circle* f);

int main()
{
	circle hmm[3] = { {{ 300 , 300 }, RED, 5} , {{ 400 , 400 }, YELLOW, 5} , {{ 200 , 450 }, BLUE, 5} };

	InitWindow(720, 720, "boo");

	SetTargetFPS(60);

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		DrawTriangleLines(hmm[0].get_cord(), hmm[1].get_cord(), hmm[2].get_cord(), WHITE);

		for (int i = 0; i < 3; i++)
		{
			hmm[i].draw();
		}

		cal_angle(hmm);

		ClearBackground(BLACK);

		EndDrawing();
	}

}

void cal_angle(circle* f)
{
	double B_and_Y = sqrt(pow(f[1].get_cord().x - f[2].get_cord().x, 2) + pow(f[1].get_cord().y - f[2].get_cord().y, 2));
	double R_and_B = sqrt(pow(f[0].get_cord().x - f[2].get_cord().x, 2) + pow(f[0].get_cord().y - f[2].get_cord().y, 2));
	double R_and_Y = sqrt(pow(f[1].get_cord().x - f[0].get_cord().x, 2) + pow(f[1].get_cord().y - f[0].get_cord().y, 2));

	double Red_angle = acos((pow(R_and_B, 2) + pow(R_and_Y, 2) - pow(B_and_Y, 2)) / (2 * R_and_B * R_and_Y)) * 180 / PI;
	double Yellow_angle = acos((pow(B_and_Y, 2) + pow(R_and_Y, 2) - pow(R_and_B, 2)) / (2 * B_and_Y * R_and_Y)) * 180 / PI;
	//float Blue_angle = acos((pow(B_and_Y, 2) + pow(R_and_B, 2) - pow(R_and_Y, 2)) / (2 * B_and_Y * R_and_B)) * 180 / PI;


	//Red_angle = Red_angle;

	DrawText(" Red : ", 10, 20, 20, WHITE);
	DrawText(TextFormat("%lf", Red_angle), 10 + 85, 20, 20, WHITE);
	DrawText(" Yellow : ", 10, 50, 20, WHITE);
	DrawText(TextFormat("%lf", Yellow_angle), 10 + 90, 50, 20, WHITE);
	DrawText(" Blue : ", 10, 80, 20, WHITE);
	//DrawText(TextFormat("%f", Blue_angle), 10 + 90, 80, 20, WHITE);
	//DrawText(" Blue : ", 10, 110, 20, WHITE);
	DrawText(TextFormat("%lf", 180 - (Red_angle + Yellow_angle)), 10 + 90, 80, 20, WHITE);
}