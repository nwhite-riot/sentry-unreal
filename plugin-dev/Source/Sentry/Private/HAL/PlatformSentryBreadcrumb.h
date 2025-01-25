#pragma once

#if PLATFORM_ANDROID
#include "Android/SentryBreadcrumbAndroid.h"
#elif PLATFORM_APPLE
#include "Apple/SentryBreadcrumbApple.h"
#else
#include "GenericPlatform/GenericPlatformSentryBreadcrumb.h"
#endif
