#include "CommonGameplayTags.h"

#include "CommonLogChannels.h"
#include "GameplayTagsManager.h"


namespace CommonGameplayTags
{
#pragma region 属性


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Essence,
	                               "Fei.Attribute.Essence",
	                               "元精");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Qi,
	                               "Fei.Attribute.Qi",
	                               "元炁");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Spirit,
	                               "Fei.Attribute.Spirit",
	                               "元神");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Metal,
	                               "Fei.Attribute.Metal",
	                               "五行属性-金");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Wood,
	                               "Fei.Attribute.Wood",
	                               "五行属性-木");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Water,
	                               "Fei.Attribute.Water",
	                               "五行属性-水");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Fire,
	                               "Fei.Attribute.Fire",
	                               "五行属性-火");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Earth,
	                               "Fei.Attribute.Earth",
	                               "五行属性-土");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_JiRou,
	                               "Fei.Attribute.JiRou",
	                               "肌肉");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_JinGu,
	                               "Fei.Attribute.JinGu",
	                               "筋骨");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_QiXue,
	                               "Fei.Attribute.QiXue",
	                               "气血");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_DanTian,
	                               "Fei.Attribute.DanTian",
	                               "丹田");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_JingMai,
	                               "Fei.Attribute.JingMai",
	                               "经脉");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_QiaoXue,
	                               "Fei.Attribute.QiaoXue",
	                               "窍穴");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Zhenling,
	                               "Fei.Attribute.Zhenling",
	                               "真灵");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_SanHun,
	                               "Fei.Attribute.SanHun",
	                               "三魂");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_QiPo,
	                               "Fei.Attribute.QiPo",
	                               "七魄");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Health,
	                               "Fei.Attribute.Health",
	                               "HP");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_MaxHealth,
	                               "Fei.Attribute.MaxHealth",
	                               "HP上限");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Mana,
	                               "Fei.Attribute.Mana",
	                               "MP");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_MaxMana,
	                               "Fei.Attribute.MaxMana",
	                               "MP上限");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Soul,
	                               "Fei.Attribute.Soul",
	                               "SP");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_MaxSoul,
	                               "Fei.Attribute.MaxSoul",
	                               "SP上限");


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_BaseAttack,
	                               "Fei.Attribute.BaseAttack",
	                               "基础攻击");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_AttackPower,
	                               "Fei.Attribute.AttackPower",
	                               "攻击力");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_BaseDefense,
	                               "Fei.Attribute.BaseDefense",
	                               "基础防御");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_DefensePower,
	                               "Fei.Attribute.DefensePower",
	                               "防御力");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_HealthRegeneration,
	                               "Fei.Attribute.HealthRegeneration",
	                               "生命恢复");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_ManaRegeneration,
	                               "Fei.Attribute.ManaRegeneration",
	                               "法力恢复");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_SoulRegeneration,
	                               "Fei.Attribute.SoulRegeneration",
	                               "魂力恢复");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_AttackSpeed,
	                               "Fei.Attribute.AttackSpeed",
	                               "攻击速度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_MoveSpeed,
	                               "Fei.Attribute.MoveSpeed",
	                               "移动速度");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_CastSpeed,
	                               "Fei.Attribute.CastSpeed",
	                               "施法速度");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Accurate,
	                               "Fei.Attribute.Accurate",
	                               "精准");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Dodge,
	                               "Fei.Attribute.Dodge",
	                               "闪避");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Critical,
	                               "Fei.Attribute.Critical",
	                               "会心");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Parry,
	                               "Fei.Attribute.Parry",
	                               "护心");

	//================================================

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Intelligence,
	                               "Fei.Attribute.Intelligence",
	                               "智商");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Emotional,
	                               "Fei.Attribute.Emotional",
	                               "情商");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Insight,
	                               "Fei.Attribute.Insight",
	                               "悟性");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Willpower,
	                               "Fei.Attribute.Willpower",
	                               "定力");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Luck,
	                               "Fei.Attribute.Luck",
	                               "气运");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Attribute_Karma,
	                               "Fei.Attribute.Karma",
	                               "业力");


#pragma endregion

#pragma region 输入
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input,
	                               "Fei.Input",
	                               "输入");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Confirm,
	                               "Fei.Input.Confirm",
	                               "输入-确认");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Cancel,
	                               "Fei.Input.Cancel",
	                               "输入-取消");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_LeftMouse,
	                               "Fei.Input.LeftMouse",
	                               "输入-鼠标左键");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_RightMouse,
	                               "Fei.Input.RightMouse",
	                               "输入-鼠标右键");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Move,
	                               "Fei.Input.Move",
	                               "输入-移动");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Look,
	                               "Fei.Input.Look",
	                               "输入-移动镜头");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Jump,
	                               "Fei.Input.Jump",
	                               "输入-跳");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Dodge,
	                               "Fei.Input.Dodge",
	                               "输入-闪");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Skill_01,
	                               "Fei.Input.Skill.01",
	                               "输入-技能01");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Skill_02,
	                               "Fei.Input.Skill.02",
	                               "输入-技能02");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Skill_03,
	                               "Fei.Input.Skill.03",
	                               "输入-技能03");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Skill_04,
	                               "Fei.Input.Skill.04",
	                               "输入-技能04");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Input_Skill_05,
	                               "Fei.Input.Skill.05",
	                               "输入-技能05");

