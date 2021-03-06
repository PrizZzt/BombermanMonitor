// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Engine/GameInstance.h"
#include "TGround.h"
#include "TObject.h"
#include "TPlayer.h"
#include "TCounterObject.h"
#include "TPointsRow.h"
#include "TPointsTable.h"
#include "TGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANMONITOR_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	enum class EObjectType : uint8
	{
		SOLID_WALL,
		WALL,
		BOOM
	};

	FHttpModule * http;
	FString url;

	void OnResponseReceived(FHttpRequestPtr _request, FHttpResponsePtr _response, bool _wasSuccessful);

	template<typename T> T* CreateObject(int _x, int _y, TSubclassOf<T> &_type);
	FVector GetVectorByCoords(int _x, int _y)
	{
		return FVector(_x * 100 + 50, _y * 100 + 50, 0);
	}

public:
	UPROPERTY(BlueprintReadOnly)
		int Size;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
		TSubclassOf<UTPointsRow> PointsRow;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
		TSubclassOf<UTPointsTable> PointsTable;
	UPROPERTY(/*BlueprintReadOnly, EditAnywhere, Category = "UI"*/)
		UTPointsTable *PointsTableInstance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATGround *Ground;

	TArray<ATObject*> Objects;
	TArray<ATObject*> Choppers;
	TArray<ATPlayer*> Players;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> SolidWall;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> Wall;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATPlayer> Player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> Chopper;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> Boom;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATCounterObject> Bomb;

	UTGameInstance();

	void Init()override;

	UFUNCTION(BlueprintCallable)
		void Connect(FString _serverAddress, FString _serverPort);
	UFUNCTION(BlueprintCallable)
		void Disconnect();

	UFUNCTION(BlueprintCallable)
		void Update();

	void CreateSolidWall(int _x, int _y);
	void CreateWall(int _x, int _y);
	void DestroyWall(int _x, int _y);
	void CreateBomb(int _x, int _y, int _counter);
	void CreateBoom(int _x, int _y);
	void DestroyObject(int _x, int _y);

	void UpdatePlayer(FString &_name, int _x, int _y, TCHAR _state);
	void UpdateChopper(int _i, int _x, int _y, TCHAR _state);

	int GetNextPlayerIndex(int startIndex)
	{
		for (int i = startIndex + 1; i < Players.Num(); i++)
		{
			return i;
		}
		for (int i = 0; i < Players.Num(); i++)
		{
			return i;
		}
		return -1;
	}
};
