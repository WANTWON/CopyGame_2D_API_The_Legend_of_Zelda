![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/0dcf6a77-0781-40ad-a8e1-383b9cdc8c11/Untitled.png)

## *동영상/GitHub*

---

[[젤다의 전설 이상한 모자 모작]쥬신게임아카데미 게임학원 게임프로그래밍 3개월차 API 개인 작품 시연회_130기 원혜연_클라이언트](https://www.youtube.com/watch?v=Ol5pRMpzDj4)

## *게임 주요 사진*

---

### 메인화면 / Edit 모드

### 스테이지 구성

스테이지는 크게 메인필드, 미니컨텐츠, 상점, 던전으로 구성되어있습니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a8c3580d-25be-4df9-a877-8cf225a62e48/Untitled.png)

- 필드

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f1a36e29-4a67-4eb7-952a-a6b6f61566a1/Untitled.png)

- 소인국 마을

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e31a6ba3-f2f5-4d1b-9a6a-eba113c4710a/Untitled.png)

- 던전

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5d4e049b-db32-4410-97f5-edc551a3f7d1/Untitled.png)

- 시장(미니게임과 상점 컨텐츠)

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/3826f41d-a845-45e0-81af-65be048089f8/Untitled.png)

- 미니 컨텐츠

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/0ed04047-c033-4b01-be7e-3cf91f459e13/Untitled.png)

- 보스룸

## *컨텐츠 및 기능 설명*

---

### 1. 플레이어

![제목 없는 동영상 - Clipchamp로 제작 (4).gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/19d30b25-08be-4d0f-9181-480c5fe9ea93/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(4).gif)

![제목 없는 동영상 - Clipchamp로 제작 (5).gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9df88b2f-543c-4071-a742-9e9e1948e8c1/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(5).gif)

플레이어는 상하좌우 움직임, 구르기, 피격, 타격 등 여러 애니메이션이 존재합니다.

몬스터랑 충돌시 피격 모션이 되며 HP가 감소됩니다.

### 2. 아이템/스킬

아이템은 상점에서 구매 가능한 일반 아이템과, 퀘스트로 얻을 수 있는 아이템으로 나뉩니다.
또한 특정 퀘스트 완료시 얻을 수 있는 스킬 기능도 추가했습니다.

![아이템을 다양하게 사용하는 모습](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8f683f15-7c0d-4868-95d9-c3bc0d1e0977/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(7).gif)

아이템을 다양하게 사용하는 모습

![특정 퀘스트를 완료하면 얻을 수 있는 스킬들](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/88e0a196-b11a-4abe-bfee-bdaf82a24f37/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(6).gif)

특정 퀘스트를 완료하면 얻을 수 있는 스킬들

<aside>
🔪 - 일반 검
- 지팡이 : 식물을 성장시킬 때도 사용
- 활 : 일직선으로 공격
- 부메랑 : 회전하며 다시 돌아옴
- 방패 : 공격 방어
- 랜턴 : 불을 키는 용도로 사용
- 탈것 : 말(스피드 증가)

</aside>

### 3. NPC

- 아빠 : 다가가서 space를 누르면 퀘스트가 활성화 됩니다.
- 신발 가게 아저씨 : 키보드 미니게임을 진행하고, 게임 성공 시 퀘스트가 완료 되며 탈것(말)을 획득합니다.
- 상점 로봇
- 소인국 마을 주민 : 일반 대화만 가능한 요정들과 퀘스트를 진행할 수 있는 이벤트 요정들이 있습니다.
- 소인국 마을 촌장 : 소인국 마을에서 진행되는 모든 퀘스트를 완료한 뒤 촌장에게 가면 스페셜 스킬을 얻을 수 있습니다.

### 4. 몬스터

- 뱀 : 플레이어에게 천천히 다가갑니다.
- 문어 : 돌 불렛을 플레이어 방향으로 직선으로 발사합니다.
- 고블린 : 플레이어가 일정 거리 내에 도달하면 플레이어를 향해 돌진합니다.
- 돌 몬스터 : 플레이어를 향해 점프하며 내리찍은 주변에 공격을 가합니다.
- 보스 : 3가지 패턴으로 구성했습니다.
    - 랜덤한 3방향으로 불렛 발사
    - 체력 50% 미만 시 몬스터를 생성하면서 공전하는 전기구체 생성
    - 체력 30% 미만 시 텔레포트를 하며 레이저 발사

### 5. UI

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a9b99be3-9a20-4d45-878e-c8ee9f104fbc/Untitled.png)

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ac7ce7d7-8535-4d04-8e0e-45e4ec78c735/Untitled.png)

