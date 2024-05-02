#include "yaLeeScript.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaGameObject.h"

namespace ya 
{
	LeeScript::LeeScript()
	{

	}
	LeeScript::~LeeScript()
	{

	}
	void LeeScript::Initialize()
	{
#pragma region 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
															// 애니메이션
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Lee_Idle", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_IDLE.png");
		Animator* at = this->GetOwner()->GetComponent<Animator>();
		at->Create(L"R_Idle", atlas, enums::eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);
		at->Create(L"L_Idle", atlas, enums::eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Lee_Walk", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_WALK.png");
		at->Create(L"R_Walk", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12);
		at->Create(L"L_Walk", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12);

		atlas
			= Resources::Load<Texture>(L"Lee_Run", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_RUN.png");
		at->Create(L"R_Run", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);
		at->Create(L"L_Run", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Lee_ArmAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_ARM.png");
		at->Create(L"R_ArmAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);
		at->Create(L"L_ArmAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Lee_KickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_KICK.png");
		at->Create(L"R_KickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);
		at->Create(L"L_KickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);

		atlas
			= Resources::Load<Texture>(L"Lee_SideKickAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_SIDEKICK.png");
		at->Create(L"R_SideKickAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);
		at->Create(L"L_SideKickAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 7);

		atlas
			= Resources::Load<Texture>(L"Lee_UpperAttack", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_UPPER.png");
		at->Create(L"R_UpperAttack", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);
		at->Create(L"L_UpperAttack", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 9);

		atlas
			= Resources::Load<Texture>(L"Lee_Guard", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_GUARD.png");
		at->Create(L"R_Guard", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);
		at->Create(L"L_Guard", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);

		atlas
			= Resources::Load<Texture>(L"Lee_Attacked1", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_ATTACKED1.png");
		at->Create(L"R_Attacked1", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 3, Vector2::Zero, 0.15f);
		at->Create(L"L_Attacked1", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 3, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Lee_Attacked2", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_ATTACKED2.png");
		at->Create(L"R_Attacked2", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);
		at->Create(L"L_Attacked2", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 0.15f);

		atlas
			= Resources::Load<Texture>(L"Lee_Attacked3", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_ATTACKED3.png");
		at->Create(L"R_Attacked3", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 14);
		at->Create(L"L_Attacked3", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 14);

		atlas
			= Resources::Load<Texture>(L"Lee_Attacked4", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_ATTACKED4.png");
		at->Create(L"R_Attacked4", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);
		at->Create(L"L_Attacked4", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4);

		atlas
			= Resources::Load<Texture>(L"Lee_GetUp", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_GETUP.png");
		at->Create(L"R_GetUp", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8, Vector2::Zero, 0.08f);
		at->Create(L"L_GetUp", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 8, Vector2::Zero, 0.08f);

		atlas
			= Resources::Load<Texture>(L"Lee_Downed", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_DEAD.png");
		at->Create(L"R_Downed", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);
		at->Create(L"L_Downed", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);

		atlas
			= Resources::Load<Texture>(L"Lee_Dead", L"..\\Resources\\TEXTURE\\STAGE01\\ENEMY\\LEE\\LEE_DEAD.png");
		at->Create(L"R_Dead", atlas, eAnimationType::Front, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);
		at->Create(L"L_Dead", atlas, eAnimationType::Back, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 4, Vector2::Zero, 1.0f);

#pragma endregion

		LukeScript::Initialize();
	}
	void LeeScript::Update()
	{
		LukeScript::Update();
	}
	void LeeScript::OnCollisionEnter(Collider2D* other)
	{
		LukeScript::OnCollisionEnter(other);
	}
	void LeeScript::OnCollisionStay(Collider2D* other)
	{
		LukeScript::OnCollisionStay(other);
	}
	void LeeScript::OnCollisionExit(Collider2D* other)
	{
		LukeScript::OnCollisionExit(other);
	}
}