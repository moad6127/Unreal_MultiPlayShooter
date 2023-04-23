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


	
</p>
</details>


<details><summary>Menu클래스의 OnFind함수</summary>
<p>

![MenuOnFindFunc](https://user-images.githubusercontent.com/101626318/233836935-c94b9797-9927-4219-b438-3d4cadbe2205.PNG)

	
</p>
</details>

<details><summary>Menu클래스의 OnJoin함수</summary>
<p>


![MenuOnJoinFunc](https://user-images.githubusercontent.com/101626318/233836948-4c70fd89-3e93-460b-8c6d-71b724bd0dd6.PNG)

</p>
</details>

