#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		int mTitleEnterCount = 0;

		GameObject* mBG_TITLE_01;
		GameObject* mBG_TITLE_02;
	};
}