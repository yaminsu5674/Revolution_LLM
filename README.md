# 🕵️‍♂️ 추리 게임 - 심문관 시뮬레이션 (동아리 게임잼)

<img width="1838" height="931" alt="image" src="https://github.com/user-attachments/assets/6568fe8c-1758-428f-b9aa-056e7a87ae49" />


## 🎮 장르

3D 추리 / 대화 시뮬레이션 게임

## 📖 소개

동아리 게임잼에서 개발한 3D 추리 게임입니다. 플레이어는 심문관이 되어 다양한 용의자 NPC들과 대화하며 범인을 찾아내야 합니다. 핵심은 각 NPC에 OpenAI GPT API를 적용해 NPC가 상황과 성격에 맞게 반응하도록 구현한 점입니다.


## 🧰 기술 스택
	•	Unreal Engine 5
	•	Visual Studio 2022
	•	OpenAI GPT API
	•	Git


## 🧩 주요 기능

### 1. GPT 기반 NPC 대화 시스템

- 각 NPC에 **OpenAI GPT API** 적용  
- **System 메시지**를 통해 캐릭터별 역할, 성격, 상황, 규칙 등 전역 설정 유지  
- **User / Assistant 메시지 구조**로 대화 흐름 설계  
- NPC별 **대화 기록 배열(MessageHistory)** 관리  
  - 유저 질문 시 이전 대화를 포함해 API 호출  
  - 긴 대화에서도 상황과 맥락을 유지  

```cpp
// 의사 예시
TArray<FChatMessage> MessageHistory; // NPC별 대화 기록

// 유저 질문 시
MessageHistory.Add(UserMessage);
FString Payload = GeneratePayload(Model, MessageHistory);
FString NPCResponse = CallGPTAPI(Payload);
MessageHistory.Add(NPCResponse);
```

### 2. NPC 특성
	•	독립적인 성격과 배경을 가짐
	•	고유 반응 패턴 설계
	•	대화 로그를 통해 일관성 유지
	•	System 메시지를 통해 언어/톤/대답 포맷(한글) 항상 명시화


## 🐞 문제 및 해결

1. 대화 언어 및 역할 혼동
	•	원인: 기존에는 한글/영어 혼용으로 응답이 일관되지 않음
	•	해결: Role을 통해 한글 대답 포맷 항상 명시

2. 대화 맥락 유실
	•	원인: 긴 대화에서 이전 발언과 상황 정보 누락
	•	해결: 대화 기록 배열(MessageHistory)을 추가하여, 유저 질문 시 이전 대화를 덧씌워 컨텍스트 유지

3. 캐릭터 일관성 문제
	•	원인: 성격, 배경, 규칙과 다른 답변 생성
	•	해결: System 메시지 강화, 캐릭터별 고정 규칙 명시, 필요 시 예시 답변 제공


