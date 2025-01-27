// Copyright (c) 2023 Sentry. All Rights Reserved.

#pragma once

#include "Convenience/SentryInclude.h"

#include "HAL/CriticalSection.h"

#include "Interface/SentryTransactionInterface.h"

#if USE_SENTRY_NATIVE

class FGenericPlatformSentryTransaction : public ISentryTransaction
{
public:
	FGenericPlatformSentryTransaction(sentry_transaction_t* transaction);
	virtual ~FGenericPlatformSentryTransaction() override;

	sentry_transaction_t* GetNativeObject();

	virtual TSharedPtr<ISentrySpan> StartChildSpan(const FString& operation, const FString& description) override;
	virtual TSharedPtr<ISentrySpan> StartChildSpanWithTimestamp(const FString& operation, const FString& description, int64 timestamp) override;
	virtual void Finish() override;
	virtual void FinishWithTimestamp(int64 timestamp) override;
	virtual bool IsFinished() const override;
	virtual void SetName(const FString& name) override;
	virtual void SetTag(const FString& key, const FString& value) override;
	virtual void RemoveTag(const FString& key) override;
	virtual void SetData(const FString& key, const TMap<FString, FString>& values) override;
	virtual void RemoveData(const FString& key) override;
	virtual void GetTrace(FString& name, FString& value) override;

private:
	sentry_transaction_t* Transaction;

	FCriticalSection CriticalSection;

	bool isFinished;
};

#endif
