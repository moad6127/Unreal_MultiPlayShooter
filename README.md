# Unreal_MultiPlayShooter

이 프로젝트는 언리얼 엔진을 사용해서 멀티플레이 3인칭 슈팅게임을 만들었습니다 
또한 유데미 강좌중 하나인 Unreal Engine 5 C++ Multiplayer Shooter 코스를 기반으로 만들었으며 여기에 몇가지를 추가해서 만들었습니다.
사용한 버전은 언리얼5.1버전입니다.

<details><summary>구분</summary>
<p>
-멀티플레이 플러그인
	
	- Menu
	- MultiplayerSessionSubsystem

-캐릭터

 	- 캐릭터 컴포넌트
		-CombatComponent
			-전투및 움직임 관련 컴포넌트
		-BuffComponent
			-버프 픽업과 관련된 컴포넌트
		-LagComponent
			-ServerSideRewind와 관련된 컴포넌트
	- PlayerController
	- PlayerState
	
-HUD

	- 캐릭터 HUD
	- 무기 Pickup HUD
	- ESCHUD
	- Elim HUD


-게임모드

 	- GameState
		-Game 전반적인 정보
 	- 맵
		-로비맵
		-대난투맵
		-팀맵
		-깃발뺏기맵


-무기

	-무기 기능들
 	- 히트스캔
		-권총
		-샷건
		-스나이퍼 라이플
 	- 발사체
		-AR
		-로켓런쳐
		-수류탄발사기
 

-픽업

	-버프 픽업
		-Health픽업
		-Shield픽업
		-Jump픽업	
		-Speed픽업
	-탄약 픽업
		-탄약 종류별로 픽업

</p>
</details>


<details><summary>사용자의 메인화면</summary>
<p>

	
	
</p>
</details>


## 멀티플레이 플러그인

SteamSocket과 언리얼엔진의 OnlineSubSystem 활용한 멀티플레이 플러그인

- [플러그인주소](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Plugins/MultiplayerSessions).

멀티플레이 플러그인의 구조는 가장 중심적인 위치에 있는 Menu클래스와 멀티플레이의 세션을 만들고 참가하는 기능들이 있는 MultiplayerSessionSubsystem클래스등으로 이루어져 있다.

