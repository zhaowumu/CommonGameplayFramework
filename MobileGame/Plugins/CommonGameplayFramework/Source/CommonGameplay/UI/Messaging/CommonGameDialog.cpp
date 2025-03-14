// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonGameDialog.h"

#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "CommonGameplay/UI/Widget/CommonButtonWithText.h"
#include "Components/DynamicEntryBox.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif


#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonGameDialog)

#define LOCTEXT_NAMESPACE "Messaging"

UCommonGameDialogDescriptor* UCommonGameDialogDescriptor::CreateConfirmationOk(const FText& Header, const FText& Body)
{
	UCommonGameDialogDescriptor* Descriptor = NewObject<UCommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = ECommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	Descriptor->ButtonActions.Add(ConfirmAction);

	return Descriptor;
}

UCommonGameDialogDescriptor* UCommonGameDialogDescriptor::CreateConfirmationOkCancel(
	const FText& Header, const FText& Body)
{
	UCommonGameDialogDescriptor* Descriptor = NewObject<UCommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = ECommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	FConfirmationDialogAction CancelAction;
	CancelAction.Result = ECommonMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UCommonGameDialogDescriptor* UCommonGameDialogDescriptor::CreateConfirmationYesNo(
	const FText& Header, const FText& Body)
{
	UCommonGameDialogDescriptor* Descriptor = NewObject<UCommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = ECommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FConfirmationDialogAction DeclineAction;
	DeclineAction.Result = ECommonMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);

	return Descriptor;
}

UCommonGameDialogDescriptor* UCommonGameDialogDescriptor::CreateConfirmationYesNoCancel(
	const FText& Header, const FText& Body)
{
	UCommonGameDialogDescriptor* Descriptor = NewObject<UCommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = ECommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FConfirmationDialogAction DeclineAction;
	DeclineAction.Result = ECommonMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	FConfirmationDialogAction CancelAction;
	CancelAction.Result = ECommonMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UCommonGameDialog::UCommonGameDialog()
{
}

void UCommonGameDialog::SetupDialog(UCommonGameDialogDescriptor* Descriptor,
                                    FCommonMessagingResultDelegate ResultCallback)
{
	// 设置标题和描述
	Text_Title->SetText(Descriptor->Header);
	RichText_Description->SetText(Descriptor->Body);

	// 重置按钮列表，确保按钮容器为空，并清除所有按钮的点击事件
	EntryBox_Buttons->Reset<UCommonButtonWithText>([](UCommonButtonWithText& Button)
	{
		Button.OnClicked().Clear();
	});

	// 遍历 Descriptor 传入的按钮配置，逐个创建按钮
	for (const FConfirmationDialogAction& Action : Descriptor->ButtonActions)
	{
		FDataTableRowHandle ActionRow;

		// 根据不同的用户交互结果，绑定不同的默认输入动作
		switch (Action.Result)
		{
		case ECommonMessagingResult::Confirmed:
			// 确认按钮使用默认点击动作
			ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;
		case ECommonMessagingResult::Declined:
			// 拒绝按钮使用默认返回动作
			ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case ECommonMessagingResult::Cancelled:
			// 取消按钮使用预设的 CancelAction
			ActionRow = CancelAction;
			break;
		default:
			// 遇到未定义的操作，触发 ensure 以便调试时捕获
			ensure(false);
			continue; // 跳过该按钮，避免无效操作
		}

		// 创建一个新的按钮条目
		UCommonButtonWithText* Button = EntryBox_Buttons->CreateEntry<UCommonButtonWithText>();
		// 设置按钮的触发输入行为
		Button->SetTriggeringInputAction(ActionRow);
		// 绑定按钮点击事件，当按钮被点击时，调用 CloseConfirmationWindow 并传递相应的用户操作结果
		Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
		// 设置按钮文本，使用 Action 提供的显示文本
		Button->SetButtonText(Action.OptionalDisplayText);
	}

	// 记录回调函数，方便后续在对话框关闭时调用
	OnResultCallback = ResultCallback;
}

void UCommonGameDialog::KillDialog()
{
}

void UCommonGameDialog::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Border_TapToCloseZone->OnMouseButtonDownEvent.BindDynamic(
		this, &UCommonGameDialog::HandleTapToCloseZoneMouseButtonDown);
}

FEventReply UCommonGameDialog::HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry,
                                                                   const FPointerEvent& MouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = FReply::Unhandled();

	if (MouseEvent.IsTouchEvent() || MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseConfirmationWindow(ECommonMessagingResult::Declined);
		Reply.NativeReply = FReply::Handled();
	}

	return Reply;
}


void UCommonGameDialog::CloseConfirmationWindow(ECommonMessagingResult Result)
{
	DeactivateWidget();
	if (OnResultCallback.IsBound())
	{
		OnResultCallback.Execute(Result);
	}
}


#if WITH_EDITOR
void UCommonGameDialog::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	if (CancelAction.IsNull())
	{
		CompileLog.Error(FText::Format(FText::FromString(TEXT("{0} has unset property: CancelAction.")), FText::FromString(GetName())));
	}
}
#endif

#undef LOCTEXT_NAMESPACE
