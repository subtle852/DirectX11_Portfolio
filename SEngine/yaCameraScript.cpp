#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaPlayScene.h"

namespace ya
{
	void CameraScript::Initialize()
	{
		mCd = this->GetOwner()->AddComponent<Collider2D>();
		mCd->SetSize(Vector2(0.5f, 0.5f));
		mCd->SetCenter(Vector2(0.0f, 0.0f));
		mCd->SetActivation(eColliderActivation::Active);
		mCd->SetIsBody(true);
	}

	void CameraScript::Update()
	{
		switch (mCameraSetting)
		{
			case eCameraSetting::Static:
			{	
				SetStatic();
				break;
			}
			case eCameraSetting::Tracking:
			// 플레이어 트래킹이 일반적
			// 특정 몹이나 특정 지역으로 트래킹하더라도
			// 트랜지션 후, 트래킹이 필수적
			{
				Vector3 targetPos = PlayScene::GetPlayerPosition();// PlayScene::TargetPosition으로 가져오도록 수정 예정
				SetTracking(targetPos);
				break;
			}
			case eCameraSetting::SmoothingTransition:
			{
				SetSmoothingTransition(mTargetPos, mTransitionSpeed);
				break;
			}
			case eCameraSetting::ShakeVertical:
			{	
				SetCameraShakeVertical();
				break;
			}
			case eCameraSetting::ShakeHorizontal:
			{	
				SetCameraShakeHorizontal();
				break;
			}
			case eCameraSetting::ShakeCircle:
			{	
				SetCameraShakeCircle();
				break;
			}
			case eCameraSetting::ShakeZoom:
			{	
				SetCameraShakeZoom();
				break;
			}
			default:
				break;
		}
	}

	void CameraScript::OnCollisionEnter(Collider2D* other)
	{
		int a = 0;
	}

	void CameraScript::OnCollisionStay(Collider2D* other)
	{
		int a = 0;
	}

	void CameraScript::OnCollisionExit(Collider2D* other)
	{
	}

	void CameraScript::SetCameraSetting(eCameraSetting cameraSetting)// Static
	{
		if (cameraSetting != eCameraSetting::Static)
			return;

		mCameraSetting = cameraSetting;
		mTargetPos = (Vector3)0.0f;
		mTransitionSpeed = 0.0f;
		mMaxDistance = 0.0f;
	}

	void CameraScript::SetCameraSetting(eCameraSetting cameraSetting, Vector3 targetPos)// Tracking
	{
		if (cameraSetting != eCameraSetting::Tracking)
			return;

		mCameraSetting = cameraSetting;
		mTargetPos = targetPos;
		mTransitionSpeed = 0.0f;
		mMaxDistance = 0.0f;

	}

	void CameraScript::SetCameraSetting(eCameraSetting cameraSetting, Vector3 targetPos, float speed)// SmoothingTransition
	{
		if (cameraSetting != eCameraSetting::SmoothingTransition)
			return;

		mCameraSetting = cameraSetting;
		mTargetPos = targetPos;
		mTransitionSpeed = speed;
		mMaxDistance = 0.0f;
	}

	void CameraScript::SetCameraSetting(eCameraSetting cameraSetting, float duration, float speed, float amplitude)// ShakeVertical, ShakeHorizontal, ShakeZoom
	{
		if (cameraSetting == eCameraSetting::ShakeVertical || cameraSetting == eCameraSetting::ShakeHorizontal)
		{
			mCameraSetting = cameraSetting;
			mTime = 0.0f;
			mDuration = duration;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			mInitialXPosition = pos.x;
			mInitialYPosition = pos.y;
			mShakeSpeed = speed;
			mAmplitude = amplitude;
		}

		else if (cameraSetting == eCameraSetting::ShakeZoom)
		{
			mCameraSetting = cameraSetting;
			mTime = 0.0f;
			mDuration = duration;
			mInitialZoomSize = 5.0f;
			mZoomSpeed = speed;
			mZoomAmplitude = amplitude;

		}
		else if (cameraSetting == eCameraSetting::ShakeCircle)
		{
			mCameraSetting = cameraSetting;
			mTime = 0.0f;
			mDuration = duration;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			mInitialXPosition = pos.x;
			mInitialYPosition = pos.y;
			mRotationSpeed = speed;
			mRadius = amplitude;
			mAngle = 0.0f;
		}
		else
		{
			return;
		}
	}

	void CameraScript::SetStatic()
	{
		// 디버깅 용
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();


			if (Input::GetKey(eKeyCode::NUM6))
			{
				pos.z += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::NUM4))
			{
				pos.z -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}

