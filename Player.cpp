#include <Novice.h>
#include <math.h>
#include <cmath>
#include "Player.h"

Player::Player()
{
	position_.x = 0.0f;
	position_.y = 0.0f;
	dashDirection_.x = 0.0f;
	dashDirection_.y = 0.0f;
	size_ = 32.0f;
	speed_ = 6.0f;
	dashFrame_ = 0;
	dashSpeed_ = 12.0f;
	dashCoolTimer_ = 0;
}

void Player::Update(const char keys[256], const char preKeys[256])
{
	// ダッシュのクールタイムを減らす
	if (dashCoolTimer_ > 0)
	{
		dashCoolTimer_--;
	}

	// 移動方向
	Vector2 move = { 0.0f, 0.0f };

	// プレイヤーの移動処理
	// 上に移動
	if (keys[DIK_W])
	{
		move.y -= 1.0f;
	}

	// 下に移動
	if (keys[DIK_S])
	{
		move.y += 1.0f;
	}

	// 左に移動
	if (keys[DIK_A])
	{
		move.x -= 1.0f;
	}

	// 右に移動
	if (keys[DIK_D])
	{
		move.x += 1.0f;
	}

	// 斜め移動の速度を統一
	float length = sqrtf(move.x * move.x + move.y * move.y);

	// 移動ベクトルを正規化
	if (length > 0.0f)
	{
		move.x /= length;
		move.y /= length;
	}

	// SPACEを押した瞬間にダッシュ開始
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && dashFrame_ == 0 && length > 0.0f && dashCoolTimer_ == 0)
	{
		dashFrame_ = 10;
		dashDirection_ = move;
		dashCoolTimer_ = 60;
	}

	// ダッシュ中
	if (dashFrame_ > 0)
	{
		position_.x += dashDirection_.x * dashSpeed_;
		position_.y += dashDirection_.y * dashSpeed_;

		dashFrame_--;
	}
	// 通常移動
	else
	{
		position_.x += move.x * speed_;
		position_.y += move.y * speed_;
	}
}

void Player::Draw()
{
	// プレイヤーの描画処理
	Novice::DrawBox
	(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(size_),
		static_cast<int>(size_),
		0.0f,
		0x00FFFFFF,
		kFillModeSolid
	);
}