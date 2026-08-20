#include "Engine.h"
#include <Level/Level.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include <Physics/CollisionSystem.h>

#include <iostream>
#include <Windows.h>
#include <cassert>

namespace Craft
{
	// 전역변수 cpp 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		// 다른 엔진객체 확인후 instance 포인터 초기화 
		assert(!instance && "instance is not null");
		instance = this;

		// 엔진 Config 로드
		LoadEngineSetting();

		// Input 객체 생성
		input = std::make_unique<Input>();

		// Renderer 객체 생성
		renderer = std::make_unique<Renderer>(Vector2(setting.width, setting.height));

		// CollisionSystem 객체 생성
		collisionSystem = std::make_unique<CollisionSystem>();
	}

	Engine::~Engine()
	{
		instance = nullptr;
	}

	void Engine::Run()
	{
		// 프레임 제한을 위해 엔진의 반복문 내부에서 쓸 고해상도 타이머 셋업 
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		int64_t current = counter.QuadPart;
		int64_t previous = current;
		float oneFrameTime = 1.0f / setting.framerate;	 // 프레인 제한값

		
		while (true)
		{
			if (isQuit) break;

			// 프레임 제한을 위한 처리
			QueryPerformanceCounter(&counter);
			current = counter.QuadPart;
			float deltaTime = static_cast<float>(current - previous) / static_cast<float>(frequency.QuadPart);

			// 메인 프로세스 (프레임 제한값보다 빨랐다면 전체 스킵)
			if (deltaTime >= oneFrameTime)
			{
				// 입력처리 
				ProcessInput();
				
				// 게임 이벤트 함수 호출
				OnInitialized();

				// 게임 이벤트의 초기화 함수 (최초 1회 호출)
				BeginPlay();

				// 게임 업데이트
				Tick(deltaTime);

				// 충돌 처리
				ProcessCollision();

				// 화면 그리기
				Draw();

				
				/* 
				 * Draw가 끝나는 순간 현재 프레임 처리는 완료됨. 이하 작업은 다음 프레임을 위한 작업들 
				 * 
				 */

				
				if (nextLevel)   // 만약 레벨 전환 요청을 받아 nextLevel이 존재한다면, 전환 후 기존 포인터 정리
				{
					if (mainLevel) mainLevel.reset();

					mainLevel = nextLevel;

					nextLevel.reset();
				}

				if (mainLevel)	
				{
					// 현재 레벨에 추가 & 제거 요청된 액터 정리 
					mainLevel->ProcessAddAndDestroyActors();

					// 충돌확인을 위한 프레임 변경 직전 위치값 저장
					mainLevel->SavePreviousActorStates();
				}

				SavePreviousInputStates();  // 현재 프레임의 키 입력 정보들을 전부 저장 (다음 프레임과 비교를 위해)

				previous = current;		    // deltaTime 설정을 위해 마지막 업데이트카운트 기록
			}
		}

		Shutdown();	 // isQuit 플래그로 탈출시 엔진 종료
	}

	void Engine::Quit()
	{
		isQuit = true;
	}

	Engine& Engine::Get()
	{
		assert(instance && "instance is null");
		return *instance;
	}

	void Engine::ProcessInput()
	{
		assert(input && "input should not be null here");
		if (!input) return;
		input->ProcessInput();
	}

	void Engine::OnInitialized()
	{
		// 엔진이 최초에 초기화될 때 레벨도 초기화
		if (!mainLevel || mainLevel->HasInitialized()) return;
		mainLevel->OnInitialized();
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel) return;
		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		if (!mainLevel) return;
		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		/* 
		 * Draw 순서 
		 * 레벨의 Draw가 호출되면, 보유한 액터를 모두 순회하며 Draw 호출
		 * 액터의 Draw가 호출되면, 본인이 보유한 드로우 데이터들을 수집해 renderQueue렌더러에게 Submit
		 * 렌더러의 Draw가 호출되면, renderQueue의 정보를 바탕으로 화면에 드로우 (상세는 Renderer.cpp Draw() 참조) 
		 */
		
		// 레벨의 Draw 이벤트 호출 : 액터들이 "정보값"을 renderQueue에 주입함
		if (!mainLevel) return;
		mainLevel->Draw();		 
		
		// 렌더러의 Draw 이벤트 호출 : renderQueue의 정보값을 바탕으로 실질적으로 화면에 "출력"
		if (!renderer) return;
		renderer->Draw();
	}

	void Engine::ProcessCollision()
	{
		if (!mainLevel || !collisionSystem) return;
		collisionSystem->ProcessCollision(mainLevel->actorList); // 의존성 주입 (Dependency Injection)
	}

	void Engine::SavePreviousInputStates()
	{
		assert(input && "input should not null here");
		if (!input) return;
		input->SavePreviousInput();
	}

	void Engine::Shutdown()
	{
	}

	void Engine::LoadEngineSetting()
	{
		// Setting.txt 파일 열기
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");
		if (!file)
		{
			std::cout << "Failed to open engine setting file.\n";
			__debugbreak();
			return;
		}

		// 버퍼 준비
		const int bufferSize = 2048;
		char buffer[bufferSize] = {};

		// 버퍼에 문자열 읽어오기
		size_t readSize = fread(buffer, sizeof(char), bufferSize, file);

		// 문자열을 자르며 해석
		char* context = nullptr;
		char* token = nullptr;
		token = strtok_s(buffer, "\n", &context);  // '\n' 기준으로 잘라 왼쪽은 token, 남은 문자열 전체는 context

		while (token)
		{
			// token을 읽어가며 공백이 나오기 전까지의 문자를 key에 저장(공백은 제외)
			char key[15] = {};	
			sscanf_s(token, "%s", key, 15);
			
			// key에 저장된 문자열과 구조체의 변수명을 비교후 대입
			if (strcmp(key, "framerate") == 0)
			{
				sscanf_s(token, "framerate = %f", &setting.framerate);
			}
			else if (strcmp(key, "width") == 0)
			{
				sscanf_s(token, "width = %d", &setting.width);
			}
			else if (strcmp(key, "height") == 0)
			{
				sscanf_s(token, "height = %d", &setting.height);
			}
			
			// 나머지 문자열을 다시 '\n' 기준으로 자르고 token이 완전히 비워질때까지 반복
			token = strtok_s(nullptr, "\n", &context);			
		}
		
		fclose(file);
		file = nullptr;		
	}
}