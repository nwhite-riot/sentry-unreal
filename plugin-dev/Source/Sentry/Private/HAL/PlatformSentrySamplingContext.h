#pragma once

#if PLATFORM_ANDROID
#include "Android/SentrySamplingContextAndroid.h"
#elif PLATFORM_APPLE
#include "Apple/SentrySamplingContextApple.h"
#else
#include "Null/NullSentrySamplingContext.h"
#endif

static TSharedPtr<ISentrySamplingContext> CreateSharedSentrySamplingContext()
{
    // Sampling context is supposed to be created internally by the SDK using the platform-specific implementations.
    // Currently, it doesn't provide default constructor for Apple/Android thus we can only return Null-version here.
    return MakeShareable(new FNullSentrySamplingContext);
}
