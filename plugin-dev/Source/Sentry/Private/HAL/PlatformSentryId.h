#pragma once

#if PLATFORM_ANDROID
#include "Android/SentryIdAndroid.h"
#elif PLATFORM_IOS || PLATFORM_MAC
#include "Apple/SentryIdApple.h"
#else
#include "GenericPlatform/GenericPlatformSentryId.h"
#endif

static TSharedPtr<ISentryId> CreateSharedSentryId()
{
#if PLATFORM_ANDROID
    return MakeShareable(new SentryIdAndroid);
#elif PLATFORM_IOS || PLATFORM_MAC
    return MakeShareable(new SentryIdApple);
#else
    return MakeShareable(new FGenericPlatformSentryId);
#endif
}
