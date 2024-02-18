#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Subspace01Scene : public Scene
	{
	public:
		Subspace01Scene();
		virtual ~Subspace01Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_STAGE01_SUBSPACE01 = nullptr;

		GameObject* mUI_STAGE01_STATE = nullptr;
	};
}