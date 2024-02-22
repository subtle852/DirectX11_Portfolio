#pragma once
//#include "yaScript.h"
#include <yaScript.h>

namespace ya
{
	class CameraScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetCameraSetting(eCameraSetting cameraSetting);// Static
		void SetCameraSetting(eCameraSetting cameraSetting, Vector3 targetPos);// Tracking
		void SetCameraSetting(eCameraSetting cameraSetting, Vector3 targetPos, float speed);// SmoothingTransition
		void SetCameraSetting(eCameraSetting cameraSetting, float duration, float speed, float amplitude);// ShakeVertical ShakeHorizontal ShakeZoom ShakeCircle

		void SetStatic();
		void SetTracking(Vector3 targetPos);
		void SetSmoothingTransition(Vector3 targetPos, float speed);
		void SetCameraShakeVertical();
		void SetCameraShakeHorizontal();
		void SetCameraShakeZoom();
		void SetCameraShakeCircle();

		bool GetCameraDurationEnd() { return mIsShakeDurationEnd; }

		void SetColliderState (eColliderActivation colliderActivation) 
		{ 
			mUpperCd->SetActivation(colliderActivation);
			mLowerCd->SetActivation(colliderActivation);
			mLeftCd->SetActivation(colliderActivation);
			mRightCd->SetActivation(colliderActivation);
		}

	private:
		eCameraSetting mCameraSetting = eCameraSetting::Static;
		Vector3 mTargetPos = Vector3::Zero;
		float mTransitionSpeed = 0.0f;
		float mMaxDistance = 0.0f;

		// ShakeVH
		float mTime = 0.0f;// Shake 공용 sin값 추출 mTime
		float mDuration = 0.0f;// Shake 공용 mDuration
		float mInitialXPosition = 0.0f;
		float mInitialYPosition = 0.0f;
		float mShakeSpeed = 1.0f;
		float mAmplitude = 1.0f;
		//float deltaTime = 0.1f;

		// ShakeCircle
		float mRotationSpeed = 10.0f;
		float mRadius = 1.0f;
		float mAngle = 0.0f;

		// ShakeZoom
		float mInitialZoomSize = 5.0f;
		float mZoomSpeed = 0.1f;
		float mZoomAmplitude = 5.0f;

		// ShakeEnd
		bool mIsShakeDurationEnd = false;

		// Collider
		Collider2D* mUpperCd = nullptr;
		Collider2D* mLowerCd = nullptr;
		Collider2D* mLeftCd = nullptr;
		Collider2D* mRightCd = nullptr;
	};

}