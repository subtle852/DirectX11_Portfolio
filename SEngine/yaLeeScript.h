#pragma once
#include "yaScript.h"
#include "yaLukeScript.h"

namespace ya
{
	class LeeScript : public LukeScript
	{
	public:
		LeeScript();
		~LeeScript();

		virtual void Initialize() override;
		virtual void Update() override;

		// 충돌 함수
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:

	};

}

