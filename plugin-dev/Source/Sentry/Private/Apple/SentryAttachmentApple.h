// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "Interface/SentryAttachmentInterface.h"

@class SentryAttachment;

class SentryAttachmentApple : public ISentryAttachment
{
public:
	virtual ~SentryAttachmentApple() override = default;

	void Initialize(const TArray<uint8>& data, const FString& filename, const FString& contentType) override;
	void Initialize(const FString& path, const FString& filename, const FString& contentType) override;

	SentryAttachment* GetNativeObject();

	virtual TArray<uint8> GetData() const override;
	virtual FString GetPath() const override;
	virtual FString GetFilename() const override;
	virtual FString GetContentType() const override;

private:
	SentryAttachment* AttachmentApple;
};

typedef SentryAttachmentApple FPlatformSentryAttachment;
