#pragma once

#include "Vector2.h"

class Player
{
public:
	Player();
	void Update(const char keys[256], const char preKeys[256]);
	void Draw();
private:
	Vector2 position_;
	Vector2 dashDirection_; // ダッシュ方向
	float size_;
	float speed_;
	int dashFrame_;         // ダッシュの残り時間
	float dashSpeed_;       // ダッシュ速度
	int dashCoolTimer_;    // ダッシュのクールタイム
};