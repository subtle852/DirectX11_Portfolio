#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		virtual ~SelectScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_SELECT_CURTAIN;
	};
}