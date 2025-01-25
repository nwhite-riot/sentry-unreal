#pragma once

#include "Interface/SentryAttachmentInterface.h"

class FNullSentryAttachment : public ISentryAttachment
{
public:
	virtual ~FNullSentryAttachment() override = default;

	virtual void Initialize(const TArray<uint8>& Data, const FString& Filename, const FString& ContentType) override {};
	virtual void Initialize(const FString& Path, const FString& Filename, const FString& ContentType) override {};

	virtual TArray<uint8> GetData() const override { return {}; }
	virtual FString GetPath() const override { return TEXT(""); }
	virtual FString GetFilename() const override { return TEXT(""); }
	virtual FString GetContentType() const override { return TEXT(""); }
};

typedef FNullSentryAttachment FPlatformSentryAttachment;
