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
			// �÷��̾� Ʈ��ŷ�� �Ϲ���
			// Ư�� ���̳� Ư�� �������� Ʈ��ŷ�ϴ���
			// Ʈ������ ��, Ʈ��ŷ�� �ʼ���
			{
				Vector3 targetPos = PlayScene::GetPlayerPosition();// PlayScene::TargetPosition���� ���������� ���� ����
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
		// ����� ��
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

		if (distance < 0.1f)// ���� ����
		{
			SetCameraSetting(eCameraSetting::Static);
			// Static or Tracking ���� �ʿ�
			// Tracking �� PlayScene::TrackingPosition �ʿ�
			// ���⼭ ���ְų� SetTracking ���ο��� ����
			// 
			// Ȥ�ó� A���� B�� ��ȯ ��, �ٽ� A�� ���ư��� ��츦 �����Ѵٸ�
			// B�� ��ȯ�� ���¿��� �󸶳� ��ٸ����� ���ڷ� �޾ƿ;� �ϰ�
			// A�� ���� (�Լ��� ó�� ȣ��� ���� ī�޶� ��ġ�� �����صΰ� ���⼭ Ȱ���ؾ� ��)
		}

		if (mMaxDistance == 0.0f)// ���� �Լ� ���Խ�, �ִ� �Ÿ� ����
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
		// �ٲ�� �� ī�޶� ���� ������ �ϰ�

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialYPosition - 0.03f <= curPos.y && curPos.y <= mInitialYPosition + 0.03f) )// ���� ����
		{
			// �ٲ�� �� �������� ������ ��ĵ� ����
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
		// �ٲ�� �� ī�޶� ���� ������ �ϰ�

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialXPosition - 0.03f <= curPos.x && curPos.x <= mInitialXPosition + 0.03f))// ���� ����
		{
			// �ٲ�� �� �������� ������ ��ĵ� ����
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
		// �ٲ�� �� ī�޶� ���� ������ �ϰ�

		mDuration -= Time::DeltaTime();

		Camera* cr = GetOwner()->GetComponent<Camera>();
		float curSize = cr->GetSize();

		if (mDuration <= 0 && (mInitialZoomSize - 0.03f <= curSize && curSize <= mInitialZoomSize + 0.03f))// ���� ����
		{
			// �ٲ�� �� �������� ������ ��ĵ� ����
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
		// �ٲ�� �� ī�޶� ���� ������ �ϰ�

		mDuration -= Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curPos = tr->GetPosition();

		if (mDuration <= 0 && (mInitialXPosition - 0.03f <= curPos.x && curPos.x <= mInitialXPosition + 0.03f))// ���� ����
		{
			// �ٲ�� �� �������� ������ ��ĵ� ����
			curPos.x = mInitialXPosition;
			curPos.y = mInitialYPosition;
			tr->SetPosition(curPos);
			SetCameraSetting(eCameraSetting::Static);
			return;
		}

		float rotatingAngle = mAngle + mRotationSpeed * Time::DeltaTime();

		// ���� x, y ��ǥ�� ��� (���� ������)
		float x = mRadius * std::cos(rotatingAngle);
		float y = mRadius * std::sin(rotatingAngle);

		curPos.x = x;
		curPos.y = y;
		tr->SetPosition(curPos);

		mAngle += mRotationSpeed * Time::DeltaTime();
	}


}