<details><summary>사용자의 메인화면</summary>
<p>

 -![MainMenu](https://user-images.githubusercontent.com/101626318/233771830-b40d17cb-48d3-49d1-a384-09099a0b66b6.PNG)
	

</p>
</details>

</p>
</details>
<details><summary>사용자의 Host화면</summary>
<p>
	
![HostSubMenu](https://user-images.githubusercontent.com/101626318/233772304-dede3ad1-d4ea-498b-835c-6199a10d27bc.PNG)
	
</p>
</details>

</p>
</details>
<details><summary>사용자의 Join화면</summary>
<p>

![JoinSubMenu](https://user-images.githubusercontent.com/101626318/233772343-7d0ccac1-c43f-49ca-b65f-9d3670a95bbf.PNG)

	
</p>
</details>

----------------------------------------------------------------------------------------------------

### MainMenu 

- [헤더파일 주소](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Plugins/MultiplayerSessions/Source/MultiplayerSessions/Public/Menu.h)

- [CPP파일 주소](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Plugins/MultiplayerSessions/Source/MultiplayerSessions/Private/Menu.cpp)

MainMenu클래스는 화면에 보여주게 되는 위젯들과 멀티플레이 기능들의 중심이 되는 클래스이다.


클래스 내부에는 다른 클래스인 MultiplayerSessionSubsystem의 커스텀 델리게이트들의 콜백 받기위한 함수들과 블루프린트와 바인딩된 위젯들이 있으며 위젯들의 기능을 하는 함수들로 이루어져 있다.


--------------------------------------
</details>

<details><summary>Menu클래스 바인딩된 위젯들</summary>
<p>

![MainMenu_BindWidget](https://user-images.githubusercontent.com/101626318/233836185-496e0047-4b8a-4f8c-bae2-7c632838f59a.PNG)

위젯들은 블루프린트와 바인딩 되어있다.


>Menu블루프린트

![MenuBlueprint](https://user-images.githubusercontent.com/101626318/233836795-a10be1f7-3208-456b-8e08-6fdbc39c354c.PNG)


	
</p>
</details>


---------------------------------------------

>Menu클래스의 델리게이트 콜백 함수들

델리게이트 함수들의 콜백을 바인딩 해서 완료되면 자동으로 Menu클래스의 함수를 호출하게 하기.

![MainMenu_DelegateBindFunctions](https://user-images.githubusercontent.com/101626318/233836148-c470ef3f-6fd8-4a89-a17a-c51a6ff0b359.PNG)

![MenuMenuSetupFuncDelegateBind](https://user-images.githubusercontent.com/101626318/233836441-ebaf496c-db7d-41b8-b5c4-67b5d7b49758.PNG)



----------------------------------------------

>대표 함수들의 정의

<details><summary>Menu클래스의 OnCreate함수</summary>
<p>

![MenuOnCreateFunc](https://user-images.githubusercontent.com/101626318/233836895-66421fe5-0688-431d-836a-c8c98e887e69.PNG)

>MultiplayerSessionSubsystem 에서 콜백 되며 bool 타입의 bWasSuccessful 로 성공여부를 알수있어 성공했을경우 Lobby로 이동하며 실패할경우 Debug메세지를 보내게 한다
	
	
</p>
</details>


<details><summary>Menu클래스의 OnFind함수</summary>
<p>

![MenuOnFindFunc](https://user-images.githubusercontent.com/101626318/233836935-c94b9797-9927-4219-b438-3d4cadbe2205.PNG)

>Find함수는 Join버튼을 누르면 호출되는 함수로 스크롤 박스에 현재 만들어진 서버들의 서버주인 이름과 매치타입을 보여주며 마우스로 클릭할경우 서버를 선택할수 있게 만들어 두었다.
	
</p>
</details>

<details><summary>Menu클래스의 OnJoin함수</summary>
<p>


![MenuOnJoinFunc](https://user-images.githubusercontent.com/101626318/233836948-4c70fd89-3e93-460b-8c6d-71b724bd0dd6.PNG)

>Join함수는 Find함수에서 서버가 선택되어 있으면 선택된 서버의 맵으로 이동하도록 만들었다.

</p>
</details>

---------------------------------------------------------------

### MultiplayerSessionSubsystem

- [헤더파일 주소](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Plugins/MultiplayerSessions/Source/MultiplayerSessions/Public/MultiplayerSessionSubsystem.h)

- [CPP파일 주소](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Plugins/MultiplayerSessions/Source/MultiplayerSessions/Private/MultiplayerSessionSubsystem.cpp)

MultiplayerSessionSubsystem 클래스는 멀티플레이의 기능들을 담당하는 클래스로 델리게이트 함수들과 관련 변수들로 이루어져 있어 Menu클래스에서 호출하면 함수의 기능들을 하고 
델리게이트의 콜백을 통해서 Menu클래스로 정보를 전해준다.

MultiplayerSessionSubsystem클래스는 UGameInstanceSubsystem를 부모로 하기때문에 온라인 기능을 수행할수 있다.

------------------------------------------------


<details><summary>MultiplayerSessionSubsystem Public부분 함수들</summary>
<p>
	
![SubsystemPublicSection](https://user-images.githubusercontent.com/101626318/233838451-f0353032-0ced-41c6-adf2-682287ab07f5.PNG)
	
>Menu클래스에서 호출하기 위해서 Public영역으로 생성함
		
</p>
</details>

<details><summary>MultiplayerSessionSubsystem 내부함수들</summary>
<p>

![SubSystemProtectedOrPrivateSection](https://user-images.githubusercontent.com/101626318/233838456-460d8120-db5f-4654-8493-200a050b645a.PNG)

>클래스 내부에서 멀티플레이 관련 기능들을 하기위해서 만든함수들로 외부에 보일 필요가 없어 내부적으로만 기능하게 함

</p>
</details>

----------------------------------------------

>대표 함수들의 정의

<details><summary>MultiplayerSessionSubsystem CreateSession</summary>
<p>
	
![SubSystemCreateFunc](https://user-images.githubusercontent.com/101626318/233839228-96aca037-3aba-4897-8c5e-d845a47b0e0e.PNG)

>Menu클래스에서 세션을 생성할때 호출하는 함수로 참가인원과 매치타입을 변수로 입력받으며 세션세팅을 마치고 성공적으로 함수가 끝나면 Menu클래스로 결과를 콜백시키는 기능을 한다.
>이미 세션이 있을경우 기존 세션을 없애고 만드는 기능도 포함되어 있다.

		
</p>
</details>


<details><summary>MultiplayerSessionSubsystem FindSession</summary>
<p>
	
![SubSystemFindFunc](https://user-images.githubusercontent.com/101626318/233839327-b2a7f95f-b913-461a-bba8-67a78cffe258.PNG)

>Menu클래스에서 세션들을 찾을때 사용되는 함수로 최대로 찾을 세션의 수를 입력받으며 성공적으로 할경우 써치 결과들을 Menu클래스로 보내게 된다.

		
</p>
</details>


<details><summary>MultiplayerSessionSubsystem JoinSession</summary>
<p>
	
![SubSystemJoinFunc](https://user-images.githubusercontent.com/101626318/233839453-6d6a1e61-146d-4129-be22-80cbc8d8176f.PNG)

>Menu클래스에서 세션에 참가할때 호출되는 함수로 써치 결과중 하나를 선택받아서 변수로 입력받게 된다. 성공적으로 함수가 작동할경우 세션에 참가하게되며 Lobby또는 맵으로 이동하게 된다.

	
</p>
</details>


<details><summary>MultiplayerSessionSubsystem 내부함수들</summary>
<p>
	
![SubSystemPrivateFunc](https://user-images.githubusercontent.com/101626318/233839585-e911bb6a-8760-40dd-8b84-9bc4e4ae67ef.PNG)

>위의 함수들이 바인딩 된 함수들로 함수들이 사용된곳에 Broadcast하여 결과들을 보내준다.
	
</p>
</details>


