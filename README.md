# ValroSix_KGW
  - 온라인 TPS / FPS 게임 모작 구현

## 목적
- 객체지향과 디자인패턴을 의미있게 적용
- 원활환 협업을 위한 Wiki 작성된 깃 컨벤션 및 코드컨벤션 적용
- 코드 가독성 및 확장성을 고려하여 작성
- Object Polling 및 GC를 통한 최적화된 코드 및 효율적인 메모리 사용
- 유효성검사 및 로깅을 통한 유지보수성 및 안정성을 향상시킨 코드 작성
- 
## 기술 스택
[![My Skills](https://skillicons.dev/icons?i=cpp,visualstudio,git,github,unreal,notion&theme=light)](https://skillicons.dev)

## 프로젝트 소개
### Project : ValroSix <br>
### Duration : 2025.03.13 ~ 2025.05.31 <br>
### Project Convention <br>
- Code   : PascalCase
- Git    : Rebase And Merge
- Directory && Commit && Unreal
- Wiki https://github.com/


## 사용 기술
- Unreal Engine 5.5.4
- Unreal RPC / Dedicated Server
- Chaos Physics Plugin
- Geometry Collection
- C++17 (v.14.38)
- MSVC v143

## 기획
Character
- Abstract / Interface
Fire Type
- Line Trace
    - 탄환 Delay없는 히트스캔 방식
    - 네트워크 상에서 처리속도가 빠르며, 성능 부담 저하
    - FPS게임에서 정밀한 판정을 위해
        - 헤드샷,바디샷 등의 판정을 빠르게 적용 할 수 있다.
    - Tracer Effect / Bullet Tracer를 사용한 궤적 표현
- Projectile
    - 특정 플레이어블 캐릭터의 스킬
Actor
- Object Pooling
Multi Play Server 
- Unreal Dedicated Server
- RPC
Mesh
- Dynamic Mesh / Destructible Mesh
UI
- MVVM / 이벤트 기반의 유지보수성 및 최적화를 고려한 UI 구현

## Project Part Directory And Main Features <br>
<details>
  <summary> Player </summary>  
    
    | -- Source
      | -- Player
        | -- PlayerCharacter.h // 플레이어 캐릭터의 상태 및 무기 장착, 입력 처리
        | -- MyPlayerController.h // 플레이어 입력 및 마우스 감도 조정, UI 모드 전환 관리
  
    | -- Content
      | -- Blueprnits
        | -- ABP_PlayerCharacter // 플레이어 애니메이션 블루프린트, 1인칭 및 3인칭 애니메이션 관리
        
### Player
</details>

<details>
  <summary> Actor </summary>  
    
    | -- Source
      | -- Actor
        | -- Actor.h // 플레이어 캐릭터의 상태 및 무기 장착, 입력 처리
  
    | -- Content
      | -- Blueprnits
        | -- ABP_PlayerCharacter // 플레이어 애니메이션 블루프린트, 1인칭 및 3인칭 애니메이션 관리
        
### Actor
</details>

<details>
  <summary> GameMode </summary>  
    
    | -- Source
      | -- GameMode
        | -- GameMode.h // 플레이어 캐릭터의 상태 및 무기 장착, 입력 처리
        | -- GameInstance.h // 플레이어 입력 및 마우스 감도 조정, UI 모드 전환 관리
        
### GameMode
</details>

<details>
  <summary> UI </summary>  
    
    | -- Source
      | -- UI
        | -- UI.h // 플레이어 캐릭터의 상태 및 무기 장착, 입력 처리
        | -- UI.h // 플레이어 입력 및 마우스 감도 조정, UI 모드 전환 관리

    | -- Content
      | -- Blueprnits
        | -- UI // 플레이어 애니메이션 블루프린트, 1인칭 및 3인칭 애니메이션 관리
        
### UI
</details>


## 시퀀스 다이어그램
- 멀티플레이 서버/클라이언트 시퀀스 다이어그램 사진

## UML 클래스 다이어그램
- 사진

