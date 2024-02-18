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

	private:

	};
}