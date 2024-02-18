#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Subspace02Scene : public Scene
	{
	public:
		Subspace02Scene();
		virtual ~Subspace02Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_STAGE01_SUBSPACE02 = nullptr;

		GameObject* mUI_STAGE01_STATE = nullptr;
	};
}