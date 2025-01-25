// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryLibrary.h"
#include "SentryEvent.h"
#include "SentryBreadcrumb.h"
#include "SentryUser.h"
#include "SentryUserFeedback.h"
#include "SentryId.h"
#include "SentryAttachment.h"
#include "SentryTransactionContext.h"

#include "HAL/PlatformSentryAttachment.h"
#include "HAL/PlatformSentryBreadcrumb.h"
#include "HAL/PlatformSentryEvent.h"
#include "HAL/PlatformSentryTransactionContext.h"
#include "HAL/PlatformSentryUser.h"
#include "HAL/PlatformSentryUserFeedback.h"

#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

USentryEvent* USentryLibrary::CreateSentryEvent(const FString& Message, ESentryLevel Level)
{
	USentryEvent* Event = USentryEvent::Create(CreateSharedSentryEvent());

	if (!Message.IsEmpty())
		Event->SetMessage(Message);

	Event->SetLevel(Level);

	return Event;
}

USentryUser* USentryLibrary::CreateSentryUser(const FString& Email, const FString& Id, const FString& Username, const FString& IpAddress, const TMap<FString, FString>& Data)
{
	USentryUser* User = USentryUser::Create(CreateSharedSentryUser());

	if (!Email.IsEmpty())
		User->SetEmail(Email);
	if (!Id.IsEmpty())
		User->SetId(Id);
	if (!Username.IsEmpty())
		User->SetUsername(Username);
	if (!IpAddress.IsEmpty())
		User->SetIpAddress(IpAddress);

	if (Data.Num() > 0)
		User->SetData(Data);

	return User;
}

USentryUserFeedback* USentryLibrary::CreateSentryUserFeedback(USentryId* EventId, const FString& Name, const FString& Email, const FString& Comments)
{
	USentryUserFeedback* UserFeedback = USentryUserFeedback::Create(CreateSharedSentryUserFeedback(EventId->GetNativeObject()));

	if (!Name.IsEmpty())
		UserFeedback->SetName(Name);
	if (!Email.IsEmpty())
		UserFeedback->SetEmail(Email);
	if (!Comments.IsEmpty())
		UserFeedback->SetComment(Comments);

	return UserFeedback;
}

USentryBreadcrumb* USentryLibrary::CreateSentryBreadcrumb(const FString& Message, const FString& Type, const FString& Category,
	const TMap<FString, FString>& Data, ESentryLevel Level)
{
	TSharedPtr<ISentryBreadcrumb> NativeBreadcrumb = MakeShareable(new FPlatformSentryBreadcrumb);
	NativeBreadcrumb->Initialize();
	NativeBreadcrumb->SetMessage(Message);
	NativeBreadcrumb->SetCategory(Category);
	NativeBreadcrumb->SetType(Type);
	NativeBreadcrumb->SetData(Data);
	NativeBreadcrumb->SetLevel(Level);

	USentryBreadcrumb* Breadcrumb = USentryBreadcrumb::Create(NativeBreadcrumb);

	return Breadcrumb;
}

USentryAttachment* USentryLibrary::CreateSentryAttachmentWithData(const TArray<uint8>& Data, const FString& Filename, const FString& ContentType)
{
	TSharedPtr<ISentryAttachment> NativeAttachment = MakeShareable(new FPlatformSentryAttachment);
	NativeAttachment->Initialize(Data, Filename, ContentType);

	return USentryAttachment::Create(NativeAttachment);
}

USentryAttachment* USentryLibrary::CreateSentryAttachmentWithPath(const FString& Path, const FString& Filename, const FString& ContentType)
{
	TSharedPtr<ISentryAttachment> NativeAttachment = MakeShareable(new FPlatformSentryAttachment);
	NativeAttachment->Initialize(Path, Filename, ContentType);

	return USentryAttachment::Create(NativeAttachment);
}

USentryTransactionContext* USentryLibrary::CreateSentryTransactionContext(const FString& Name, const FString& Operation)
{
	return USentryTransactionContext::Create(CreateSharedSentryTransactionContext(Name, Operation));
}

TArray<uint8> USentryLibrary::StringToBytesArray(const FString& InString)
{
	TArray<uint8> byteArray;
	byteArray.AddUninitialized(InString.Len());

	uint8* byteArrayPtr = byteArray.GetData();

	int32 NumBytes = 0;
	const TCHAR* CharPos = *InString;

	while (*CharPos && NumBytes < TNumericLimits<int16>::Max())
	{
		byteArrayPtr[NumBytes] = (int8)(*CharPos);
		CharPos++;
		++NumBytes;
	}

	return byteArray;
}

FString USentryLibrary::ByteArrayToString(const TArray<uint8>& Array)
{
	return BytesToString(Array.GetData(), Array.Num());
}

FString USentryLibrary::SaveStringToFile(const FString& InString, const FString& Filename)
{
	FString filePath = FPaths::Combine(FPaths::ProjectPersistentDownloadDir(), Filename);

	FFileHelper::SaveStringToFile(InString, *filePath);

	return IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*filePath);
}
