#pragma once
#include "yaEntity.h"
#include "yaComponent.h"
#include "yaScript.h"
#include "yaRenderer.h"
#include "yaConstantBuffer.h"

namespace ya
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			
			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);
			
			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}

		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

		void BindConstantBuffer()
		{
			renderer::EffectCB efCB = {};
			efCB.effectLightColor = mEffectColor;
			efCB.isFlickering = mIsEffectFlickering;
			efCB.isFlashing = mIsEffectFlashing;
			//flCB.minAlpha = 0.0f;
			//flCB.maxAlpha = 1.0f;
			//flCB.amplitude = 0.5f;
			//flCB.duration = 5.0f;

			ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Effect];
			cb->SetData(&efCB);
			cb->Bind(eShaderStage::PS);
		}

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;

	public:
		bool mIsEffectFlickering = false;
		bool mIsEffectFlashing = false;
		Vector4 mEffectColor = Vector4(0.8f, 0.8f, 0.8f, 1.0f);

	};
}
