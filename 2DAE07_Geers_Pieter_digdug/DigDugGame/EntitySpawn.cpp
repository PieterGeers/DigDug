#include "pch.h"
#include "EntitySpawn.h"
#include "TextureRenderComponent.h"
#include "Animator.h"
#include "QuadCollisionComponent.h"
#include "AgentComponent.h"
#include "DigDugCharacterComp.h"
#include "DigDugLivesComp.h"
#include "DigDugWeaponComp.h"
#include "FygarCharacterComp.h"

std::shared_ptr<GameObject> EntitySpawn::SpawnPlayer(MVector2_INT pos, const std::string& textPath,
	int index, bool healthRight, MVector2_INT healthPos)
{
	const std::shared_ptr<Animation> left = CreateAnimation("Left", 1, 0, 0, 1);
	const std::shared_ptr<Animation> leftDig = CreateAnimation("LeftDig", 1, 2, 0, 1);
	const std::shared_ptr<Animation> right = CreateAnimation("Right", 0, 0, 0, 1);
	const std::shared_ptr<Animation> rightDig = CreateAnimation("RightDig", 0, 2, 0, 1);
	const std::shared_ptr<Animation> rightUp = CreateAnimation("RightUp", 5, 0, 0, 1);
	const std::shared_ptr<Animation> leftUp = CreateAnimation("LeftUp", 4, 0, 0, 1);
	const std::shared_ptr<Animation> rightUpDig = CreateAnimation("RightUpDig", 5, 2, 0, 1);
	const std::shared_ptr<Animation> leftUpDig = CreateAnimation("LeftUpDig", 4, 2, 0, 1);
	const std::shared_ptr<Animation> rightDown = CreateAnimation("RightDown", 2, 0, 0, 1);
	const std::shared_ptr<Animation> leftDown = CreateAnimation("LeftDown", 3, 0, 0, 1);
	const std::shared_ptr<Animation> rightDownDig = CreateAnimation("RightDownDig", 2, 2, 0, 1);
	const std::shared_ptr<Animation> leftDownDig = CreateAnimation("LeftDownDig", 3, 2, 0, 1);
	const std::shared_ptr<Animation> death = CreateAnimation("Dead", 6, 0, 0, 6);

	std::shared_ptr<GameObject>	m_DigDug = std::make_shared<GameObject>();

	std::shared_ptr<TextureRenderComponent> DigDugTexture = std::make_shared<TextureRenderComponent>(textPath, 7, 7, 2);
	std::shared_ptr<DigDugCharacterComp> character = std::make_shared<DigDugCharacterComp>(Boundaries{ 32, 32 * 17,0,32 * 13 }, index);
	std::shared_ptr<Animator> animator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> collision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, "Player" + std::to_string(index));
	std::shared_ptr<DigDugLivesComp> lives = std::make_shared<DigDugLivesComp>("P" + std::to_string(index) + "Live.png", 3,pos, healthPos, healthRight);
	animator->AddAnimation(std::vector<std::shared_ptr<Animation>>{left, leftDig, right, rightDig, leftUp, rightUp, leftUpDig, rightUpDig, rightDown, leftDown, rightDownDig, leftDownDig, death});
	DigDugTexture->SetSpritePosition(0, 0, 6, 6);
	character->SetGridSize(32);
	m_DigDug->AddComponent(DigDugTexture);
	m_DigDug->AddComponent(character);
	m_DigDug->AddComponent(animator);
	m_DigDug->AddComponent(collision);
	m_DigDug->AddComponent(lives);

	std::shared_ptr<GameObject> Weapon = std::make_shared<GameObject>();
	std::shared_ptr<DigDugWeaponComp> weaponComp = std::make_shared<DigDugWeaponComp>("digdug_attack.png", 2);
	std::shared_ptr<QuadCollisionComponent> weaponColl = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, "AttackP" + std::to_string(index));
	weaponColl->SetIsActive(false);
	Weapon->AddComponent(weaponComp);
	Weapon->AddComponent(weaponColl);

	m_DigDug->AddChild("Weapon", Weapon);
	m_DigDug->SetPosition(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
	ServiceLocator::RegisterPlayer(index, m_DigDug);
	
	return m_DigDug;
}