			if (Input::GetKey(eKeyCode::NUM1))
			{
				pos.x -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::NUM3))
			{
				pos.x += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::NUM2))
			{
				pos.y -= 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (Input::GetKey(eKeyCode::NUM5))
			{
				pos.y += 5.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
	}

	void CameraScript::SetTracking(Vector3 targetPos)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x = targetPos.x;
		pos.y = targetPos.y;

		tr->SetPosition(pos);
	}

	void CameraScript::SetSmoothingTransition(Vector3 targetPos, float speed)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		float distance = Vector2::Distance(Vector2(pos.x, pos.y), Vector2(targetPos.x, targetPos.y));

		if (distance < 0.1f)// 종료 시점
		{
			SetCameraSetting(eCameraSetting::Static);
			// Static or Tracking 설정 필요
			// Tracking 시 PlayScene::TrackingPosition 필요
			// 여기서 해주거나 SetTracking 내부에서 설정
			// 
			// 혹시나 A에서 B로 전환 후, 다시 A로 돌아가는 경우를 구현한다면
			// B로 전환된 상태에서 얼마나 기다릴건지 인자로 받아와야 하고
			// A의 상태 (함수가 처음 호출될 때의 카메라 위치를 저장해두고 여기서 활용해야 함)
		}

		if (mMaxDistance == 0.0f)// 최초 함수 진입시, 최대 거리 측정
		{
			mMaxDistance = distance;
		}

		float maxSpeed = speed;
		float minSpeed = speed * 0.25f;
		float accelerationDistance = mMaxDistance / 4.0f * 1.0f;
		float decelerationDistance = mMaxDistance / 4.0f * 3.0f;

		if (distance <= accelerationDistance)
		{
			speed = minSpeed + ((maxSpeed - minSpeed) * (distance / accelerationDistance));
		}
		else if (accelerationDistance <= distance && distance <= decelerationDistance)
		{
			speed = maxSpeed;
		}
		else
		{
			speed = maxSpeed - ((maxSpeed - minSpeed) * ((distance - decelerationDistance) / (mMaxDistance - decelerationDistance)));
		}

		Vector2 direction = { targetPos.x - pos.x, targetPos.y - pos.y };
		direction.Normalize();

		Vector2 movement = direction * speed * Time::DeltaTime();

		pos.x += movement.x;
		pos.y += movement.y;

		tr->SetPosition(pos);
	}

	void CameraScript::SetCameraShakeVertical()
	{
		// 바뀌기 전 카메라 세팅 저장을 하고

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialYPosition - 0.03f <= curPos.y && curPos.y <= mInitialYPosition + 0.03f) )// 종료 시점
		{
			// 바뀌기 전 세팅으로 돌리는 방식도 있음
			curPos.y = mInitialYPosition;
			tr->SetPosition(curPos);
			SetCameraSetting(eCameraSetting::Static);
			return;
		}

		float sinValue = std::sin(mTime * mShakeSpeed);

		float newYPosition = mInitialYPosition + sinValue * mAmplitude;
		curPos.y = newYPosition;
		tr->SetPosition(curPos);

		mTime += Time::DeltaTime();
	}

	void CameraScript::SetCameraShakeHorizontal()
	{
		// 바뀌기 전 카메라 세팅 저장을 하고

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialXPosition - 0.03f <= curPos.x && curPos.x <= mInitialXPosition + 0.03f))// 종료 시점
		{
			// 바뀌기 전 세팅으로 돌리는 방식도 있음
			curPos.x = mInitialXPosition;
			tr->SetPosition(curPos);
			SetCameraSetting(eCameraSetting::Static);
			return;
		}

		float sinValue = std::sin(mTime * mShakeSpeed);

		float newXPosition = mInitialXPosition + sinValue * mAmplitude;
		curPos.x = newXPosition;
		tr->SetPosition(curPos);

		mTime += Time::DeltaTime();
	}

	void CameraScript::SetCameraShakeZoom()
	{
		// 바뀌기 전 카메라 세팅 저장을 하고

		mDuration -= Time::DeltaTime();

		Camera* cr = GetOwner()->GetComponent<Camera>();
		float curSize = cr->GetSize();

		if (mDuration <= 0 && (mInitialZoomSize - 0.03f <= curSize && curSize <= mInitialZoomSize + 0.03f))// 종료 시점
		{
			// 바뀌기 전 세팅으로 돌리는 방식도 있음
			cr->SetSize(mInitialZoomSize);
			SetCameraSetting(eCameraSetting::Static);
			return;
		}

		const float mZoomStandardSize = 0.9f;
		float sinValue = std::cos(mTime * mZoomAmplitude);
		float scale = mZoomStandardSize + sinValue * mZoomSpeed;

		cr->SetSize(mInitialZoomSize * scale);

		mTime += Time::DeltaTime();
	}

	void CameraScript::SetCameraShakeCircle()
	{
		// 바뀌기 전 카메라 세팅 저장을 하고

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialXPosition - 0.03f <= curPos.x && curPos.x <= mInitialXPosition + 0.03f))// 종료 시점
		{
			// 바뀌기 전 세팅으로 돌리는 방식도 있음
			curPos.x = mInitialXPosition;
			curPos.y = mInitialYPosition;
			tr->SetPosition(curPos);
			SetCameraSetting(eCameraSetting::Static);
			return;
		}

		float rotatingAngle = mAngle + mRotationSpeed * Time::DeltaTime();

		// 원의 x, y 좌표를 계산 (원의 방정식)
		float x = mRadius * std::cos(rotatingAngle);
		float y = mRadius * std::sin(rotatingAngle);

		curPos.x = x;
		curPos.y = y;
		tr->SetPosition(curPos);

		mAngle += mRotationSpeed * Time::DeltaTime();
	}


}
