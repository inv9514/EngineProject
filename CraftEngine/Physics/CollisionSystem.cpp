#include "CollisionSystem.h"
#include "Actor/Actor.h"

namespace Craft
{
	void CollisionSystem::ProcessCollision(const std::vector<std::shared_ptr<Actor>>& actorList)
	{
		// 레벨의 actorList가 비어있다면 충돌처리 x (actorList는 Engine::Run에서 mainLevel->actorList로 의존성 주입)
		if (actorList.empty()) return;
		
		// 해당 프레임에 충돌한 액터들에게 이벤트를 한번에 전달하기 위한 배열
		std::vector<CollisionPair> collidedActorList;

		// 레벨에 배치된 액터 수
		const int count = static_cast<int>(actorList.size());

		// 레벨에 배치된 모든 액터를 대상으로 충돌 검사
		for (int ix = 0; ix < count; ++ix)
		{
			const std::shared_ptr<Actor>& left = actorList[ix];
			if (!left || !left->IsActive()) continue;

			for (int jx = ix + 1; jx < count; ++jx)
			{
				const std::shared_ptr<Actor>& right = actorList[jx];
				if (!right || !right->IsActive()) continue;
				
				if (Test(left, right))   // 충돌 검사 실행 : Test()에서 두 액터의 위치를 교차검증 
				{
					// 충돌이 있었던 두 액터를 구조체에 담아 정리
					CollisionPair pair = {};
					pair.actor = left;
					pair.other = right;
					
					collidedActorList.emplace_back(pair); // 목록에 추가
				}
			}
		}

		// 충돌이 있었던 액터 목록이 비었다면 종료 
		if (collidedActorList.empty()) return;

		// 충돌한 액터 목록을 순회하며 이벤트 전달
		for (const CollisionPair& pair : collidedActorList)
		{
			// 이미 비활성화된 액터라면 스킵
			if (!pair.actor->IsActive() || !pair.other->IsActive()) continue;

			// 두 액터 모두에게 충돌 이벤트 전달
			pair.actor->OnCollision(pair.other);
			pair.other->OnCollision(pair.actor);
		}
	}

	bool CollisionSystem::Test(
		const std::shared_ptr<Actor>& left,
		const std::shared_ptr<Actor>& right)
	{
		if (!left || !right) return false;
		// AABB (Axis Aligned Bounding Box).

		// left 액터의 현재/이전 위치
		const Vector2 leftCurrent = left->GetPosition();
		const Vector2 leftPrevious = left->GetPreviousPosition();

		// right 액터의 현재/이전 위치
		const Vector2 rightCurrent = right->GetPosition();
		const Vector2 rightPrevious = right->GetPreviousPosition();

		// 이전 프레임 위치와 현재 위치를 모두 포함하는 swept bounds 계산. (최악을 상정한 실제보다 긴 히트박스)
		const int leftXMin = (leftCurrent.x < leftPrevious.x) ? leftCurrent.x : leftPrevious.x;
		const int leftXMaxCurrent = leftCurrent.x + left->GetWidth() - 1;
		const int leftXMaxPrevious = leftPrevious.x + left->GetWidth() - 1;
		const int leftXMax = (leftXMaxCurrent > leftXMaxPrevious) ? leftXMaxCurrent : leftXMaxPrevious;

		const int rightXMin = (rightCurrent.x < rightPrevious.x) ? rightCurrent.x : rightPrevious.x;
		const int rightXMaxCurrent = rightCurrent.x + right->GetWidth() - 1;
		const int rightXMaxPrevious = rightPrevious.x + right->GetWidth() - 1;
		const int rightXMax = (rightXMaxCurrent > rightXMaxPrevious) ? rightXMaxCurrent : rightXMaxPrevious;

		// X좌표 기준으로 충돌이 발생할 수 없는 상황 처리.
		if (rightXMin > leftXMax) return false;    // 2번액터의 x좌표 최소치가 1번액터의 x좌표 최대치보다 오른쪽 = 떨어짐
		if (rightXMax < leftXMin) return false;    // 대충 비슷함
		
		// 이전 프레임까지 고려한 y 충돌 영역 계산.  TODO : y충돌 역시 x충돌과 동일하게 처리
		const int leftYMin = (leftCurrent.y < leftPrevious.y) ? leftCurrent.y : leftPrevious.y;
		const int leftYMax = (leftCurrent.y > leftPrevious.y) ? leftCurrent.y : leftPrevious.y;

		const int rightYMin = (rightCurrent.y < rightPrevious.y) ? rightCurrent.y : rightPrevious.y;
		const int rightYMax = (rightCurrent.y > rightPrevious.y) ? rightCurrent.y : rightPrevious.y;

		// y좌표 기준으로 충돌이 발생할 수 없는 상황 처리.
		if (rightYMin > leftYMax) return false;
		if (rightYMax < leftYMin) return false;

		// 충돌 발생
		return true;
	}
}