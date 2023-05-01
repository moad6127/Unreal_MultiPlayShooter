# *Unreal_MultiPlayShooter*

이 프로젝트는 언리얼 엔진을 사용해서 멀티플레이 3인칭 슈팅게임을 만들었습니다 
또한 유데미 강좌중 하나인 Unreal Engine 5 C++ Multiplayer Shooter 코스를 기반으로 만들었으며 여기에 몇가지를 추가해서 만들었습니다.
사용한 버전은 언리얼5.1버전입니다.

<details><summary>구분</summary>
<p>
-멀티플레이 플러그인
	
	- Menu
	- MultiplayerSessionSubsystem

-캐릭터

	- 애님인스턴스
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



# *멀티플레이 플러그인*

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

## MainMenu 

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

## MultiplayerSessionSubsystem

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

>Menu클래스에서 세션을 생성할때 호출하는 함수로 참가인원과 매치타입을 변수로 입력받으며 세션세팅을 마치고 성공적으로 함수가 끝나면 내부함수로 이동하고 내부함수에서 Menu클래스로 콜백한다.
>이미 세션이 있을경우 기존 세션을 없애고 만드는 기능도 포함되어 있다.

		
</p>
</details>


<details><summary>MultiplayerSessionSubsystem FindSession</summary>
<p>
	
