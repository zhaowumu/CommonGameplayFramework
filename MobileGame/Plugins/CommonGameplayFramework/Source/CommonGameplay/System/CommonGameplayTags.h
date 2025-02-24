#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"


namespace CommonGameplayTags
{
	COMMONGAMEPLAY_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// =================声明Native GameplayTag=================
#pragma region 属性

	// 元精
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Essence);
	// 元炁
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Qi);
	// 元神
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Spirit);


	// 五行元素
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Metal);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Wood);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Water);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Fire);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Earth);


	// 身体-外分为 肌肉(皮肉)、筋骨、气血
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_JiRou);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_JinGu);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_QiXue);
	

	// 内分-[丹田]气海（储存法力）、[经脉]玄关（能量通道）、[窍穴]灵台/灵窍（灵气的吸收效率）
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_DanTian);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_JingMai);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_QiaoXue);

	// 魂分-真灵[神识、显化]-神宫[三魂：主意识，记忆]-紫府[七魄：本能，条件反射]
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Zhenling);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_SanHun);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_QiPo);
	
	// 身体健康（躯壳气血）元精+血肉  (具体表现为体修的血量高)
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Health);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_MaxHealth);

	// 身体健康（躯壳法力）元气+丹田  (具体表现为法修的法力高)
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Mana);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_MaxMana);

	// 身体健康（躯壳魂力）元神+真灵  (具体表现为魂修的神力高)
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Soul);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_MaxSoul);


	/*
	 * 徒手攻击力（ 基础攻击力 = [丹田/皮肉/真灵]*系数+主五行） 
     * 表现为：体修为肌肉力量强度，法修为灵气外放[丹田能量精纯度]，魂修为真灵强度
     * 徒手防御力（基础防御力 = [经脉/筋骨/三魂]*系数+主五行） 
     * 表现为：体修筋骨强悍，法修为灵气通过经脉护体，魂修主动防御本能
     * 总攻击力 = 基础攻击力 +*（武器+装备+心法+技能+buff）
     * 总防御力 = 基础防御力 +*（武器+装备+心法+技能+buff）
	 */

	// 基础攻击
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_BaseAttack);
	// 攻击力
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_AttackPower);

	// 基础防御
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_BaseDefense);
	// 护体防御力
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_DefensePower);
	
	// 生命恢复 =（血肉*系数*主五行）
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_HealthRegeneration);
	// 法恢复 =（灵窍*系数*主五行） 
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_ManaRegeneration);
	// 魂力恢复 =（七魄*系数*主五行）
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_SoulRegeneration);

	// 攻击速度
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_AttackSpeed);
	// 移动速度
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_MoveSpeed);
	// 施法速度（不影响无CD技能[普通攻击]）
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_CastSpeed);

	//3.技能（伤害=消耗量*技能放大公式）
	
	// 精准
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Accurate);
	// 闪避
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Dodge);

	// 会心（破体）奋力一击
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Critical);
	// 护心（！破绽）护体
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Parry);

	// ================================

	// 智商
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Intelligence);
	// 情商
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Emotional);
	// 悟性
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Insight);
	// 定力
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Willpower);
	// 气运
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Luck);
	// 业力
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Attribute_Karma);

#pragma endregion

#pragma region 输入
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input);

	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Confirm);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Cancel);

	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_LeftMouse);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_LeftMouse);

	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Move);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Look);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Jump);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Dodge);

	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Skill_01);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Skill_02);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Skill_03);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Skill_04);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Input_Skill_05);
#pragma endregion


