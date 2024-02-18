#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class Title01Scene : public Scene
	{
	public:
		Title01Scene();
		virtual ~Title01Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_TITLE01_01;
	};
}