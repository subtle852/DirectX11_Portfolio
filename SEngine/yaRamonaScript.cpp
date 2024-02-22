#include "yaRamonaScript.h"
#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaCollider2D.h"
#include "yaLukeScript.h"
#include "yaRigidbody.h"
#include "yaRenderer.h"
#include "yaConstantBuffer.h"

namespace ya
{
	RamonaScript::RamonaScript()
	{

	}

	RamonaScript::~RamonaScript()
	{

	}

	void RamonaScript::Initialize()
	{
		SetEffectFlickering(0.25f, 5.0f);// 특정 상황에서 함수 호출 ex. 충돌

		#pragma region 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Idle", L"..\\Resources\\TEXTURE\\RAMONA\\Idle.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_Idle", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(151.0f / 5.0f, 65.0f), 5);
		at->Create(L"L_Idle", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(151.0f / 5.0f, 65.0f), 5);

		atlas
			= Resources::Load<Texture>(L"Walk", L"..\\Resources\\TEXTURE\\RAMONA\\Walk.png");
		at->Create(L"R_Walk", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(210.0f / 6.0f, 68.0f), 6);//, Vector2::Zero, 0.05f);
		at->Create(L"L_Walk", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(210.0f / 6.0f, 68.0f), 6);

		atlas
			= Resources::Load<Texture>(L"Run", L"..\\Resources\\TEXTURE\\RAMONA\\Run.png");
		at->Create(L"R_Run", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(424.0f / 8.0f, 67.0f), 8);
		at->Create(L"L_Run", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(424.0f / 8.0f, 67.0f), 8);
		
		atlas
			= Resources::Load<Texture>(L"Jump", L"..\\Resources\\TEXTURE\\RAMONA\\Jump.png");
		at->Create(L"R_Jump", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(432.0f / 9.0f, 78.0f), 9);
		at->Create(L"L_Jump", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(432.0f / 9.0f, 78.0f), 9);

		atlas
			= Resources::Load<Texture>(L"DJump", L"..\\Resources\\TEXTURE\\RAMONA\\DJumpEdited.png");
		//at->Create(L"R_DJump", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(309.0f / 6.0f, 75.0f), 6);
		//at->Create(L"L_DJump", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(309.0f / 6.0f, 75.0f), 6);
		at->Create(L"R_DJump", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(757.0f / 12.0f, 63.0f), 12);
		at->Create(L"L_DJump", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(757.0f / 12.0f, 63.0f), 12);

		atlas
			= Resources::Load<Texture>(L"Guard", L"..\\Resources\\TEXTURE\\RAMONA\\Guard_ING.png");
		at->Create(L"R_Guard", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(87.0f / 2.0f, 70.0f), 2);
		at->Create(L"L_Guard", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(87.0f / 2.0f, 70.0f), 2);

		atlas
			= Resources::Load<Texture>(L"Evade", L"..\\Resources\\TEXTURE\\RAMONA\\Evade.png");
		at->Create(L"R_Evade", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(399.0f / 7.0f, 64.0f), 7);
		at->Create(L"L_Evade", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(399.0f / 7.0f, 64.0f), 7);

		atlas
			= Resources::Load<Texture>(L"NormalAttack1", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack1.png");
		at->Create(L"R_NormalAttack1", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"NormalAttack1_L", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack1_L.png");
		at->Create(L"L_NormalAttack1", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"NormalAttack2", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack2.png");
		at->Create(L"R_NormalAttack2", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"NormalAttack2_L", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack2_L.png");
		at->Create(L"L_NormalAttack2", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"NormalAttack3", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack3.png");
		at->Create(L"R_NormalAttack3", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"NormalAttack3_L", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack3_L.png");
		at->Create(L"L_NormalAttack3", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Kick", L"..\\Resources\\TEXTURE\\RAMONA\\Kick.png");
		at->Create(L"R_Kick", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(310.0f / 5.0f, 70.0f), 5);
		at->Create(L"L_Kick", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(310.0f / 5.0f, 70.0f), 5);

		atlas
			= Resources::Load<Texture>(L"RoundKick", L"..\\Resources\\TEXTURE\\RAMONA\\RoundKick.png");
		at->Create(L"R_RoundKick", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(897.0f / 13.0f, 72.0f), 13, Vector2::Zero, 0.07f);
		at->Create(L"L_RoundKick", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(897.0f / 13.0f, 72.0f), 13, Vector2::Zero, 0.07f);

		atlas
			= Resources::Load<Texture>(L"BehindAttack", L"..\\Resources\\TEXTURE\\RAMONA\\BehindAttack.png");
		at->Create(L"R_BehindKick", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(240.0f / 6.0f, 69.0f), 6);
		at->Create(L"L_BehindKick", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(240.0f / 6.0f, 69.0f), 6);

		atlas
			= Resources::Load<Texture>(L"WeaponNormalAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponNormalAttack.png");
		at->Create(L"R_WeaponNormalAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(663.0f / 8.0f, 86.0f), 8);
		at->Create(L"L_WeaponNormalAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(663.0f / 8.0f, 86.0f), 8);

		atlas
			= Resources::Load<Texture>(L"WeaponDownAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponDownAttack.png");
		at->Create(L"R_WeaponDownAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(255.0f / 5.0f, 75.0f), 5);
		at->Create(L"L_WeaponDownAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(255.0f / 5.0f, 75.0f), 5);

		atlas
			= Resources::Load<Texture>(L"WeaponSideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponSideAttack.png");
		at->Create(L"R_WeaponSideAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(805.0f / 8.0f, 79.0f), 8);
		at->Create(L"L_WeaponSideAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(805.0f / 8.0f, 79.0f), 8);
		 
		atlas
			= Resources::Load<Texture>(L"WeaponStabAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponStabAttack.png");
		at->Create(L"R_WeaponStabAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(394.0f / 5.0f, 71.0f), 5);
		at->Create(L"L_WeaponStabAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(394.0f / 5.0f, 71.0f), 5);
		
		atlas
			= Resources::Load<Texture>(L"JumpDownAttack", L"..\\Resources\\TEXTURE\\RAMONA\\JumpDownAttack.png");
		at->Create(L"R_JumpDownAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(200.0f / 4.0f, 79.0f), 4, Vector2::Zero, 0.12f);
		atlas
			= Resources::Load<Texture>(L"JumpDownAttack_L", L"..\\Resources\\TEXTURE\\RAMONA\\JumpDownAttack_L.png");
		at->Create(L"L_JumpDownAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(200.0f / 4.0f, 79.0f), 4, Vector2::Zero, 0.12f);

		atlas
			= Resources::Load<Texture>(L"JumpSlideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\JumpSlideAttack.png");
		at->Create(L"R_JumpSlideAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(384.0f / 6.0f, 68.0f), 6, Vector2::Zero, 0.09f);
		atlas
			= Resources::Load<Texture>(L"JumpSlideAttack_L", L"..\\Resources\\TEXTURE\\RAMONA\\JumpSlideAttack_L.png");
		at->Create(L"L_JumpSlideAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(384.0f / 6.0f, 68.0f), 6, Vector2::Zero, 0.09f);

		atlas
			= Resources::Load<Texture>(L"RunJumpAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunJumpAttack.png");
		at->Create(L"R_RunJumpAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(581.0f / 7.0f, 89.0f), 7, Vector2::Zero, 0.07f);
		atlas
			= Resources::Load<Texture>(L"RunJumpAttack_L", L"..\\Resources\\TEXTURE\\RAMONA\\RunJumpAttack_L.png");
		at->Create(L"L_RunJumpAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(581.0f / 7.0f, 89.0f), 7, Vector2::Zero, 0.07f);

		atlas
			= Resources::Load<Texture>(L"RunWeaponAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunWeaponAttack.png");
		at->Create(L"R_RunWeaponAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(752.0f / 8.0f, 70.0f), 8);
		at->Create(L"L_RunWeaponAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(752.0f / 8.0f, 70.0f), 8);
		
		atlas
			= Resources::Load<Texture>(L"RunSlideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunSlideAttack.png");
		at->Create(L"R_RunSlideAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(328.0f / 5.0f, 66.0f), 5);
		atlas
			= Resources::Load<Texture>(L"RunSlideAttack_L", L"..\\Resources\\TEXTURE\\RAMONA\\RunSlideAttack_L.png");
		at->Create(L"L_RunSlideAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(328.0f / 5.0f, 66.0f), 5);

		atlas
			= Resources::Load<Texture>(L"Super", L"..\\Resources\\TEXTURE\\RAMONA\\Super.png");
		at->Create(L"R_Super", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(3913.0f / 31.0f, 126.0f), 31, Vector2::Zero, 0.06f);
		at->Create(L"L_Super", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(3913.0f / 31.0f, 126.0f), 31, Vector2::Zero, 0.06f);

		atlas
			= Resources::Load<Texture>(L"FireBall", L"..\\Resources\\TEXTURE\\RAMONA\\FireBall.png");
		at->Create(L"R_FireBall", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1144.0f / 13.0f, 70.0f), 13);
		at->Create(L"L_FireBall", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(1144.0f / 13.0f, 70.0f), 13);
		
		atlas
			= Resources::Load<Texture>(L"Stun", L"..\\Resources\\TEXTURE\\RAMONA\\Stun.png");
		at->Create(L"R_Stun", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(231.0f / 2.0f, 116.0f), 2, Vector2::Zero, 0.5f);
		at->Create(L"L_Stun", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(231.0f / 2.0f, 116.0f), 2, Vector2::Zero, 0.5f);

		atlas
			= Resources::Load<Texture>(L"BackStun", L"..\\Resources\\TEXTURE\\RAMONA\\BackStun.png");
		at->Create(L"R_BackStun", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(150.0f / 3.0f, 69.0f), 3, Vector2::Zero, 0.5f);
		at->Create(L"L_BackStun", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(150.0f / 3.0f, 69.0f), 3, Vector2::Zero, 0.5f);

		atlas
			= Resources::Load<Texture>(L"KnockDown", L"..\\Resources\\TEXTURE\\RAMONA\\KnockDown.png");
		at->Create(L"R_KnockDown", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(988.0f / 13.0f, 88.0f), 13);

		atlas
			= Resources::Load<Texture>(L"KnockDown_L", L"..\\Resources\\TEXTURE\\RAMONA\\KnockDown_L.png");
		at->Create(L"L_KnockDown", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1500.0f / 13.0f, 116.0f), 13);

		atlas
			= Resources::Load<Texture>(L"Downed", L"..\\Resources\\TEXTURE\\RAMONA\\Downed.png");
		at->Create(L"R_Downed", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);
		at->Create(L"L_Downed", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(462.0f / 4.0f, 116.0f), 4);

		atlas
			= Resources::Load<Texture>(L"GetUp", L"..\\Resources\\TEXTURE\\RAMONA\\GetUp.png");
		at->Create(L"R_GetUp", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1038.0f / 9.0f, 116.0f), 9);

		atlas
			= Resources::Load<Texture>(L"GetUp_L", L"..\\Resources\\TEXTURE\\RAMONA\\GetUp_L.png");
		at->Create(L"L_GetUp", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(1038.0f / 9.0f, 116.0f), 9);

		#pragma region Animation Path, Size
		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Walk", L"..\\Resources\\TEXTURE\\RAMONA\\Walk.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Walk", atlas, Vector2(0.0f, 0.0f), Vector2(210.0f / 6.0f, 68.0f), 6);
		//at->PlayAnimation(L"Walk", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Run", L"..\\Resources\\TEXTURE\\RAMONA\\Run.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Run", atlas, Vector2(0.0f, 0.0f), Vector2(424.0f / 8.0f, 67.0f), 8);
		//at->PlayAnimation(L"Run", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Jump", L"..\\Resources\\TEXTURE\\RAMONA\\Jump.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Jump", atlas, Vector2(0.0f, 0.0f), Vector2(432.0f / 9.0f, 78.0f), 9);
		//at->PlayAnimation(L"Jump", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"DJump", L"..\\Resources\\TEXTURE\\RAMONA\\DJump.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"DJump", atlas, Vector2(0.0f, 0.0f), Vector2(309.0f / 6.0f, 75.0f), 6);
		//at->PlayAnimation(L"DJump", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Guard", L"..\\Resources\\TEXTURE\\RAMONA\\Guard.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Guard", atlas, Vector2(0.0f, 0.0f), Vector2(219.0f / 5.0f, 70.0f), 5);
		//at->PlayAnimation(L"Guard", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Evade", L"..\\Resources\\TEXTURE\\RAMONA\\Evade.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Evade", atlas, Vector2(0.0f, 0.0f), Vector2(399.0f / 7.0f, 64.0f), 7);
		//at->PlayAnimation(L"Evade", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Downed", L"..\\Resources\\TEXTURE\\RAMONA\\Downed.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Downed", atlas, Vector2(0.0f, 0.0f), Vector2(292.0f / 4.0f, 69.0f), 4);
		//at->PlayAnimation(L"Downed", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Held", L"..\\Resources\\TEXTURE\\RAMONA\\Held_.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Held", atlas, Vector2(0.0f, 0.0f), Vector2(106.0f / 2.0f, 64.0f), 2);
		//at->PlayAnimation(L"Held", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Behind", L"..\\Resources\\TEXTURE\\RAMONA\\Behind.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Behind", atlas, Vector2(0.0f, 0.0f), Vector2(150.0f / 3.0f, 69.0f), 3);
		//at->PlayAnimation(L"Behind", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Front", L"..\\Resources\\TEXTURE\\RAMONA\\Front.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Front", atlas, Vector2(0.0f, 0.0f), Vector2(192.0f / 4.0f, 70.0f), 4);
		//at->PlayAnimation(L"Front", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Stun", L"..\\Resources\\TEXTURE\\RAMONA\\Stun.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Stun", atlas, Vector2(0.0f, 0.0f), Vector2(92.0f / 2.0f, 66.0f), 2);
		//at->PlayAnimation(L"Stun", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"KnockDown", L"..\\Resources\\TEXTURE\\RAMONA\\KnockDown.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"KnockDown", atlas, Vector2(0.0f, 0.0f), Vector2(988.0f / 13.0f, 88.0f), 13);
		//at->PlayAnimation(L"KnockDown", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Revived", L"..\\Resources\\TEXTURE\\RAMONA\\Revived.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Revived", atlas, Vector2(0.0f, 0.0f), Vector2(592.0f / 8.0f, 160.0f), 8);
		//at->PlayAnimation(L"Revived", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"GetUp", L"..\\Resources\\TEXTURE\\RAMONA\\GetUp.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"GetUp", atlas, Vector2(0.0f, 0.0f), Vector2(675.0f / 9.0f, 86.0f), 9);
		//at->PlayAnimation(L"GetUp", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"StageClear", L"..\\Resources\\TEXTURE\\RAMONA\\StageClear.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"StageClear", atlas, Vector2(0.0f, 0.0f), Vector2(364.0f / 7.0f, 83.0f), 7);
		//at->PlayAnimation(L"StageClear", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"StageExit", L"..\\Resources\\TEXTURE\\RAMONA\\StageExit.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"StageExit", atlas, Vector2(0.0f, 0.0f), Vector2(986.0f / 21.0f, 78.0f), 21);
		//at->PlayAnimation(L"StageExit", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"NormalAttack1", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"NormalAttack", atlas, Vector2(0.0f, 0.0f), Vector2(558.0f / 9.0f, 70.0f), 9);
		//at->PlayAnimation(L"NormalAttack", true);

		//// 공격 1,2,3 1애니메이션 진행중에 공격키 누르면 2 진행, 2 진행중에 공격키 누르면 3진행
		//std::shared_ptr<Texture> atlas
		//= Resources::Load<Texture>(L"NormalAttack1", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack1.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"NormalAttack1", atlas, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3);
		//at->PlayAnimation(L"NormalAttack1", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"NormalAttack2", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack2.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"NormalAttack2", atlas, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3);
		//at->PlayAnimation(L"NormalAttack2", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"NormalAttack3", L"..\\Resources\\TEXTURE\\RAMONA\\NormalAttack3.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"NormalAttack3", atlas, Vector2(0.0f, 0.0f), Vector2(186.0f / 3.0f, 70.0f), 3);
		//at->PlayAnimation(L"NormalAttack3", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Kick", L"..\\Resources\\TEXTURE\\RAMONA\\Kick.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Kick", atlas, Vector2(0.0f, 0.0f), Vector2(310.0f / 5.0f, 70.0f), 5);
		//at->PlayAnimation(L"Kick", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponNormalAttack", L"..\\Resources\\TEXTURE\\RAMONA\\NormalWeaponAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponNormalAttack", atlas, Vector2(0.0f, 0.0f), Vector2(663.0f / 8.0f, 86.0f), 8);
		//at->PlayAnimation(L"WeaponNormalAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"RunSlideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunSlideAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"RunSlideAttack", atlas, Vector2(0.0f, 0.0f), Vector2(328.0f / 5.0f, 66.0f), 5);
		//at->PlayAnimation(L"RunSlideAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"RunWeaponAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunWeaponAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"RunWeaponAttack", atlas, Vector2(0.0f, 0.0f), Vector2(752.0f / 8.0f, 70.0f), 8);
		//at->PlayAnimation(L"RunWeaponAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"BehindAttack", L"..\\Resources\\TEXTURE\\RAMONA\\BehindAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"BehindAttack", atlas, Vector2(0.0f, 0.0f), Vector2(240.0f / 6.0f, 69.0f), 6);
		//at->PlayAnimation(L"BehindAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponStabAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponStabAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponStabAttack", atlas, Vector2(0.0f, 0.0f), Vector2(394.0f / 5.0f, 71.0f), 5);
		//at->PlayAnimation(L"WeaponStabAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponDownAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponDownAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponDownAttack", atlas, Vector2(0.0f, 0.0f), Vector2(255.0f / 5.0f, 75.0f), 5);
		//at->PlayAnimation(L"WeaponDownAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"JumpSlideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\JumpSlideAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"JumpSlideAttack", atlas, Vector2(0.0f, 0.0f), Vector2(384.0f / 6.0f, 68.0f), 6);
		//at->PlayAnimation(L"JumpSlideAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"RunJumpAttack", L"..\\Resources\\TEXTURE\\RAMONA\\RunJumpAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"RunJumpAttack", atlas, Vector2(0.0f, 0.0f), Vector2(581.0f / 7.0f, 89.0f), 7);
		//at->PlayAnimation(L"RunJumpAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponLand", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponLand.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponLand", atlas, Vector2(0.0f, 0.0f), Vector2(612.0f / 9.0f, 78.0f), 9);
		//at->PlayAnimation(L"WeaponLand", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponSideAttack", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponSideAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponSideAttack", atlas, Vector2(0.0f, 0.0f), Vector2(805.0f / 8.0f, 79.0f), 8);
		//at->PlayAnimation(L"WeaponSideAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"JumpDownAttack", L"..\\Resources\\TEXTURE\\RAMONA\\JumpDownAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"JumpDownAttack", atlas, Vector2(0.0f, 0.0f), Vector2(200.0f / 4.0f, 79.0f), 4);
		//at->PlayAnimation(L"JumpDownAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"RunJumpDownAttck", L"..\\Resources\\TEXTURE\\RAMONA\\RunJumpDownAttack.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"RunJumpDownAttack", atlas, Vector2(0.0f, 0.0f), Vector2(372.0f / 6.0f, 82.0f), 6);
		//at->PlayAnimation(L"RunJumpDownAttack", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"JumpDownHit", L"..\\Resources\\TEXTURE\\RAMONA\\JumpDownHit.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"JumpDownHit", atlas, Vector2(0.0f, 0.0f), Vector2(329.0f / 7.0f, 76.0f), 7);
		//at->PlayAnimation(L"JumpDownHit", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"RoundKick", L"..\\Resources\\TEXTURE\\RAMONA\\RoundKick.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"RoundKick", atlas, Vector2(0.0f, 0.0f), Vector2(897.0f / 13.0f, 72.0f), 13);
		//at->PlayAnimation(L"RoundKick", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"FireBall", L"..\\Resources\\TEXTURE\\RAMONA\\FireBall.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"FireBall", atlas, Vector2(0.0f, 0.0f), Vector2(1144.0f / 13.0f, 70.0f), 13);
		//at->PlayAnimation(L"FireBall", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"NormalGlowCombo", L"..\\Resources\\TEXTURE\\RAMONA\\NormalGlowCombo.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"NormalGlowCombo", atlas, Vector2(0.0f, 0.0f), Vector2(434.0f / 7.0f, 71.0f), 7);
		//at->PlayAnimation(L"NormalGlowCombo", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"WeaponGlowCombo", L"..\\Resources\\TEXTURE\\RAMONA\\WeaponGlowCombo.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"WeaponGlowCombo", atlas, Vector2(0.0f, 0.0f), Vector2(839.0f / 10.0f, 84.0f), 10);
		//at->PlayAnimation(L"WeaponGlowCombo", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Counter", L"..\\Resources\\TEXTURE\\RAMONA\\Counter.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Counter", atlas, Vector2(0.0f, 0.0f), Vector2(1596.0f / 17.0f, 87.0f), 17);
		//at->PlayAnimation(L"Counter", true);

		//std::shared_ptr<Texture> atlas
		//	= Resources::Load<Texture>(L"Super", L"..\\Resources\\TEXTURE\\RAMONA\\Super.png");
		//Animator* at = player->AddComponent<Animator>();
		//at->Create(L"Super", atlas, Vector2(0.0f, 0.0f), Vector2(3913.0f / 31.0f, 126.0f), 31);
		//at->PlayAnimation(L"Super", true);
		#pragma endregion
		
		#pragma endregion

		#pragma region 이벤트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		                                                    // 이벤트
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		at = GetOwner()->GetComponent<Animator>();

		//at->StartEvent(L"L_Jump") = std::bind(&RamonaScript::JumpStart, this);
		//at->StartEvent(L"R_Jump") = std::bind(&RamonaScript::JumpStart, this);

		at->CompleteEvent(L"L_Evade") = std::bind(&RamonaScript::EvadeComplete, this);
		at->CompleteEvent(L"R_Evade") = std::bind(&RamonaScript::EvadeComplete, this);

		at->CompleteEvent(L"L_NormalAttack1") = std::bind(&RamonaScript::NormalAttackComplete, this);
		at->CompleteEvent(L"R_NormalAttack1") = std::bind(&RamonaScript::NormalAttackComplete, this);
		at->CompleteEvent(L"L_NormalAttack2") = std::bind(&RamonaScript::NormalAttackComplete, this);
		at->CompleteEvent(L"R_NormalAttack2") = std::bind(&RamonaScript::NormalAttackComplete, this);
		at->CompleteEvent(L"L_NormalAttack3") = std::bind(&RamonaScript::NormalAttackComplete, this);
		at->CompleteEvent(L"R_NormalAttack3") = std::bind(&RamonaScript::NormalAttackComplete, this);

		at->CompleteEvent(L"L_Kick") = std::bind(&RamonaScript::KickComplete, this);
		at->CompleteEvent(L"R_Kick") = std::bind(&RamonaScript::KickComplete, this);
		at->CompleteEvent(L"L_RoundKick") = std::bind(&RamonaScript::KickComplete, this);
		at->CompleteEvent(L"R_RoundKick") = std::bind(&RamonaScript::KickComplete, this);
		at->CompleteEvent(L"L_BehindKick") = std::bind(&RamonaScript::KickComplete, this);
		at->CompleteEvent(L"R_BehindKick") = std::bind(&RamonaScript::KickComplete, this);

		at->CompleteEvent(L"L_WeaponNormalAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"R_WeaponNormalAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"L_WeaponDownAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"R_WeaponDownAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"L_WeaponSideAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"R_WeaponSideAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"L_WeaponStabAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);
		at->CompleteEvent(L"R_WeaponStabAttack") = std::bind(&RamonaScript::WeaponAttackComplete, this);

		at->CompleteEvent(L"L_JumpDownAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);
		at->CompleteEvent(L"R_JumpDownAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);
		at->CompleteEvent(L"L_JumpSlideAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);
		at->CompleteEvent(L"R_JumpSlideAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);
		at->CompleteEvent(L"L_RunJumpAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);
		at->CompleteEvent(L"R_RunJumpAttack") = std::bind(&RamonaScript::JumpAttackComplete, this);

		at->CompleteEvent(L"L_RunWeaponAttack") = std::bind(&RamonaScript::RunAttackComplete, this);
		at->CompleteEvent(L"R_RunWeaponAttack") = std::bind(&RamonaScript::RunAttackComplete, this);
		at->CompleteEvent(L"L_RunSlideAttack") = std::bind(&RamonaScript::RunAttackComplete, this);
		at->CompleteEvent(L"R_RunSlideAttack") = std::bind(&RamonaScript::RunAttackComplete, this);
		
		at->CompleteEvent(L"L_FireBall") = std::bind(&RamonaScript::FireBallComplete, this);
		at->CompleteEvent(L"R_FireBall") = std::bind(&RamonaScript::FireBallComplete, this);
		at->CompleteEvent(L"L_Super") = std::bind(&RamonaScript::SuperComplete, this);
		at->CompleteEvent(L"R_Super") = std::bind(&RamonaScript::SuperComplete, this);

		at->CompleteEvent(L"L_Stun") = std::bind(&RamonaScript::StunComplete, this);
		at->CompleteEvent(L"R_Stun") = std::bind(&RamonaScript::StunComplete, this);

		at->CompleteEvent(L"L_KnockDown") = std::bind(&RamonaScript::KnockDownComplete, this);
		at->CompleteEvent(L"R_KnockDown") = std::bind(&RamonaScript::KnockDownComplete, this);

		at->CompleteEvent(L"L_Downed") = std::bind(&RamonaScript::DownedComplete, this);
		at->CompleteEvent(L"R_Downed") = std::bind(&RamonaScript::DownedComplete, this);

		at->CompleteEvent(L"L_GetUp") = std::bind(&RamonaScript::GetUpComplete, this);
		at->CompleteEvent(L"R_GetUp") = std::bind(&RamonaScript::GetUpComplete, this);

		#pragma endregion

		#pragma region 속성
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 속성
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mAttribute.mHp = 100.f;

        #pragma endregion

		#pragma region 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mBodyCd = this->GetOwner()->AddComponent<Collider2D>();
		mBodyCd->SetSize(Vector2(0.2f, 0.2f));
		mBodyCd->SetCenter(Vector2(0.0f, 0.0f));
		mBodyCd->SetActivation(eColliderActivation::Active);
		mBodyCd->SetIsBody(true);

		mUpperCd = this->GetOwner()->AddComponent<Collider2D>();
		mUpperCd->SetSize(Vector2(0.2f, 0.1f));
		mUpperCd->SetCenter(Vector2(0.2f, 0.08f));
		mUpperCd->SetActivation(eColliderActivation::InActive);

		mLowerCd = this->GetOwner()->AddComponent<Collider2D>();
		mLowerCd->SetSize(Vector2(0.2f, 0.1f));
		mLowerCd->SetCenter(Vector2(0.2f, -0.2f));
		mLowerCd->SetActivation(eColliderActivation::InActive);

		mBothCd = this->GetOwner()->AddComponent<Collider2D>();
		mBothCd->SetSize(Vector2(0.2f, 0.3f));
		mBothCd->SetCenter(Vector2(0.3f, 0.0f));
		mBothCd->SetActivation(eColliderActivation::InActive);
	
		mBackCd = this->GetOwner()->AddComponent<Collider2D>();
		mBackCd->SetSize(Vector2(0.1f, 0.1f));
		mBackCd->SetCenter(Vector2(-0.3f, -0.2f));
		mBackCd->SetActivation(eColliderActivation::InActive);

		mAllCd = this->GetOwner()->AddComponent<Collider2D>();
		mAllCd->SetSize(Vector2(0.35f, 0.25f));
		mAllCd->SetCenter(Vector2(0.0f, -0.0f));
		mAllCd->SetActivation(eColliderActivation::InActive);

		#pragma endregion
}

	void RamonaScript::Update()
	{

		if (mOnFlickering == true)
		{
			mFlickeringCurTime += Time::DeltaTime();
			mFlickeringMaxTime -= Time::DeltaTime();
			if (mFlickeringMaxTime <= 0.0f && GetOwner()->mIsEffectFlickering == false)
			{
				GetOwner()->mIsEffectFlickering = false;
				mOnFlickering = false;
			}

			else 
			{
				if (GetOwner()->mIsEffectFlickering == true)
				{
					if (mFlickeringCurTime >= mFlickeringTickTime)
					{
						mFlickeringCurTime = 0.0f;
						GetOwner()->mIsEffectFlickering = false;
					}
				}
				if (GetOwner()->mIsEffectFlickering == false)
				{
					if (mFlickeringCurTime >= mFlickeringTickTime)
					{
						mFlickeringCurTime = 0.0f;
						GetOwner()->mIsEffectFlickering = true;
					}
				}
			}
		}

		#pragma region FSM
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// FSM
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mPreviousState != mState)
		{
			Animator* at = this->GetOwner()->GetComponent<Animator>();

			switch (mState)
			{
			case ePlayerState::L_Idle:
				L_idle();
				break;
			case ePlayerState::R_Idle:
				R_idle();
				break;

			case ePlayerState::L_Walk:
				L_walk();
				break;
			case ePlayerState::R_Walk:
				R_walk();
				break;

			case ePlayerState::L_Run:
				L_run();
				break;
			case ePlayerState::R_Run:
				R_run();
				break;

			case ePlayerState::L_Jump:
				L_jump();
				break;
			case ePlayerState::R_Jump:
				R_jump();
				break;
			case ePlayerState::L_DJump:
				L_djump();
				break;
			case ePlayerState::R_DJump:
				R_djump();
				break;

			case ePlayerState::L_Guard:
				L_guard();
				break;
			case ePlayerState::R_Guard:
				R_guard();
				break;

			case ePlayerState::L_Evade:
				L_evade();
				break;
			case ePlayerState::R_Evade:
				R_evade();
				break;

			case ePlayerState::L_NormalAttack1:
				L_normalattack1();
				break;
			case ePlayerState::R_NormalAttack1:
				R_normalattack1();
				break;
			case ePlayerState::L_NormalAttack2:
				L_normalattack2();
				break;
			case ePlayerState::R_NormalAttack2:
				R_normalattack2();
				break;
			case ePlayerState::L_NormalAttack3:
				L_normalattack3();
				break;
			case ePlayerState::R_NormalAttack3:
				R_normalattack3();
				break;

			case ePlayerState::R_Kick:
				R_kick();
				break;
			case ePlayerState::L_Kick:
				L_kick();
				break;
			case ePlayerState::R_RoundKick:
				R_roundkick();
				break;
			case ePlayerState::L_RoundKick:
				L_roundkick();
				break;
			case ePlayerState::R_BehindKick:
				R_behindkick();
				break;
			case ePlayerState::L_BehindKick:
				L_behindkick();
				break;

			case ePlayerState::R_WeaponNormalAttack:
				R_weaponnormalattack();
				break;
			case ePlayerState::L_WeaponNormalAttack:
				L_weaponnormalattack();
				break;
			case ePlayerState::R_WeaponDownAttack:
				R_weapondownattack();
				break;
			case ePlayerState::L_WeaponDownAttack:
				L_weapondownattack();
				break;
			case ePlayerState::R_WeaponSideAttack:
				R_weaponsideattack();
				break;
			case ePlayerState::L_WeaponSideAttack:
				L_weaponsideattack();
				break;
			case ePlayerState::R_WeaponStabAttack:
				R_weaponstabattack();
				break;
			case ePlayerState::L_WeaponStabAttack:
				L_weaponstabattack();
				break;

			case ePlayerState::R_JumpDownAttack:
				R_jumpdownattack();
				break;
			case ePlayerState::L_JumpDownAttack:
				L_jumpdownattack();
				break;
			case ePlayerState::R_JumpSlideAttack:
				R_jumpslideattack();
				break;
			case ePlayerState::L_JumpSlideAttack:
				L_jumpslideattack();
				break;
			case ePlayerState::R_RunJumpAttack:
				R_runjumpattack();
				break;
			case ePlayerState::L_RunJumpAttack:
				L_runjumpattack();
				break;

			case ePlayerState::R_RunWeaponAttack:
				R_runweaponattack();
				break;
			case ePlayerState::L_RunWeaponAttack:
				L_runweaponattack();
				break;
			case ePlayerState::R_RunSlideAttack:
				R_runslideattack();
				break;
			case ePlayerState::L_RunSlideAttack:
				L_runslideattack();
				break;

			case ePlayerState::R_FireBall:
				R_fireball();
				break;
			case ePlayerState::L_FireBall:
				L_fireball();
				break;
			case ePlayerState::R_Super:
				R_super();
				break;
			case ePlayerState::L_Super:
				L_super();
				break;

			case ePlayerState::R_Stun:
				R_stun();
				break;
			case ePlayerState::L_Stun:
				L_stun();
				break;
			case ePlayerState::R_BackStun:
				R_backstun();
				break;
			case ePlayerState::L_BackStun:
				L_backstun();
				break;
			case ePlayerState::R_KnockDown:
				R_knockdown();
				break;
			case ePlayerState::L_KnockDown:
				L_knockdown();
				break;

			case ePlayerState::R_Downed:
				R_downed();
				break;
			case ePlayerState::L_Downed:
				L_downed();
				break;

			case ePlayerState::R_GetUp:
				R_getup();
				break;
			case ePlayerState::L_GetUp:
				L_getup();
				break;
			}
		}

		mPreviousState = mState;
		// 이전 상태 설정
		// 여기 아래에서부터 상태 변화가 진행되어야
		// 다음번 Update 부분으로 들어올 때, mState의 switch문 조건인
		// 이전 상태와 현재 상태를 비교해서 다른 경우, case에 따라 작동하게 됨
#pragma endregion

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 속성
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mAttribute.mHp <= 0.0f)
		{
			int a = 0;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 콜라이더
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mDirection == eDirection::L)
		{
			//std::vector<Collider2D*> comps
			//	= this->GetOwner()->GetComponents<Collider2D>();

			//mUpperCd = comps[1];
			mUpperCd->SetCenter(Vector2(-0.2f, 0.08f));

			//mLowerCd = comps[2];
			mLowerCd->SetCenter(Vector2(-0.2f, -0.2f));

			//mBothCd = comps[3];
			mBothCd->SetCenter(Vector2(-0.3f, 0.0f));

			mBackCd->SetCenter(Vector2(0.3f, -0.2f));
		}
		else
		{
			mUpperCd->SetCenter(Vector2(0.2f, 0.08f));

			mLowerCd->SetCenter(Vector2(0.2f, -0.2f));

			mBothCd->SetCenter(Vector2(0.3f, 0.0f));

			mBackCd->SetCenter(Vector2(-0.3f, -0.2f));
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 위치
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//// 좌우상하 이동제한
		//{
		//	if (pos.x <= -2.89)// 좌
		//	{
		//		pos.x = -2.89;
		//	}

		//	if (pos.y >= 0.75)// 상
		//	{
		//		pos.y = 0.75;
		//	}

		//	if (pos.x >= 2.88)// 우
		//	{
		//		pos.x = 2.88;
		//	}

		//	if (pos.y <= -1.29)// 하
		//	{
		//		pos.y = -1.29;
		//	}

		//	tr->SetPosition(pos);
		//}


		if (CanChangeState())// 독립성이 부여되어야 하는 상태들은 여기서 걸러짐
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 좌우 이동
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 좌
			if (Input::GetKey(eKeyCode::LEFT))// 좌표 지속 이동
			{
				mDirection = eDirection::L;

				if (NoneAnimationCondition())
				{
					mState = ePlayerState::L_Walk;
				}

				if (CanMoveCondition())// 좌우 움직임 제한하지 않는 스킬인지 확인
				{
					pos.x -= mWalkSpeed * Time::DeltaTime();
					tr->SetPosition(pos);
				}
			}

			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				mDirection = eDirection::L;

				if (NoneAnimationCondition())
					mState = ePlayerState::L_Walk;
			}

			if (Input::GetKeyUp(eKeyCode::LEFT))// 키 입력이 끝나고 이동하지 않을 때, Idle 상태로 전환
			{
				mDirection = eDirection::L;

				if (NoneAnimationCondition())
					mState = ePlayerState::L_Idle;
			}

			// 우
			if (Input::GetKey(eKeyCode::RIGHT))// 좌표 지속 이동
			{
				mDirection = eDirection::R;

				if (NoneAnimationCondition())
					mState = ePlayerState::R_Walk;

				if (CanMoveCondition())// 좌우 움직임 제한하지 않는 스킬인지 확인
				{
					pos.x += mWalkSpeed * Time::DeltaTime();
					tr->SetPosition(pos);
					
					//Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
					//rb->SetGround(true);
					//rb->AddForce(Vector2(600.0f, 0.0f));

					//Vector2 velocity = rb->GetVelocity();
					//velocity.y += 0.1f;
					//rb->SetVelocity(velocity);
				}
			}

			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				mDirection = eDirection::R;

				if (NoneAnimationCondition())
					mState = ePlayerState::R_Walk;
			}

			if (Input::GetKeyUp(eKeyCode::RIGHT))// 키 입력이 끝나고 이동하지 않을 때, Idle 상태로 전환
			{
				mDirection = eDirection::R;

				if (NoneAnimationCondition())
					mState = ePlayerState::R_Idle;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 상하 이동
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 하
			if (Input::GetKey(eKeyCode::DOWN))
			{
				if (NoneAnimationCondition())
				{
					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Walk;
					}
					else
					{
						mState = ePlayerState::R_Walk;
					}
				}

				if (CanMoveCondition())// 상하 움직임 제한하지 않는 스킬인지 확인
				{
					pos.y -= mWalkSpeed * Time::DeltaTime();
					tr->SetPosition(pos);
				}
			}
			if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				if (NoneAnimationCondition())
				{
					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Walk;
					}
					else
					{
						mState = ePlayerState::R_Walk;
					}
				}
			}
			if (Input::GetKeyUp(eKeyCode::DOWN))// 키 입력이 끝나고 이동하지 않을 때, Idle 상태로 전환
			{
				if (NoneAnimationCondition())
				{
					if (!(Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT)))// 좌우키 입력이 있는 상태라면 Idle 상태로 전환시킬 필요가 없음
					{
						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_Idle;
						}
						else
						{
							mState = ePlayerState::R_Idle;
						}
					}
				}
			}

			// 상
			if (Input::GetKey(eKeyCode::UP))
			{
				if (NoneAnimationCondition())
				{
					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Walk;
					}
					else
					{
						mState = ePlayerState::R_Walk;
					}
				}

				if (CanMoveCondition())// 상하 움직임 제한하지 않는 스킬인지 확인
				{
					pos.y += mWalkSpeed * Time::DeltaTime();
					tr->SetPosition(pos);
				}
			}
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				if (NoneAnimationCondition())
				{
					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Walk;
					}
					else
					{
						mState = ePlayerState::R_Walk;
					}
				}
			}
			if (Input::GetKeyUp(eKeyCode::UP))// 키 입력이 끝나고 이동하지 않을 때, Idle 상태로 전환
			{
				if (NoneAnimationCondition())
				{
					if (!(Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT)))// 좌우키 입력이 있는 상태라면 Idle 상태로 전환시킬 필요가 없음
					{
						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_Idle;
						}
						else
						{
							mState = ePlayerState::R_Idle;
						}
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 달리기
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Input::GetKey(eKeyCode::LSHIFT))
			{
				if (mState == ePlayerState::L_Walk || mState == ePlayerState::R_Walk)
				{
					mIsRun = true;

					if (mDirection == eDirection::L)
					{
						if (Input::GetKey(eKeyCode::UP))
						{
							pos.y += mRunSpeed2 * Time::DeltaTime();
							tr->SetPosition(pos);
						}
						else if (Input::GetKey(eKeyCode::DOWN))
						{
							pos.y -= mRunSpeed2 * Time::DeltaTime();
							tr->SetPosition(pos);
						}
						else
						{
							pos.x -= mRunSpeed1 * Time::DeltaTime();
							tr->SetPosition(pos);
						}

						mState = ePlayerState::L_Run;
					}
					else
					{
						if (Input::GetKey(eKeyCode::UP))
						{
							pos.y += mRunSpeed2 * Time::DeltaTime();
							tr->SetPosition(pos);
						}
						else if (Input::GetKey(eKeyCode::DOWN))
						{
							pos.y -= mRunSpeed2 * Time::DeltaTime();
							tr->SetPosition(pos);
						}
						else
						{
							pos.x += mRunSpeed1 * Time::DeltaTime();
							tr->SetPosition(pos);
						}

						mState = ePlayerState::R_Run;
					}
				}
			}

			if (Input::GetKeyUp(eKeyCode::LSHIFT))
			{
				mIsRun = false;

				if (mState == ePlayerState::L_Run || mState == ePlayerState::R_Run)
				{
					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Walk;
					}
					else
					{
						mState = ePlayerState::R_Walk;
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 점프
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Input::GetKeyDown(eKeyCode::SPACE) && CanJumpCondition())
			{
				mIsJump = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_Jump;
				}
				else
				{
					mState = ePlayerState::R_Jump;
				}
			}

			if (mIsJump == true)
			{
				if (mJumpStartPosY == -100.0f)// 점프 애니메이션 첫 시작할 때만 불러오는 조건
				{
					// 점프 관련 기술 상태 변수들 초기화를 통한 오류 방지
					mIsJumpDownAttack = false;
					mIsJumpSlideAttack = false;
					mIsRunJumpAttack = false;

					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					mJumpStartPosY = pos.y;

					if (Input::GetKey(eKeyCode::LSHIFT))// 달릴 때, 점프 높이 더 높게 수정
					{
						mJumpHeight = mDJumpHeight;
					}
					else// 달리지 않을 때, 점프 높이 원래 수치로 조정
					{
						mJumpHeight = 1.8f;
					}
				}

				mJumpTime += Time::DeltaTime();// 점프 체공 시간

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 점프 상승 구간
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (mJumpTime < mJumpHalfTime)
				{
					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					pos.y += mJumpHeight * Time::DeltaTime();
					tr->SetPosition(pos);

					if (Input::GetKey(eKeyCode::LSHIFT))// 달리기 키를 누른 상태에서 점프는 더 멀리 가도록 조정 (상승 하는 경우)
					{
						//mIsRun = true;

						if (mDirection == eDirection::L)
						{
							if (Input::GetKey(eKeyCode::UP))
							{
								pos.y += mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else if (Input::GetKey(eKeyCode::DOWN))
							{
								pos.y -= mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else
							{
								pos.x -= mRunSpeed1 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
						}
						else
						{
							if (Input::GetKey(eKeyCode::UP))
							{
								pos.y += mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else if (Input::GetKey(eKeyCode::DOWN))
							{
								pos.y -= mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else
							{
								pos.x += mRunSpeed1 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
						}
					}

					// JumpDownAttack: 점프 중 + W (공격 성공 시, JumpDownHit 애니메이션 실행 후 마저 착지)
					if (Input::GetKeyDown(eKeyCode::W) && mIsJumpDownAttack == false && CanAttackCondition())
					{
						mIsJumpDownAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_JumpDownAttack;
						}
						else
						{
							mState = ePlayerState::R_JumpDownAttack;
						}
					}
					// JumpSlideAttack: 점프 중 + E
					if (Input::GetKeyDown(eKeyCode::E) && mIsJumpSlideAttack == false && CanAttackCondition())
					{
						mIsJumpSlideAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_JumpSlideAttack;
						}
						else
						{
							mState = ePlayerState::R_JumpSlideAttack;
						}
					}
					// JumpSlideAttack: 점프 중 + D
					if (Input::GetKey(eKeyCode::LSHIFT) && Input::GetKeyDown(eKeyCode::D) && mIsJumpSlideAttack == false && CanAttackCondition())
					{
						mIsJumpSlideAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_RunJumpAttack;
						}
						else
						{
							mState = ePlayerState::R_RunJumpAttack;
						}
					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 점프 하락 구간
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				else
				{
					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					pos.y -= mJumpHeight * Time::DeltaTime();
					tr->SetPosition(pos);

					if (pos.y <= mJumpStartPosY)// 좌표 하락하다가 점프 시작한 y좌표 위치에 도달(점프를, 좌표를 멈춰야 함)
					{
						Transform* tr = GetOwner()->GetComponent<Transform>();
						Vector3 pos = tr->GetPosition();
						Vector3 tempPos = Vector3(0.0f, mJumpStartPosY, 0.0f);
						pos.y = tempPos.y;
						tr->SetPosition(pos);// 점프 시작 위치로 강제 이동

						// 점프 관련 변수 초기화
						mJumpStartPosY = -100.0f;
						mJumpTime = 0.0f;
						mIsJump = false;
						mIsDJump = false;

						// 점프 관련 기술들도 착지하면 초기화 해줘야 함
						mIsJumpDownAttack = false;
						mIsJumpSlideAttack = false;
						mIsRunJumpAttack = false;

						// 점프 끝난 직후 이동이 있다면 mState가 알아서 바뀌지만
						// 점프 끝난 직후 이동이 없다면 mState를 아래와 같이 Jump에서 Idle로 전환 
						if (!Input::GetKey(eKeyCode::LEFT) || !Input::GetKey(eKeyCode::RIGHT))
						{
							if (mDirection == eDirection::L)
							{
								mState = ePlayerState::L_Idle;
							}
							else
							{
								mState = ePlayerState::R_Idle;
							}
						}
					}

					if (Input::GetKey(eKeyCode::LSHIFT))// 달리기 키를 누른 상태에서 점프는 더 멀리 가도록 조정 (하락하는 경우)
					{
						//mIsRun = true;

						if (mDirection == eDirection::L)
						{
							if (Input::GetKey(eKeyCode::UP))
							{
								pos.y += mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else if (Input::GetKey(eKeyCode::DOWN))
							{
								pos.y -= mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else
							{
								pos.x -= mRunSpeed1 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
						}
						else
						{
							if (Input::GetKey(eKeyCode::UP))
							{
								pos.y += mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else if (Input::GetKey(eKeyCode::DOWN))
							{
								pos.y -= mRunSpeed2 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
							else
							{
								pos.x += mRunSpeed1 * Time::DeltaTime();
								tr->SetPosition(pos);
							}
						}
					}

					// JumpDownAttack: 점프 중 + W (공격 성공 시, JumpDownHit 애니메이션 실행 후 마저 착지)
					if (Input::GetKeyDown(eKeyCode::W) && mIsJumpDownAttack == false && mIsJump == true && mIsDJump == true && CanAttackCondition())
					{
						mIsJumpDownAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_JumpDownAttack;
						}
						else
						{
							mState = ePlayerState::R_JumpDownAttack;
						}
					}
					// JumpSlideAttack: 점프 중 + E
					if (Input::GetKeyDown(eKeyCode::E) && mIsJumpSlideAttack == false && mIsJump == true && mIsDJump == true && CanAttackCondition())
					{
						mIsJumpSlideAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_JumpSlideAttack;
						}
						else
						{
							mState = ePlayerState::R_JumpSlideAttack;
						}
					}
					// RunJumpAttack: 점프 중 + D
					if (Input::GetKey(eKeyCode::LSHIFT) && Input::GetKeyDown(eKeyCode::D) && mIsJumpSlideAttack == false && mIsJump == true && mIsDJump == true && CanAttackCondition())
					{
						mIsJumpSlideAttack = true;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_RunJumpAttack;
						}
						else
						{
							mState = ePlayerState::R_RunJumpAttack;
						}
					}
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 더블 점프
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				if (Input::GetKeyDown(eKeyCode::SPACE) && mJumpTime > 0.01f)// 점프 중 더블 점프가 발동되는 조건
				{
					if (mIsDJump == false)
					{
						mIsDJump = true;
						mJumpTime = 0.0f;

						if (mDirection == eDirection::L)
						{
							mState = ePlayerState::L_DJump;
						}
						else
						{
							mState = ePlayerState::R_DJump;
						}
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 가드
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Input::GetKey(eKeyCode::Q))
			{
				if (mState == ePlayerState::L_Idle || mState == ePlayerState::R_Idle || mState == ePlayerState::L_Walk || mState == ePlayerState::R_Walk)
				{
					mIsGuard = true;
					//mBodyCd->SetActivation(eColliderActivation::InActive);

					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Guard;
					}
					else
					{
						mState = ePlayerState::R_Guard;
					}
				}
			}
			if (Input::GetKeyUp(eKeyCode::Q) && mIsGuard == true)
			{
				mIsGuard = false;
				mBodyCd->SetActivation(eColliderActivation::Active);

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_Idle;
				}
				else
				{
					mState = ePlayerState::R_Idle;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 회피
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Input::GetKeyDown(eKeyCode::F))
			{
				if (mIsJump == false && mIsDJump == false)
				{
					mIsEvade = true;

					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_Evade;
					}
					else
					{
						mState = ePlayerState::R_Evade;
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	// 평타
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 첫번째 공격
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (Input::GetKeyDown(eKeyCode::W) && mIsNormalAttack3 == false && mIsJump == false && mIsDJump == false && CanAttackCondition())// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsNormalAttack1 = true;
				mIsNormalAttack2 = false;
				mIsNormalAttack3 = false;
				//mCanNormalAttack2 = false;
				//mCanNormalAttack3 = false;
				mNormalAttack2Time = 0.0f;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_NormalAttack1;
				}
				else
				{
					mState = ePlayerState::R_NormalAttack1;
				}
			}

			// 오류 방지 1 
			// 공격 하지 않을 때는 공격 관련 변수 모두 초기화
			if (mIsNormalAttack1 == false && mIsNormalAttack2 == false && mIsNormalAttack3 == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsNormalAttack1 = false;
				mIsNormalAttack2 = false;
				mIsNormalAttack3 = false;
				mCanNormalAttack2 = false;
				mCanNormalAttack3 = false;
				mNormalAttack2Time = 0.0f;
			}

			// 오류 방지 2
			// 공격 하지 않을 때는 공격 관련 변수 모두 초기화
			if (!(mState == ePlayerState::L_NormalAttack1 || mState == ePlayerState::R_NormalAttack1
				|| mState == ePlayerState::L_NormalAttack2 || mState == ePlayerState::R_NormalAttack2
				|| mState == ePlayerState::L_NormalAttack3 || mState == ePlayerState::R_NormalAttack3))
			{
				mIsNormalAttack1 = false;
				mIsNormalAttack2 = false;
				mIsNormalAttack3 = false;
				mCanNormalAttack2 = false;
				mCanNormalAttack3 = false;
				mNormalAttack2Time = 0.0f;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 두번째 공격 
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 두번째 공격 조건
			if (Input::GetKeyUp(eKeyCode::W) && mIsNormalAttack1 == true && mIsNormalAttack2 == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mCanNormalAttack2 = true;
			}

			// 두번째 공격
			if (mCanNormalAttack2 == true && Input::GetKeyDown(eKeyCode::W) && mIsNormalAttack2 == false && mIsNormalAttack3 == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsNormalAttack1 = false;
				mIsNormalAttack2 = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_NormalAttack2;
				}
				else
				{
					mState = ePlayerState::R_NormalAttack2;
				}

			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 세번째 공격 
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 세번째 공격 조건을 위한 시간 측정
			if (mIsNormalAttack2)
			{
				mNormalAttack2Time += Time::DeltaTime();
			}

			// 세번째 공격 조건
			if (Input::GetKeyUp(eKeyCode::W) && mIsNormalAttack1 == false && mIsNormalAttack2 == true && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				if (mNormalAttack2Time > 0.004f)// 2 동작이 실행되자마자 바로 3 동작이 실행되지 않도록 시간 차이를 의도적으로 설정
				{
					mCanNormalAttack3 = true;
				}
			}

			// 세번째 공격
			if (mCanNormalAttack3 == true && Input::GetKeyDown(eKeyCode::W) && mIsNormalAttack3 == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsNormalAttack2 = false;
				mNormalAttack2Time = 0.0f;
				mIsNormalAttack3 = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_NormalAttack3;
				}
				else
				{
					mState = ePlayerState::R_NormalAttack3;
				}

			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 발차기
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Kick: E
			if (mIsRun == false && Input::GetKeyDown(eKeyCode::E) && mIsKickAttack == false && mIsRoundKickAttack == false && mIsBehindKickAttack == false && mIsJump == false && mIsDJump == false && CanAttackCondition())// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsKickAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_Kick;
				}
				else
				{
					mState = ePlayerState::R_Kick;
				}
			}
			// Kick 오류 방지
			if (!(mState == ePlayerState::L_Kick || mState == ePlayerState::R_Kick))
			{
				mIsKickAttack = false;
			}

			// Round Kick: UP + E
			if (mIsRun == false && Input::GetKey(eKeyCode::UP) && Input::GetKeyDown(eKeyCode::E) && mIsRoundKickAttack == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsKickAttack = false;
				mIsRoundKickAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_RoundKick;
				}
				else
				{
					mState = ePlayerState::R_RoundKick;
				}
			}
			// Round Kick 오류 방지
			if (!(mState == ePlayerState::L_RoundKick || mState == ePlayerState::R_RoundKick))
			{
				mIsRoundKickAttack = false;
			}

			// Behind Kick: DOWN + E
			if (mIsRun == false && Input::GetKey(eKeyCode::DOWN) && Input::GetKeyDown(eKeyCode::E) && mIsBehindKickAttack == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsKickAttack = false;
				mIsBehindKickAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_BehindKick;
				}
				else
				{
					mState = ePlayerState::R_BehindKick;
				}
			}
			// Behind Kick 오류 방지
			if (!(mState == ePlayerState::L_BehindKick || mState == ePlayerState::R_BehindKick))
			{
				mIsBehindKickAttack = false;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 무기 공격
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// WeaponNormalAttack: D
			if (Input::GetKeyDown(eKeyCode::D) && mIsWeaponNormalAttack == false && mIsWeaponDownAttack == false && mIsWeaponSideAttack == false && mIsWeaponStabAttack == false && mIsJump == false && mIsDJump == false && CanAttackCondition())// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsWeaponNormalAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_WeaponNormalAttack;
				}
				else
				{
					mState = ePlayerState::R_WeaponNormalAttack;
				}
			}
			// WeaponNormalAttack 오류 방지
			if (!(mState == ePlayerState::L_WeaponNormalAttack || mState == ePlayerState::R_WeaponNormalAttack))
			{
				mIsWeaponNormalAttack = false;
			}

			// WeaponDownAttack: DOWN + D 
			if (Input::GetKey(eKeyCode::DOWN) && Input::GetKeyDown(eKeyCode::D) && mIsWeaponDownAttack == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsWeaponNormalAttack = false;
				mIsWeaponDownAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_WeaponDownAttack;
				}
				else
				{
					mState = ePlayerState::R_WeaponDownAttack;
				}
			}
			// WeaponDownAttack오류 방지
			if (!(mState == ePlayerState::L_WeaponDownAttack || mState == ePlayerState::R_WeaponDownAttack))
			{
				mIsWeaponDownAttack = false;
			}

			// WeaponSideAttack:LEFT OR RIGHT + D
			if ((Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT)) && Input::GetKeyDown(eKeyCode::D) && mIsWeaponSideAttack == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsWeaponNormalAttack = false;
				mIsWeaponSideAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_WeaponSideAttack;
				}
				else
				{
					mState = ePlayerState::R_WeaponSideAttack;
				}
			}
			// WeaponSideAttack 오류 방지
			if (!(mState == ePlayerState::L_WeaponSideAttack || mState == ePlayerState::R_WeaponSideAttack))
			{
				mIsWeaponSideAttack = false;
			}

			// WeaponStabAttack: D + UP
			if (Input::GetKey(eKeyCode::UP) && Input::GetKeyDown(eKeyCode::D) && mIsWeaponStabAttack == false && mIsJump == false && mIsDJump == false)// 점프와 더블점프 중 키입력은 다른 기술이 나가야 함
			{
				mIsWeaponNormalAttack = false;
				mIsWeaponStabAttack = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_WeaponStabAttack;
				}
				else
				{
					mState = ePlayerState::R_WeaponStabAttack;
				}
			}
			// WeaponStabAttack 오류 방지
			if (!(mState == ePlayerState::L_WeaponStabAttack || mState == ePlayerState::R_WeaponStabAttack))
			{
				mIsWeaponStabAttack = false;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 점프 중 공격
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// JumpDownAttack: 점프 중 + W (공격 성공 시, JumpDownHit 애니메이션 실행 후 마저 착지)
			// 점프 중 동작 내 부분에 구현됨

			// JumpSlideAttack: 점프 중 + E
			// 점프 중 동작 내 부분에 구현됨

			// RunJumpAttack: SHIFT + 점프 중 + D
			// 점프 중 동작 내 부분에 구현됨

			// RunJumpDownAttack: SHIFT(눌러졌던 상태에서) + 점프 중 + E 
			// 구현 미정

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 달리기 중 공격
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// RunWeaponAttack: 달리는 상태에서 + D
			if (mIsRun == true && mIsRunWeaponAttack == false && mIsJump == false && mIsDJump == false)
			{
				if (Input::GetKeyDown(eKeyCode::D) && mIsRunSlideAttack == false)
				{
					mIsRunWeaponAttack = true;

					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_RunWeaponAttack;
					}
					else
					{
						mState = ePlayerState::R_RunWeaponAttack;
					}
				}
			}

			// RunSlideAttack: 달리는 상태에서 + E
			if (mIsRun == true && mIsRunSlideAttack == false && mIsJump == false && mIsDJump == false)
			{
				if (Input::GetKeyDown(eKeyCode::E) && mIsRunWeaponAttack == false)
				{
					mIsRunSlideAttack = true;

					if (mDirection == eDirection::L)
					{
						mState = ePlayerState::L_RunSlideAttack;
					}
					else
					{
						mState = ePlayerState::R_RunSlideAttack;
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 궁극기
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// FireBall: R (GP 50 이하)
			if (Input::GetKeyDown(eKeyCode::R) && NoneAnimationCondition() && CanAttackCondition())
			{
				//if (0.0f <= mAbilty.mGP && mAbilty.mGP <= 50.0f)
				//{

				//}

				mIsFireBall = true;

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_FireBall;
				}
				else
				{
					mState = ePlayerState::R_FireBall;
				}
			}

			// Super: R (GP 50 초과)// R버튼인데 GP 구현이 되지 않아서 일단 T키로 입력
			//if (Input::GetKeyDown(eKeyCode::R) && mIsSuper == false && mIsJump == false && mIsDJump == false)
			//{
			//	if (mAbilty.mGP > 50.0f)
			//	{

			//	}
			//}
			if (Input::GetKeyDown(eKeyCode::T) && NoneAnimationCondition() && CanAttackCondition() && CanAttackCondition())
			{
				mIsSuper = true;

				//Transform* tr = this->GetOwner()->GetComponent<Transform>();
				//Vector3 pos = tr->GetPosition();
				//pos.y += 1.0f;
				//tr->SetPosition(pos);

				if (mDirection == eDirection::L)
				{
					mState = ePlayerState::L_Super;
				}
				else
				{
					mState = ePlayerState::R_Super;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 추가해야할 부분
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Glow, Counter,...
			// 위 상태는 Collider를 추가하는 선행작업이 요구
			// Collider 몇 개를? 어떤 위치에? 배치할지 고민 후 진행
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 콜라이더 & 스킬 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 유의점
		// Activation은 Set으로 설정하는 것이 일반적
		// State는 Get으로 받아와 충돌 유무를 파악하는 것이 일반적

		//  mIsNormalAttack1 U || mIsNormalAttack2 U || mIsNormalAttack3 U ||
		//	mIsKickAttack L|| mIsRoundKickAttack B || mIsBehindKickAttack Back||
		//	mIsWeaponNormalAttack B || mIsWeaponDownAttack L || mIsWeaponSideAttack B || mIsWeaponStabAttack L ||
		//	mIsJumpDownAttack L || mIsJumpSlideAttack L  || mIsRunJumpAttack L ||
		//	mIsRunWeaponAttack B || mIsRunSlideAttack L ||
		//	mIsFireBall B || mIsSuper A

		//// mBodyCd 활성화 비활성화 조건
		//if (//mState == ePlayerState::L_Guard || mState == ePlayerState::R_Guard
		//	 mIsEvade || mIsNormalAttack1 || mIsNormalAttack2 || mIsNormalAttack3 || mIsKickAttack || mIsRoundKickAttack || mIsBehindKickAttack
		//	|| mIsWeaponNormalAttack || mIsWeaponDownAttack || mIsWeaponSideAttack || mIsWeaponStabAttack || mIsJumpDownAttack || mIsJumpSlideAttack || mIsRunJumpAttack 
		//	|| mIsRunWeaponAttack || mIsRunSlideAttack
		//	|| mIsFireBall || mIsSuper
		//	|| mIsStun || mIsKnockDown || mIsDowned || mIsGetUp || mIsBackStun
		//	)
		//	// 가드가 붙은 스킬아냐 아니냐로 구분을 해서 적용을 할지 고민중
		//	// 가드를 하고 있다가 바로 스킬을 쓴다면, 계속 무적이고 플레이어의 공격상태와 겹치게 되면 상황이 애매해짐 
		//{
		//	mBodyCd->SetActivation(eColliderActivation::InActive);
		//}
		//else if//mState == ePlayerState::L_Guard || mState == ePlayerState::R_Guard
		//	(! (mIsEvade || mIsNormalAttack1 || mIsNormalAttack2 || mIsNormalAttack3 || mIsKickAttack || mIsRoundKickAttack || mIsBehindKickAttack
		//	|| mIsWeaponNormalAttack || mIsWeaponDownAttack || mIsWeaponSideAttack || mIsWeaponStabAttack || mIsJumpDownAttack || mIsJumpSlideAttack || mIsRunJumpAttack
		//	|| mIsRunWeaponAttack || mIsRunSlideAttack
		//	|| mIsFireBall || mIsSuper
		//	|| mIsStun || mIsKnockDown || mIsDowned || mIsGetUp || mIsBackStun
		//	))
		//{
		//	mBodyCd->SetActivation(eColliderActivation::Active);
		//}

		
		if(! (mState == ePlayerState::L_Guard || mState == ePlayerState::R_Guard))// 가드를 사용하지 않는 상태는 false로 초기화
		{
			mBodyCd->SetCanGuard(false);
		}

		// Upper
		if (mIsNormalAttack1 || mIsNormalAttack2 || mIsNormalAttack3)
		{
			mUpperCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mUpperCd->SetActivation(eColliderActivation::InActive);
		}

		// Lower
		if (mIsKickAttack || mIsWeaponDownAttack || mIsWeaponStabAttack 
			|| mIsJumpDownAttack || mIsJumpSlideAttack || mIsRunJumpAttack || mIsRunSlideAttack)
		{
			mLowerCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mLowerCd->SetActivation(eColliderActivation::InActive);
		}

		// Both
		if (mIsRoundKickAttack || mIsWeaponNormalAttack || mIsWeaponSideAttack 
			|| mIsRunWeaponAttack || mIsFireBall)
		{

			mBothCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mBothCd->SetActivation(eColliderActivation::InActive);
		}

		// Back
		if (mIsBehindKickAttack)
		{
			mBackCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mBackCd->SetActivation(eColliderActivation::InActive);
		}

		// All
		if (mIsSuper)
		{
			mAllCd->SetActivation(eColliderActivation::Active);
		}
		else
		{
			mAllCd->SetActivation(eColliderActivation::InActive);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 충돌
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
		if (mState == ePlayerState::L_Idle || mState == ePlayerState::R_Idle || mState == ePlayerState::L_Run || mState == ePlayerState::R_Run)
		{
			mIsCollidingFirst = 0;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// 상태 bool 변수 동기화
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Input::GetKey(eKeyCode::LSHIFT))
		{
			mIsRun = true;
		}
		else
		{
			mIsRun = false;
		}

		// 공격 당하는 관련 변수들
		if (mState == ePlayerState::L_Stun || mState == ePlayerState::R_Stun)
		{
			if (mEnemyPosition == -1)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.2f, 0.0f));
			}

			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.2f, 0.0f));
			}

			mIsStun = true;
		}
		else
		{
			mIsStun = false;
		}

		if (mState == ePlayerState::L_KnockDown || mState == ePlayerState::R_KnockDown)
		{
			if (mEnemyPosition == -1)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.4f, 0.0f));
			}

			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.4f, 0.0f));
			}

			mIsKnockDown = true;
		}
		else
		{
			mIsKnockDown = false;
		}

		if (mState == ePlayerState::L_Downed || mState == ePlayerState::R_Downed)
		{
			mIsDowned = true;
		}
		else
		{
			mIsDowned = false;
		}

		if (mState == ePlayerState::L_GetUp || mState == ePlayerState::R_GetUp)
		{
			mIsGetUp = true;
		}
		else
		{
			mIsGetUp = false;
		}

		if (mState == ePlayerState::L_BackStun || mState == ePlayerState::R_BackStun)
		{
			if (mEnemyPosition == -1)
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(100.5f, 0.0f));
			}

			else
			{
				Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();
				rb->SetGround(true);
				rb->AddForce(Vector2(-100.5f, 0.0f));
			}

			mIsBackStun = true;
		}
		else
		{
			mIsBackStun = false;
		}

		// 공격 변수들
		//...
		if (mState == ePlayerState::L_RunSlideAttack || mState == ePlayerState::R_RunSlideAttack)
		{
			mIsRunSlideAttack = true;
		}
		else
		{
			mIsRunSlideAttack = false;
		}

		if (mState == ePlayerState::L_NormalAttack1 || mState == ePlayerState::R_NormalAttack1)
		{
			mIsNormalAttack1 = true;
		}
		else
		{
			mIsNormalAttack1 = false;
		}
		if (mState == ePlayerState::L_NormalAttack2 || mState == ePlayerState::R_NormalAttack2)
		{
			mIsNormalAttack2 = true;
		}
		else
		{
			mIsNormalAttack2 = false;
		}
		if (mState == ePlayerState::L_NormalAttack3 || mState == ePlayerState::R_NormalAttack3)
		{
			mIsNormalAttack3 = true;
		}
		else
		{
			mIsNormalAttack3 = false;
		}

		// 공격 변수들 강제 초기화
		if (mState == ePlayerState::L_Idle || mState == ePlayerState::R_Idle || mState == ePlayerState::L_Run|| mState == ePlayerState::R_Run)
		{
			mIsNormalAttack1 = false;
			mIsNormalAttack2 = false;
			mIsNormalAttack3 = false;
			mIsKickAttack = false;
			mIsRoundKickAttack = false;
			mIsBehindKickAttack = false;
			mIsWeaponNormalAttack = false;
			mIsWeaponDownAttack = false;
			mIsWeaponSideAttack = false;
			mIsWeaponStabAttack = false;
			mIsJumpDownAttack = false;
			mIsJumpSlideAttack = false;
			mIsRunJumpAttack = false;
			mIsRunWeaponAttack = false;
			mIsRunSlideAttack = false;
			mIsFireBall = false;
			mIsSuper = false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 스킬 상태 Update
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		mAttackState[0] = mIsNormalAttack1;
		mAttackState[1] = mIsNormalAttack2;
		mAttackState[2] = mIsNormalAttack3;
		mAttackState[3] = mIsKickAttack;
		mAttackState[4] = mIsRoundKickAttack;
		mAttackState[5] = mIsBehindKickAttack;
		mAttackState[6] = mIsWeaponNormalAttack;
		mAttackState[7] = mIsWeaponDownAttack;
		mAttackState[8] = mIsWeaponSideAttack;
		mAttackState[9] = mIsWeaponStabAttack;
		mAttackState[10] = mIsJumpDownAttack;
		mAttackState[11] = mIsJumpSlideAttack;
		mAttackState[12] = mIsRunJumpAttack;
		mAttackState[13] = mIsRunWeaponAttack;
		mAttackState[14] = mIsRunSlideAttack;
		mAttackState[15] = mIsFireBall;
		mAttackState[16] = mIsSuper;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 이벤트 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void RamonaScript::EvadeComplete()
	{
		mIsEvade = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::NormalAttackComplete()
	{
		if (mIsNormalAttack1 == true)
		{
			mIsNormalAttack1 = false;

			mCanNormalAttack2 = false;
			mCanNormalAttack3 = false;
		}

		if (mIsNormalAttack2 == true)
		{
			mIsNormalAttack2 = false;

			mCanNormalAttack2 = false;
			mCanNormalAttack3 = false;
		}

		if (mIsNormalAttack3 == true)
		{
			mIsNormalAttack3 = false;

			mCanNormalAttack2 = false;
			mCanNormalAttack3 = false;
			mNormalAttack2Time = 0.0f;
		}

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::KickComplete()
	{
		mIsKickAttack = false;
		mIsRoundKickAttack = false;
		mIsBehindKickAttack = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::WeaponAttackComplete()
	{
		mIsWeaponNormalAttack = false;
		mIsWeaponDownAttack = false;
		mIsWeaponSideAttack = false;
		mIsWeaponStabAttack = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::JumpAttackComplete()
	{
		mIsJumpDownAttack = false;
		mIsJumpSlideAttack = false;
		mIsRunJumpAttack = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::RunAttackComplete()
	{
		mIsRunWeaponAttack = false;
		mIsRunSlideAttack = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::FireBallComplete()
	{
		mIsFireBall = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::SuperComplete()
	{
		mIsSuper = false;

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::StunComplete()
	{
		// 멤버 변수 mIsStun

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	void RamonaScript::KnockDownComplete()
	{
		// 멤버 변수 mIsKnockDown

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Downed;
		}
		else
		{
			mState = ePlayerState::R_Downed;
		}
	}

	void RamonaScript::DownedComplete()
	{
		// 멤버 변수 mIsDowned

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_GetUp;
		}
		else
		{
			mState = ePlayerState::R_GetUp;
		}
	}

	void RamonaScript::GetUpComplete()
	{
		// 멤버 변수 mIsGetUp

		if (mDirection == eDirection::L)
		{
			mState = ePlayerState::L_Idle;
		}
		else
		{
			mState = ePlayerState::R_Idle;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 충돌
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void RamonaScript::OnCollisionEnter(Collider2D* other)// Enter가 정상 작동하는지 재확인 요망
	{
		if (other->GetOwner()->GetName() == L"Luke" || other->GetOwner()->GetName() == L"Luke2" || other->GetOwner()->GetName() == L"Luke3")
		{
			for (int i = 0; i < 4; i++)
			{
				mEnemyAttackState[i] = (other->GetOwner()->GetComponent<LukeScript>()->GetAttackState())[i];
			}
		}
	}
	void RamonaScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetOwner()->GetName() == L"Luke" || other->GetOwner()->GetName() == L"Luke2" || other->GetOwner()->GetName() == L"Luke3")// 이 부분은 GameObject 상속받은 Enemy 만의 고유 이름이나 고유 상태를 확인 하거나 형변환으로 확인할 예정
		{
			if (mBodyCd->GetState() == eColliderState::IsColliding)
			{
				// 공격 당하는 스킬이 무엇인지에 대한 업데이트
				for (int i = 0; i < 4; i++)
				{
					mEnemyAttackState[i] = (other->GetOwner()->GetComponent<LukeScript>()->GetAttackState())[i];
				}

				// 가드 상태
				if (mState == ePlayerState::L_Guard || mState == ePlayerState::R_Guard)
				{
					// Guard 상태일 때, InActive로 바꾸는 것이 아니라
					// Guard 상태도 상시 Active 상태로 바꾸고
					// mCanGuard로 판단해서 
					// mCanGuard가 true이면 맞는 동작, 상태, 애니를 실행 안하도록 아래 충돌 부분에 구현하면 됨
					mBodyCd->SetActivation(eColliderActivation::Active);

					// 충돌을 한 경우
					if (mBodyCd->GetPosition().x < mBodyCd->GetOtherPos().x)// 바디 - 상대스킬
					{
						if (mDirection == eDirection::R)// 막을 수 있음
						{
							mBodyCd->SetCanGuard(true);
						}
						else// 막을 수 없음
						{
							mBodyCd->SetCanGuard(false);
						}
					}
					else// 상대 스킬 - 바디
					{
						if (mDirection == eDirection::R)// 막을 수 없음
						{
							mBodyCd->SetCanGuard(false);
						}
						else// 막을 수 있음
						{
							mBodyCd->SetCanGuard(true);
						}
					}
				}
				else// 가드 상태가 아니면 false로 (이 부분은 Update에서도 해주고 있음)
				{
					mBodyCd->SetCanGuard(false);
				}

				// 공격 당하는 모션
				if (mBodyCd->GetCanGuard() == false)// 가드로 스킬을 막는 경우가 아니라면, 공격 당하는 상태로 전환
				{
					if (mIsCollidingFirst == 0
						&& mIsStun == false && mIsKnockDown == false && mIsDowned == false && mIsGetUp == false && mIsBackStun == false)
						// 처음 충돌
						// + 충돌 조건(다운되어있는데 갑자기 공격을 받았다고 해서 Guard나 Idle로 바뀌지 않기 위한 조건)
						// 추후 충돌 조건은 따로 정리할 예정
						// 물론, Downed 상태에서 또 공격을 당했을 때, DownStun을 발동해야하는 경우 예외적으로 설정해주어야 함
					{
						// 적 공격 스킬 참고 
						// mAttackState[0] = mIsArm;
						// mAttackState[1] = mIsKick;
						// mAttackState[2] = mIsSideKick;
						// mAttackState[3] = mIsUpper;

						if (mBodyCd->GetPosition().x < mBodyCd->GetOtherPos().x)
							mEnemyPosition = 1;
						else
							mEnemyPosition = -1;

						// 적의 공격 스킬에 따라 해당하는 상태 전환 
						if (mEnemyAttackState[3])
						{
							mAttribute.mHp -= 50.0f;

							if (mDirection == eDirection::L)
							{
								mState = ePlayerState::L_KnockDown;
							}
							else
							{
								mState = ePlayerState::R_KnockDown;
							}
						}
						else
						{
							mAttribute.mHp -= 50.0f;

							if (mDirection == eDirection::L)
							{
								mState = ePlayerState::L_Stun;
							}
							else
							{
								mState = ePlayerState::R_Stun;
							}
						}

						mIsCollidingFirst == 1;
					}
				}
			}

			if (mUpperCd->GetState() == eColliderState::IsColliding)
			{
				int a = 0;
			}
		}
	}
	void RamonaScript::OnCollisionExit(Collider2D* other)
	{
		int a = 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 기타 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 애니메이션이 동작되어서는 안되는 상황: 
	// ex. 점프 중 우측 키를 눌렀다고 해서 R_Walk가 실행되면 안됨
	bool RamonaScript::NoneAnimationCondition()
	{
		if (
				mIsJump == false && mIsEvade == false // mIsDJump는 어짜피 mIsJump가 true인 상태에서만 진행되기에 넣지 않음
				&& mIsNormalAttack1 == false && mIsNormalAttack2 == false && mIsNormalAttack3 == false
				&& mIsKickAttack == false && mIsRoundKickAttack == false && mIsBehindKickAttack == false
				&& mIsWeaponNormalAttack == false && mIsWeaponDownAttack == false && mIsWeaponSideAttack == false && mIsWeaponStabAttack == false
				&& mIsJumpDownAttack == false && mIsJumpSlideAttack == false
				&& mIsRunWeaponAttack == false && mIsRunSlideAttack == false
				&& mIsFireBall == false && mIsSuper == false
			)
			return true;

		return false;
	}

	// 좌우 상하 이동을 막아야하는 상황
	bool RamonaScript::CanMoveCondition()
	{
		if (
				mIsGuard == true
				|| mIsNormalAttack1 == true || mIsNormalAttack2 == true || mIsNormalAttack3 == true
				|| mIsKickAttack == true || mIsRoundKickAttack == true || mIsBehindKickAttack == true
				|| mIsWeaponNormalAttack == true || mIsWeaponDownAttack == true || mIsWeaponSideAttack == true || mIsWeaponStabAttack == true
				|| mIsFireBall == true
				|| mIsStun || mIsKnockDown || mIsDowned || mIsGetUp || mIsBackStun
			)
		{
			return false;
		}

		return true;
	}

	bool RamonaScript::CanJumpCondition()
	{
		if (
				mIsJump == false && mIsDJump == false
				&& mIsGuard == false && mIsEvade == false
				&& mIsNormalAttack1 == false && mIsNormalAttack2 == false && mIsNormalAttack3 == false
				&& mIsKickAttack == false && mIsRoundKickAttack == false && mIsBehindKickAttack == false
				&& mIsWeaponNormalAttack == false && mIsWeaponDownAttack == false && mIsWeaponSideAttack == false && mIsWeaponStabAttack == false
				&& mIsRunWeaponAttack == false && mIsRunSlideAttack == false
				&& mIsFireBall == false && mIsSuper == false
			)
			return true;

		return false;
	}

	bool RamonaScript::CanAttackCondition()
	{
		if (
				mIsEvade == true
				|| mIsNormalAttack1 == true || mIsNormalAttack2 == true || mIsNormalAttack3 == true
				|| mIsKickAttack == true || mIsRoundKickAttack == true || mIsBehindKickAttack == true
				|| mIsWeaponNormalAttack == true || mIsWeaponDownAttack == true || mIsWeaponSideAttack == true || mIsWeaponStabAttack == true
				|| mIsJumpDownAttack == true || mIsJumpSlideAttack == true
				|| mIsRunWeaponAttack == true || mIsRunSlideAttack == true
				|| mIsFireBall == true || mIsSuper == true
			)
			return false;

		return true;
	}

	bool RamonaScript::CanChangeState()
	{
		if (
				mIsStun == true || mIsKnockDown == true || mIsDowned == true || mIsGetUp == true || mIsBackStun == true
			// || mIsKickAttack == true || mIsRoundKickAttack == true || mIsBehindKickAttack == true
			)
			return false;

		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														// 상태 애니메이션 함수
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void RamonaScript::L_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Idle", true);
	}
	void RamonaScript::R_idle()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Idle", true);
	}
	void RamonaScript::L_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Walk", true);
	}
	void RamonaScript::R_walk()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Walk", true);
	}
	void RamonaScript::L_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Run", true);
	}
	void RamonaScript::R_run()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Run", true);
	}
	void RamonaScript::L_jump()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Jump", true);
	}
	void RamonaScript::R_jump()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Jump", true);
	}
	void RamonaScript::L_djump()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_DJump", false);
	}
	void RamonaScript::R_djump()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_DJump", false);
	}
	void RamonaScript::L_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Guard", false);
	}
	void RamonaScript::R_guard()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Guard", false);
	}
	void RamonaScript::L_evade()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Evade", true);
	}
	void RamonaScript::R_evade()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Evade", true);
	}
	void RamonaScript::L_normalattack1()
	{
		mIsNormalAttack1 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_NormalAttack1", true);
	}
	void RamonaScript::R_normalattack1()
	{
		mIsNormalAttack1 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_NormalAttack1", true);
	}
	void RamonaScript::L_normalattack2()
	{
		mCanNormalAttack2 = false;
		mIsNormalAttack2 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_NormalAttack2", true);
	}
	void RamonaScript::R_normalattack2()
	{
		mCanNormalAttack2 = false;
		mIsNormalAttack2 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_NormalAttack2", true);
	}
	void RamonaScript::L_normalattack3()
	{
		mCanNormalAttack3 = false;
		mIsNormalAttack3 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_NormalAttack3", true);
	}
	void RamonaScript::R_normalattack3()
	{
		mCanNormalAttack3 = false;
		mIsNormalAttack3 = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_NormalAttack3", true);
	}
	void RamonaScript::L_kick()
	{
		mIsKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Kick", true);
	}
	void RamonaScript::R_kick()
	{
		mIsKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Kick", true);
	}
	void RamonaScript::L_roundkick()
	{
		mIsRoundKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_RoundKick", true);
	}
	void RamonaScript::R_roundkick()
	{
		mIsRoundKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_RoundKick", true);
	}
	void RamonaScript::L_behindkick()
	{
		mIsBehindKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_BehindKick", true);
	}
	void RamonaScript::R_behindkick()
	{
		mIsBehindKickAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_BehindKick", true);
	}
	void RamonaScript::L_weaponnormalattack()
	{
		mIsWeaponNormalAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_WeaponNormalAttack", true);
	}
	void RamonaScript::R_weaponnormalattack()
	{
		mIsWeaponNormalAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_WeaponNormalAttack", true);
	}
	void RamonaScript::L_weapondownattack()
	{
		mIsWeaponDownAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_WeaponDownAttack", true);
	}
	void RamonaScript::R_weapondownattack()
	{
		mIsWeaponDownAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_WeaponDownAttack", true);
	}
	void RamonaScript::L_weaponsideattack()
	{
		mIsWeaponSideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_WeaponSideAttack", true);
	}
	void RamonaScript::R_weaponsideattack()
	{
		mIsWeaponSideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_WeaponSideAttack", true);
	}
	void RamonaScript::L_weaponstabattack()
	{
		mIsWeaponStabAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_WeaponStabAttack", true);
	}
	void RamonaScript::R_weaponstabattack()
	{
		mIsWeaponStabAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_WeaponStabAttack", true);
	}
	void RamonaScript::L_jumpdownattack()
	{
		mIsJumpDownAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_JumpDownAttack", true);
	}
	void RamonaScript::R_jumpdownattack()
	{
		mIsJumpDownAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_JumpDownAttack", true);
	}
	void RamonaScript::L_jumpslideattack()
	{
		mIsJumpSlideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_JumpSlideAttack", true);
	}
	void RamonaScript::R_jumpslideattack()
	{
		mIsJumpSlideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_JumpSlideAttack", true);
	}
	void RamonaScript::L_runjumpattack()
	{
		mIsRunJumpAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_RunJumpAttack", true);
	}
	void RamonaScript::R_runjumpattack()
	{
		mIsRunJumpAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_RunJumpAttack", true);
	}
	void RamonaScript::L_runweaponattack()
	{
		mIsRunWeaponAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_RunWeaponAttack", true);
	}
	void RamonaScript::R_runweaponattack()
	{
		mIsRunWeaponAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_RunWeaponAttack", true);
	}
	void RamonaScript::L_runslideattack()
	{
		mIsRunSlideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_RunSlideAttack", true);
	}
	void RamonaScript::R_runslideattack()
	{
		mIsRunSlideAttack = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_RunSlideAttack", true);
	}
	void RamonaScript::L_fireball()
	{
		mIsFireBall = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_FireBall", true);
	}
	void RamonaScript::R_fireball()
	{
		mIsFireBall = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_FireBall", true);
	}
	void RamonaScript::L_super()
	{
		mIsSuper = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Super", true);
	}
	void RamonaScript::R_super()
	{
		mIsSuper = true;

		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Super", true);
	}
	void RamonaScript::L_stun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Stun", true);
	}
	void RamonaScript::R_stun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Stun", true);
	}
	void RamonaScript::L_backstun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_BackStun", true);
	}
	void RamonaScript::R_backstun()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_BackStun", true);
	}
	void RamonaScript::L_knockdown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_KnockDown", true);
	}
	void RamonaScript::R_knockdown()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_KnockDown", true);
	}
	void RamonaScript::L_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_Downed", true);
	}
	void RamonaScript::R_downed()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_Downed", true);
	}
	void RamonaScript::L_getup()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"L_GetUp", true);
	}
	void RamonaScript::R_getup()
	{
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"R_GetUp", true);
	}
	void RamonaScript::SetEffectFlickering(float tick, float duration)
	{
		GetOwner()->mIsEffectFlickering = true;
		mOnFlickering = true;
		mFlickeringCurTime = 0.0f;
		mFlickeringMaxTime = duration;
		mFlickeringTickTime = tick;
	}
}