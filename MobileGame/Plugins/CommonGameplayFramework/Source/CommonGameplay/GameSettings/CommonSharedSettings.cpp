#include "CommonSharedSettings.h"

#include "Internationalization/Culture.h"

UCommonSharedSettings::UCommonSharedSettings()
{
}

void UCommonSharedSettings::SaveSettings()
{
}

void UCommonSharedSettings::ApplySettings()
{
}

const FString& UCommonSharedSettings::GetPendingCulture() const
{
	return PendingCulture;
}

void UCommonSharedSettings::SetPendingCulture(const FString& NewCulture)
{
	PendingCulture = NewCulture;
	bResetToDefaultCulture = false;
	bIsDirty = true;
}

void UCommonSharedSettings::OnCultureChanged()
{
	ClearPendingCulture();
	bResetToDefaultCulture = false;
}

void UCommonSharedSettings::ClearPendingCulture()
{
	PendingCulture.Reset();
}

bool UCommonSharedSettings::IsUsingDefaultCulture() const
{
	FString Culture;
	GConfig->GetString(TEXT("Internationalization"), TEXT("Culture"), Culture, GGameUserSettingsIni);

	return Culture.IsEmpty();
}

void UCommonSharedSettings::ResetToDefaultCulture()
{
	ClearPendingCulture();
	bResetToDefaultCulture = true;
	bIsDirty = true;
}

void UCommonSharedSettings::ApplyCultureSettings()
{
	// 检查是否需要将文化设置重置为默认值
	if (bResetToDefaultCulture)
	{
		// 获取系统的默认文化设置
		const FCulturePtr SystemDefaultCulture = FInternationalization::Get().GetDefaultCulture();
		check(SystemDefaultCulture.IsValid());

		// 获取默认文化的名称（例如 "en-US"） 尝试将当前文化设置为系统默认文化
		const FString CultureToApply = SystemDefaultCulture->GetName();
		if (FInternationalization::Get().SetCurrentCulture(CultureToApply))
		{
			// Clear this string
			// 如果设置成功，清除配置文件中的文化设置项，恢复为默认值 立即写入配置文件
			GConfig->RemoveKey(TEXT("Internationalization"), TEXT("Culture"), GGameUserSettingsIni);
			GConfig->Flush(false, GGameUserSettingsIni);
		}
		// 重置标志位，表示已经处理过重置操作
		bResetToDefaultCulture = false;
	}
	// 如果用户选择了新的文化设置（PendingCulture 不为空）
	else if (!PendingCulture.IsEmpty())
	{
		// 由于 SetCurrentCulture 可能会触发广播事件并清空 PendingCulture，
		// 所以这里先保存一份副本
		const FString CultureToApply = PendingCulture;
		if (FInternationalization::Get().SetCurrentCulture(CultureToApply))
		{
			// Note: This is intentionally saved to the users config
			// We need to localize text before the player logs in and very early in the loading screen
			// 如果设置成功，将用户选择的文化保存到配置文件中
			// 注意：这里特意保存到用户配置中，以便在玩家登录前或加载屏幕早期阶段使用
			GConfig->SetString(TEXT("Internationalization"), TEXT("Culture"), *CultureToApply, GGameUserSettingsIni);
			GConfig->Flush(false, GGameUserSettingsIni);
		}
		// 清除待处理的文化设置
		ClearPendingCulture();
	}
}

void UCommonSharedSettings::ResetCultureToCurrentSettings()
{
	ClearPendingCulture();
	bResetToDefaultCulture = false;
}
