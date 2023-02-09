#include "stdafx.h"
#include "Monster.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/StateComponent.h"

Monster::Monster(Context* const context)
	: Actor(context)
{
	SetActorType(ActorType::Monster);
	AddComponents();
	AddAnimations();
}

void Monster::AddComponents()
{
	auto state = AddComponent<StateComponent>();
	AddComponent<MeshRendererComponent>();
	AddComponent<AnimatorComponent>();
	state->SetState(State::Walk);
}

void Monster::AddAnimations()
{
	auto animator = GetComponent<AnimatorComponent>();
	//기본
	animator->AddAnimation("./Assets/Animation/Monster/M1_Walk.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M1_Pulled.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M1_Damaged.xml");
	//불 속성
	animator->AddAnimation("./Assets/Animation/Monster/M_Fire1_Walk.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M_Fire1_Pulled.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M_Fire1_Damaged.xml");
	//얼음 속성
	animator->AddAnimation("./Assets/Animation/Monster/M_Ice1_Walk.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M_Ice1_Pulled.xml");
	animator->AddAnimation("./Assets/Animation/Monster/M_Ice1_Damaged.xml");
	//보스
	animator->AddAnimation("./Assets/Animation/Monster/Boss/Boss_Idle.xml");
	animator->AddAnimation("./Assets/Animation/Monster/Boss/Boss_Walk.xml");
	animator->AddAnimation("./Assets/Animation/Monster/Boss/Boss_Damaged.xml");
	animator->AddAnimation("./Assets/Animation/Monster/Boss/Boss_Jump.xml");
	animator->AddAnimation("./Assets/Animation/Monster/Boss/Boss_Action.xml");

	//초기 이미지, 혹시나..
	animator->SetCurrentAnimation("M1_Walk");
}
