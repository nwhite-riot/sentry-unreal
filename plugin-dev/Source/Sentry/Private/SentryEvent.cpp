// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryEvent.h"

#include "HAL/PlatformSentryEvent.h"

USentryEvent::USentryEvent()
{
	if (USentryEvent::StaticClass()->GetDefaultObject() != this)
	{
		NativeImpl = CreateSharedSentryEvent();
	}
}

USentryEvent* USentryEvent::CreateEventWithMessageAndLevel(const FString& Message, ESentryLevel Level)
{
	USentryEvent* Event = NewObject<USentryEvent>();

	if(!Message.IsEmpty())
	{
		Event->SetMessage(Message);
	}

	Event->SetLevel(Level);

	return Event;
}

void USentryEvent::SetMessage(const FString &Message)
{
	if (!NativeImpl)
		return;

	NativeImpl->SetMessage(Message);
}

FString USentryEvent::GetMessage() const
{
	if(!NativeImpl)
		return FString();

	return NativeImpl->GetMessage();
}

void USentryEvent::SetLevel(ESentryLevel Level)
{
	if (!NativeImpl)
		return;

	NativeImpl->SetLevel(Level);
}

ESentryLevel USentryEvent::GetLevel() const
{
	if(!NativeImpl)
		return ESentryLevel::Debug;

	return NativeImpl->GetLevel();
}

bool USentryEvent::IsCrash() const
{
	if(!NativeImpl)
		return false;

	return NativeImpl->IsCrash();
}

bool USentryEvent::IsAnr() const
{
	if(!NativeImpl)
		return false;

	return NativeImpl->IsAnr();
}
