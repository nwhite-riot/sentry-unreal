// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ISentryAttachment
{
public:
	virtual ~ISentryAttachment() = default;

	virtual void Initialize(const TArray<uint8>& Data, const FString& Filename, const FString& ContentType) = 0;
	virtual void Initialize(const FString& Path, const FString& Filename, const FString& ContentType) = 0;

	virtual TArray<uint8> GetData() const = 0;
	virtual FString GetPath() const = 0;
	virtual FString GetFilename() const = 0;
	virtual FString GetContentType() const = 0;
};
