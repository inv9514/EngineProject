#pragma once

#include <Core/Core.h>
#include <Actor/Actor.h>
#include <Core/CraftObject.h>
#include <Camera/LevelCamera.h>
#include <memory>	
#include <vector>	

namespace Craft
{
	class CRAFT_API Level : public CraftObject, public std::enable_shared_from_this<Level>
	{
		TYPE_DECLARATIONS(Level, CraftObject)

		friend class Engine;

	public:
		Level(); 
		virtual ~Level();		

	public:
		virtual void OnInitialized();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();		
		
	public:
		// 레벨에 액터 추가 (탬플릿 함수)
		template<typename T, typename ...Args,
			typename = std::enable_if_t<std::is_base_of<Actor, T>::value>>
			std::shared_ptr<T> SpawnActor(Args&& ...args)
		{
			// 새로운 액터 생성
			std::shared_ptr<T> newActor
				= std::make_shared<T>(std::forward<Args>(args)...);

			// 추가 요청 목록에 포함
			addRequestedActorList.emplace_back(newActor);

			// 생성된 액터는 현재 레벨에 대한 오너십 설정
			newActor->SetOwner(weak_from_this());

			// 생성한 액터 반환
			return newActor;
		}

		// 레벨의 액터 검색 함수 (템플릿)
		template<typename T,
			typename = std::enable_if_t<std::is_base_of<Actor, T>::value>>
			std::shared_ptr<T> FindActor()
		{
			for (const auto& actor : actorList)
			{
				// T 타입으로 형변환 시도, 아닌 경우에는 null 반환
				std::shared_ptr<T> targetActor
					= std::dynamic_pointer_cast<T>(actor);
				if (targetActor)
				{
					return targetActor;
				}
			}
			
			return nullptr; // 못찾은 경우 null 반환
		}

		// Initialized 플래그 접근 Getter
		inline bool HasInitialized() const { return hasInitialized; }

	protected:
		// 이전 프레임에 추가/제거 요청된 액터 처리 함수
		void ProcessAddAndDestroyActors();

		// 액터의 이전 상태 처리 함수.
		void SavePreviousActorStates();

	protected:
		// 초기화 처리 여부 플래그
		bool hasInitialized = false;

		// 레벨에 배치된 모든 액터
		std::vector<std::shared_ptr<Actor>> actorList;

		// 추가 요청된 액터 (프레임의 드로우가 끝나고 다음 프레임 전에 호출되어 처리)
		std::vector<std::shared_ptr<Actor>> addRequestedActorList;				
		
	/* Camera Section */
	public:
		inline const std::shared_ptr<LevelCamera>& GetLevelCamera() const { return levelCamera; }
		
		inline void SetLevelCamera(const std::shared_ptr<LevelCamera>& camera) { levelCamera = camera; }
		
	private:
		std::shared_ptr<LevelCamera> levelCamera;
	};
}