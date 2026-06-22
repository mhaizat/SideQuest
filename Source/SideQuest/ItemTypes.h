#pragma once

#include "CoreMinimal.h"
#include "ItemTypes.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Basic UMETA(DisplayName = "Basic"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EAffixType : uint8
{
	None UMETA(DisplayName = "None"),

	CritChance UMETA(DisplayName = "Crit Chance"),
	CritDamage UMETA(DisplayName = "Crit Damage"),
	AttackSpeed UMETA(DisplayName = "Attack Speed"),
	BonusDamage UMETA(DisplayName = "Bonus Damage"),

	ArmorPenetration UMETA(DisplayName = "Armor Penetration"),
	Health UMETA(DisplayName = "Health"),
	Armor UMETA(DisplayName = "Armor"),
	LifeSteal UMETA(DisplayName = "Life Steal"),

	MovementSpeed UMETA(DisplayName = "Movement Speed"),
	CooldownReduction UMETA(DisplayName = "Cooldown Reduction")
};

USTRUCT(BlueprintType)
struct FAffixDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffixType Type = EAffixType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxValue = 0.f;
};

USTRUCT(BlueprintType)
struct FAffixInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAffixType Type = EAffixType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAffixInstance> Affixes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 0.f;
};
