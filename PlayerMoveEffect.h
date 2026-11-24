#pragma once
#include "Vector2.h"

class MoveEffect
{
public:
	MoveEffect();
	void Emit(Vector2 position, Vector2 direction);
	void Update();
	void Draw();
private:
	struct Particle
	{
		bool isActive;
		Vector2 position;
		Vector2 velocity;
		float radius;
	};

	struct Emitter
	{
		Vector2 position;
		Vector2 size;
	};

	static const int kParticleCount_ = 300;
	Particle particle_[kParticleCount_];
	Emitter emitter_;
	Vector2 particleAcceleration_;
	float particleSpeed_;
	float shrinkRate_;
};
