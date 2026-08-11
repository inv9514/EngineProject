#pragma once

#include <vector>
#include <memory>

namespace Craft
{
	class Actor;

	class CollisionSystem
	{
		struct CollisionPair   // 충돌 이벤트 발생시, 두 액터를 저장하는 구조체
		{
			std::shared_ptr<Actor> actor;
			std::shared_ptr<Actor> other;
		};

	public:
		CollisionSystem() = default;
		~CollisionSystem() = default;

		// 레벨의 모든 액터를 순회하며 충돌을 확인
		void ProcessCollision(const std::vector<std::shared_ptr<Actor>>& actorList);

	private:

		// 두 액터가 충돌했는지 확인하는 함수
		bool Test(
			const std::shared_ptr<Actor>& left,
			const std::shared_ptr<Actor>& right
		);
	};
}