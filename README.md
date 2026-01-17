# 🎮 Kirby - DirectX 11 2D Game

> **DirectX 11**과 **C++**로 구현한 2D 액션 게임 "커비" 모작 프로젝트

[![Video](https://img.youtube.com/vi/YUSV_vlYPQU/maxresdefault.jpg)](https://www.youtube.com/watch?v=YUSV_vlYPQU)
**▶️ [YouTube 플레이 영상 보기](https://www.youtube.com/watch?v=YUSV_vlYPQU)**

---

## 📋 프로젝트 개요

- **개발 기간**: 2023.01 ~ 2023.02 (2개월)
- **개발 인원**: 1인 (개인 프로젝트)
- **장르**: 2D 액션 플랫포머
- **목적**: DirectX 11 렌더링 파이프라인 학습 및 2D 게임 개발 경험

---

## 🛠 기술 스택

| 분류 | 기술 |
|------|------|
| **언어** | C++ |
| **그래픽스 API** | DirectX 11 |
| **개발 환경** | Visual Studio 2019 |
| **패턴** | Component-Based Architecture |

---

## ✨ 주요 구현 기능

### 1️⃣ 커비 상태 시스템
- **Hungry**: 기본 상태 (적을 먹을 수 있음)
- **Full**: 적을 흡수한 상태
- **Fire**: 불 속성 능력 획득
- **Ice**: 얼음 속성 능력 획득

### 2️⃣ 몬스터 AI 시스템
- **기본 AI**: 패턴 기반 이동 및 공격
- **보스 AI**: 복잡한 페이즈별 패턴
- **속성 시스템**: Fire/Ice 속성 구현

### 3️⃣ 물리 & 충돌 처리
- 중력 및 점프 물리 구현
- AABB 기반 충돌 감지
- 픽셀 퍼펙트 충돌 처리

### 4️⃣ 컴포넌트 기반 아키텍처
총 **15개 컴포넌트**로 모듈화된 설계:
- `AnimatorComponent`: 애니메이션 재생
- `PhysicsComponent`: 물리 연산
- `ColliderComponent`: 충돌 처리
- `AiScriptBasicComponent` / `AiScriptBossComponent`: AI 로직
- `StateComponent`: 상태 머신
- `ActionComponent`: 입력 처리
- 기타 렌더링, 카메라, 씬 전환 컴포넌트 등

---

## 📁 프로젝트 구조

```
Kirby/
├── Core/                    # 엔진 코어
│   ├── D3D11/              # DirectX 11 래퍼
│   ├── SubSystem/          # 서브 시스템 (Input, Timer 등)
│   └── Engine.cpp          # 메인 엔진
├── Scene/                   # 게임 씬 관리
│   ├── Actors/             # Player, Monster 클래스
│   ├── Component/          # 15개 컴포넌트 구현
│   └── Scenes/             # 스테이지별 씬 (1-1 ~ 1-5)
├── Resource/                # 텍스처, 사운드 리소스
├── Assets/                  # 게임 에셋
└── Utility/                 # 유틸리티 함수
```

---

## 🎯 구현 하이라이트

### 🔹 컴포넌트 기반 설계
각 기능을 독립적인 컴포넌트로 분리하여 **재사용성**과 **유지보수성** 향상

```cpp
class Player final : public Actor
{
    KirbyState state = KirbyState::Hungry;
    Monster_Attribute kirby_eaten = Monster_Attribute::None;
    float hp = 500.0f;
};
```

### 🔹 상태 기반 애니메이션
Kirby의 4가지 상태(Hungry/Full/Fire/Ice)에 따라 동적으로 애니메이션 전환

### 🔹 5개 스테이지
`Scene_1_1` ~ `Scene_1_5`까지 각기 다른 난이도와 패턴 구성

---

## 🚀 실행 방법

### 📦 필수 요구사항
- **Visual Studio 2019** 이상
- **DirectX 11 SDK**
- **Windows 10/11**

### ⚙️ 빌드 설정
1. **DirectX 경로 설정**
   - Visual Studio 속성 관리자에서 `PropertySheet.props` 확인
   - DirectX 라이브러리 경로를 시스템 환경에 맞게 수정

2. **라이브러리 디렉터리**
   ```
   프로젝트 속성 → VC++ 디렉터리 → 포함 디렉터리/라이브러리 디렉터리
   → DirectX SDK 경로 추가
   ```

3. **빌드 및 실행**
   ```
   1. D2DGame.sln 열기
   2. Debug | Win32 구성 선택
   3. F5로 빌드 및 실행
   ```

자세한 설정 방법은 `ProjectSetting.txt` 참고

---

## 📚 학습 성과

### 기술적 성장
- ✅ **DirectX 11 렌더링 파이프라인** 이해
- ✅ **컴포넌트 기반 아키텍처** 설계 경험
- ✅ **2D 물리 엔진** 직접 구현
- ✅ **상태 머신 패턴** 실무 적용

### 코드 품질 개선
- 기능별 컴포넌트 분리로 코드 재사용성 향상
- Actor-Component 구조로 확장성 확보
- AI 스크립트 컴포넌트로 다양한 적 패턴 구현 용이

---

## 🎨 게임 특징

- 🎭 **4가지 커비 상태** 전환 시스템
- 🔥 **속성 기반** 몬스터 및 능력 시스템
- 🎯 **보스전** 구현 (페이즈별 패턴)
- 🏃 **5개 스테이지** 진행
- 💫 **픽셀 퍼펙트** 애니메이션 & 충돌

---

## 📌 참고사항

- 이 프로젝트는 학습 목적으로 제작되었습니다
- DirectX 11의 기본 개념 습득을 위한 개인 프로젝트입니다
- 원작 게임의 그래픽 및 사운드 에셋은 교육 목적으로만 사용되었습니다

---

## 📧 Contact

- **Email**: ggoggal@gmail.com
- **Portfolio**: [https://shimwoojin-portfolio.vercel.app/](https://shimwoojin-portfolio.vercel.app/)
- **GitHub**: [@shimwoojin](https://github.com/shimwoojin)

---

**Made with ❤️ by Woojin Shim** | 2023.01 ~ 2023.02
