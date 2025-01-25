// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryAttachmentAndroid.h"

#include "Infrastructure/SentryConvertersAndroid.h"
#include "Infrastructure/SentryJavaClasses.h"
#include "Infrastructure/SentryJavaObjectWrapper.h"

void SentryAttachmentAndroid::Initialize(const TArray<uint8>& data, const FString& filename, const FString& contentType)
{
	AttachmentWrapper = MakeShareable(
		new FSentryJavaObjectWrapper(SentryJavaClasses::Attachment
			, "([BLjava/lang/String;Ljava/lang/String;)V"
			, SentryConvertersAndroid::ByteArrayToNative(data)
			, *FSentryJavaObjectWrapper::GetJString(filename)
			, *FSentryJavaObjectWrapper::GetJString(contentType)
		)
	);

	SetupClassMethods();
}

void SentryAttachmentAndroid::Initialize(const FString& path, const FString& filename, const FString& contentType)
{
	AttachmentWrapper = MakeShareable(
		new FSentryJavaObjectWrapper(SentryJavaClasses::Attachment
			, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
			, *FSentryJavaObjectWrapper::GetJString(path)
			, *FSentryJavaObjectWrapper::GetJString(filename)
			, *FSentryJavaObjectWrapper::GetJString(contentType)
		)
	);

	SetupClassMethods();
}

void SentryAttachmentAndroid::SetupClassMethods()
{
	if (AttachmentWrapper)
	{
		GetDataMethod = AttachmentWrapper->GetMethod("getBytes", "()[B");
		GetPathMethod = AttachmentWrapper->GetMethod("getPathname", "()Ljava/lang/String;");
		GetFilenameMethod = AttachmentWrapper->GetMethod("getFilename", "()Ljava/lang/String;");
		GetContentTypeMethod = AttachmentWrapper->GetMethod("getContentType", "()Ljava/lang/String;");
	}
}

TArray<uint8> SentryAttachmentAndroid::GetData() const
{
	if (AttachmentWrapper)
	{
		auto data = CallObjectMethod<jobject>(GetDataMethod);
		return SentryConvertersAndroid::ByteArrayToUnreal(static_cast<jbyteArray>(*data));
	}
	else
	{
		return {};
	}
}

FString SentryAttachmentAndroid::GetPath() const
{
	if (AttachmentWrapper)
	{
		return AttachmentWrapper->CallMethod<FString>(GetPathMethod);
	}
	else
	{
		return TEXT("");
	}
}

FString SentryAttachmentAndroid::GetFilename() const
{
	if (AttachmentWrapper)
	{
		return AttachmentWrapper->CallMethod<FString>(GetFilenameMethod);
	}
	else
	{
		return TEXT("");
	}
}

FString SentryAttachmentAndroid::GetContentType() const
{
	if (AttachmentWrapper)
	{
		return AttachmentWrapper->CallMethod<FString>(GetContentTypeMethod);
	}
	else
	{
		return TEXT("");
	}
}