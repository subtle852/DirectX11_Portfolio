#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Title02Scene : public Scene
	{
	public:
		Title02Scene();
		virtual ~Title02Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_TITLE02_01 = nullptr;
		GameObject* mUI_TITLE02_ENTER = nullptr;
		bool mUI_TITLE02_ENTER_SizeState = true;// false 감소, true 증가
	};
}