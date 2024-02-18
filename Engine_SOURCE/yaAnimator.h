#pragma once
#include "yaComponent.h"
#include "yaAnimation.h"

namespace ya
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, enums::eAnimationType type
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);
		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
		// void OnAlphaBlend(const std::wstring& name, bool isBlend, float time);
		// 이렇게 하지말고 update에서 확인?
		// 애니메이션이 돌다가 신호가 오면
		// 번쩍 번쩍해야함
		// 라모나스크립트에서 해야하나? 번쩍 신호 주고
		// 라모나스크립트에서 현재 실행중인 애니메이션 찾아서?
		void Binds();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		bool mbLoop;
	};
}