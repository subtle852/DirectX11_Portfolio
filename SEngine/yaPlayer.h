#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		float mHeart = 3.0f;
		float mHp = 100.0f;
		float mGp = 0.0f;
		float mCoin = 0.0f;
	};
}