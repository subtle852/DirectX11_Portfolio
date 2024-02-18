#pragma once
#include "yaScript.h"
#include "yaPlayerScript.h"

namespace ya
{
	class MiniScript : public PlayerScript
	{
	public:
		MiniScript();
		~MiniScript();


		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		bool mRoute[9][13] =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,1,1,1,0},
			{0,0,0,1,0,0,0,1,0,1,0,1,0},
			{0,0,0,1,1,1,1,1,1,1,0,1,0},
			{0,0,0,0,0,1,0,0,0,1,0,1,0},
			{0,1,0,0,0,1,0,0,0,1,1,1,0},
			{0,1,0,0,0,1,0,0,0,1,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		Vector2 mPos = { 0,3 };
		Vector2 mPosbyMatrix = { 1, 7 };
		Vector2 zeroPos = Vector2(-2.26f, 1.65f);
	};
}