// Copyright (c) 2023 Sentry. All Rights Reserved.

#include "SentryHint.h"

#include "SentryAttachment.h"
#include "HAL/PlatformSentryHint.h"

USentryHint::USentryHint()
{
	if (USentryHint::StaticClass()->GetDefaultObject() != this)
	{
		NativeImpl = CreateSharedSentryHint();
	}	
}

void USentryHint::AddAttachment(USentryAttachment* Attachment)
{
	if(!NativeImpl)
		return;

	NativeImpl->AddAttachment(Attachment->GetNativeObject());
}
