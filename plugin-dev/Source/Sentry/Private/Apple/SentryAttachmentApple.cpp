// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryAttachmentApple.h"

#include "Infrastructure/SentryConvertersApple.h"

#include "Convenience/SentryInclude.h"
#include "Convenience/SentryMacro.h"

void SentryAttachmentApple::Initialize(const TArray<uint8>& data, const FString& filename, const FString& contentType)
{
	AttachmentApple = [[SENTRY_APPLE_CLASS(SentryAttachment) alloc] initWithData:SentryConvertersApple::ByteDataToNative(data)
		filename:filename.GetNSString() contentType:contentType.GetNSString()];
}

void SentryAttachmentApple::Initialize(const FString& path, const FString& filename, const FString& contentType)
{
	AttachmentApple = [[SENTRY_APPLE_CLASS(SentryAttachment) alloc] initWithPath:path.GetNSString()
		filename:filename.GetNSString() contentType:contentType.GetNSString()];
}

SentryAttachment* SentryAttachmentApple::GetNativeObject()
{
	return AttachmentApple;
}

TArray<uint8> SentryAttachmentApple::GetData() const
{
	if (AttachmentApple)
	{
		return SentryConvertersApple::ByteDataToUnreal(AttachmentApple.data);
	}
	else
	{
		return {};
	}
}

FString SentryAttachmentApple::GetPath() const
{
	if (AttachmentApple)
	{
		return FString(AttachmentApple.path);
	}
	else
	{
		return TEXT("");
	}
}

FString SentryAttachmentApple::GetFilename() const
{
	if (AttachmentApple)
	{
		return FString(AttachmentApple.filename);
	}
	else
	{
		return TEXT("");
	}
}

FString SentryAttachmentApple::GetContentType() const
{
	if (AttachmentApple)
	{
		return FString(AttachmentApple.contentType);
	}
	else
	{
		return TEXT("");
	}
}
