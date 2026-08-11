#pragma once

#include <Core/Core.h>
#include <Math/Vector2.h>
#include <Math/Color.h>
#include <Core/CraftObject.h>
#include <memory>	
#include <string>

namespace Craft
{
	class Level;

	class CRAFT_API Actor : public CraftObject
	{
		TYPE_DECLARATIONS(Actor, CraftObject)

	public:
		Actor(
			const std::string& image = "",
			const Vector2& position = Vector2::Zero,
			Color color = Color::White
		);
		virtual ~Actor();
	
		// 게임플레이 이벤트 함수 
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 충돌 이벤트 함수
		virtual void OnCollision(const std::shared_ptr<Actor>& other);

		void Destroy();

		// 엔진 종료요청 (주로 상속받은 Player에서) TODO : 이거그냥 레벨이 종료조건을 갖고있는게 낫지않나?
		void QuitGame();

		// 액터가 본인을 소유한 레벨에 접근하기 위한 weak_ptr
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }
		inline void SetOwner(std::weak_ptr<Level> newOwner) { owner = newOwner; }

		// 액터의 현재 위치값 Getter / Setter
		inline Vector2 GetPosition() const { return position; }
		void SetPosition(const Vector2& newPosition);

		// 액터의 이전 위치값 Getter / Setter 
		inline Vector2 GetPreviousPosition() const { return previousPosition; }
		inline void SavePreviousState() { previousPosition = position; } 

		// X너비 반환 함수					 // TODO : Y너비 추가
		inline int GetWidth() const { return width; }

		// 액터의 이미지 설정 함수
		inline void ChangeImage(const std::string& newImage)
		{
			width = static_cast<int>(newImage.length());	// 이미지 길이 설정  TODO : 너비도 설정
			image = newImage;								// 새로운 글자값 설정
		}
		
		// 플래그 접근 Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && !hasExpired; }
		inline bool HasExpired() const { return hasExpired; }

	protected:
		// 액터 플래그
		bool hasBeganPlay = false;

		bool isActive = true;

		bool hasExpired = false;

		// 이 액터를 소유하는 레벨 객체에 대한 weak_ptr
		std::weak_ptr<Level> owner;
		
		// 충돌 이벤트 처리를 위한 이전값
		Vector2 previousPosition;

		// 드로우를 위한 설정값
		std::string image;

		Color color = Color::White;

		int width = 0;  // TODO : height 추가

		int sortingOrder = 0;

		Vector2 position;		
	};
}