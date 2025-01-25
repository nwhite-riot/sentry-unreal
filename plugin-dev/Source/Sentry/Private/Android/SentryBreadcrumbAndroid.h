// Copyright (c) 2022 Sentry. All Rights Reserved.

#pragma once

#include "Interface/SentryBreadcrumbInterface.h"

class FSentryJavaObjectWrapper;

class SentryBreadcrumbAndroid : public ISentryBreadcrumb
{
public:
	virtual void Initialize() override;

	virtual void SetMessage(const FString& message) override;
	virtual FString GetMessage() const override;
	virtual void SetType(const FString& type) override;
	virtual FString GetType() const override;
	virtual void SetCategory(const FString& category) override;
	virtual FString GetCategory() const override;
	virtual void SetData(const TMap<FString, FString>& data) override;
	virtual TMap<FString, FString> GetData() const override;
	virtual void SetLevel(ESentryLevel level) override;
	virtual ESentryLevel GetLevel() const override;

private:
	void SetupClassMethods();

	FSentryJavaMethod SetMessageMethod;
	FSentryJavaMethod GetMessageMethod;
	FSentryJavaMethod SetTypeMethod;
	FSentryJavaMethod GetTypeMethod;
	FSentryJavaMethod SetCategoryMethod;
	FSentryJavaMethod GetCategoryMethod;
	FSentryJavaMethod SetDataMethod;
	FSentryJavaMethod GetDataMethod;
	FSentryJavaMethod SetLevelMethod;
	FSentryJavaMethod GetLevelMethod;

	TSharedPtr<FSentryJavaObjectWrapper> BreadcrumbWrapper;
};

typedef SentryBreadcrumbAndroid FPlatformSentryBreadcrumb;
