#pragma once
#include "yaComponent.h"
#include "yaTransform.h"


namespace ya
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		Vector3 GetPosition() { return mPosition; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetCenter() { return mCenter; }
		void SetCenter(Vector2 size) { mCenter = size; }
		UINT GetColliderID() { return mColliderID; }

		eColliderActivation GetActivation() { return mActivation; }
		void SetActivation(eColliderActivation activation) { mActivation = activation; }
		eColliderState GetState() { return mState; }
		void SetState(eColliderState state) { mState = state; }
		bool GetIsBody() { return mIsBody; }
		void SetIsBody(bool isBody) { mIsBody = isBody; }
		bool GetCanGuard() { return mCanGuard; }
		void SetCanGuard(bool canGuard) { mCanGuard = canGuard; }

		Vector3 GetOtherPos() { return mOtherPosition; }
		void SetOtherPos(Vector3 otherPos) { mOtherPosition = otherPos; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;

		eColliderActivation mActivation = eColliderActivation::Active;
		eColliderState mState = eColliderState::NotColliding;
		bool mIsBody = false;
		bool mCanGuard = false;
		Vector3 mOtherPosition = Vector3(9999.0f, 9999.0f, 9999.0f);
	};
}