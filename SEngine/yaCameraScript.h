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

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

		void SetPosSetting(int camaraPosSettingNumber) { mCameraPosSetting = camaraPosSettingNumber; }
		void MoveFree();
		void MoveFix(Vector3 targetPos);

	private:
		int mCameraPosSetting = 0;
	};
}