- UI는 인벤토리창과 퀘스트 창이 있습니다. 인벤토리 창에서는 방향키를 통해 아이템을 고를 수 있고 해당 아이템을 Q창과 W창에 구분하여 장착 시킬 수 있습니다.
- 메인 플레이에서는 UI는 아이템 착용 창 / 다이아 개수 / 열쇠 개수 / HP가 존재하며, HP 감소시 하트의 1/4가 감소되는 형태입니다.
- UI Object들을 관리하는 UI_Manager를 따로 만들어서, 해당 Manager내에서 플레이어로부터 Hp, 보유 다이아, 보유 열쇠들을 받아오게 했습니다. 그리고 해당 수 만큼 화면에 업데이트 하게 처리했습니다.

### 6. 이벤트 오브젝트

- 소인화 변신 : 해당 공간에서 특정 키를 누르면 미니 모드로 변하게 됩니다 → 소인국 마을로 이동하는 것이 가능해집니다.
- 던전 퍼즐 : 싱글톤 패턴을 이용해서 던전 내부의 바닥 타일을 밟으면 문이 열리게 처리했습니다.
- 꺼진 횃불을 랜턴을 이용하여 켜지게 하였습니다.
- 버섯을 잡아당겨서 멀리 있는 곳까지 도약하도록 처리했습니다.

### 7. 미니컨텐츠/미니게임

- **신발가게 아저씨의 키보드게임**

신발이 가리키는 방향으로 키보드를 누르는 게임입니다. 총 3번의 턴을 성공하면 보상으로 탈것 획득합니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/045e52ad-021a-4a22-aecb-e71075867185/Untitled.png)

![제목 없는 동영상 - Clipchamp로 제작 (2).gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b9efe54a-e05c-48bd-8469-59f097394ae1/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(2).gif)

- **욕심꾸러기 요정과의 가위바위보**

랜덤으로 가위바위보 게임을 진행합니다. 욕심꾸러기 요정의 비위를 맞춰줘야해서 3번 져줘야 게임 승리합니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a5241644-da00-45c3-ae89-00a08d3d7787/Untitled.png)

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4f96f41c-8e0b-44dd-977e-921f25258e45/Untitled.png)

- **꽃의 요정을 위해 식물 키우기**

꽃의 요정의 부탁으로 식물을 키워야합니다. 해당 식물은 마법지팡이의 주문으로부터 자라기때문에 링크가 지팡이를 장착하고 화분을 향해 공격해야 꽃이 자랍니다. 모든 꽃이 자라면 보상을 획득합니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d4f8a5c3-8678-47c2-8125-0956d414b345/Untitled.png)

![제목 없는 동영상 - Clipchamp로 제작 (3).gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/66caa69b-05f5-4ed0-b8bf-6cf8c961028c/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91_(3).gif)

### 8. **Client Mode/Edit  Mode**

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/48abe2ea-6809-47f2-8d58-5979b5ae80e0/Untitled.png)

메인화면. Space 키를 누를시 메뉴 선택화면으로 이동합니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c1dfd2ad-df26-409d-97fd-0576be981477/Untitled.png)

Edit 모드를 통해 맵 Object를 설치하는 툴을 만들었습니다. Start 버튼을 누르면 Client 모드로 게임이 실행됩니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1c98baf9-2f8e-4dbb-bb3d-14b640169497/Untitled.png)

![제목 없는 동영상 - Clipchamp로 제작.gif](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/3e0d3891-cc5d-4d7a-96f2-580405ac883f/%EC%A0%9C%EB%AA%A9_%EC%97%86%EB%8A%94_%EB%8F%99%EC%98%81%EC%83%81_-_Clipchamp%EB%A1%9C_%EC%A0%9C%EC%9E%91.gif)

- 에디트 모드의 경우 마우스피킹을 통해서 충돌렉트의 타입을 설정했고, 이틀 통해 플레이어가 접근 가능한 공간과 접근 불가능한 공간을 구분짓게 했습니다. (Block Tile, Water Tile, Fall Tile 등 플레이어가 타일에 닿을 때 이루어지는 상호작용이 다릅니다.)
- 해당 데이터는 dat 파일로 저장하게 하여 클라이언트에 바로 연동 가능하게 했습니다. 오브젝트 또한 툴 안에서 마우스 좌표로 설치 가능하게 했습니다.

### 9. 기타 환경

- 풀/잔디 : 풀이 자라있을 땐 지나갈 수 없지만 칼로 자르면 지나갈 수 있게 했습니다.
- 물 : 물에 닿으면 물에 빠져서 체력이 깎이고 리스폰 되게 했습니다.

## *기술적 요소*

---

- 상/하체 2D 스프라이트 애니메이션
- 포물선운동, 점프 기능
- 싱글톤 패턴으로 던전 퍼즐 깨기
- 윈도우 좌표계에서의 렉트 충돌, 충돌처리
- 스폰 시스템 구성(함정에 빠질 시 플레이어가 체력이 깎이고 리스폰)
- X/Y 컬링 Scroll