![SubSystemFindFunc](https://user-images.githubusercontent.com/101626318/233839327-b2a7f95f-b913-461a-bba8-67a78cffe258.PNG)

>Menu클래스에서 세션들을 찾을때 사용되는 함수로 최대로 찾을 세션의 수를 입력받으며 성공적으로 할경우 써치 결과를 내부함수로 보내고 Menu클래스로 콜백하게 된다.

		
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

-------------------------------------------------------------------------------------------

# *캐릭터*

프로젝트의 캐릭터와 그와 관련된 클래스들을 사용해서 캐릭터를 구성하게 만들었다.
캐릭터의 기본적인 클래스와 애니메이션과 관련된 애님 인스턴스, 캐릭터의 여러가지 기능을 담당할 컴포넌트들과 HUD에 보여주거나 게임모드에서 사용될 정보들이 저장된 PlayerState와 Controller등으로 캐릭터를 구성하게 된다.

[캐릭터 폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/Character)

## 캐릭터 클래스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Character/BlasterCharacter.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Character/BlasterCharacter.cpp)


캐릭터 클래스에는 캐릭터의 기능들을 위한 변수들과 함수들로 이루어져 있다.
기본적인 움직임을 위함 함수들과 TPS에 필요한 조준및 발사기능들, ServerSideRewind를 위한 HitBox등으로 이루어져 있으며 프로젝트의 여러 클래스와 연결되어 있다.
또한 멀티플레이를 위한 RPC들과 복제 함수들이 포함되어 서버클라이언트 멀티플레이에서 사용할수 있다.


<details><summary>캐릭터 클래스의 기본적인 함수들</summary>
<p>
	
![Character_BaseFunc](https://user-images.githubusercontent.com/101626318/233901044-c4e42ca6-a534-4c50-8137-88bae692fe94.PNG)
![Character_KeyBind](https://user-images.githubusercontent.com/101626318/233901214-89e2cd54-0408-4c82-8eba-6c6c13b8725f.PNG)


>캐릭터 클래스에서 기본적으로 사용되는 함수들, 각각 엔진에서 매핑된 함수들과 움직임 관련함수들, 발사키나 리로드같은 함수들이 있다.

	
</p>
</details>

<details><summary>움직임 관련 함수들</summary>
<p>
	

![Character_MovementFunc](https://user-images.githubusercontent.com/101626318/233901243-647b617f-404d-4a50-ae36-8e1371479a13.PNG)

>캐릭터의 기본적임 움직임을 담당하는 함수들
	
</p>
</details>

<details><summary>엔진에서 매핑된것들</summary>
<p>
	

![EngineInput](https://user-images.githubusercontent.com/101626318/233901269-840c6adc-c38a-49e4-aec5-fcd4e47daa37.PNG)

>엔진에서 설정된 매핑기능들
	
</p>
</details>

----------------------------------------------------------------

## 애님 인스턴스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Character/BlasterAnimInstance.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Character/BlasterAnimInstance.cpp)



캐릭터의 애니메이션과 관련된 클래스로 엔진의 애니메이션블루프린트을 통해서 캐릭터의 애니메이션을 담당한다 애님인스턴스 클래스에는 블루프린트에 필요한 변수들과 변수들을 설정하는 함수로 이루어져 있으며 필요하다면 C++코드로 AninNotify함수를 만들어서 사용할수 있다.



![AnimInstance_AnimGraph](https://user-images.githubusercontent.com/101626318/233910680-72c7772f-b668-44e4-a2e1-a65f0b24b258.PNG)
>애님 인스턴스 블루프린트의 AnimGraph구조도

<details><summary>Equip상태 State구조</summary>
<p>
	
![AnimInstance_EquipState](https://user-images.githubusercontent.com/101626318/233912732-ced4d565-83ef-43bf-8ed1-db0bcf9db5a2.PNG)
>Equip 상태에서의 State구조도

</p>
</details>


<details><summary>애님 인스턴스 변수들</summary>
<p>
	
![AnimInstance_V](https://user-images.githubusercontent.com/101626318/233912619-3f7a8c34-7c4d-4b1c-bc2e-9cf17a1635fb.PNG)
>애님 인스턴스에서 사용되는 변수들 일부분

	
</p>
</details>

<details><summary>애님 인스턴스 기본함수</summary>
<p>
	
![AnimInstance_Func](https://user-images.githubusercontent.com/101626318/233912870-d0341a54-08f0-4dd1-9eee-cf8593f7fc7e.PNG)
>애님 인스턴스의 변수들은 캐릭터 클래스의 Getter함수로 얻어와서 변수를 설정하게 된다.

</p>
</details>

----------------------------------------------------------------------------------

## *캐릭터 액터 컴포넌트*

캐릭터 클래스에 friend형식으로 붙여서 사용되는 컴포넌트로 각각의 컴포넌트들은 각각의 기능들을 담당하고 있으며, 캐릭터 클래스에서는 컴포넌트 클래스들의 함수를 호출해서 기능을 할수있게 만들었다.

현재 컴포넌트는 3가지로 전투밎 총기 관련 컴포넌트인 Combat컴포넌트와 캐릭터의 버프를 담당하는 Buff컴포넌트, ServerSideRewind와 랙보상을 담당하는 Lag컴포넌트가 있다.


[컴포넌트 폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents)

## Combat컴포넌트


- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/CombatComponent.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/CombatComponent.cpp)

캐릭터의 전투부분을 담당하는 컴포넌트로 대표적으로 발사기능과 재장전기능이 있으며 무기장착과 수류탄 발사, 조준선등의 기능들도 포함되어 있다.




<details><summary>발사 함수 기능</summary>
<p>

![CharacterFireButtonPressed](https://user-images.githubusercontent.com/101626318/234179152-6a04d864-323d-448d-854e-b45c00bfabbb.PNG)

![CombatFireButtonPressed](https://user-images.githubusercontent.com/101626318/234179194-61a4bc7a-b5d6-4863-80ad-983163fc4624.PNG)

![CombatFire](https://user-images.githubusercontent.com/101626318/234179206-093b9a86-5871-4e2e-8daf-9fc11fcead0a.PNG)

>Combat의 대표적인 함수인 발사 함수의 기능이다.
>우선 플레이어가 발사를 위한 키를 누르게 되면 캐릭터 클래스에서 매핑된 함수를 호출하게 되고 매핑된 함수에서 Combat의 함수를 호출, Combat의 Fire함수를 호출하게된다.
>이때 총의 종류에 호출되는 함수를 다르게 설정한다
>이후 Weapon클래스에서 발사를 완료한다.

</p>
</details>

<details><summary>재장전 기능</summary>
<p>

![CombatReload](https://user-images.githubusercontent.com/101626318/234180696-96b94da4-fcb8-4cbc-ab84-517344a358f7.PNG)

![CharacterReload](https://user-images.githubusercontent.com/101626318/234180748-a38e0123-2b77-44a1-acf3-205f2e757ab2.PNG)

![CombatFinishReload](https://user-images.githubusercontent.com/101626318/234180771-ef2e9e55-e5a9-47e6-b01e-52978c2e9347.PNG)

![EngineReloadMontage](https://user-images.githubusercontent.com/101626318/234180795-8bf2ec13-9c61-474d-ba92-c083d737bfee.PNG)

![CombatUpdateAmmo](https://user-images.githubusercontent.com/101626318/234180818-6965e754-c8c6-48f1-8e9a-e85619c70d21.PNG)

>플레이어가 재장전 키를 누르게되면 발사기능과 마찬가지로 캐릭터 클래스에서 재장전키와 매핑된 함수를 호출하고 Combat의 Reload함수를 호출하게 된다.
>이후 캐릭터 클래스의 ReloadMontage를 사용하며 총의 종류에 따라서 재생되는 애니메이션이 다르게 설정되어있다.
>재장전 모션이 끝날때 정도에 BlueprintCallable로 설정된 FinishReload가 호출되며 탄약을 업데이트 하게 된다.


</p>
</details>

------------------------------------------------------------------------------------------

## Buff컴포넌트


- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/BuffComponent.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/BuffComponent.cpp)


버프픽업을 얻게되면 나오는 이벤트들을 담당하는 컴포넌트로 힐,쉴드회복,스피드업,점프업등이 있다.


![Buffs](https://user-images.githubusercontent.com/101626318/234496622-89d31024-57d3-4609-94b1-d30f868e55b6.PNG)

 
 
<details><summary>Buff 컴포넌트 코드일부분</summary>
<p>

![BuffCompV](https://user-images.githubusercontent.com/101626318/234497584-d3fdf6fa-45ad-44bf-8da6-9fc96633fa03.PNG)

![BuffCompFunc](https://user-images.githubusercontent.com/101626318/234497640-e94ddf5d-d981-49d4-bb94-310b9b816ce3.PNG)

>각각의 이벤트에서 필요한 변수와 함수들이다.

</p>
</details>

<details><summary>Heal 함수</summary>
<p>

![BuffCompHeal](https://user-images.githubusercontent.com/101626318/234497847-e1a17ef6-66ec-4e65-ac49-a7a0f2a803ae.PNG)

![BuffCompTickComp](https://user-images.githubusercontent.com/101626318/234498008-7976088b-9348-46e4-8f09-e9b388999ca5.PNG)


> 캐릭터가 힐링픽업을 획득하게되면 먼저 Heal함수가 호출된다. 이후 캐릭터의 체력을 순차적으로 회복하도록 보이게 위해서 프레임마다 일정한 체력만 회복하게 하게 만든다.
> 쉴드 회복도 같은 방식으로 회복한다.


</p>
</details>

<details><summary>Speed 버프</summary>
<p>
	
![BuffCompSpeedBuff](https://user-images.githubusercontent.com/101626318/234498760-2cddd093-199a-4785-9bdb-e9c501761839.PNG)

>캐릭터가 스피드 버프 픽업을 획득하게 되면 발동되는 함수들이다. 버프픽업에서 세팅된 스피드의 속도와 시간을 받고 Timer를 사용해서 Time만큼만 버프가 지속되도록 만들었다.
>또한 멀티플레이를 위해서 NetMulticast형식으로 만들어서 서버와 클라이언트모두 버프가 작동되도록 설정해놓았다.


</p>
</details>


-----------------------------------------------------------------------------

## Lag컴포넌트

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/LagCompensationComponent.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/BlasterComponents/LagCompensationComponent.cpp)



클라이언트의 게임 경험을 좋게 하기 위해서 사용한 기술인 ServerSideRewind를 사용하기 위해서 필요한 기능들이 모여있는 컴포넌트로 캐릭터의 HitBox들을 저장하는 기능과
각각의 총타입에 따라서 ServerSideRewind를 사용하기 위한 함수들로 이루어져 있다.
ServerSideRewind는 게임에 인터넷등의 문제로 인해서 Ping이 높아 지연이 있을경우 사용된다.

![ScreenShot00001](https://user-images.githubusercontent.com/101626318/234503588-7fc0422d-8b03-4390-8f06-3f7b8e57b999.png)
> 캐릭터의 HitBox를 저장한것을 보여주는 사진이다.


<details><summary>LagComp 함수들</summary>
<p>
	
![LagCompSaveFrame](https://user-images.githubusercontent.com/101626318/234506690-d4b7d6eb-e8a2-4335-aad6-a350bae8d282.PNG)
![LagCompWeaponFunc](https://user-images.githubusercontent.com/101626318/234506711-5e6b9715-7382-45c8-87a2-1a7ac4efdeb7.PNG)
>HitBox를 저장하는 함수들과 ServerSideRewind를 위한 함수들
	
</p>
</details>

<details><summary>LagComp 변수들</summary>
<p>
	
![LagCompPrivate](https://user-images.githubusercontent.com/101626318/234506783-ab311b5c-51a7-4389-8d16-5ed0bd5c019a.PNG)

> 더블링크리스트로 캐릭터의 HitBox를 MaxRecodeTime의 시간만큼 저장을 해둔다.

</p>
</details>

<details><summary>LagComp 구조체</summary>
<p>

![LagCompStruct](https://user-images.githubusercontent.com/101626318/234507771-04c16da6-d8b1-4f83-b7e9-bae4a3c6ac3a.PNG)
>HitBox들의 정보와 언제 저장했는지 알기위한 시간, 캐릭터들을 한번에 저장하기위해서 만든 구조체와 결과를 보내기위한 구조체
	
</p>
</details>



>HitBox저장을 위한 함수기능
<details><summary>SaveFrame</summary>
<p>

![LagCompSaveFrameFunc1](https://user-images.githubusercontent.com/101626318/234511674-3caf4a70-4552-40e8-94a0-3485cdf50ea0.PNG)
![LagCompSaveFrameFunc2](https://user-images.githubusercontent.com/101626318/234511745-8eb140f2-d385-4949-b68c-445dffaeaf3f.PNG)
>ServerSideRewind를 위해서 캐릭터의 HitBox를 FrameHistory에 더블링크드로 저장한다.
>History의 끝부분이 정한 시간보다 크면 끝부분을 삭제하면서 일정한 크기를 유지하도록 한다.
>매 틱마다 호출되면서 저장된다.

</p>
</details>


>ServerSideRewind 기능
<details><summary>ServerSideRewind</summary>
<p>

![LagCompServerSideRewind1](https://user-images.githubusercontent.com/101626318/234512814-0e170778-f0c3-4885-8ab9-6a25166abcd2.PNG)
	
>ServerSideRewind를 위해서 함수가 호출이 되면 받은 변수들을 사용해서 어느시점의 HitBox를 체크해야될지 찾아낸다.
![LagCompServerSideRewind_GetCheckFrame](https://user-images.githubusercontent.com/101626318/234512844-5b18adf8-4564-4275-a272-2a3c25d7bf1b.PNG)
![LagCompServerSideRewind_GetCheckFrame2](https://user-images.githubusercontent.com/101626318/234512852-30f9154a-09ed-40de-8b70-f40e92b6ff17.PNG)

	
>체크할 HitBoxPackage를 이용해서 그때의 시간에 다른 캐릭터가 총에 맞았는지 확인하고 확인한 결과를 리턴한다.
![LagCompServerSideRewind_confirmHit1](https://user-images.githubusercontent.com/101626318/234512863-f0bae19e-5494-4ccd-939b-b9cd2871d77f.PNG)
![LagCompServerSideRewind_ConfirmHit2](https://user-images.githubusercontent.com/101626318/234512872-0286cbb2-a83c-4670-a90b-eb86466cad43.PNG)


>HitBox들의 위치를 설정하고 되돌리기위한 함수들
![LagCompServerSideRewind_otherFunc1](https://user-images.githubusercontent.com/101626318/234512880-5710c29a-e3bb-40a6-9dee-3f6375635b86.PNG)
![LagCompServerSideRewind_otherFunc2](https://user-images.githubusercontent.com/101626318/234512884-43068149-f093-4e2e-99e5-0d3b6a7aef8a.PNG)


</p>
</details>

-----------------------------------------------------------------------------------
## PlayerState


- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/PlayerState/BlasterPlayerState.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/PlayerState/BlasterPlayerState.cpp)


기본 점수는 부모 클래스인APlayerState의 Score를 사용했지만 다른 변수들은 직접 만들어서 사용했다.

<details><summary>Public부분</summary>
<p>

![PlayerStatePublicSection](https://user-images.githubusercontent.com/101626318/234775723-0df96fbd-51ef-43ce-b349-4653b0f8dc21.PNG)

![PlayerStateScoreAdd](https://user-images.githubusercontent.com/101626318/234776045-d841d957-9ccc-43b9-b72c-bb70f63ebdea.PNG)

>각종 복제 함수들과 업데이트 함수들이 저장되어 있다.
>화면에 보여주는HUD등을 업데이트 하는 기능은 Controller에 함수로 만들어 두었다.


</p>
</details>

<details><summary>Private부분</summary>
<p>

![PlayerStatePrivate](https://user-images.githubusercontent.com/101626318/234775625-0a28dc02-d973-44b6-bc7f-0df7e5022f9a.PNG)
>플레이어의 정보들을 저장하고있다.


</p>
</details>

-----------------------------------------------------------------------------
## PlayerController 

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/PlayerController/BlasterPlayerController.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/PlayerController/BlasterPlayerController.cpp)

플레이어 컨트롤러클래스 부분에 HUD와 관련된 것들을 연동시켜서 클라이언트의 개별적인 HUD를 담당하게 만들었다. 그리고 서버와 클라이언트의 시간을 동기화 하는 기능과 서버와 클라이언트의 지연등을 체크하고 관리하는 기능등 여려가지 기능들을 담당하고 있다.

<details><summary>SetHUD 관련</summary>
<p>

![PlayerControllerSetHUD](https://user-images.githubusercontent.com/101626318/234779453-c485cf27-5da5-405e-bff6-7b11d7d39740.PNG)
>클라이언트는 자신의 캐릭터의 컨트롤러에 접근할수 있으므로 자신의 HUD를 설정하는데 이용할수 있다.


</p>
</details>


<details><summary>서버와 클라이언트 TimeSync</summary>
<p>

> 서버와 클라이언트의 시간을 동기화 하는데 필요한 함수들과 변수들,
> 게임에서 모든사람들이 같은 시간을 사용하는것이 중요하다.
![PlayerControllerSyncTime](https://user-images.githubusercontent.com/101626318/234779717-0f215bb7-e806-4abb-9dfa-df86eec5704a.PNG)

>일정 시간마다 서버와 클라이언트의 시간을 동기화 하기, 
>설정한 주기마다 클라이언트의 시간을 체크하고 서버의 시간과 같게 만든다.

![PlayerControllerTimeCheck](https://user-images.githubusercontent.com/101626318/234779993-f89a42f0-b561-40fc-9c2d-402d4df5b6fe.PNG)
![PlayerControllerTimeCheck2](https://user-images.githubusercontent.com/101626318/234780001-3350d89d-a74d-4211-929b-f7570f036fc4.PNG)

>이렇게 동기화된 시간은 다시 화면에 HUD로 표시하고 남은 게임시간등을 표시할수 있다.
	
</p>
</details>

--------------------------------------------------------------------------
# *GameMode && GameState*


- [GameMode폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/GameMode)
- [GameState폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/GameState)


게임의 룰과 목표를 결정하는 게임모드는 각각 대난투 게임모드, 팀게임모드, 깃발뺏기 모드가 있으며 
대난투 모드는 팀없이 개인전으로 모든플레이어가 서로를 적으로 하는 모드로 킬을 할경우 개인점수가 올라가며 개인점수가 제일 높은 사람이 승리하는 모드이며, 팀게임 모드는 블루팀,레드팀이 생기며 적군 팀을 제거할경우 팀점수가 올라가는 방식이다, 깃발뺏기모드는 각팀의 리스폰 장소에 적의 깃발이 생성되며 깃발을 아군팀의 진영으로 가져올경우 팀점수가 올라가는 방식의 게임모드이다.

각각의 모드는 각각의 맵이 있다.

## BlasterGameMode

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/BlasterGameMode.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/BlasterGameMode.cpp)


![BlasterGameMode](https://user-images.githubusercontent.com/101626318/235115428-1781e296-fc53-40ba-b1cb-5923a1f40b41.png)


- 가장 기본이 되는 게임모드로 팀게임모드와 깃발뺏기모드들도 BlasterGameMode를 기반으로 만들어 졌다.   기능으로는 매치상태 체크및 매치상태 세팅, 플레이어 제거함수, 플레이어 리스폰 등이 존재한다.


<details><summary>PlayerEliminated 함수</summary>
<p>

![BaseGameModePlayerElim_1](https://user-images.githubusercontent.com/101626318/235117903-de1c50fb-e00e-48c6-9586-e3b2a4e36333.PNG)
![BaseGameModePlayerElim_2](https://user-images.githubusercontent.com/101626318/235117908-79148ef6-fc1f-4546-9b85-e6140d5a87df.PNG)


>플레이어 Elim함수
>플레이어를 잡은 컨트롤러와 죽은 컨트롤러, 죽은 캐릭터를 입력받고 각각의 플레이어 스텟에 킬과 데스를 저장한다.
>이후 킬을 한 플레이어의 점수가 현재 매치에서 제일 높을경우 킬리더로 설정한다.

![BaseGameModeKill](https://user-images.githubusercontent.com/101626318/235118691-62e07c54-a5a2-4180-b6d3-b2256b6a4e9c.png)
>죽은 플레이어의 화면에는 죽인 사람의 아이디가 나오게 만들었으며, 전체 킬피드가 나오게 만들었다.

</p>
</details>

<details><summary>매치 상태</summary>
<p>

![BaseGameMode_MatchState](https://user-images.githubusercontent.com/101626318/235119136-b6c38fe8-ff45-4ec1-b9b9-a8cc3c325ea4.PNG)
![BaseGameMode_OnMatchSet](https://user-images.githubusercontent.com/101626318/235119144-7382b7fa-1416-42b9-92bd-15c0597e68d1.PNG)
>BeginPlay함수에서 LevelStartingTime변수를 설정하고 Tick함수에서 각각의 매치상태시간에 따라서 상태를 변화하게 만들었다.

</p>
</details>

-----------------------------------------
## TeamGameMode

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/TeamsGameMode.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/TeamsGameMode.cpp)



![TeamGameMode](https://user-images.githubusercontent.com/101626318/235119804-6136ecfc-d9f9-4be7-8850-dea2b90666ed.png)
- 팀맵에서 사용되는 팀 게임모드 이다. 각각 레드팀과 블루팀이 있으며 팀의 설정은 캐릭터가 맵에 들어올때 설정이 되고 다시는 교체할수 없다.
- 같은팀끼리는 데미지를 줄수없도록 설정되어 있다.

<details><summary>팀 설정</summary>
<p>
	
> 게임에 들어오게 되면 GameState에 모든 플레이어의 팀을 저장하면서 개인의 팀을 설정하는 함수와 게임에서 나가게 되면 팀에서 제거하는 함수.
	
![TeamsGameModeLogInLogou](https://user-images.githubusercontent.com/101626318/235122845-95d551d7-ee5e-47fc-8291-6e95b40d3837.PNG)

>PlayerState에서 팀을 설정하고 팀컬러를 선택하도록 하는 함수
![PlayerStateSetTeam](https://user-images.githubusercontent.com/101626318/235143035-cbe5874f-8281-4b76-87ee-e46f08d9224b.PNG)

>Character클래스에서 팀 컬러를 세팅 하는 함수
![CharacterSetTeamColor](https://user-images.githubusercontent.com/101626318/235143356-ec7fcb6c-952b-473d-b382-2d7aeb462c54.PNG)

</p>
</details>

<details><summary>팀킬 방지 함수</summary>
<p>

> 같은 팀일경우 데미지가 들어가지 않게 만드는 함수.   
![TeamsGameModeCalculateDamage](https://user-images.githubusercontent.com/101626318/235144014-ea21964c-33db-4b17-834c-0cc7e964da96.PNG)

> 캐릭터 클래스의 ReceviveDamage함수에서 데미지를 설정할때 호출된다.
![CharacterReceiveDamage](https://user-images.githubusercontent.com/101626318/235144388-e7bad525-c516-4726-8cc5-6f032715fba4.PNG)

	
</p>
</details>

<details><summary>TeamGameMode에서 플레이어 킬</summary>
<p>

>TeamsGameMode는 BlasterGameMode를 부모로 해서 PlayerElimination함수를 상속받아서 사용할수있다.   
>TeamsGameMode에 맞게 기능을 더해서 함수를 만들수 있다.
>적팀을 죽이면 TeamScore가 증가하도록 만들었다.

	
![TeamsGameModePlayerElim](https://user-images.githubusercontent.com/101626318/235144677-f1912de6-212f-435d-9308-cc664699ea79.PNG)

	
</p>
</details>

--------------------------------------------------------------------------------
## CaptureTheFlagGameMode

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/CaptureTheFlagGameMode.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameMode/CaptureTheFlagGameMode.cpp)


![ScreenShot00000](https://user-images.githubusercontent.com/101626318/235148789-b83689eb-0df4-4b45-b9a4-48bdda787aa4.png)
>TeamGameMode를 부모로 만들어진 클래스이다. 깃발로 설정된 물체를 자신의 팀 베이스에 있는 FlagZone에 깃발을 가져오면 점수를 획득한다.
>깃발을 잡은 플레이어는 공격및 점프등의 모든 행동이 제약이 생기게 된다.


- [FlagZone클래스폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/CaptureTheFlag)


<details><summary>깃발 점수 획득</summary>
<p>

>FlagZone에 깃발로 설정된 물체가 들어오면 SpherOverlap함수가 호출되면서 GameMode의 깃발 점수획득 함수가 호출된다.

![FlagZoneOverlap](https://user-images.githubusercontent.com/101626318/235150270-77162bc4-e0f5-418d-ab05-2bbd010ff899.PNG)
![FlagAddScroe](https://user-images.githubusercontent.com/101626318/235150275-6e17bd3e-39cb-4ab5-96ff-609772ad5d6d.PNG)

	
</p>
</details>


--------------------------------------------------------------------------
## GameState

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameState/BlasterGameState.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/GameState/BlasterGameState.cpp)


>게임의 전체적인 상태를 저장하는 클래스로 TopScore를 저장하거나 팀게임경우 팀의 점수등을 저장하는 클래스이다.


<details><summary>TopScore체크 함수</summary>
<p>


![GameStateTopScore](https://user-images.githubusercontent.com/101626318/235152795-953b97db-8cc3-4b5c-8cd9-80d163daee06.PNG)
	
>캐릭터를 킬하게 되면 GameMode의 PlayerEliminated함수에서 호출되는 함수이다.  
>킬한 플레이어의 Score를 비교하면서 TopScore로 설정되면 머리위에 원반이 생기게 된다.
	
![ScreenShot00000](https://user-images.githubusercontent.com/101626318/235153928-1990c0df-e4e2-46be-a91b-875db6720de6.png)

	
</p>
</details>

<details><summary>TeamScore</summary>
<p>


![GameModeTeamScore](https://user-images.githubusercontent.com/101626318/235154154-03eb3c9b-e1e3-452d-b08c-a3b44079998d.PNG)

> 팀게임에서 사용되는 함수들로 팀점수를 획득할때 나오게 된다.

	
</p>
</details>



-------------------------------------------------------------------------
# *Weapons*

- [폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/Weapon)


![Weapons](https://user-images.githubusercontent.com/101626318/235296634-58b3b845-ba03-4651-9c24-22e51e0355e0.png)
- 총과 관련된 모든 클래스들이 있는 폴더로 기본 베이스가되는 Weapon클래스와 Weapon클래스를 부모로 하는 히트스캔무기와 발사체 무기, 샷건등이 있고, 발사체 무기들의 발사체 클래스들도 모여있으며, 총의 탄피 클래스, 깃발뺏기 모드에서 사용되는 깃발도 Weapon폴더에 모여있다.

--------------------------------------------------------------------------
## BaseWeapon클래스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Weapon.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Weapon.cpp)


- 모든 총의 클래스에서 기본이 되는 클래스로 히트스캔무기와 발사체 무기들은 Weapon클래스를 부모로 해서 만들어져있다.  
- 히트스캔과 발사체 무기의 기본이 되는 기능들을 가지고 있으며 Crosshair또한 Weapon클래스에서 선택한것이 화면에 보여지게 된다.


<details><summary>BaseWeaponFire</summary>
<p>

![BaseWeaponFIreFunc](https://user-images.githubusercontent.com/101626318/235344167-cd3e4168-ce25-40e2-96d2-8cc21023e214.PNG)
>기본무기의 발사함수이다.  
>무기의 Fire애니메이션을 재생한후, 탄피를 배출하는 기능과 Ammo를 소모하는 기능으로 이루어져있으며 HitScan과 발사체 무기클래스에서도 사용될수 있도록 만들었다.
	
</p>
</details>


<details><summary>무기 상태 변경함수</summary>
<p>

![BaseWeaponState](https://user-images.githubusercontent.com/101626318/235344209-d7398a25-62f0-44aa-afd9-99444461f1c1.PNG)
>무기 상태들을 EnumClass로 만들어 낸것이다.  
>기본 상태, 장착상태, 두번째무기 장착상태, 떨어진 상태등으로 이루어져 있다.

	
![BaseWeaponStateFunc](https://user-images.githubusercontent.com/101626318/235344239-a8cae369-ebd3-4332-a8c6-6923f356a2ac.PNG)
![BaseWeaponStateEquip](https://user-images.githubusercontent.com/101626318/235344241-85213278-e06d-4ad2-967a-226aa99e543c.PNG)

>무기의 상태가 변하게되면 각각의 함수들을 호출해서 무기의 콜리젼과 피직스들을 다시 설정하게 된다.

</p>
</details>

---------------------------------------------------------------------------------
## HitScan클래스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/HitScanWeapon.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/HitScanWeapon.cpp)

![Shoot](https://user-images.githubusercontent.com/101626318/235344350-7e9f5dc9-3880-4c14-b66b-b703ee884a24.png)

- HitScan무기클래스로 LineTrace를 사용해서 적이 적중했는지를 얻으며 적중했으면 데미지를 주는 방식이다.  
- 발사체무기처럼 발사체를 발사하는 방식이 아니라 총구에서 발사하는 방향으로 Line를 그려서 적중했는지 확인하는 방식이라 적이 적중했는지 바로 알수있다.  
- HitScan무기로는 권총, SMG, 스나이퍼 라이플이 있으며 샷건도HitScan무기이지만 여러개의 총알을 발사해야하므로 새로운 클래스로 만들어서 사용한다.

<details><summary>LineTrace 함수</summary>
<p>

![HitScanWeaponLineTrace](https://user-images.githubusercontent.com/101626318/235344463-9f3054d8-0ce6-4fda-a455-779504a62e3e.PNG)
> HitScan에서 LineTrace를 담당하는 함수이다.   
> 적중했는지 여부를 알수있으며 SmokeTrail을 추가해서 End지점까지 연기로 보이게 만들었다.
	
</p>
</details>

<details><summary>HitScanFire함수</summary>
<p>

![HitScanWeaponFireFunc_1](https://user-images.githubusercontent.com/101626318/235344521-55500a19-61f4-4db3-9168-29e7e5a3da42.PNG)
![HitScanWeaponFireFunc_2](https://user-images.githubusercontent.com/101626318/235344523-c4a4e877-1586-45f0-bede-cf88ce942335.PNG)
![HitScanWeaponFireFunc_3](https://user-images.githubusercontent.com/101626318/235344526-ad837c92-063e-4509-b1a5-9cecd86eeb7b.PNG)

> LineTrace를 통해서 얻은 적중값을 활용해서 적에게 대미지를 주도록 하는 함수이다.  
> 만약 ServerSideRewind를 사용하면 ServerSideRewind를 통해서 데미지를 주도록 만들어져 있다.

	
</p>
</details>


-------------------------------------------------------------------------------
## Shotgun클래스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Shotgun.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Shotgun.cpp)

![FireShotgun](https://user-images.githubusercontent.com/101626318/235344716-8084778c-dca9-49b5-99ee-48ab2fbe5a6c.png)

- HitScan무기이지만 한번 발사할때 여러발을 발사해야 하므로 새로운 클래스로 만들었다.

<details><summary>ShotgunLineTrace</summary>
<p>

![ShotgunHitTargets](https://user-images.githubusercontent.com/101626318/235344943-9f307e2e-509a-48a0-b594-94cc83776fdb.PNG)
> 샷건은 한번 발사에 여러발을 발사하게 되는데 이때 총알의 수는 변경가능하도록 만들어져 있고,  
> 총알의 횟수만큼 반복문을 사용해 적중결과를 저장하게 된다.


</p>
</details>

<details><summary>Shotgun Fire함수 일부분</summary>
<p>

![ShotgunFireFraction](https://user-images.githubusercontent.com/101626318/235344855-cf5b1ba4-45b7-4fd0-b539-bc8c1935bd27.PNG)
![ShotgunFireDamageStore](https://user-images.githubusercontent.com/101626318/235344857-5b826bcf-4c6c-4fee-ae9e-a9278a877342.PNG)
![ShotgunDamageSection](https://user-images.githubusercontent.com/101626318/235344860-fc320f1c-0c46-4320-9f34-3eba13322a91.PNG)

> 샷건무기는 한번발사에 여러발을 발사하므로 Map을 사용해서 HeadShot과 Body샷을 구분해 저장했으며 여러 캐릭터를 한번에 맞출수도 있기때문에 Array를 사용해서 맞은 캐릭터도 저장한다   
>이후 반복문을 사용해서 캐릭터당 데미지를 계산하고 저장한다음 ServerSideRewind여부를 통해서 데미지를 주게 된다.
	
	
</p>
</details>


-----------------------------------------------------------------------
## ProjectileWeapon 클래스

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileWeapon.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileWeapon.cpp)

![ProjectileWeapon](https://user-images.githubusercontent.com/101626318/235425362-d07e65a6-7ff5-4ffc-9911-5354a1035c93.png)

- 총을 발사할때 총구에서 발사체를 소환하고 발사체를 발사하여 공격하는 무기로 지금 프로젝트에서 발사체 무기는 돌격소총, 수류탄발사기, 로켓런쳐등이 있다.
- 총의 종류마다 발사체가 달라서 발사체 클래스가 따로 존재한다.


<details><summary>ProjectileFire </summary>
<p>

![ProjectileWeaponFire](https://user-images.githubusercontent.com/101626318/235426375-3faedd06-4580-44f9-bf26-e5b1b40e9d94.PNG)
![ProjectileServerSideRewindUse](https://user-images.githubusercontent.com/101626318/235426377-79ccc7ed-1bcc-46c7-9347-f4b073bc501b.PNG)
![ProjectileServerSideRewindNotUse](https://user-images.githubusercontent.com/101626318/235426380-56614894-84b3-433e-928f-8246524b6a9b.PNG)

>발사체 무기에서 Fire함수이다. 발사체 무기에서 Fire함수가 호출되면 각각의 발사체 무기에 맞는 발사체가 소환되여 진행하는 방식이다.  
>ServerSideRewind를 사용할경우와 사용하지 않는 경우로 나누어서 사용하게 된다.



![LagCompProjectileHitPredict](https://user-images.githubusercontent.com/101626318/235428426-df96b690-01f5-43a2-be85-cb93bdd50268.PNG)
>ServerSideRewind를 사용할경우 LagComp에서 발사체 예측함수인 PredictProjectilePath함수를 사용해서 발사체의 예상경로로 적이 적중했는지 파악한다.  
> 발사체의 예측함수, 각종 변수들은 Input으로 입력받는다.


	
</p>
</details>

--------------------------------------------------------------------------------
## ProjectileClass

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Projectile.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/Projectile.cpp)


- 발사체의 기본이되는 클래스로 이 클래스를 부모로해서 각각의 발사체 클래스들을 만든다.
- 각각의 발사체들의 기본이 되는 함수들로 이루어져 있으며 
- 현재 만들어져 있는 클래스들로는 돌격소총에 사용되는 발사체인 ProjectileBullet과 로켓에 사용되는 ProjectileRocket, 수류탄발사기인 ProjectileGrenade클래스들이 있다.

<details><summary>OnHitFunc</summary>
<p>

![ProjectileBulletOnHitFunc](https://user-images.githubusercontent.com/101626318/235427667-53dfafeb-6d1b-4121-96ee-93320187138b.PNG)
>발사체의 OnHit함수이다. 발사체가 다른액터에 Hit할경우 함수가 호출되도록 되어있으며 멀티플레이를 위해서 Multicast로 만들어져 있다.  
>플레이어와 맞을경우와 다른 액터에 맞을경우를 다르게 설정해서 다른 파티클과 사운드가 나오게 설정되어 있다.

	
</p>
</details>

<details><summary>ProjectileBulletClass</summary>
<p>

-----------------------------------------------------------------------------------------

## ProjectileBullet

- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileBullet.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileBullet.cpp)

![ProjectileBulletFire](https://user-images.githubusercontent.com/101626318/235428296-c4379776-f0bc-46d8-b043-bcd44fad584f.png)

-돌격소총무기의 발사체로 Tracer로 잔광이 남아서 발사체가 얼마나 진행했는지 확인할수 있다.

<details><summary>OnHitFunc</summary>
<p>

![BulletOnHit](https://user-images.githubusercontent.com/101626318/235428979-2fb6f8cc-07c6-421e-a3de-51a4245f0aca.PNG)
	
>Bullet의 OnHit함수로 캐릭터가 맞을경우 데미지를 주도록 되어있으며 ServerSideRewind를 사용할경우와 사용하지 않을경우로 나누어져 있다.

	
</p>
</details>
	
------------------------------------------------------------------------------------
	
</p>
</details>


<details><summary>ProjectileRocektClass</summary>
<p>

--------------------------------------------------------------------------

## ProjectileRocketClass
	
- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileRocket.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileRocket.cpp)
	

![RocketClass](https://user-images.githubusercontent.com/101626318/235430463-a3030364-6254-4e16-b31a-73989743a3ff.PNG)

>로켓의 발사체 클래스이다. 로켓은 로켓클래스만의 MovementComponent를 가지고 있으며 폭발성 대미지를 가지고 있기때문에 발사체에 직접맞지 않고 근처에 있기만 해도 어느정도의 대미지를 줄수 있다.
>또한 날아가는 동안 TrailSystem을 활용해서 연기를 연출하고 있다.


	
<details><summary>RocketOnHitFunc</summary>
<p>

![RocketOnHit](https://user-images.githubusercontent.com/101626318/235431259-c5e2b94b-98e6-4a4c-bf8b-0bab90d98afa.PNG)
![ExplodeDamage](https://user-images.githubusercontent.com/101626318/235431264-cf4497dc-1a71-4ced-a601-3f1a1cfddfcb.PNG)

>Rocket클래스의 OnHit함수이다. 자기자신은 피해를 입지 않도록 설정되어있으며 RocketMovementComponent를 통해서 움직임도 그대로 이어가도록 만들었다.  
>자기자신 말고 다른액터에 닿게되면 폭발데미지를 주고 일정시간이 지난후에 파괴되도록 Timer를 설정해서 사용한다.

</p>
</details>
	
<details><summary>TrailSystem</summary>
<p>

![BeginPlay](https://user-images.githubusercontent.com/101626318/235431515-55d23272-d191-4a15-872d-0e3b249611df.PNG)
![TrailSystem](https://user-images.githubusercontent.com/101626318/235431520-59dc752f-803b-42ea-b035-f9ea50c8b188.PNG)
>나이아가라 시스템을 사용해서 로켓의 연기를 연출한 함수들이다.  
>기본 Projectile함수에서 TrailSystem함수를 만든후 RocketClass의 BeginPlay에서 호출해 연기를 연출하였다.  
>OnHit함수에서 TrailSystem을 멈추도록 만들어져 있다.


</p>
</details>

	
------------------------------------------------------------------------------------------------------	


</p>
</details>


<details><summary>ProjectileGrenadeClass</summary>
<p>

--------------------------------------------------------------------------
- [헤더파일](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileGrenade.h)
- [CPP](https://github.com/moad6127/Unreal_MultiPlayShooter/blob/master/MultiplayerGame/Blaster/Source/Blaster/Weapon/ProjectileGrenade.cpp)
	
![Grenade](https://user-images.githubusercontent.com/101626318/235433255-d5d764e9-c627-411b-9a4a-067b026ea743.png)

- 수류탄 발사기에서 발사되는 클래스로 다른발사체와 다르게 OnHit될경우 바로 대미지를 주는것이 아닌 바운스 되는 점이 다르다.  

>생성자와 BeginPlay함수, 생성자에서 Bounce할지를 선택해서 사용한다.
![GreandeBeginPlay](https://user-images.githubusercontent.com/101626318/235433436-052a0b7d-73e5-41db-95d5-3a0ba36f317f.PNG)


![GrenadeBounceAndDestroy](https://user-images.githubusercontent.com/101626318/235433440-5f2e8708-57d5-4082-9cee-5d7274b87ecf.PNG)
>다른 발사체와는 다르게 적에게 맞을때 대미지를 주는것이 아니라 파괴될때 폭발성 대미지를 주도록 되어있다. 다른액터에 맞을경우 단순히 팅겨져 나오게 된다.
	
	
	
	
	

	
	
----------------------------------------------------------------------------------
</p>
</details>





---------------------------------------------------------------------------
# *HUD클래스*

- [HUD폴더](https://github.com/moad6127/Unreal_MultiPlayShooter/tree/master/MultiplayerGame/Blaster/Source/Blaster/HUD)

![HUD](https://user-images.githubusercontent.com/101626318/234789338-ad1d28e5-5dc3-4e0a-bc09-5b1c086411d7.PNG)


게임중 화면에 그려지는 모든것을 HUD라고 한다.
HUD에는 기본 CharcterOverlayHUD와 WeaponPickupHUD등 여러가지가 있으며 게임중 정보를 알려주는 역할을 하게 된다.


