#pragma once
#include "..\\Engine_SOURCE\\yaGameObject.h"
#include "Engine_SOURCE/yaRenderer.h"
#include "Engine_SOURCE/yaConstantBuffer.h"

namespace gui
{
	class DebugObject : public ya::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer(ya::eColliderActivation activation, ya::eColliderState state)
		{
			renderer::ColliderCB cdCB = {};
			cdCB.colliderActivation = (UINT)activation;
			cdCB.colliderState = (UINT)state;

			ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Collider];
			cb->SetData(&cdCB);
			cb->Bind(eShaderStage::PS);
		}

	private:
	};
}