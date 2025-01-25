// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "Interface/SentryAttachmentInterface.h"

class FSentryJavaObjectWrapper;

class SentryAttachmentAndroid : public ISentryAttachment
{
public:
	virtual ~SentryAttachmentAndroid() override = default;

	virtual void Initialize(const TArray<uint8>& data, const FString& filename, const FString& contentType) override;
	virtual void Initialize(const FString& path, const FString& filename, const FString& contentType) override;

	virtual TArray<uint8> GetData() const override;
	virtual FString GetPath() const override;
	virtual FString GetFilename() const override;
	virtual FString GetContentType() const override;

private:
	void SetupClassMethods();

	FSentryJavaMethod GetDataMethod;
	FSentryJavaMethod GetPathMethod;
	FSentryJavaMethod GetFilenameMethod;
	FSentryJavaMethod GetContentTypeMethod;

	TSharedPtr<FSentryJavaObjectWrapper> AttachmentWrapper;
};

typedef SentryAttachmentAndroid FPlatformSentryAttachment;
