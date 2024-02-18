#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Boss01Scene : public Scene
	{
	public:
		Boss01Scene();
		virtual ~Boss01Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_STAGE01_BOSS01 = nullptr;

		GameObject* mUI_STAGE01_STATE = nullptr;
	};
}