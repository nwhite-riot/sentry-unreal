// Copyright (c) 2024 Sentry. All Rights Reserved.

#include "SentryTransactionContext.h"

#include "HAL/PlatformSentryTransactionContext.h"

void USentryTransactionContext::Initialize(const FString& Name, const FString& Operation)
{
	if (USentryTransactionContext::StaticClass()->GetDefaultObject() != this)
	{
		NativeImpl = CreateSharedSentryTransactionContext(Name, Operation);
	}
}

FString USentryTransactionContext::GetName() const
{
	if (!NativeImpl)
		return FString();

	return NativeImpl->GetName();
}

FString USentryTransactionContext::GetOperation() const
{
	if (!NativeImpl)
		return FString();

	return NativeImpl->GetOperation();
}
