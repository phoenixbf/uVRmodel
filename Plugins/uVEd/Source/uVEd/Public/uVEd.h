/*
	uVR Model open-source UE4 plugin
	author: B.Fanini (bruno.fanini__AT__gmail.com)
	https://github.com/phoenixbf/uVRmodel

===================================================*/

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FuVEdModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};