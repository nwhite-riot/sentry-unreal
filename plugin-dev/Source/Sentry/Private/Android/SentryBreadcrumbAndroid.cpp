// Copyright (c) 2022 Sentry. All Rights Reserved.

#include "SentryBreadcrumbAndroid.h"

#include "Infrastructure/SentryConvertersAndroid.h"
#include "Infrastructure/SentryJavaClasses.h"
#include "Infrastructure/SentryJavaObjectWrapper.h"

void SentryBreadcrumbAndroid::Initialize()
{
	BreadcrumbWrapper = MakeShareable(new FSentryJavaObjectWrapper(SentryJavaClasses::Breadcrumb, "()V"));

	SetupClassMethods();
}

void SentryBreadcrumbAndroid::SetupClassMethods()
{
	if (BreadcrumbWrapper)
	{
		SetMessageMethod = BreadcrumbWrapper->GetMethod("setMessage", "(Ljava/lang/String;)V");
		GetMessageMethod = BreadcrumbWrapper->GetMethod("getMessage", "()Ljava/lang/String;");
		SetTypeMethod = BreadcrumbWrapper->GetMethod("setType", "(Ljava/lang/String;)V");
		GetTypeMethod = BreadcrumbWrapper->GetMethod("getType", "()Ljava/lang/String;");
		SetCategoryMethod = BreadcrumbWrapper->GetMethod("setCategory", "(Ljava/lang/String;)V");
		GetCategoryMethod = BreadcrumbWrapper->GetMethod("getCategory", "()Ljava/lang/String;");
		SetDataMethod = BreadcrumbWrapper->GetMethod("setData", "(Ljava/lang/String;Ljava/lang/Object;)V");
		GetDataMethod = BreadcrumbWrapper->GetMethod("getData", "()Ljava/util/Map;");
		SetLevelMethod = BreadcrumbWrapper->GetMethod("setLevel", "(Lio/sentry/SentryLevel;)V");
		GetLevelMethod = BreadcrumbWrapper->GetMethod("getLevel", "()Lio/sentry/SentryLevel;");
	}
}

void SentryBreadcrumbAndroid::SetMessage(const FString& message)
{
	if (BreadcrumbWrapper)
	{
		BreadcrumbWrapper->CallMethod<void>(SetMessageMethod, *FSentryJavaObjectWrapper::GetJString(message));
	}
}

FString SentryBreadcrumbAndroid::GetMessage() const
{
	if (BreadcrumbWrapper)
	{
		return BreadcrumbWrapper->CallMethod<FString>(GetMessageMethod);
	}
	else
	{
		return TEXT("");
	}
}

void SentryBreadcrumbAndroid::SetType(const FString& type)
{
	if (BreadcrumbWrapper)
	{
		BreadcrumbWrapper->CallMethod<void>(SetTypeMethod, *FSentryJavaObjectWrapper::GetJString(type));
	}
}

FString SentryBreadcrumbAndroid::GetType() const
{
	if (BreadcrumbWrapper)
	{
		return BreadcrumbWrapper->CallMethod<FString>(GetTypeMethod);
	}
	else
	{
		return TEXT("");
	}
}

void SentryBreadcrumbAndroid::SetCategory(const FString& category)
{
	if (BreadcrumbWrapper)
	{
		BreadcrumbWrapper->CallMethod<void>(SetCategoryMethod, *FSentryJavaObjectWrapper::GetJString(category));
	}
}

FString SentryBreadcrumbAndroid::GetCategory() const
{
	if (BreadcrumbWrapper)
	{
		return BreadcrumbWrapper->CallMethod<FString>(GetCategoryMethod);
	}
	else
	{
		return TEXT("");
	}
}

void SentryBreadcrumbAndroid::SetData(const TMap<FString, FString>& data)
{
	if (BreadcrumbWrapper)
	{
		for (const auto& dataItem : data)
		{
			BreadcrumbWrapper->CallMethod<void>(
				SetDataMethod,
				*FSentryJavaObjectWrapper::GetJString(dataItem.Key),
				*FSentryJavaObjectWrapper::GetJString(dataItem.Value)
			);
		}
	}
}

TMap<FString, FString> SentryBreadcrumbAndroid::GetData() const
{
	if (BreadcrumbWrapper)
	{
		auto data = BreadcrumbWrapper->CallObjectMethod<jobject>(GetDataMethod);
		return SentryConvertersAndroid::StringMapToUnreal(*data);
	}
	else
	{
		return {};
	}
}

void SentryBreadcrumbAndroid::SetLevel(ESentryLevel level)
{
	if (BreadcrumbWrapper)
	{
		BreadcrumbWrapper->CallMethod<void>(SetLevelMethod, SentryConvertersAndroid::SentryLevelToNative(level)->GetJObject());
	}
}

ESentryLevel SentryBreadcrumbAndroid::GetLevel() const
{
	if (BreadcrumbWrapper)
	{
		auto level = BreadcrumbWrapper->CallObjectMethod<jobject>(GetLevelMethod);
		return SentryConvertersAndroid::SentryLevelToUnreal(*level);
	}
	else
	{
		return ESentryLevel::Debug;
	}
}