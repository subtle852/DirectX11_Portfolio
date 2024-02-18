#pragma once
#include "..\Engine_SOURCE\yaScene.h"

namespace ya
{
	class ShopScene : public Scene
	{
	public:
		ShopScene();
		virtual ~ShopScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* mBG_STAGE01_SHOP = nullptr;
	};
}