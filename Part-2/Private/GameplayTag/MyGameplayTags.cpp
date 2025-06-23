// Aditya Singh Gajawat All Rights Reserved

#include "GameplayTag/MyGameplayTags.h"
namespace WarriorGameplayTags
{
	/** INPUT TAGS **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipKatana, "InputTag.EquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnquipKatana, "InputTag.UnquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Light_Katana, "InputTag.Attack.Light.Katana");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Heavy_Katana, "InputTag.Attack.Heavy.Katana");

	/** PLAYER TAGS **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Katana, "Player.Weapon.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Effect_Attack_Light, "Player.Effect.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Effect_Attack_Heavy, "Player.Effect.Attack.Heavy");

	/*ABILITY TAGS (MAINLY USED FOR BLOCKING OTHER ABILITY WHILE DOING ONE)*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OnEquip_Katana, "Player.Ability.OnEquip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OnUnequip_Katana, "Player.Ability.OnUnequip.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Katana, "Player.Ability.Attack.Light.Katana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Katana, "Player.Ability.Attack.Heavy.Katana");

	/** GAMEPLAY EVENTS **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipKatana, "Player.Event.EquipKatana");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnequipKatana, "Player.Event.UnequipKatana");
	/**SHARED GAMEPLAY EVENTS**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_RegisterHit, "Shared.Event.RegisterHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_EffectSpec_BaseDamage, "Shared.EffectSpec.BaseDamage");
}