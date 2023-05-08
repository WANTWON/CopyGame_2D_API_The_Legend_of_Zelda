<div align="center">

# [API] 젤다의 전설 이상한 모자 모작


<img src="https://user-images.githubusercontent.com/106663427/236747771-7753267d-4e14-4942-9873-62f6405765d7.png" width="300" height="300"/>
</div>

개발기간 : 2주

개발인원 : 개인

## *동영상*
[[젤다의 전설 이상한 모자 모작]쥬신게임아카데미 게임학원 게임프로그래밍 3개월차 API 개인 작품 시연회_130기 원혜연_클라이언트](https://www.youtube.com/watch?v=Ol5pRMpzDj4)

## *게임 주요 사진*
### 메인화면 / Edit 모드
<img src="https://user-images.githubusercontent.com/106663427/236748542-67f28ab2-2102-4616-bce5-c36f1fc81471.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236749385-6833800f-26bc-483d-b3e1-051e2032a9e2.png" width="20%">

### 스테이지 구성
스테이지는 크게 메인필드, 미니컨텐츠, 상점, 던전으로 구성되어있습니다.
- 필드
- 시장(미니게임과 상점 컨텐츠)
- 소인국 마을
- 미니컨텐츠
- 던전
- 보스룸

<img src="https://user-images.githubusercontent.com/106663427/236750713-89ccdaa2-50df-41dd-8f85-ff788f45b239.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236750725-5d060bcf-3160-40e8-897e-889af915f778.png" width="20%">

<img src="https://user-images.githubusercontent.com/106663427/236751591-ec68fa59-c5ef-4574-a26b-79fd41ba3738.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236751601-a02f9081-c519-4035-93fc-6336292057e1.png" width="20%">

<img src="https://user-images.githubusercontent.com/106663427/236751610-1d3c7f5d-b087-4866-acf2-a27b034d2a70.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236751624-54cdab9f-fc2d-4240-b95f-56b71a519dca.png" width="20%">




## *컨텐츠 및 기능 설명*


### 1. 플레이어
<img src="https://user-images.githubusercontent.com/106663427/236753066-37f41e9a-7619-4622-bd1c-2342c7f640a3.gif" width="30%">

플레이어는 상하좌우 움직임, 구르기, 피격, 타격 등 여러 애니메이션이 존재합니다.

몬스터랑 충돌시 피격 모션이 되며 HP가 감소됩니다.

### 2. 아이템/스킬

아이템은 상점에서 구매 가능한 일반 아이템과, 퀘스트로 얻을 수 있는 아이템으로 나뉩니다.
또한 특정 퀘스트 완료시 얻을 수 있는 스킬 기능도 추가했습니다.

<aside>

- 일반 검
- 지팡이 : 식물을 성장시킬 때도 사용
- 활 : 일직선으로 공격
- 부메랑 : 회전하며 다시 돌아옴
- 방패 : 공격 방어
- 랜턴 : 불을 키는 용도로 사용
- 탈것 : 말(스피드 증가)
</aside>

### 3. NPC

NPC는 공통적으로 플레이어와 Rect 충돌하면 말풍선을 표시하며 대화 기능을 나타냅니다.

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

<img src="https://user-images.githubusercontent.com/106663427/236754129-a224c446-7c46-4d19-8d51-f0eae5bc4def.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236754137-f8377ac0-2ba6-4b90-bc48-4bdd2b2a70c1.png" width="20%">

- UI는 인벤토리창과 퀘스트 창이 있습니다. 인벤토리 창에서는 방향키를 통해 아이템을 고를 수 있고 해당 아이템을 Q창과 W창에 구분하여 장착 시킬 수 있습니다. 퀘스트 창은 현재 받은 퀘스트 내용을 보여주고 완료된 퀘스트는 파란색으로 표시됩니다.
- 메인 플레이에서는 UI는 아이템 착용 창 / 다이아 개수 / 열쇠 개수 / HP가 존재하며, HP 감소시 하트의 1/4가 감소되는 형태입니다.
- UI Object들을 관리하는 UI_Manager를 따로 만들어서, 해당 Manager내에서 플레이어로부터 Hp, 보유 다이아, 보유 열쇠들을 받아오게 했습니다. 그리고 해당 수 만큼 화면에 업데이트 하게 처리했습니다.

### 6. 이벤트 오브젝트

### 소인화 변신
<img src="https://user-images.githubusercontent.com/106663427/236754465-94eaf9fa-824f-4cf8-b0a4-eefdbc0ee812.png" width="20%">

- 소인화 변신 : 특정 공간에서 특정 키를 누르면 미니 모드로 변하게 됩니다 → 소인국 마을로 이동하는 것이 가능해집니다.

<img src="https://user-images.githubusercontent.com/106663427/236754569-577ed09a-9ba7-4203-a14e-09a34ef0d9de.gif" width="30%">

- 던전 퍼즐 : 싱글톤 패턴을 이용해서 던전 내부의 바닥 타일을 밟으면 문이 열리게 처리했습니다.
- 꺼진 횃불을 랜턴을 이용하여 켜지게 하였습니다.
- 버섯을 잡아당겨서 멀리 있는 곳까지 도약하도록 처리했습니다.

### 7. 미니컨텐츠/미니게임

- **신발가게 아저씨의 키보드게임**

신발이 가리키는 방향으로 키보드를 누르는 게임입니다. 총 3번의 턴을 성공하면 보상으로 탈것 획득합니다.

<img src="https://user-images.githubusercontent.com/106663427/236756290-3f2ca804-c103-4b04-b998-0b35c9184000.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236756356-f1f77db7-667c-4e24-bf97-0ce24979ca0f.gif" width="20%">


- **욕심꾸러기 요정과의 가위바위보**

랜덤으로 가위바위보 게임을 진행합니다. 욕심꾸러기 요정의 비위를 맞춰줘야해서 3번 져줘야 게임 승리합니다.

<img src="https://user-images.githubusercontent.com/106663427/236756476-335b43f1-f50b-4502-93cb-84c80ddd9edf.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236756490-4898be3e-a0d6-4244-8a01-8bd9ada4ef6f.png" width="20%">


- **꽃의 요정을 위해 식물 키우기**

꽃의 요정의 부탁으로 식물을 키워야합니다. 해당 식물은 마법지팡이의 주문으로부터 자라기때문에 링크가 지팡이를 장착하고 화분을 향해 공격해야 꽃이 자랍니다. 모든 꽃이 자라면 보상을 획득합니다.

<img src="https://user-images.githubusercontent.com/106663427/236756637-858db66b-1992-45e1-bdcb-8f4477adf8af.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236756764-88957305-3f64-4c04-b543-ef473cc05ca9.gif" width="20%">

### 8. **Client Mode/Edit  Mode**

<img src="https://user-images.githubusercontent.com/106663427/236748542-67f28ab2-2102-4616-bce5-c36f1fc81471.png" width="20%"><img src="https://user-images.githubusercontent.com/106663427/236749385-6833800f-26bc-483d-b3e1-051e2032a9e2.png" width="20%">

메인화면. Space 키를 누를시 메뉴 선택화면으로 이동합니다.

Edit 모드를 통해 맵 Object를 설치하는 툴을 만들었습니다. Start 버튼을 누르면 Client 모드로 게임이 실행됩니다.

<img src="https://user-images.githubusercontent.com/106663427/236756929-860b5932-9174-4042-b054-15b629aea845.gif" width="30%">

- 에디트 모드의 경우 마우스피킹을 통해서 충돌렉트의 타입을 설정했고, 이틀 통해 플레이어가 접근 가능한 공간과 접근 불가능한 공간을 구분짓게 했습니다.
- 해당 설치 데이터는 dat 파일로 저장하게 하여 클라이언트에 바로 연동 가능하게 했습니다. 오브젝트 또한 툴 안에서 마우스 좌표로 설치 가능하게 했습니다.
- Block, Water, Fall 등 플레이어가 충돌하는 타일의 종류에 따라 이루어지는 상호작용이 다릅니다.
    - Water - 해당 렉트와 충돌하면 플레이어가 물에 빠져서 체력이 깎이고 리스폰 됩니다.

        <img src="https://user-images.githubusercontent.com/106663427/236757038-c7747047-3539-4727-842c-a7a5d58beef6.gif" width="30%">
        
    - Fall - 플레이어가 낭떠러지에 떨어지고 체력이 깎이고 리스폰 됩니다.

        <img src="https://user-images.githubusercontent.com/106663427/236757074-5d503b37-5e1e-42b3-b542-aca415420fb0.gif" width="30%">
        
    - Block - 일반 충돌 렉트로 플레이어의 이동 경로를 제어합니다.

### 9. 기타 환경

- 풀/잔디 :풀이 자라있을 땐 지나갈 수 없지만 칼로 자르면 지나갈 수 있게 했습니다.

- 항아리 : 항아리를 들고 움직일 수 있으며 던져서 아이템을 획득할 수 있습니다. 아이템은 랜덤으로 다이아, 하트가 나옵니다.

## *기술적 요소*

자세한 코드 설명은 기술소개서 혹은 프로젝트 내에서 확인 가능합니다.

- 상/하체 2D 스프라이트 애니메이션
- 추상 팩토리 패턴  AbstractFactory 패턴 사용
- 윈도우 좌표계에서의 렉트 충돌, 충돌처리
- 포물선운동, 점프 기능
- TileManager를 만들어서 던전 퍼즐 깨기
- 오브젝트 X/Y 컬링 ScrollManager
