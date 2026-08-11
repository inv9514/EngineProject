#include "GameLevel.h"

#include <cassert>
#include <Actor/Player.h>

#include "Actor/Wall.h"

using namespace Craft;


GameLevel::GameLevel()
{
    camera = std::make_unique<Camera>();
}

void GameLevel::OnInitialized()
{
    Level::OnInitialized();
    LoadMap("Stage1.txt");
    SpawnActor<Player>();
}

void GameLevel::LoadMap(const std::string& filename)
{
    // 읽을 맵 문자열 준비
    std::string path = std::string("../Assets/") + filename;
    
    // C스타일 파일 읽기
    FILE* file = nullptr;
    fopen_s(&file, path.c_str(), "rt");
    if (!file)
    {
        assert(false && "Failed to open a map file.");
        return;
    }
    
    // 확보한 파일 크기 확인
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    
    // 파일 크기 만큼 버퍼 생성후 읽기
    char* buffer = new char[fileSize] {}; // {} 0으로 초기화
    size_t readSize = fread(buffer, sizeof(char), fileSize, file);    
    assert(readSize > 0 && "There's no data in Map file.");
    
    // TODO : 읽은 데이터를 기반으로 로직 제작
    int index = 0;
    Vector2 position;
    while (true)
    {
        // 파일 크기만큼 인덱스가 순회했다면 읽었다면 종료
        if (index >= fileSize) break;        
        
        // 그릴 문자열 : 파일을 저장한 임시버퍼의 문자열[인덱스]
        char mapCharacter = buffer[index++];
                
        // 공백문자라면 전체 스킵하고 위치를 다음줄 첫번째로 (1차원배열 버퍼 -> 2차원 콘솔 구조화)
        if (mapCharacter == '\n')            
        {
            ++position.y;
            position.x = 0;
            continue;
        }
        
        switch (mapCharacter)
        {
        case '#': // Wall
            SpawnActor<Wall>(position);
            break;
        }
        
        ++position.x; // **해주고 위치 업데이트
    }    
    
    // 버퍼와 파일 정리
    delete[] buffer;
    buffer = nullptr;    
    fclose(file);
    file = nullptr;
}
