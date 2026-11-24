#include <Novice.h>
#include <cstdlib>
#include "PlayerMoveEffect.h"

MoveEffect::MoveEffect()
{
	for (int i = 0; i < kParticleCount_; i++)
	{
		particle_[i] = {};
	}
	emitter_.position = {};
	emitter_.size = { 32.0f, 32.0f };
	particleAcceleration_ = {};
	particleSpeed_ = 2.0f;
	shrinkRate_ = 0.95f;
}

void MoveEffect::Emit(Vector2 position, Vector2 direction)
{
	// エミッターをプレイヤーの位置に移動
	emitter_.position = position;

	// パーティクルの発生処理
	for (int i = 0; i < kParticleCount_; i++)
	{
		if (!particle_[i].isActive)
		{
			particle_[i].isActive = true;

			// 発生座標をランダムに設定
			particle_[i].position.x = emitter_.position.x - emitter_.size.x / 2.0f + rand() % static_cast<int>(emitter_.size.x);
			particle_[i].position.y = emitter_.position.y - emitter_.size.y / 2.0f + rand() % static_cast<int>(emitter_.size.y);

			// 半径をランダムに設定
			particle_[i].radius = static_cast<float>(rand() % 6 + 3);

			// プレイヤーの移動方向と反対方向に移動
			particle_[i].velocity.x = -direction.x * particleSpeed_;
			particle_[i].velocity.y = -direction.y * particleSpeed_;

			break;
		}
	}
}

void MoveEffect::Update()
{
	for (int i = 0; i < kParticleCount_; i++)
	{
		if (particle_[i].isActive)
		{
			// 加速度を加算
			particle_[i].velocity.x += particleAcceleration_.x;
			particle_[i].velocity.y += particleAcceleration_.y;

			// 速度を座標に加算
			particle_[i].position.x += particle_[i].velocity.x;
			particle_[i].position.y += particle_[i].velocity.y;

			// パーティクルを縮小
			particle_[i].radius *= shrinkRate_;

			// 画面外に出たら非アクティブにする
			if (particle_[i].position.x < 0.0f || particle_[i].position.x > 1920.0f || particle_[i].position.y < 0.0f || particle_[i].position.y > 1080.0f)
			{
				particle_[i].isActive = false;
			}
		}
	}
}

void MoveEffect::Draw()
{
	for (int i = 0; i < kParticleCount_; i++)
	{
		if (particle_[i].isActive)
		{
			Novice::DrawEllipse
			(
				static_cast<int>(particle_[i].position.x),
				static_cast<int>(particle_[i].position.y),
				static_cast<int>(particle_[i].radius),
				static_cast<int>(particle_[i].radius),
				0.0f,
				0x00FFFFFF,
				kFillModeSolid
			);
		}
	}
}