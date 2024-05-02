#pragma once
#include "yaScript.h"

namespace ya
{
	class EnemyScript : public Script
	{
	public:
		EnemyScript();
		~EnemyScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual bool IsWait() = 0;
		virtual void ChangeWalkDirectionNState(eDirection dir) = 0;

		virtual float ZValueLerp(float a, float b, float t) { return a + t * (b - a); }

	protected:
		// 어떤 공격 스킬을 사용중인지 담고 있는 bool vector
		std::vector<bool> mAttackState;

	public:
		const std::vector<bool>& GetAttackState() const { return mAttackState; }
	};
}