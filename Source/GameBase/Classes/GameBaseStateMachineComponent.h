// Copyright (c) 2017, Peter Bačinský <peter@bacinsky.sk>

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameBaseStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterState, uint8, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitState, uint8, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTickState, uint8, State);

/**
 * State Machine Component
 */
UCLASS(Blueprintable, ClassGroup = (Custom,StateMachine), meta = (BlueprintSpawnableComponent))
class GAMEBASE_API UGameBaseStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameBaseStateMachineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Component tick delta seconds
	UPROPERTY(BlueprintReadOnly, Category = StateMachine)
	float DeltaSeconds;

	// Network active state
	UPROPERTY(BlueprintReadOnly, Replicated, Category = StateMachine)
	uint8 NetActiveState;

	// Active state
	UPROPERTY(BlueprintReadOnly, Category = StateMachine)
	uint8 ActiveState;

	// Active duration
	UPROPERTY(BlueprintReadOnly, Category = StateMachine)
	float ActiveStateSeconds;

	// Last state
	UPROPERTY(BlueprintReadOnly, Category = StateMachine)
	uint8 LastState;

public:
	// Activates component
	void Activate(bool bReset = false) override;

	// Deactivates component
	void Deactivate() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// On enter state
	UPROPERTY(BlueprintAssignable, Category = StateMachine)
	FOnEnterState OnEnterState;

	// On exit state
	UPROPERTY(BlueprintAssignable, Category = StateMachine)
	FOnExitState OnExitState;

	// On tick state
	UPROPERTY(BlueprintAssignable, Category = StateMachine)
	FOnTickState OnTickState;

	// On state initialization
	UFUNCTION(BlueprintImplementableEvent, DisplayName = InitState, Category = StateMachine)
	void EventInitState();

	// On enter state
	UFUNCTION(BlueprintImplementableEvent, DisplayName = EnterState, Category = StateMachine)
	void EventEnterState();

	// On exit state
	UFUNCTION(BlueprintImplementableEvent, DisplayName = ExitState, Category = StateMachine)
	void EventExitState();

	// Tick state
	UFUNCTION(BlueprintImplementableEvent, DisplayName = TickState, Category = StateMachine)
	void EventTickState();

	// Before enter state
	UFUNCTION(BlueprintNativeEvent, Category = StateMachine)
	bool CanEnterState() const;

	// Before exit state
	UFUNCTION(BlueprintNativeEvent, Category = StateMachine)
	bool CanExitState() const;

	// Return state
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = StateMachine)
	uint8 GetState();

	// Return last state
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = StateMachine)
	uint8 GetLastState();

	// Enter state
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	bool EnterState(uint8 NewState, bool bLock = false);

	// Toggle state
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	bool ToggleState(uint8 NewState, bool bLock = false);

	// Lock with delay
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	void LockDelay(float Seconds);

	// Lock
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	void Lock();

	// Unlocks
	UFUNCTION(BlueprintCallable, Category = StateMachine)
	void UnLock();

	// Lock
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StateMachine)
	bool bLocked;

	// Tick interval (-1 no tick)
	UPROPERTY(EditAnywhere, Category = Tick)
	float TickInterval;
};
