#include "Input.h"
#include <cassert>
#include <Windows.h>

namespace Craft
{
	Input* Input::instance = nullptr;

	Input::Input()
	{
		// static 멤버변수 instance 포인터는 모든 Input 객체가 공유하므로, 기존 instance 체크 및 추가 생성을 제한 (싱글톤)
		assert(!instance && "instance should be null here.");
		instance = this;
	}

	bool Input::GetKeyDown(int keyCode) const
	{
		return !keyStates[keyCode].wasKeyDown
			&& keyStates[keyCode].isKeyDown;
	}
	
	bool Input::GetKeyUp(int keyCode) const
	{
		return keyStates[keyCode].wasKeyDown
			&& !keyStates[keyCode].isKeyDown;
	}
	
	bool Input::GetKey(int keyCode) const
	{
		return keyStates[keyCode].isKeyDown;
	}
	
	Input& Input::Get()
	{
		// 존재하는 Input 객체 싱글톤 반환
		assert(instance && "instance should not be null here");
		return *instance;
	}
	
	void Input::ProcessInput()
	{
		for (int ix = 0; ix < keyCount; ++ix)   // 현재 프레임에 키 입력이 발생했는지 확인.
		{
			// 가상 키가 매핑한 256개의 모든 키에 대해 입력을 검사하고, 구조체의 is/was 플래그 중 is를 설정함
			keyStates[ix].isKeyDown = ( (GetAsyncKeyState(ix) & 0x8000) != 0 );
		}
	}
	
	void Input::SavePreviousStates()
	{
		for (KeyState& state : keyStates)    // 한 프레임이 끝날 때, 해당프레임에 눌렸던 키를 전부 저장함
		{
			// 가상 키가 매핑한 256개의 모든 키에 대해 입력을 검사하고, 구조체의 is/was 플래그 중 was를 설정함
			state.wasKeyDown = state.isKeyDown;
		}
	}
}