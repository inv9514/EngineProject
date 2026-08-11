#include "Level.h"

namespace Craft
{
	Level::Level()
	{

	}

	Level::~Level()
	{

	}

	void Level::OnInitialized()
	{
		// 레벨 초기화 시 플래그 설정
		hasInitialized = true;
	}

	void Level::BeginPlay()
	{
		// 레벨의 BeginPlay (보통 초기화 시점) 시 보유한 모든 액터를 대상으로
		for (const std::shared_ptr<Actor>& actor : actorList)
		{			
			if (actor->HasBeganPlay()) continue; // 액터가 이미 BeginPlay 처리된 경우 스킵			
			actor->BeginPlay();					 // 액터의 BeginPlay 호출
		}
	}

	void Level::Tick(float deltaTime)
	{
		// 레벨에 존재하는 모든 액터를 대상으로
		for (const std::shared_ptr<Actor>& actor : actorList)
		{
			if (!actor->IsActive()) continue; // 비활성화 상태인 액터는 스킵
			actor->Tick(deltaTime);		   	  // 액터의 Tick 이벤트 호출
		}
	}

	void Level::Draw()
	{
		// 레벨에 존재하는 모든 액터를 대상으로
		for (const std::shared_ptr<Actor>& actor : actorList)
		{
			if (!actor->IsActive()) continue; // 비활성화 상태인 액터는 스킵
			actor->Draw();		   			  // 액터의 Draw 이벤트 호출
		}
	}

	void Level::ProcessAddAndDestroyActors()
	{
		/* Step 1 : 액터 제거 처리 */	
		
		for (auto iterator = actorList.begin(); iterator != actorList.end();)
		{
			// 제거 요청된 액터인지 확인 후 제거
			auto actor = *iterator;
			if (actor->HasExpired())
			{
				iterator = actorList.erase(iterator); // 배열에서 빠져나가면 메모리도 해제 (shared_ptr)
				continue;
			}

			++iterator;
		}

		/* Step 2 : 액터 추가 처리 */
		
		// 추가요청 목록이 비어있으면 스킵
		if (addRequestedActorList.empty()) return;   

		// 추가요청된 액터를 전부 actorList에 추가 
		for (const auto& actor : addRequestedActorList) actorList.emplace_back(actor);

		// 추가 완료되면 목록 정리.
		addRequestedActorList.clear();
	}

	void Level::SavePreviousActorStates()
	{
		// 레벨에 존재하는 모든 액터를 대상으로
		for (const auto& actor : actorList)
		{
			if (!actor->IsActive()) continue;  // 비활성화 상태인 액터는 스킵
			actor->SavePreviousState();		   // 액터의 이전 상태 저장
		}
	}
}