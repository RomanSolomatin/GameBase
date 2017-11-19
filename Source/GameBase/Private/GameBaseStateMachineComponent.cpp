// Copyright (c) 2017, Peter Bačinský <peter@bacinsky.sk>

#include "GameBaseStateMachineComponent.h"
#include "UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UGameBaseStateMachineComponent::UGameBaseStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = (TickInterval >= 0);
	ActiveState = 0;
	bAutoActivate = true;
	bLocked = false;
	bReplicates = true;
}

// Activates component
void UGameBaseStateMachineComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	bLocked = false;
}

// Deactivates component
void UGameBaseStateMachineComponent::Deactivate()
{
	Super::Deactivate();
	bLocked = true;
}


// Called when the game starts
void UGameBaseStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	bLocked = !IsActive();
	PrimaryComponentTick.TickInterval = TickInterval;
	SetComponentTickEnabled(TickInterval >= 0);

	// Enter first state
	ActiveState = -1;
	NetActiveState = -1;
	EnterState(0);
}


// Called every frame
void UGameBaseStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DeltaSeconds = DeltaTime;
	ActiveStateSeconds += DeltaTime;

	this->EventTickState();
	OnTickState.Broadcast(ActiveState);

	// TODO update net state
	if (ActiveState != NetActiveState)
		EnterState(NetActiveState);
}


// Lock with delay
void UGameBaseStateMachineComponent::LockDelay(float Seconds)
{
	Lock();
	FTimerHandle LockDelayTimer;
	GetWorld()->GetTimerManager().SetTimer(LockDelayTimer, this, &UGameBaseStateMachineComponent::UnLock, Seconds);
}


// Locks
void UGameBaseStateMachineComponent::Lock()
{
	bLocked = true;
}


// Unlocks
void UGameBaseStateMachineComponent::UnLock()
{
	bLocked = false;
}


// Return state
uint8 UGameBaseStateMachineComponent::GetState()
{
	return ActiveState;
}


// Return last state
uint8 UGameBaseStateMachineComponent::GetLastState()
{
	return LastState;
}


// Enter state
bool UGameBaseStateMachineComponent::EnterState(uint8 NewState, bool bLock)
{
	if (bLocked || NewState == ActiveState) return false;

	bool CanEnterState = true;

	if (-1 != ActiveState)
	{
		this->EventExitState();
		OnExitState.Broadcast(ActiveState);
		LastState = ActiveState;

		bool CanEnterState = this->CanEnterState();
	}

	if (CanEnterState)
	{
		if (bLock) bLocked = true;

		ActiveState = NewState;
		NetActiveState = NewState;
		ActiveStateSeconds = 0;
		this->EventEnterState();
		OnEnterState.Broadcast(ActiveState);
		return true;
	}

	return false;
}


// Toggles state
bool UGameBaseStateMachineComponent::ToggleState(uint8 NewState, bool bLock)
{
	if (NewState == ActiveState)
		return EnterState(LastState);

	return EnterState(NewState);
}


// Before enter state, default implementation
bool UGameBaseStateMachineComponent::CanEnterState_Implementation() const
{
	return true;
}


// Before exit state, default implementation
bool UGameBaseStateMachineComponent::CanExitState_Implementation() const
{
	return true;
}


// Set network properties
void UGameBaseStateMachineComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGameBaseStateMachineComponent, NetActiveState);
}
