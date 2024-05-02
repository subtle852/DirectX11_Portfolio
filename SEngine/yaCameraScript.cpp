#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaPlayScene.h"
#include "yaRamonaScript.h"
#include "yaLukeScript.h"
#include "yaBoss01Script.h"
#include "yaMinionScript.h"
#include "yaLeeScript.h"
#include "yaJesseScript.h"
#include "yaDogScript.h"
#include "yaLinusScript.h"
#include "yaHarleyScript.h"
#include "yaRigidbody.h"

namespace ya
{
	void CameraScript::Initialize()
	{
		mUpperCd = this->GetOwner()->AddComponent<Collider2D>();
		mUpperCd->SetSize(Vector2(6.2f, 0.2f));
		mUpperCd->SetCenter(Vector2(0.0f, 0.8f));
		mUpperCd->SetActivation(eColliderActivation::Active);
		//mUpperCd->SetIsBody(true);

		mLowerCd = this->GetOwner()->AddComponent<Collider2D>();
		mLowerCd->SetSize(Vector2(6.2f, 0.2f));
		mLowerCd->SetCenter(Vector2(0.0f, -1.8f));
		mLowerCd->SetActivation(eColliderActivation::Active);
		//mLowerCd->SetIsBody(true);

		mLeftCd = this->GetOwner()->AddComponent<Collider2D>();
		mLeftCd->SetSize(Vector2(0.2f, 2.8f));
		mLeftCd->SetCenter(Vector2(-3.1f, -0.4f));
		mLeftCd->SetActivation(eColliderActivation::Active);
		//mLeftCd->SetIsBody(true);

		mRightCd = this->GetOwner()->AddComponent<Collider2D>();
		mRightCd->SetSize(Vector2(0.2f, 2.8f));
		mRightCd->SetCenter(Vector2(3.1f, -0.4f));
		mRightCd->SetActivation(eColliderActivation::Active);
		//mRightCd->SetIsBody(true);
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

		if (mCameraSetting != eCameraSetting::Static)
		{
			mUpperCd->SetActivation(eColliderActivation::InActive);
			mLowerCd->SetActivation(eColliderActivation::InActive);
			mLeftCd->SetActivation(eColliderActivation::InActive);
			mRightCd->SetActivation(eColliderActivation::InActive);
		}
		else
		{
			mUpperCd->SetActivation(eColliderActivation::Active);
			mLowerCd->SetActivation(eColliderActivation::Active);
			mLeftCd->SetActivation(eColliderActivation::Active);
			mRightCd->SetActivation(eColliderActivation::Active);
		}
	}

	void CameraScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void CameraScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* ob = other->GetOwner();
		if (ob == nullptr)
			return;

		if (other->IsBody() == false)// �ٵ� �ݶ��̴� O, ��ų �ݶ��̴� X
			return;

		Transform* obTr = ob->GetComponent<Transform>();
		Vector3 obPos = obTr->GetPosition();

		if (ob->GetName() == L"Ramona")
		{
			if (mUpperCd->GetState() == eColliderState::IsColliding)
			{
				// ob�� �����߿��� ���� 
				// ���� 1) ���� ����� ���ƾ��ϳ�?
				// ���� 2) ���⼭ �����ϴ� ���� �ƴ� ��𳪽�ũ��Ʈ���� ī�޶�� �浹 ���϶�, Ư�� �̵� �� Ư�� ���¸� ���ų� �����ϰ� �����ϴ� ���?
				// ���� 3) �浹 ��, �ٸ� �������� �̵��� �ӵ� ����
				// ���� 4) ��� ��ũ��Ʈ �Ʒ����� ������ ���� �߻� (�� ��Ȳ���� ����)
				// ���� 5) �浹ü�� �����ϴ� ��Ȳ���� ���� (ex. ������ ���� �浹 O/X ��� ����, Transition ��,...)
				RamonaScript* Rs = ob->GetComponent<RamonaScript>();
				if (Rs == nullptr)
					return;

				if (Rs->IsJump() == true)
					return;
				if (Rs->IsDJump() == true)
					return;

				obPos.y -= 0.005f;
				obTr->SetPosition(obPos);
			}
			else if (mLowerCd->GetState() == eColliderState::IsColliding)
			{
				obPos.y += 0.005f;
				obTr->SetPosition(obPos);
			}
			else if (mLeftCd->GetState() == eColliderState::IsColliding)
			{
				obPos.x += 0.005f;
				obTr->SetPosition(obPos);
			}
			else if (mRightCd->GetState() == eColliderState::IsColliding)
			{
				obPos.x -= 0.005f;
				obTr->SetPosition(obPos);
			}
		}
		else
		{
			if (mUpperCd->GetState() == eColliderState::IsColliding)
			{
				obPos.y -= 0.005f;
				obTr->SetPosition(obPos);
			}
			else if (mLowerCd->GetState() == eColliderState::IsColliding)
			{
				obPos.y += 0.005f;
				obTr->SetPosition(obPos);
			}
			else if (mLeftCd->GetState() == eColliderState::IsColliding)
			{
				if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
				{
					obPos.x += 0.005f;
					obTr->SetPosition(obPos);
				}
				
				if (dynamic_cast<MinionScript*>(other->GetOwner()->GetComponent<MinionScript>()))
				{

				}
				else if (dynamic_cast<EnemyScript*>(other->GetOwner()->GetComponent<EnemyScript>()))
				{
					if (ob->GetComponent<EnemyScript>()->IsWait())
						ob->GetComponent<EnemyScript>()->ChangeWalkDirectionNState(eDirection::R);

					obPos.x += 0.005f;
					obTr->SetPosition(obPos);
				}
			}
			else if (mRightCd->GetState() == eColliderState::IsColliding)
			{
				if (dynamic_cast<PlayerScript*>(other->GetOwner()->GetComponent<PlayerScript>()))
				{
					obPos.x -= 0.005f;
					obTr->SetPosition(obPos);
				}

				if (dynamic_cast<MinionScript*>(other->GetOwner()->GetComponent<MinionScript>()))
				{

				}
				else if (dynamic_cast<EnemyScript*>(other->GetOwner()->GetComponent<EnemyScript>()))
				{
					if (ob->GetComponent<EnemyScript>()->IsWait())
						ob->GetComponent<EnemyScript>()->ChangeWalkDirectionNState(eDirection::L);

					obPos.x -= 0.005f;
					obTr->SetPosition(obPos);
				}
			}
		}
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
		//pos.y = targetPos.y;

		tr->SetPosition(pos);
	}

	void CameraScript::SetSmoothingTransition(Vector3 targetPos, float speed)
	{
		SetColliderState(eColliderActivation::InActive);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		float distance = Vector2::Distance(Vector2(pos.x, pos.y), Vector2(targetPos.x, targetPos.y));

		if (distance < 0.1f)// ���� ����
		{
			SetColliderState(eColliderActivation::Active);
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