#pragma endregion

#pragma region 伤害
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Physical,
	                               "Fei.Damage.Physical",
	                               "物理伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_DamageDefense_Physical,
	                               "Fei.DamageDefense.Physical",
	                               "物理伤害-防御");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Magical,
	                               "Fei.Damage.Magical",
	                               "法术伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_DamageDefense_Magical,
	                               "Fei.DamageDefense.Magical",
	                               "法术伤害-防御");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Soul,
	                               "Fei.Damage.Soul",
	                               "灵魂伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_DamageDefense_Soul,
	                               "Fei.DamageDefense.Soul",
	                               "灵魂伤害-防御");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Essence,
	                               "Fei.Damage.Essence",
	                               "精元伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_DamageDefense_Essence,
	                               "Fei.DamageDefense.Essence",
	                               "精元伤害防御");


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Metal,
	                               "Fei.Damage.Metal",
	                               "元素伤害-金");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Wood,
	                               "Fei.Damage.Wood",
	                               "元素伤害-木");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Water,
	                               "Fei.Damage.Water",
	                               "元素伤害-水");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Fire,
	                               "Fei.Damage.Fire",
	                               "元素伤害-火");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Damage_Earth,
	                               "Fei.Damage.Earth",
	                               "元素伤害-土");


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Effect_HitReact,
	                               "Fei.Effect.HitReact",
	                               "受击反应");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Meta_IncomingXP,
	                               "Fei.Meta.IncomingXP",
	                               "元属性-经验");
#pragma endregion

#pragma region 技能
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Ability,
	                               "Fei.Ability",
	                               "技能");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Ability_Trigger_Manual,
	                               "Fei.Ability.Trigger.Manual",
	                               "技能-触发-手动");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Ability_Trigger_Attack,
	                               "Fei.Ability.Trigger.Attack",
	                               "技能-触发-攻击");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Ability_Trigger_Hit,
	                               "Fei.Ability.Trigger.Hit",
	                               "技能-触发-受击");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_Ability_Trigger_Spell,
	                               "Fei.Ability.Trigger.Spell",
	                               "技能-触发-施法");

#pragma endregion

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fei_AnimNotify,
	                               "Fei.AnimNotify",
	                               "动画通知");
	// ================================

	// 伤害列表（伤害和抗性）
	const TMap<FGameplayTag, FGameplayTag> FeiDamageTypesDataMap =
	{
		// 伤害和对应抗性
		{Fei_Damage_Physical, Fei_DamageDefense_Physical},
		{Fei_Damage_Magical, Fei_DamageDefense_Magical},
		{Fei_Damage_Soul, Fei_DamageDefense_Soul},
		{Fei_Damage_Essence, Fei_DamageDefense_Essence},

		// 五行相克
		{Fei_Damage_Metal, Fei_Attribute_Fire},
		{Fei_Damage_Wood, Fei_Attribute_Metal},
		{Fei_Damage_Water, Fei_Attribute_Earth},
		{Fei_Damage_Fire, Fei_Attribute_Water},
		{Fei_Damage_Earth, Fei_Attribute_Wood},
	};

	// 五行相克
	const TMap<FGameplayTag, FGameplayTag> FeiFiveGenerationMap =
	{
		// 五行相克
		{Fei_Attribute_Metal, Fei_Attribute_Water},
		{Fei_Attribute_Wood, Fei_Attribute_Fire},
		{Fei_Attribute_Water, Fei_Attribute_Wood},
		{Fei_Attribute_Fire, Fei_Attribute_Earth},
		{Fei_Attribute_Earth, Fei_Attribute_Metal},
	};

	// 五行相克
	const TMap<FGameplayTag, FGameplayTag> FeiFiveRestraintMap =
	{
		// 五行相克
		{Fei_Attribute_Metal, Fei_Attribute_Wood},
		{Fei_Attribute_Wood, Fei_Attribute_Earth},
		{Fei_Attribute_Water, Fei_Attribute_Fire},
		{Fei_Attribute_Fire, Fei_Attribute_Metal},
		{Fei_Attribute_Earth, Fei_Attribute_Water},
	};

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogCommon, Display,
					       TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."),
					       *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}


/*
FFeiGameplayTags FFeiGameplayTags::GameplayTags;


	GameplayTags.Fei_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Fei.Meta.IncomingXP"), FString("Meta tag IncomingXP"));

	GameplayTags.FeiDamageTypesDataMap.Add(GameplayTags.Fei_Damage_Physical,
	                                       GameplayTags.Fei_Attribute_PhysicalResistance);
	GameplayTags.FeiDamageTypesDataMap.Add(GameplayTags.Fei_Damage_Magical,
	                                       GameplayTags.Fei_Attribute_MagicalResistance);


	GameplayTags.FeiDamageBuffDataMap.Add(GameplayTags.Fei_Damage_Fire, GameplayTags.Fei_Buff_Burn);
	GameplayTags.FeiDamageBuffDataMap.Add(GameplayTags.Fei_Damage_Water, GameplayTags.Fei_Buff_Frost);
	GameplayTags.FeiDamageBuffDataMap.Add(GameplayTags.Fei_Damage_Physical, GameplayTags.Fei_Buff_Stun);
	GameplayTags.FeiDamageBuffDataMap.Add(GameplayTags.Fei_Damage_Wood, GameplayTags.Fei_Buff_Poison);
}
*/