#pragma region 伤害

	/* // 正确顺序，木火土金水(木毒、电、雷、冰、磁) 阳刚 阴柔
	//金>> 电、磁（庚阳金-剑戟之金[电]麻痹，辛阴金-纯阴饰金[磁]吸引）
	//木>> 风、雷，（甲阳木-大树[风]乱流，乙阴木-花草[雷]爆炸）
	//水>> 药、毒 （壬阳水-江河之水[冰]冻，癸阴水-为纯阴之水[毒]减速，又名雨露坑涧之水，它气化而得，其性静弱，有滋生万物之能，故为阴水，其水有形无体，随变而变，一生漂流。）
	//火>> 光、丹（丙阳火-太阳之火[炎]灼伤，丁阴火-灯烛之火[]）
	//土>> 石、腐（戊阳土-高山之石[石]晕，己阴土-田园之土[尸]复生）

	精气神
	八字转灵根？？？
	三魂七魄

	五行（金、木、水、火、土）可以根据其性质和作用划分为阴阳，具体如下：
	1. 金
	阳金：刚硬、外向，代表锋利的刀剑、金属工具等。
	阴金：柔和、内敛，代表精致的饰品、珠宝等。
	2. 木
	阳木：向上生长、挺拔，代表高大的树木、竹子等。
	阴木：柔软、弯曲，代表藤蔓、花草等。
	3. 水
	阳水：奔流、动态，代表江河、大海等大水流。
	阴水：静止、内敛，代表湖泊、井水、露水等。
	4. 火
	阳火：猛烈、炽热，代表烈日、熊熊大火等。
	阴火：柔和、温暖，代表烛光、星光等微弱的火光。
	5. 土
	阳土：坚固、厚重，代表高山、岩石等。
	阴土：柔软、滋养，代表田地、泥土等适合生长的土壤。


	八卦与五行及其属性
	八卦	五行	象征属性	自然现象	方位
	乾（☰）	金	刚健、主宰	天	西北
	兑（☱）	金	喜悦、柔顺	泽	正西
	离（☲）	火	光明、依附	火	正南
	震（☳）	木	动荡、生发	雷	正东
	巽（☴）	木	进入、柔顺	风	东南
	坎（☵）	水	险难、流动	水	正北
	艮（☶）	土	静止、止步	山	东北
	坤（☷）	土	包容、柔顺	地	西南
	八卦与象征意义
	乾：阳刚之极，代表天，主刚健、创始、主宰。
	兑：阳中有阴，象征泽，主愉悦、沟通。
	离：阴中有阳，象征火，主光明、文化、依附。
	震：阴阳互动，象征雷，主震动、生发、行动力。
	巽：阴中含阴，象征风，主柔顺、进入、渗透。
	坎：阳中有阴，象征水，主险难、流动、智谋。
	艮：阴阳并存，象征山，主稳定、静止、止步。
	坤：至阴之极，代表地，主包容、生养、承载。

	基础自然元素
	火（Fire）：火球术、燃烧之刃、火焰风暴。

	示例：**《魔兽世界》**中的火焰法师，擅长高爆发群体伤害。
	示例：**《最终幻想》**中的“火系魔法”（Fire/Fira/Firaga）。
	水（Water）：水流冲击、治疗之泉、召唤潮汐。

	示例：**《英雄联盟》**中的娜美（Nami），利用水进行控制和治疗。
	示例：**《塞尔达传说》**中的水属性神庙及其谜题设计。
	土（Earth）：地震术、石墙防御、召唤岩石怪物。

	示例：**《魔兽争霸3》**中的牛头人酋长，使用地震技能。
	示例：**《炉石传说》**中的“石拳地震术”卡牌。
	空气/风（Air/Wind）：风刃、飓风、风速加持。

	示例：**《龙与地下城》**中的空气元素生物。
	示例：**《火焰纹章》**中的风系魔法（克制飞行单位）。
	组合自然元素
	冰（Ice）：冰锥术、暴风雪、寒冰牢笼。

	示例：**《冰封王座》**中的冰霜巨龙。
	示例：**《魔兽世界》**中的冰霜死亡骑士，利用冰冻和减速控制战局。
	雷（Lightning）：闪电链、雷暴、超速冲击。

	示例：**《最终幻想》**中的雷系魔法（Thunder/Thundara/Thundaga）。
	示例：**《守望先锋》**中的温斯顿，使用特斯拉电弧进行攻击。
	毒（Poison）：毒液喷射、瘟疫领域、腐蚀箭。

	示例：**《巫师3》**中的毒雾地带，玩家需避免进入。
	示例：**《暗黑破坏神2》**中的毒素技能（如毒标枪）。
	熔岩（Lava）：熔岩爆发、岩浆护盾、地裂术。

	示例：**《魔兽世界》**中的熔火之心副本。
	示例：**《宝可梦》**中的喷火驼（火与岩石的结合属性）。
	蒸汽（Steam）：蒸汽喷射、高温迷雾、蒸汽炮。

	示例：**《最终幻想》**中的蒸汽机关战斗环境。
	示例：**《雷霆战机》**中的蒸汽机器人敌人。
	2. 超自然元素扩展
	正义与邪恶对立
	光（Light）：圣光治疗、光之盾、驱散邪恶。

	示例：**《魔兽世界》**中的圣骑士（Paladin），以圣光之力治疗盟友。
	示例：**《龙与地下城》**中的神圣战士，使用光攻击亡灵。
	暗（Dark）：暗影箭、吸取生命、召唤亡灵。

	示例：**《黑暗之魂》**中的暗属性魔法，常用于强力攻击。
	示例：**《英雄联盟》**中的莫甘娜，利用暗影法术控制敌人。
	虚空与混沌
	虚空（Void）：湮灭射线、虚空召唤、传送术。

	示例：**《星际争霸》**中的虚空裂隙武器。
	示例：**《魔兽世界》**中的虚空行者恶魔。
	混沌（Chaos）：混乱爆发、随机传送、不可预测伤害。

	示例：**《战锤40K》**中的混沌军团，崇拜混沌之力。
	示例：**《最终幻想》**中的混乱骑士（Chaos Knight）。
	灵魂与精神
	灵魂（Spirit）：灵魂治愈、召唤先祖、灵魂冲击。

	示例：**《塞尔达传说》**中的灵魂之泉，可治愈玩家生命值。
	示例：**《鬼泣》**中的灵魂力量用于释放特殊攻击。
	梦境（Dream）：梦境入侵、催眠术、幻象攻击。

	示例：**《英雄联盟》**中的佐伊，利用梦境法术控制敌人。
	示例：**《宝可梦》**中的梦妖怪，擅长催眠和噩梦技能。
	3. 科学与幻想结合的扩展元素
	电（Electricity）：电磁脉冲、感电效果、闪电链。

	示例：**《守望先锋》**中的电磁技能（如黑影的EMP）。
	示例：**《龙珠Z》**中电气化的超级赛亚人形态。
	磁（Magnetism）：磁力牵引、金属操控、磁场防护。

	示例：**《X战警》**中的万磁王，控制金属物体。
	示例：**《合金装备》**中的磁场干扰技能。
	辐射（Radiation）：辐射爆发、腐蚀效应、瘟疫领域。

	示例：**《辐射4》**中的核辐射环境。
	示例：**《暗黑破坏神》**中放射性毒素技能。
	4. 高级与独特元素扩展
	时间（Time）：时间冻结、加速、回溯。

	示例：**《时空幻境》**中的时间操控解谜玩法。
	示例：**《英雄联盟》**中的艾克（Ekko），可以操控时间逆转战局。
	空间（Space）：黑洞、传送术、空间压缩。

	示例：**《星际争霸》**中的空间跳跃技术。
	示例：**《守望先锋》**中的黑影（Sombra）使用传送装置移动。
	重力（Gravity）：引力场、失重效果、重力打击。

	示例：**《质量效应》**中的重力操控武器。
	示例：**《火焰纹章》**中通过重力技能减缓敌人行动。
	
	*/

	// 伤害（发出的伤害类型） - 物理、法术、灵魂、精元
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Physical);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_DamageDefense_Physical);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Magical);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_DamageDefense_Magical);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Soul);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_DamageDefense_Soul);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Essence);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_DamageDefense_Essence);

	// 五行伤害
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Metal);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Wood);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Water);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Fire);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Damage_Earth);


	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Effect_HitReact);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Meta_IncomingXP);
