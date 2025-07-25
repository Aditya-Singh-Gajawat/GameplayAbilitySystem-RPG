// Aditya Singh Gajawat All Rights Reserved

#pragma once
#include "NativeGameplayTags.h" 

namespace WarriorGameplayTags
{
	/** INPUT TAGS **/ 
	//Default Input Policy
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	//Weapon Equipped Only Input Policy
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipKatana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipKatana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Light_Katana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack_Heavy_Katana);
	//Multiple Keys Input Policy
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AttackDash);
	//Hold A Key Input Policy
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HoldKey);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HoldKey_Block);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HoldKey_Sprint);
	//Toggle A Key Input Policy 
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggle);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggle_TargetAim);

	/** PLAYER TAGS **/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Katana);

	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Effect_Attack_Light);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Effect_Attack_Heavy);
	
	/**ENEMY TAGS**/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafe);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	/**ENEMY ABILITY TAGS **/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee); 
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	/*ABILITY TAGS*/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_OnEquip_Katana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_OnUnequip_Katana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Katana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Katana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_StickyAttackEffect);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_AttackDash);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Jump);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Fall);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Sprint);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetAim);

	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsAttackDashing);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsRolling);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Jump);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Fall);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Block);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Sprint);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_ToggleTargetAim);
	
	/*SHARED ABILITY TAGS*/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_LightAttackHitReact);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HeavyAttackHitReact);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);
	
	/** GAMEPLAY EVENTS **/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EquipKatana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnequipKatana);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_StickyAttackEffect);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_BlockSuccess);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_BlockFailed);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Fall);
	
	/**SHARED GAMEPLAY EVENTS**/
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_RegisterHit);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_EffectSpec_BaseDamage);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_AttackHitReact);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_LightAttackHitReact);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HeavyAttackHitReact);

	//STATUS TAGS may be used for in blueprint tags!
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	GAS_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
}