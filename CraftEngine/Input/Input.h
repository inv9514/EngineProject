#pragma once

#include <Core/Core.h>

namespace Craft
{
	class CRAFT_API Input
	{
		friend class Engine;

		/* 키 입력 상태를 저장하기 위한 구조체 */
		struct KeyState
		{
			bool isKeyDown = false;   // 현재 프레임에 키가 눌렸는가?          
			bool wasKeyDown = false;  // 이전 프레임에 키가 눌렸는가?
		};

	public:
		Input();
		~Input() = default;

		/* 키 입력 & 해제 여부 확인 */
		bool GetKeyDown(int keyCode) const;   // 이전 프레임에 안 눌렀다가, 이번 프레임에 눌렀다면 true
		bool GetKeyUp(int keyCode) const;     // 이전 프레임에 눌렀다가, 이번 프레임에 안 눌렀다면 true
		bool GetKey(int keyCode) const;       // 현재 프레임에 입력이 감지되면 반복해서 true


		// Input 객체 싱글톤 접근 
		static Input& Get();

	private:
		// 현재 프레임에 특정 키 입력이 발생했는지 처리하는 함수
		void ProcessInput();

		// 이전 프레임의 키 눌림 상태를 저장하는 함수
		void SavePreviousStates();

	private:
		// Input 객체 싱글톤
		static Input* instance;
		
		/* Windows에서 매핑한 가상 키 */
		const int keyCount = 256;        // 가상 키의 수
		KeyState keyStates[256] = { };   // 키 상태를 관리할 배열    
	};
}