#pragma endregion


#pragma region 技能
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Ability);

	// 触发方式-手动-攻击时-受击时-施法时
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Ability_Trigger_Manual);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Ability_Trigger_Attack);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Ability_Trigger_Hit);
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_Ability_Trigger_Spell);
#pragma endregion

	// 动画通知
	COMMONGAMEPLAY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fei_AnimNotify);

	// 伤害类型列表
	COMMONGAMEPLAY_API extern const TMap<FGameplayTag, FGameplayTag> FeiDamageTypesDataMap;
	// 五行相生
	COMMONGAMEPLAY_API extern const TMap<FGameplayTag, FGameplayTag> FeiFiveGenerationMap;
	// 五行相克
	COMMONGAMEPLAY_API extern const TMap<FGameplayTag, FGameplayTag> FeiFiveRestraintMap;
};


/*
/**
 * FeiGameplayTags
 *
 * Singleton native Gameplay Tags
 #1#
struct FFeiGameplayTags
{
public:
	static const FFeiGameplayTags& Get() { return GameplayTags; }
	static void InitNativeGameplayTags();

#pragma region 属性
	FGameplayTag Fei_Attribute_PhysicalResistance;
	FGameplayTag Fei_Attribute_MagicalResistance;
	
	FGameplayTag Fei_Attribute_Armor;
#pragma endregion

#pragma region 伤害

	TMap<FGameplayTag, FGameplayTag> FeiDamageTypesDataMap;
	TMap<FGameplayTag, FGameplayTag> FeiDamageBuffDataMap;
#pragma endregion

#pragma region Skill

	FGameplayTag Fei_Skill_Test;

	// 技能输入
	FGameplayTag Fei_Skill_Input;

	// 主动触发技能
	FGameplayTag Fei_Skill_Trigger_Active;

	// 被动触发技能
	FGameplayTag Fei_Skill_Trigger_Passive;

#pragma endregion

#pragma region buff

	FGameplayTag Fei_Buff_Burn;
	FGameplayTag Fei_Buff_Stun;
	FGameplayTag Fei_Buff_Frost;
	FGameplayTag Fei_Buff_Poison;
#pragma endregion


	FGameplayTag Fei_Effect_HitReact;

#pragma region 输入按键
	// player按键
	FGameplayTag Fei_InputTag_LMB;
	FGameplayTag Fei_InputTag_RMB;
	FGameplayTag Fei_InputTag_Key1;
	FGameplayTag Fei_InputTag_Key2;
	FGameplayTag Fei_InputTag_Key3;
	FGameplayTag Fei_InputTag_Key4;

	FGameplayTag Fei_InputTag_Passive1;
	FGameplayTag Fei_InputTag_Passive2;
	FGameplayTag Fei_InputTag_Passive3;

#pragma endregion

	// 技能通用触发
	FGameplayTag Fei_Ability_Attack;

	// 火焰箭
	FGameplayTag Fei_Ability_FireBolt;
	// 雷电箭
	FGameplayTag Fei_Ability_Lightning;
	// 火焰箭CD
	FGameplayTag Fei_Cooldown_FireBolt;
	// 雷电CD
	FGameplayTag Fei_Cooldown_Lightning;


	// 元属性
	FGameplayTag Fei_Meta_IncomingXP;

	// 技能属性
	FGameplayTag Fei_Ability_Type_None;
	FGameplayTag Fei_Ability_Type_Offensive;
	FGameplayTag Fei_Ability_Type_Passive;

	// 技能状态
	FGameplayTag Fei_Ability_Status_Locked;
	FGameplayTag Fei_Ability_Status_Eligible;
	FGameplayTag Fei_Ability_Status_Unlocked;
	FGameplayTag Fei_Ability_Status_Equipped;

protected:
private:
	static FFeiGameplayTags GameplayTags;
};
*/
