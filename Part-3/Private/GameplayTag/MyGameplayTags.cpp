// Aditya Singh Gajawat All Rights Reserved

#include "GameplayTag/MyGameplayTags.h"
namespace WarriorGameplayTags
{
	/** INPUT TAGS **/
	//Default Input Policy
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	//Weapon Equipped Only Input Policy
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipKatana, "InputTag.EquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnquipKatana, "InputTag.UnquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light_Katana, "InputTag.Attack.Light.Katana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy_Katana, "InputTag.Attack.Heavy.Katana");
	//Multiple Keys Input Policy
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_AttackDash, "InputTag.AttackDash");
	//Hold A Key Input Policy
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HoldKey, "InputTag.HoldKey");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HoldKey_Block, "InputTag.HoldKey.Block");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HoldKey_Sprint, "InputTag.HoldKey.Sprint");
	//Toggle A Key Input Policy 
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle, "Input.Toggle");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggle_TargetAim, "InputTag.Toggle.TargetAim");

	/** PLAYER TAGS **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Katana, "Player.Weapon.Katana");

	UE_DEFINE_GAMEPLAY_TAG(Player_Effect_Attack_Light, "Player.Effect.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Effect_Attack_Heavy, "Player.Effect.Attack.Heavy");

	/** ENEMY TAGS **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafe, "Enemy.Status.Strafe");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");

	/** ENEMY ABILITY TAGS **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");

	/*ABILITY TAGS*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OnEquip_Katana, "Player.Ability.OnEquip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OnUnequip_Katana, "Player.Ability.OnUnequip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Katana, "Player.Ability.Attack.Light.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Katana, "Player.Ability.Attack.Heavy.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_StickyAttackEffect, "Player.Ability.StickyAttackEffect");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_AttackDash, "Player.Ability.AttackDash");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Fall, "Player.Ability.Fall");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Sprint, "Player.Ability.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetAim, "Player.Ability.TargetAim");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsAttackDashing, "Player.Status.IsAttackDashing");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jump, "Player.Status.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Fall, "Player.Status.Fall");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsRolling, "Player.Status.IsRolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Block, "Player.Status.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Sprint, "Player.Status.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_ToggleTargetAim, "Player.Status.ToggleTargetAim");

	/*SHARED ABILITY TAGS*/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_LightAttackHitReact, "Shared.Ability.LightAttackHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HeavyAttackHitReact, "Shared.Ability.HeavyAttackHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	/** GAMEPLAY EVENTS **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipKatana, "Player.Event.EquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnequipKatana, "Player.Event.UnequipKatana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_StickyAttackEffect, "Player.Event.StickyAttackEffect");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_BlockSuccess, "Player.Event.BlockSuccess");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_BlockFailed, "Player.Event.BlockFailed");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Fall, "Player.Event.Fall");

	/**SHARED GAMEPLAY EVENTS**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_RegisterHit, "Shared.Event.RegisterHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_EffectSpec_BaseDamage, "Shared.EffectSpec.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_AttackHitReact, "Shared.Event.AttackHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_LightAttackHitReact, "Shared.Event.LightAttackHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HeavyAttackHitReact, "Shared.Event.HeavyAttackHitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
}