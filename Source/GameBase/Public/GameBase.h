// Copyright (c) 2017, Peter Bačinský <peter@bacinsky.sk>

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FGameBaseModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