std::shared_ptr<GameObject> EntitySpawn::SpawnPlayableFygar(MVector2_INT pos,const std::string& tag, int index, bool healthRight, MVector2_INT healthPos)
{
	std::shared_ptr<GameObject> Fygar = std::make_shared<GameObject>();
	const std::shared_ptr<Animation> walk = CreateAnimation("Walk", 1, 0, 0, 1);
	const std::shared_ptr<Animation> invis = CreateAnimation("Invisible", 1, 3, 0, 1);
	const std::shared_ptr<Animation> dead = CreateAnimation("Explode", 1, 5, 0, 3);
	const std::shared_ptr<Animation> flat = CreateAnimation("Flat", 1, 9, 0, 0);

	std::shared_ptr<TextureRenderComponent> PookaTexture = std::make_shared<TextureRenderComponent>("digdug_spriteEnemies.png", 2, 10, 2);
	std::shared_ptr<FygarCharacterComp> character = std::make_shared<FygarCharacterComp>(Boundaries{ 32, 32 * 17,0,32 * 13 }, index);
	std::shared_ptr<Animator> animator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> collision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, tag);
	std::shared_ptr<DigDugLivesComp> lives = std::make_shared<DigDugLivesComp>("FygarLive.png", 4, pos, healthPos, healthRight, false);
	animator->AddAnimation(std::vector<std::shared_ptr<Animation>>{walk, invis, dead, flat});
	character->SetGridSize(32);
	Fygar->AddComponent(PookaTexture);
	Fygar->AddComponent(character);
	Fygar->AddComponent(animator);
	Fygar->AddComponent(collision);
	Fygar->AddComponent(lives);
	animator->SetActiveAnimation("Walk");

	const std::shared_ptr<Animation> aLeft = CreateAnimation("Left", 1, 0, 0, 2);
	const std::shared_ptr<Animation> aRight = CreateAnimation("Right", 0, 0, 0, 2);

	std::shared_ptr<GameObject> Weapon = std::make_shared<GameObject>();
	std::shared_ptr<DigDugWeaponComp> weaponComp = std::make_shared<DigDugWeaponComp>("digdug_spriteFire.png", 2, 3, 2);
	std::shared_ptr<Animator> weaponAnimator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> weaponColl = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 96,32, tag+"Weapon");
	weaponAnimator->AddAnimation(std::vector<std::shared_ptr<Animation>>{aLeft, aRight});
	weaponColl->SetIsActive(false);
	Weapon->AddComponent(weaponComp);
	Weapon->AddComponent(weaponAnimator);
	Weapon->AddComponent(weaponColl);

	Fygar->AddChild("EnemyWeapon", Weapon);
	Fygar->SetPosition(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
	ServiceLocator::RegisterPlayer(index, Fygar);

	return Fygar;
}

std::shared_ptr<GameObject> EntitySpawn::SpawnPooka(MVector2_INT pos, const std::string& tag)
{
	std::shared_ptr<GameObject> pooka = std::make_shared<GameObject>();
	const std::shared_ptr<Animation> walk = CreateAnimation("Walk", 0, 0, 0, 1);
	const std::shared_ptr<Animation> invis = CreateAnimation("Invisible", 0, 2, 0, 1);
	const std::shared_ptr<Animation> stage1 = CreateAnimation("Stage1", 0, 4, 0, 0);
	const std::shared_ptr<Animation> stage2 = CreateAnimation("Stage2", 0, 5, 0, 0);
	const std::shared_ptr<Animation> stage3 = CreateAnimation("Stage3", 0, 6, 0, 0);
	const std::shared_ptr<Animation> dead = CreateAnimation("Explode", 0, 7, 0, 0);
	const std::shared_ptr<Animation> flat = CreateAnimation("Flat", 0, 8, 0, 0);

	std::shared_ptr<TextureRenderComponent> PookaTexture = std::make_shared<TextureRenderComponent>("digdug_spriteEnemies.png", 2, 10, 2);
	std::shared_ptr<Animator> pookaAnimator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> pookaCollision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, tag);
	pookaAnimator->AddAnimation({ walk, invis, stage1, stage2, stage3, dead, flat });
	pooka->AddComponent(PookaTexture);
	pooka->AddComponent(pookaAnimator);
	pooka->AddComponent(pookaCollision);
	pooka->SetPosition(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
	pookaAnimator->SetActiveAnimation("Walk");
	const std::shared_ptr<AgentComponent> agent = std::make_shared<AgentComponent>(4, 32, 14);
	pooka->AddComponent(agent);
	ServiceLocator::RegisterAgent(AgentComponent::GetCount(), pooka);
	pooka->GetComponent<AgentComponent>()->Initialize();
	return pooka;
}

std::shared_ptr<GameObject> EntitySpawn::SpawnFygar(MVector2_INT pos, const std::string& tag)
{
	std::shared_ptr<GameObject> Fygar = std::make_shared<GameObject>();
	const std::shared_ptr<Animation> walk = CreateAnimation("Walk", 1, 0, 0, 1);
	const std::shared_ptr<Animation> invis = CreateAnimation("Invisible", 1, 3, 0, 1);
	const std::shared_ptr<Animation> stage1 = CreateAnimation("Stage1", 1, 5, 0, 0);
	const std::shared_ptr<Animation> stage2 = CreateAnimation("Stage2", 1, 6, 0, 0);
	const std::shared_ptr<Animation> stage3 = CreateAnimation("Stage3", 1, 7, 0, 0);
	const std::shared_ptr<Animation> dead = CreateAnimation("Explode", 1, 8, 0, 0);
	const std::shared_ptr<Animation> flat = CreateAnimation("Flat", 1, 9, 0, 0);

	std::shared_ptr<TextureRenderComponent> PookaTexture = std::make_shared<TextureRenderComponent>("digdug_spriteEnemies.png", 2, 10, 2);
	std::shared_ptr<Animator> pookaAnimator = std::make_shared<Animator>();
	std::shared_ptr<QuadCollisionComponent> pookaCollision = std::make_shared<QuadCollisionComponent>(MVector2_INT(0, 0), 32, tag);
	pookaAnimator->AddAnimation({ walk, invis, stage1, stage2, stage3, dead, flat });
	Fygar->AddComponent(PookaTexture);
	Fygar->AddComponent(pookaAnimator);
	Fygar->AddComponent(pookaCollision);
	Fygar->SetPosition(static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
	pookaAnimator->SetActiveAnimation("Walk");
	const std::shared_ptr<AgentComponent> agent = std::make_shared<AgentComponent>(4, 32, 14);
	Fygar->AddComponent(agent);
	ServiceLocator::RegisterAgent(AgentComponent::GetCount(), Fygar);
	Fygar->GetComponent<AgentComponent>()->Initialize();
	return Fygar;

}
