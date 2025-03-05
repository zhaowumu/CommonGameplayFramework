#include "CommonDevelopSettings.h"

TArray<FCommonSettingCfgData> UCommonDeveloperSettings::GetAllGameSettingDataList()
{
	const UCommonDeveloperSettings* DTSettings = GetDefault<UCommonDeveloperSettings>();

	TArray<FCommonSettingCfgData> OutSettings;

	if (const UDataTable* DataTable = DTSettings->GameSettingDataTable.LoadSynchronous())
	{
		TArray<FCommonSettingCfgData*> AllSettingDatas;
		DataTable->GetAllRows<FCommonSettingCfgData>("FindFCommonSettingData", AllSettingDatas);

		for (auto Setting : AllSettingDatas)
		{
			OutSettings.Add(*Setting);
		}
	}

	return OutSettings;
}
