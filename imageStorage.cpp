#include "pch.h"
#include "imageStorage.h"

imageStorage::imageStorage()
	:_background(nullptr),
	_currentCount(0)
{
}

imageStorage::~imageStorage()
{
}


HRESULT imageStorage::init()
{


	//로딩씬
	

	//로딩씬 우측하단 스프라이트


	_background = IMAGEMANAGER->addImage("SCENE_loadingScene", "Resource/IMG/ui/scene/LoadingScene_Background.bmp", 1280, 720, true, RGB(255, 0, 255));
	_loading = IMAGEMANAGER->addFrameImage("SCENE_loadingSprite", "Resource/IMG/ui/scene/loadingSprite.bmp", 1152, 227, 4, 1, true, RGB(255, 0, 255));

	frameX = 0;
	_count = 0;
	


	CreateThread(
		NULL,				//스레드 보안속성(자식윈도우 존재할때)
		NULL,				//스레드의 스택크기(0이면 메인쓰레드 동일)
		threadFunction,		//사용할 함수
		this,				//스레드 매개변수(this 로 뒀으니 본 클래스)
		NULL,				//스레드 특성
		NULL);				//스레드 ID

	return S_OK;
}

void imageStorage::release()
{
}

void imageStorage::update()
{
	

	if (_currentCount >= LOADINGMAX)
	{

		SCENEMANAGER->changeScene("stage1");
	}
	_count++;

	if (_count % 10 == 0)
	{
		frameX++;
	}

	if (frameX >= 4) frameX = 0;

}
void imageStorage::render()
{
	_background->render(getMemDC());
	

	_loading->frameRender(getMemDC(), WINSIZEX - 300, WINSIZEY - 250, frameX, 0);


}


//로딩 미리 이미지 다로드 시켜주자
DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	imageStorage* loadingHelper = (imageStorage*)lpParameter;

	//여러분은 그냥 여기에 사용하실 이미지랑 사운드 추가만 하면됩니다


	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		//이미지 총합
#pragma region IMAGESOURCES

		IMAGEMANAGER->addImage("SHADOW", "Resource/IMG/character/shadow.bmp", 128, 38, true, RGB(255, 0, 255));


		//////////////////////////////////////////////////////////////////////======플레이어======/////////////////////////////////////////////////////////////////////////////////
#pragma region PLAYERIMAGE

	//플레이어의 기본적인 상태/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	//IDLE
		IMAGEMANAGER->addFrameImage("PLAYER_idle", "Resource/IMG/character/player/idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
		//걷는상태

		IMAGEMANAGER->addFrameImage("PLAYER_walk", "Resource/IMG/character/player/walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));

		//RUN
		IMAGEMANAGER->addFrameImage("PLAYER_run", "Resource/IMG/character/player/run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));

		//JUMP
		IMAGEMANAGER->addFrameImage("PLAYER_jump", "Resource/IMG/character/player/jump.bmp", 480, 640, 3, 2, true, RGB(255, 0, 255));

		//ROLL
		IMAGEMANAGER->addFrameImage("PLAYER_roll", "Resource/IMG/character/player/roll.bmp", 900, 402, 9, 2, true, RGB(255, 0, 255));

		//대기상태
		IMAGEMANAGER->addFrameImage("PLAYER_wait", "Resource/IMG/character/player/wait.bmp", 2520, 440, 18, 2, true, RGB(255, 0, 255));

		//지갑...?
		IMAGEMANAGER->addFrameImage("PLAYER_wallet", "Resource/IMG/character/player/wallet.bmp", 2964, 420, 26, 2, true, RGB(255, 0, 255));

		//벽면에 붙어있는
		IMAGEMANAGER->addFrameImage("PLAYER_stick", "Resource/IMG/character/player/stick.bmp", 294, 330, 2, 2, true, RGB(255, 0, 255));


		// 사다리 이미지/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//사다리 탔을때
		IMAGEMANAGER->addFrameImage("PLAYER_climb", "Resource/IMG/character/player/climb.bmp", 720, 237, 6, 1, true, RGB(255, 0, 255));

		//사다리 타고 다 올라갔을때 이미지
		IMAGEMANAGER->addFrameImage("PLAYER_climbTop", "Resource/IMG/character/player/climbTop.bmp", 288, 192, 3, 1, true, RGB(255, 0, 255));

		//사다리 타고 내려올려고 할때 이미지
		IMAGEMANAGER->addFrameImage("PLAYER_climbTopDown", "Resource/IMG/character/player/climbDown.bmp", 288, 234, 3, 1, true, RGB(255, 0, 255));


		//공격/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//콤보어택 1일때 // 주먹
		IMAGEMANAGER->addFrameImage("PLAYER_comboAttack1", "Resource/IMG/character/player/comboAttack1.bmp", 1548, 390, 6, 2, true, RGB(255, 0, 255));

		//콤보어택 2일때 // 발차기
		IMAGEMANAGER->addFrameImage("PLAYER_comboAttack2", "Resource/IMG/character/player/comboAttack2.bmp", 1869, 402, 7, 2, true, RGB(255, 0, 255));

		//콤보어택 3일때 /다리 내려찍기
		IMAGEMANAGER->addFrameImage("PLAYER_comboAttack3", "Resource/IMG/character/player/comboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));

		//바닥의 적 공격
		IMAGEMANAGER->addFrameImage("PLAYER_stomp", "Resource/IMG/character/player/stomp.bmp", 1290, 420, 10, 2, true, RGB(255, 0, 255));

		//내려찍기 공격
		IMAGEMANAGER->addFrameImage("PLAYER_sAttack", "Resource/IMG/character/player/sAttack.bmp", 3030, 560, 10, 2, true, RGB(255, 0, 255));

		//회전회오리 공격
		IMAGEMANAGER->addFrameImage("PLAYER_sAttackDown", "Resource/IMG/character/player/sAttackDown.bmp", 7992, 438, 24, 2, true, RGB(255, 0, 255));

		//잡기
		IMAGEMANAGER->addFrameImage("PLAYER_grab", "Resource/IMG/character/player/grab.bmp", 270, 384, 2, 2, true, RGB(255, 0, 255));

		//잡기실패
		IMAGEMANAGER->addFrameImage("PLAYER_grabFail", "Resource/IMG/character/player/grabFail.bmp", 812, 422, 4, 2, true, RGB(255, 0, 255));

		//달릴떄 공격/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//대쉬 어택  //주먹
		IMAGEMANAGER->addFrameImage("PLAYER_dashAttack", "Resource/IMG/character/player/dashAttack.bmp", 2565, 414, 8, 2, true, RGB(255, 0, 255));

		//대쉬 날아서 어택
		IMAGEMANAGER->addFrameImage("PLAYER_dashSAttack", "Resource/IMG/character/player/dashSAttack.bmp", 5460, 456, 21, 2, true, RGB(255, 0, 255));

		//점프일때 공격/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//JUMPAttack
		IMAGEMANAGER->addFrameImage("PLAYER_jumpAttack", "Resource/IMG/character/player/jump_Attack.bmp", 1560, 432, 10, 2, true, RGB(255, 0, 255));


		//플레이어 피격/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//가드
		IMAGEMANAGER->addFrameImage("PLAYER_guard", "Resource/IMG/character/player/guard.bmp", 351, 378, 3, 2, true, RGB(255, 0, 255));

		//타격
		IMAGEMANAGER->addFrameImage("PLAYER_hit", "Resource/IMG/character/player/hit.bmp", 246, 420, 2, 2, true, RGB(255, 0, 255));

		//일정타수 방어 못하고 다운
		IMAGEMANAGER->addFrameImage("PLAYER_down", "Resource/IMG/character/player/down.bmp", 4968, 390, 23, 2, true, RGB(255, 0, 255));

		//스턴상태
		IMAGEMANAGER->addFrameImage("PLAYER_stun", "Resource/IMG/character/player/stun.bmp", 384, 384, 4, 2, true, RGB(255, 0, 255));

		//다운상태에서 다시 idle로
		IMAGEMANAGER->addFrameImage("PLAYER_stand", "Resource/IMG/character/player/stand.bmp", 1863, 450, 9, 2, true, RGB(255, 0, 255));

		//사망/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//앞에서 맞았을때 뒤통수로 넘어지면서 사망
		IMAGEMANAGER->addFrameImage("PLAYER_dead", "Resource/IMG/character/player/dead.bmp", 7280, 478, 26, 2, true, RGB(255, 0, 255));

		//뒤에서 맞았을때 뒤통수로 넘어지면서 사망 게임끝나고
		IMAGEMANAGER->addFrameImage("PLAYER_gameOver", "Resource/IMG/character/player/gameOver.bmp", 6240, 282, 26, 2, true, RGB(255, 0, 255));


		//특수무기 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

		//PICK
		IMAGEMANAGER->addFrameImage("PLAYER_pick", "Resource/IMG/character/player/pick.bmp", 222, 450, 2, 2, true, RGB(255, 0, 255));

		//야구방망이 IDLE
		IMAGEMANAGER->addFrameImage("PLAYER_batIdle", "Resource/IMG/character/player/wBatIdle.bmp", 1440, 560, 12, 2, true, RGB(255, 0, 255));

		//야구방망이 WALK
		IMAGEMANAGER->addFrameImage("PLAYER_batWalk", "Resource/IMG/character/player/wBatWalk.bmp", 1476, 500, 8, 2, true, RGB(255, 0, 255));

		//야구방망이 RUN
		IMAGEMANAGER->addFrameImage("PLAYER_batRun", "Resource/IMG/character/player/wBatRun.bmp", 6784, 560, 16, 2, true, RGB(255, 0, 255));

		//야구방망이 JUMP
		IMAGEMANAGER->addFrameImage("PLAYER_batJump", "Resource/IMG/character/player/wBatJump.bmp", 480, 640, 3, 2, true, RGB(255, 0, 255));

		//야구방망이 THROW
		IMAGEMANAGER->addFrameImage("PLAYER_batThrow", "Resource/IMG/character/player/wBatThrow.bmp", 1616, 600, 8, 2, true, RGB(255, 0, 255));

		//야구방망이로 공격
		IMAGEMANAGER->addFrameImage("PLAYER_batAttack", "Resource/IMG/character/player/wBatAttack.bmp", 1700, 700, 5, 2, true, RGB(255, 0, 255));

#pragma endregion PLAYERIMAGE

		//////////////////////////////////////////////////////////////////////////======NPC======/////////////////////////////////////////////////////////////////////////////////
#pragma region NPCIMAGE
	//남자1
		IMAGEMANAGER->addFrameImage("BOY1", "Resource/IMG/character/npc/boy1.bmp", 396, 480, 4, 2, true, RGB(255, 0, 255));
		//남자1 반응
		IMAGEMANAGER->addFrameImage("BOY1", "Resource/IMG/character/npc/boy1_react.bmp", 306, 480, 3, 2, true, RGB(255, 0, 255));

		//여자1
		IMAGEMANAGER->addFrameImage("GIRL1", "Resource/IMG/character/npc/girl.bmp", 312, 396, 4, 2, true, RGB(255, 0, 255));
		//여자1 반응
		IMAGEMANAGER->addFrameImage("GIRL1", "Resource/IMG/character/npc/girl1_react.bmp", 297, 384, 3, 2, true, RGB(255, 0, 255));

		//여자2
		IMAGEMANAGER->addFrameImage("GIRL2", "Resource/IMG/character/npc/girl2.bmp", 324, 522, 4, 2, true, RGB(255, 0, 255));
		//여자2 반응
		IMAGEMANAGER->addFrameImage("GIRL2", "Resource/IMG/character/npc/girl2_react.bmp", 360, 504, 3, 2, true, RGB(255, 0, 255));

#pragma endregion NPCIMAGE

		//////////////////////////////////////////////////////////////////////////======ENEMY======///////////////////////////////////////////////////////////////////////////////
#pragma region ENEMYIMAGE

	// 보스 =============================================================================================================================
		IMAGEMANAGER->addFrameImage("BOSS_attacked0", "Resource/IMG/character/enemy/boss/attacked.bmp", 2214, 594, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_attacked1", "Resource/IMG/character/enemy/boss/attacked 01.bmp", 737, 594, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_attacked2", "Resource/IMG/character/enemy/boss/attacked 02.bmp", 737, 594, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_attacked3", "Resource/IMG/character/enemy/boss/attacked 03.bmp", 738, 598, 3, 2, true, RGB(255, 0, 255));

		// 보스 대쉬(들이 박치기?)
		IMAGEMANAGER->addFrameImage("BOSS_dash", "Resource/IMG/character/enemy/boss/dash.bmp", 2619, 582, 10, 2, true, RGB(255, 0, 255));

		// 보스 가드
		IMAGEMANAGER->addFrameImage("BOSS_block", "Resource/IMG/character/enemy/boss/block.bmp", 1688, 576, 8, 2, true, RGB(255, 0, 255));


		// 보스 죽음
		IMAGEMANAGER->addFrameImage("BOSS_death", "Resource/IMG/character/enemy/boss/death.bmp", 4576, 576, 13, 2, true, RGB(255, 0, 255));
		// 보스 패배
		IMAGEMANAGER->addFrameImage("BOSS_defeat", "Resource/IMG/character/enemy/boss/defeat.bmp", 4576, 576, 13, 2, true, RGB(255, 0, 255));
		// 보스 어지러워
		IMAGEMANAGER->addFrameImage("BOSS_dizzy", "Resource/IMG/character/enemy/boss/dizzy.bmp", 1024, 434, 4, 2, true, RGB(255, 0, 255));
		// 보스 다운
		IMAGEMANAGER->addFrameImage("BOSS_down", "Resource/IMG/character/enemy/boss/down.bmp", 5830, 510, 22, 2, true, RGB(255, 0, 255));
		// 보스 엘보우
		IMAGEMANAGER->addFrameImage("BOSS_elbow1", "Resource/IMG/character/enemy/boss/elbow.bmp", 2915, 652, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_elbow2", "Resource/IMG/character/enemy/boss/elbow2.bmp", 2885, 652, 11, 2, true, RGB(255, 0, 255));
		// 보스 일반 히트
		IMAGEMANAGER->addFrameImage("BOSS_getHit", "Resource/IMG/character/enemy/boss/gethit.bmp", 2214, 594, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_getHit_A", "Resource/IMG/character/enemy/boss/gethit_A.bmp", 5830, 510, 22, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_getHit_K", "Resource/IMG/character/enemy/boss/gethit_K.bmp", 2880, 594, 10, 2, true, RGB(255, 0, 255));
		// 보스 일어남(기상)
		IMAGEMANAGER->addFrameImage("BOSS_getUp_C", "Resource/IMG/character/enemy/boss/getup_C.bmp", 2187, 576, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_getUp_S", "Resource/IMG/character/enemy/boss/getup_S.bmp", 2560, 466, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_getUp_SS", "Resource/IMG/character/enemy/boss/getup_SS.bmp", 3735, 580, 15, 2, true, RGB(255, 0, 255));
		// 보스 그로기
		IMAGEMANAGER->addFrameImage("BOSS_groggy", "Resource/IMG/character/enemy/boss/groggy.bmp", 1024, 434, 4, 2, true, RGB(255, 0, 255));
		// 보스 넘어져 있을 때 히트
		IMAGEMANAGER->addFrameImage("BOSS_groundHit", "Resource/IMG/character/enemy/boss/groundhit.bmp", 1036, 460, 4, 2, true, RGB(255, 0, 255));
		// 보스 소리지르기
		IMAGEMANAGER->addFrameImage("BOSS_howling", "Resource/IMG/character/enemy/boss/howling.bmp", 2916, 576, 12, 2, true, RGB(255, 0, 255));
		// 보스 가만히
		IMAGEMANAGER->addFrameImage("BOSS_idle", "Resource/IMG/character/enemy/boss/idle.bmp", 3180, 634, 12, 2, true, RGB(255, 0, 255));
		// 보스 엉덩방아 찍기
		IMAGEMANAGER->addFrameImage("BOSS_meteor", "Resource/IMG/character/enemy/boss/meteor.bmp", 480, 460, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_meteor_A", "Resource/IMG/character/enemy/boss/meteor_A.bmp", 410, 660, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_meteor_C", "Resource/IMG/character/enemy/boss/meteor_C.bmp", 2988, 576, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_meteor_G", "Resource/IMG/character/enemy/boss/meteor_G.bmp", 1224, 422, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_meteor_J", "Resource/IMG/character/enemy/boss/meteor_J.bmp", 1888, 672, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_meteor_M", "Resource/IMG/character/enemy/boss/meteor_M.bmp", 4674, 576, 19, 2, true, RGB(255, 0, 255));
		// 보스 이동
		IMAGEMANAGER->addFrameImage("BOSS_move", "Resource/IMG/character/enemy/boss/move.bmp", 2110, 588, 10, 2, true, RGB(255, 0, 255));
		// 보스 페이즈 변경?
		IMAGEMANAGER->addFrameImage("BOSS_phase", "Resource/IMG/character/enemy/boss/phase.bmp", 5658, 748, 23, 2, true, RGB(255, 0, 255));
		// 보스 포효
		IMAGEMANAGER->addFrameImage("BOSS_roar", "Resource/IMG/character/enemy/boss/roar.bmp", 2916, 576, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_roar_U", "Resource/IMG/character/enemy/boss/roar_U.bmp", 1000, 474, 4, 2, true, RGB(255, 0, 255));
		// 보스 뒤후리기
		IMAGEMANAGER->addFrameImage("BOSS_slab", "Resource/IMG/character/enemy/boss/slab.bmp", 5278, 582, 14, 2, true, RGB(255, 0, 255));
		// 보스 앞후리기
		IMAGEMANAGER->addFrameImage("BOSS_slap", "Resource/IMG/character/enemy/boss/slap.bmp", 5278, 582, 14, 2, true, RGB(255, 0, 255));
		// 보스 주먹질
		IMAGEMANAGER->addFrameImage("BOSS_smash", "Resource/IMG/character/enemy/boss/smash.bmp", 11880, 594, 27, 2, true, RGB(255, 0, 255));
		// 보스 앉아서 때리기
		IMAGEMANAGER->addFrameImage("BOSS_standAttack", "Resource/IMG/character/enemy/boss/standattack.bmp", 2187, 576, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_standAttack1", "Resource/IMG/character/enemy/boss/standattack1.bmp", 2560, 466, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_standAttack2", "Resource/IMG/character/enemy/boss/standattack2.bmp", 3735, 580, 15, 2, true, RGB(255, 0, 255));
		// 보스 숄더태클(어깨밀치기)
		IMAGEMANAGER->addFrameImage("BOSS_tackle", "Resource/IMG/character/enemy/boss/tackle.bmp", 1120, 576, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("BOSS_tackle_L", "Resource/IMG/character/enemy/boss/tackle_L.bmp", 2882, 576, 11, 2, true, RGB(255, 0, 255));
		// 보스 등장?
		IMAGEMANAGER->addFrameImage("BOSS_taunt", "Resource/IMG/character/enemy/boss/taunt.bmp", 5658, 748, 23, 2, true, RGB(255, 0, 255));
		// 보스 걷기
		IMAGEMANAGER->addFrameImage("BOSS_walk", "Resource/IMG/character/enemy/boss/walk.bmp", 2110, 588, 10, 2, true, RGB(255, 0, 255));
		// 보스 펀치
		IMAGEMANAGER->addFrameImage("BOSS_wupunch", "Resource/IMG/character/enemy/boss/wupunch.bmp", 11880, 594, 27, 2, true, RGB(255, 0, 255));
#pragma endregion BOSS
		// 치어리더 =========================================================================================================================
#pragma region CHEERLEADER
	// 치어리더 다운
		IMAGEMANAGER->addFrameImage("CHEERLEADER_backDown", "Resource/IMG/character/enemy/cheerLeader/backdown.bmp", 9338, 436, 29, 2, true, RGB(255, 0, 255));
		// 치어리더 백플립(백덤블링)
		IMAGEMANAGER->addFrameImage("CHEERLEADER_backFlip", "Resource/IMG/character/enemy/cheerLeader/backflip.bmp", 6732, 612, 22, 2, true, RGB(255, 0, 255));
		// 치어리더 구걸(팀 합류)
		IMAGEMANAGER->addFrameImage("CHEERLEADER_begging", "Resource/IMG/character/enemy/cheerLeader/begging.bmp", 513, 372, 3, 2, true, RGB(255, 0, 255));
		// 치어리더 가드
		IMAGEMANAGER->addFrameImage("CHEERLEADER_block", "Resource/IMG/character/enemy/cheerLeader/block.bmp", 519, 428, 3, 2, true, RGB(255, 0, 255));
		// 치어리더 콤보공격
		IMAGEMANAGER->addFrameImage("CHEERLEADER_comboAttack1", "Resource/IMG/character/enemy/cheerLeader/ComboAttack1.bmp", 1332, 468, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("CHEERLEADER_comboAttack2", "Resource/IMG/character/enemy/cheerLeader/ComboAttack2.bmp", 1827, 426, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("CHEERLEADER_comboAttack3", "Resource/IMG/character/enemy/cheerLeader/ComboAttack3.bmp", 4050, 498, 15, 2, true, RGB(255, 0, 255));
		// 치어리더 히트
		IMAGEMANAGER->addFrameImage("CHEERLEADER_getHit", "Resource/IMG/character/enemy/cheerLeader/gethit.bmp", 1539, 426, 9, 2, true, RGB(255, 0, 255));
		// 치어리더 잡기히트
		IMAGEMANAGER->addFrameImage("CHEERLEADER_heldHit", "Resource/IMG/character/enemy/cheerLeader/HeldHit.bmp", 840, 384, 5, 2, true, RGB(255, 0, 255));
		// 치어리더 잡기 해방
		IMAGEMANAGER->addFrameImage("CHEERLEADER_heldRelease", "Resource/IMG/character/enemy/cheerLeader/HeldRelease.bmp", 840, 456, 4, 2, true, RGB(255, 0, 255));
		// 치어리더 가만히
		IMAGEMANAGER->addFrameImage("CHEERLEADER_idle", "Resource/IMG/character/enemy/cheerLeader/idle.bmp", 2304, 432, 12, 2, true, RGB(255, 0, 255));
		// 치어리더 점프
		IMAGEMANAGER->addFrameImage("CHEERLEADER_jump", "Resource/IMG/character/enemy/cheerLeader/jump.bmp", 540, 474, 3, 2, true, RGB(255, 0, 255));
		// 치어리더 점프 공격
		IMAGEMANAGER->addFrameImage("CHEERLEADER_jumpAttack", "Resource/IMG/character/enemy/cheerLeader/JumpAttack.bmp", 1491, 654, 7, 2, true, RGB(255, 0, 255));
		// 치어리더 오르기(사다리 등)
		IMAGEMANAGER->addFrameImage("CHEERLEADER_ladder", "Resource/IMG/character/enemy/cheerLeader/ladder.bmp", 900, 255, 6, 1, true, RGB(255, 0, 255));
		// 치어리더 달리기
		IMAGEMANAGER->addFrameImage("CHEERLEADER_run", "Resource/IMG/character/enemy/cheerLeader/run.bmp", 1368, 318, 8, 2, true, RGB(255, 0, 255));
		// 치어리더 기절
		IMAGEMANAGER->addFrameImage("CHEERLEADER_stun", "Resource/IMG/character/enemy/cheerLeader/stun.bmp", 540, 390, 4, 2, true, RGB(255, 0, 255));
		// 치어리더 착지?(아마도 사다리같은 곳에서 내려오는)
		IMAGEMANAGER->addFrameImage("CHEERLEADER_transition", "Resource/IMG/character/enemy/cheerLeader/transition.bmp", 396, 186, 3, 1, true, RGB(255, 0, 255));
		// 치어리더 걷기
		IMAGEMANAGER->addFrameImage("CHEERLEADER_walk", "Resource/IMG/character/enemy/cheerLeader/walk.bmp", 2736, 438, 12, 2, true, RGB(255, 0, 255));
		// 치어리더 무기히트
		IMAGEMANAGER->addFrameImage("CHEERLEADER_weaponHit", "Resource/IMG/character/enemy/cheerLeader/weaponHit.bmp", 7084, 436, 22, 2, true, RGB(255, 0, 255));


#pragma endregion CHEERLEADER

		// 스쿨보이 =========================================================================================================================
#pragma region SCHOOLBOYIMAGE 

	//SCHOOLBOYIMAGE

		IMAGEMANAGER->addFrameImage("SCHOOLBOY_backdown", "Resource/IMG/character/enemy/scoolBoy/backdown.bmp", 7695, 438, 27, 2, true, RGB(255, 0, 255));			//넘어졌을때
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_begging", "Resource/IMG/character/enemy/scoolBoy/begging.bmp", 216, 354, 2, 2, true, RGB(255, 0, 255));				//항복
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_block", "Resource/IMG/character/enemy/scoolBoy/block.bmp", 459, 438, 3, 2, true, RGB(255, 0, 255));					//막기
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_comboAttack1", "Resource/IMG/character/enemy/scoolBoy/ComboAttack1.bmp", 2352, 426, 7, 2, true, RGB(255, 0, 255));	//공격1
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_comboAttack2", "Resource/IMG/character/enemy/scoolBoy/ComboAttack2.bmp", 1757, 444, 7, 2, true, RGB(255, 0, 255));	//공격2
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_comboAttack3", "Resource/IMG/character/enemy/scoolBoy/ComboAttack3.bmp", 1890, 558, 9, 2, true, RGB(255, 0, 255));	//공격3

		IMAGEMANAGER->addFrameImage("SCHOOLBOY_gethit", "Resource/IMG/character/enemy/scoolBoy/gethit.bmp", 1728, 450, 9, 2, true, RGB(255, 0, 255));				//맞는 동작
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_heldHit", "Resource/IMG/character/enemy/scoolBoy/HeldHit.bmp", 576, 372, 3, 2, true, RGB(255, 0, 255));				//잡히고 맞는 동작
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_heldRelease", "Resource/IMG/character/enemy/scoolBoy/HeldRelease.bmp", 660, 480, 4, 2, true, RGB(255, 0, 255));		//잡히고 푼 동작
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_idle", "Resource/IMG/character/enemy/scoolBoy/idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));					//기본
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_jump", "Resource/IMG/character/enemy/scoolBoy/jump.bmp", 423, 486, 3, 2, true, RGB(255, 0, 255));					//점프
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_jumpAttack", "Resource/IMG/character/enemy/scoolBoy/jumpAttack.bmp", 1224, 468, 6, 2, true, RGB(255, 0, 255));		//점프 공격
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_ladder", "Resource/IMG/character/enemy/scoolBoy/ladder.bmp", 738, 264, 6, 1, true, RGB(255, 0, 255));				//기어올라가는동작
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_run", "Resource/IMG/character/enemy/scoolBoy/run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));					//달리기
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_stun", "Resource/IMG/character/enemy/scoolBoy/Stun.bmp", 633, 408, 4, 2, true, RGB(255, 0, 255));					//스턴
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_transition", "Resource/IMG/character/enemy/scoolBoy/transition.bmp", 405, 183, 3, 1, true, RGB(255, 0, 255));		//기어올라온 후
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_upercut", "Resource/IMG/character/enemy/scoolBoy/upercut.bmp", 1386, 502, 7, 2, true, RGB(255, 0, 255));				//어퍼컷
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_walk", "Resource/IMG/character/enemy/scoolBoy/Walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));					//걷기
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wAttack", "Resource/IMG/character/enemy/scoolBoy/WAttack.bmp", 1830, 660, 5, 2, true, RGB(255, 0, 255));				//무기 휘둘기

		IMAGEMANAGER->addFrameImage("SCHOOLBOY_weaponSwing", "Resource/IMG/character/enemy/scoolBoy/weapon_swing.bmp", 5415, 438, 19, 2, true, RGB(255, 0, 255));	//무기 맞는 동작
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_weaponHit", "Resource/IMG/character/enemy/scoolBoy/weaponHit.bmp", 5415, 438, 19, 2, true, RGB(255, 0, 255));		//무기 맞은 동작

		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wIdle", "Resource/IMG/character/enemy/scoolBoy/WIdle.bmp", 1224, 552, 8, 2, true, RGB(255, 0, 255));					//무기 든 상태
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wJump", "Resource/IMG/character/enemy/scoolBoy/WJump.bmp", 432, 468, 3, 2, true, RGB(255, 0, 255));					//무기 점프
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wRun", "Resource/IMG/character/enemy/scoolBoy/WRun.bmp", 2250, 516, 10, 2, true, RGB(255, 0, 255));					//무기 런
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wThrow", "Resource/IMG/character/enemy/scoolBoy/WThrow.bmp", 1752, 564, 8, 2, true, RGB(255, 0, 255));				//무기 던지기
		IMAGEMANAGER->addFrameImage("SCHOOLBOY_wWalk", "Resource/IMG/character/enemy/scoolBoy/WWalk.bmp", 1572, 556, 12, 2, true, RGB(255, 0, 255));				//무기 들고 걷기



		//Resource/IMG/character/enemy/

#pragma endregion SCHOOLBOYIMAGE

	// 스쿨걸   =========================================================================================================================
#pragma region SCHOOLGIRL

	//SCHOOLGIRLIMAGE

		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_attack1", "Resource/IMG/character/enemy/schoolGirl/attack1.bmp", 2208, 354, 8, 2, true, RGB(255, 0, 255));				//어택1 있는이유가? 
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_backdown", "Resource/IMG/character/enemy/schoolGirl/backdown.bmp", 6939, 376, 27, 2, true, RGB(255, 0, 255));			//넘어졌다 일어남
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_begging", "Resource/IMG/character/enemy/schoolGirl/begging.bmp", 378, 336, 3, 2, true, RGB(255, 0, 255));				//항복
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_block", "Resource/IMG/character/enemy/schoolGirl/block.bmp", 351, 338, 3, 2, true, RGB(255, 0, 255));					//막기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_comboAttack1", "Resource/IMG/character/enemy/schoolGirl/ComboAttack1.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));	//콤보 어택1
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_comboAttack2", "Resource/IMG/character/enemy/schoolGirl/ComboAttack2.bmp", 2208, 354, 8, 2, true, RGB(255, 0, 255));	//콤보 어택2
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_comboAttack3", "Resource/IMG/character/enemy/schoolGirl/ComboAttack3.bmp", 2412, 414, 12, 2, true, RGB(255, 0, 255));	//콤보 어택3

		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_gethit", "Resource/IMG/character/enemy/schoolGirl/gethit.bmp", 1431, 360, 9, 2, true, RGB(255, 0, 255));				//피격당함
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_heldHit", "Resource/IMG/character/enemy/schoolGirl/HeldHit.bmp", 576, 336, 4, 2, true, RGB(255, 0, 255));				//잡힌후 피격당함
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_heldRelease", "Resource/IMG/character/enemy/schoolGirl/HeldRelease.bmp", 528, 360, 4, 2, true, RGB(255, 0, 255));		//잡힌거 해제
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_idle", "Resource/IMG/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255));					//기본
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_jump", "Resource/IMG/character/enemy/schoolGirl/jump.bmp", 342, 366, 3, 2, true, RGB(255, 0, 255));						//점프
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_jumpAttack", "Resource/IMG/character/enemy/schoolGirl/jumpAttack.bmp", 1197, 354, 7, 2, true, RGB(255, 0, 255));		//점프 공격
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_ladder", "Resource/IMG/character/enemy/schoolGirl/ladder.bmp", 594, 219, 6, 1, true, RGB(255, 0, 255));					//기어올라가기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_run", "Resource/IMG/character/enemy/schoolGirl/run.bmp", 1470, 330, 10, 2, true, RGB(255, 0, 255));						//달리기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_stun", "Resource/IMG/character/enemy/schoolGirl/stun.bmp", 456, 324, 4, 2, true, RGB(255, 0, 255));						//스턴
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_transition", "Resource/IMG/character/enemy/schoolGirl/transition.bmp", 387, 168, 3, 1, true, RGB(255, 0, 255));			//기어올라 온 후
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_walk", "Resource/IMG/character/enemy/schoolGirl/walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));					//걷기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wAttack", "Resource/IMG/character/enemy/schoolGirl/WAttack.bmp", 1580, 558, 5, 2, true, RGB(255, 0, 255));				//무기 어택

		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_weapon_swing", "Resource/IMG/character/enemy/schoolGirl/weapon_swing.bmp", 4369, 336, 17, 2, true, RGB(255, 0, 255));	//무기 스윙 피격당할시
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_weaponHit", "Resource/IMG/character/enemy/schoolGirl/weaponHit.bmp", 4369, 336, 17, 2, true, RGB(255, 0, 255));			//무기 피격당할시

		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wIdle", "Resource/IMG/character/enemy/schoolGirl/WIdle.bmp", 1950, 408, 10, 2, true, RGB(255, 0, 255));					//무기 기본
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wJump", "Resource/IMG/character/enemy/schoolGirl/WJump.bmp", 429, 450, 3, 2, true, RGB(255, 0, 255));					//무기 점프
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wRun", "Resource/IMG/character/enemy/schoolGirl/WRun.bmp", 1880, 458, 10, 2, true, RGB(255, 0, 255));					//무기 달리기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wThrow", "Resource/IMG/character/enemy/schoolGirl/WThrow.bmp", 1488, 540, 8, 2, true, RGB(255, 0, 255));				//무기 던지기
		IMAGEMANAGER->addFrameImage("SCHOOLGIRL_wWalk", "Resource/IMG/character/enemy/schoolGirl/WWalk.bmp", 2232, 502, 12, 2, true, RGB(255, 0, 255));					//무기 걷기

#pragma endregion SCHOOLGIRL

#pragma endregion ENEMYIMAGE

	//////////////////////////////////////////////////////////////////////////======UI======//////////////////////////////////////////////////////////////////////////////////
#pragma region UI

	//battle
	//보스 HP 뒤
		IMAGEMANAGER->addImage("BATTLE_bossHPBack", "Resource/IMG/ui/battle/boss_HP_back.bmp", 689, 120, true, RGB(255, 0, 255));

		//보스 HP 프레임
		IMAGEMANAGER->addImage("BATTLE_bossHPFrame", "Resource/IMG/ui/battle/boss_HP_frame.bmp", 898, 120, true, RGB(255, 0, 255));

		//보스 HP 앞
		IMAGEMANAGER->addImage("BATTLE_bossHPFront", "Resource/IMG/ui/battle/boss_HP_front.bmp", 689, 120, true, RGB(255, 0, 255));

		//코인
		IMAGEMANAGER->addImage("BATTLE_coin", "Resource/IMG/ui/battle/coin.bmp", 36, 36, true, RGB(255, 0, 255));

		//HP 한칸
		IMAGEMANAGER->addImage("BATTLE_HP", "Resource/IMG/ui/battle/HP_Point.bmp", 25, 23, true, RGB(255, 0, 255));

		//스테이지 화면 락 아래
		IMAGEMANAGER->addImage("BATTLE_stageChainBottom", "Resource/IMG/ui/battle/Stage_UI_Chain_Bottom.bmp", 1600, 43, true, RGB(255, 0, 255));

		//스테이지 화면 락 왼쪽
		IMAGEMANAGER->addImage("BATTLE_stageChainLeft", "Resource/IMG/ui/battle/Stage_UI_Chain_Left.bmp", 42, 900, true, RGB(255, 0, 255));

		//스테이지 화면 락 오른쪽
		IMAGEMANAGER->addImage("BATTLE_stageChainRight", "Resource/IMG/ui/battle/Stage_UI_Chain_Right.bmp", 41, 900, true, RGB(255, 0, 255));

		//스테이지 화면 락 위
		IMAGEMANAGER->addImage("BATTLE_stageChainTop", "Resource/IMG/ui/battle/Stage_UI_Chain_Top.bmp", 1600, 43, true, RGB(255, 0, 255));

		//스테이지 잠금시 자물쇠
		IMAGEMANAGER->addFrameImage("BATTLE_lockAppear", "Resource/IMG/ui/battle/Stage_UI_Lock_Appear.bmp", 650, 116, 7, 1, true, RGB(255, 0, 255));

		//스테이지 잠금시 자물쇠 깨짐
		IMAGEMANAGER->addFrameImage("BATTLE_lockDamage1", "Resource/IMG/ui/battle/Stage_UI_Lock_Damage1.bmp", 650, 116, 7, 1, true, RGB(255, 0, 255));

		//스테이지 잠금시 자물쇠 더 깨짐
		IMAGEMANAGER->addFrameImage("BATTLE_lockDamage2", "Resource/IMG/ui/battle/Stage_UI_Lock_Damage2.bmp", 650, 116, 7, 1, true, RGB(255, 0, 255));

		//스테이지 잠금시 자물쇠 진짜 깨짐
		IMAGEMANAGER->addFrameImage("BATTLE_lockDisappear", "Resource/IMG/ui/battle/Stage_UI_Lock_Disappear.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

		//하트 UI <- 게임 오버됐을 때 나오는거 같은데,.
		IMAGEMANAGER->addImage("BATTLE_Heart", "Resource/IMG/ui/battle/UI_heart.bmp", 6400, 3600, true, RGB(255, 0, 255));

		//플레이어 프로필
		IMAGEMANAGER->addImage("BATTLE_playerPortrait", "Resource/IMG/ui/battle/UI_Kyoko_Portrait.bmp", 120, 135, true, RGB(255, 0, 255));

		//플레이어 UI바
		IMAGEMANAGER->addImage("BATTLE_playerBar", "Resource/IMG/ui/battle/UI_Player_bar.bmp", 414, 94, true, RGB(255, 0, 255));

		//상점 표시-플레이어 가까울 때
		IMAGEMANAGER->addImage("BATTLE_shopDoor1", "Resource/IMG/ui/battle/UI_Shop_Door1.bmp", 52, 45, true, RGB(255, 0, 255));

		//상점 표시-플레이어 멀 때
		IMAGEMANAGER->addImage("BATTLE_shopDoor2", "Resource/IMG/ui/battle/UI_Shop_Door2.bmp", 52, 45, true, RGB(255, 0, 255));

		//문 잠김 표시
		IMAGEMANAGER->addImage("BATTLE_lockedDoor", "Resource/IMG/ui/battle/UI_Locked_Door.bmp", 52, 76, true, RGB(255, 0, 255));

		//문 열림-플레이어 가까울 때
		IMAGEMANAGER->addImage("BATTLE_unlockDoor1", "Resource/IMG/ui/battle/UI_UnLocked_Door.bmp", 52, 76, true, RGB(255, 0, 255));

		//문 열림-플레이어 멀 때
		IMAGEMANAGER->addImage("BATTLE_unlockDoor2", "Resource/IMG/ui/battle/UI_UnLocked_Door22.bmp", 52, 76, true, RGB(255, 0, 255));



		//inven
		//핸드폰
		IMAGEMANAGER->addImage("INVEN_phone", "Resource/IMG/ui/inven/phone.bmp", 480, 642, true, RGB(255, 0, 255));

		//방망이
		IMAGEMANAGER->addImage("INVEN_bat", "Resource/IMG/ui/inven/ui_bat.bmp", 80, 79, true, RGB(255, 0, 255));



		//scene
		//스타트씬 배경
		IMAGEMANAGER->addImage("SCENE_startSceneBackground", "Resource/IMG/ui/scene/StartScene_Background.bmp", 1280, 720, true, RGB(255, 0, 255));

		//스타트씬 프레임
		IMAGEMANAGER->addImage("SCENE_startSceneFrame", "Resource/IMG/ui/scene/StartScene_Frame.bmp", 1600, 900, true, RGB(255, 0, 255));

		//스타트씬 쿄코
		IMAGEMANAGER->addImage("SCENE_startSceneKyoko", "Resource/IMG/ui/scene/StartScene_Kyoko.bmp", 672, 1024, true, RGB(255, 0, 255));

		//스타트씬 미사코
		IMAGEMANAGER->addImage("SCENE_startSceneMisako", "Resource/IMG/ui/scene/StartScene_Misako.bmp", 672, 1024, true, RGB(255, 0, 255));

		//스타트씬 타이틀(제목)
		IMAGEMANAGER->addImage("SCENE_startSceneTitle", "Resource/IMG/ui/scene/StartScene_Title.bmp", 537, 308, true, RGB(255, 0, 255));

		//샵씬 배경
		IMAGEMANAGER->addImage("SCENE_shopBackground", "Resource/IMG/ui/scene/ShopScene_background.bmp", 1280, 720, true, RGB(255, 0, 255));

		//샵씬 구매 버튼
		IMAGEMANAGER->addImage("SCENE_shopBuyButton", "Resource/IMG/ui/scene/ShopScene_buyButton.bmp", 145, 92, true, RGB(255, 0, 255));

		//샵씬 아이템 선택했을때-리스트
		IMAGEMANAGER->addImage("SCENE_shopList", "Resource/IMG/ui/scene/ShopScene_list.bmp", 403, 168, true, RGB(255, 0, 255));

		//다이얼로그 뒷배경
		IMAGEMANAGER->addImage("SCENE_dialogWindow", "Resource/IMG/ui/scene/dialogWindow.bmp", 1280, 150, true, RGB(255, 0, 255));

		//게임 엔딩 장면-이건 수정해야될듯!!!!!!!!!!!!!!!!!!!!!!!!
		//IMAGEMANAGER->addImage("SCENE_endScene", "Resource/IMG/ui/scene/endScene.bmp", 1280, 720, true, RGB(255, 0, 255));

		//다이얼로그 플레이어
		IMAGEMANAGER->addImage("SCENE_kyoko1", "Resource/IMG/ui/scene/kyoko_1.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 플레이어
		IMAGEMANAGER->addImage("SCENE_kyoko2", "Resource/IMG/ui/scene/kyoko_2.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 플레이어
		IMAGEMANAGER->addImage("SCENE_kyoko3", "Resource/IMG/ui/scene/kyoko_3.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 플레이어 이름
		IMAGEMANAGER->addImage("SCENE_kyokoName", "Resource/IMG/ui/scene/kyoko_name.bmp", 200, 76, true, RGB(255, 0, 255));

		//다이얼로그 보스
		IMAGEMANAGER->addImage("SCENE_misuzu1", "Resource/IMG/ui/scene/misuzu_1.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 보스
		IMAGEMANAGER->addImage("SCENE_misuzu2", "Resource/IMG/ui/scene/misuzu_2.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 보스
		IMAGEMANAGER->addImage("SCENE_misuzu3", "Resource/IMG/ui/scene/misuzu_3.bmp", 386, 460, true, RGB(255, 0, 255));

		//다이얼로그 보스 이름
		IMAGEMANAGER->addImage("SCENE_misuzuName", "Resource/IMG/ui/scene/misuzu_name.bmp", 200, 76, true, RGB(255, 0, 255));

		//다이얼로그 스킵 표시-레드
		IMAGEMANAGER->addImage("SCENE_skipOutlines1", "Resource/IMG/ui/scene/UI_skip_outlines_FULL.bmp", 206, 78, true, RGB(255, 0, 255));

		//다이얼로그 스킵 표시-화이트
		IMAGEMANAGER->addImage("SCENE_skipOutlines2", "Resource/IMG/ui/scene/UI_skip_outlines_WHITE.bmp", 206, 78, true, RGB(255, 0, 255));

		//세이브 로드
		IMAGEMANAGER->addImage("SCENE_saveLoadClose1", "Resource/IMG/ui/scene/save_load_close.bmp", 365, 150, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("SCENE_saveLoadOpen1", "Resource/IMG/ui/scene/save_load_open.bmp", 365, 150, true, RGB(255, 0, 255));

		//세이브 로드 새파일
		IMAGEMANAGER->addImage("SCENE_saveLoadClose2", "Resource/IMG/ui/scene/save_load_close0.bmp", 365, 150, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("SCENE_saveLoadOpen2", "Resource/IMG/ui/scene/save_load_open0.bmp", 365, 150, true, RGB(255, 0, 255));

		//세이브 로드 스테이지1
		IMAGEMANAGER->addImage("SCENE_saveLoadClose3", "Resource/IMG/ui/scene/save_load_close1.bmp", 365, 150, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("SCENE_saveLoadOpen3", "Resource/IMG/ui/scene/save_load_open1.bmp", 365, 150, true, RGB(255, 0, 255));

		//캐릭터 셀렉트씬 배경 파란색
		IMAGEMANAGER->addImage("SCENE_selectSceneBackground1", "Resource/IMG/ui/scene/SelectScene_Background.bmp", 1280, 720, true, RGB(255, 0, 255));

		//캐릭터 셀렉트씬 배경 초록색
		IMAGEMANAGER->addImage("SCENE_selectSceneBackground2", "Resource/IMG/ui/scene/SelectScene_background2.bmp", 1280, 720, true, RGB(255, 0, 255));

		//셀렉트씬 캐릭터 일러스트
		IMAGEMANAGER->addImage("SCENE_selectSceneIllust", "Resource/IMG/ui/scene/SelectScene_illust.bmp", 996, 1705, true, RGB(255, 0, 255));

		//셀렉트씬 쿄코 선택했을 때
		IMAGEMANAGER->addImage("SCENE_selectSceneKyoko1", "Resource/IMG/ui/scene/SelectScene_kyoko.bmp", 375, 675, true, RGB(255, 0, 255));
		//안했을 때
		IMAGEMANAGER->addImage("SCENE_selectSceneKyoko2", "Resource/IMG/ui/scene/SelectScene_kyoko2.bmp", 375, 675, true, RGB(255, 0, 255));
		//뒷배경
		IMAGEMANAGER->addImage("SCENE_selectSceneKyokoBackground", "Resource/IMG/ui/scene/SelectScene_kyoko_background.bmp", 360, 563, true, RGB(255, 0, 255));

		//셀렉트씬 미사코 선택했을 때
		IMAGEMANAGER->addImage("SCENE_selectSceneMisako1", "Resource/IMG/ui/scene/SelectScene_misako.bmp", 375, 675, true, RGB(255, 0, 255));
		//안했을 때
		IMAGEMANAGER->addImage("SCENE_selectSceneMisako2", "Resource/IMG/ui/scene/SelectScene_misako2.bmp", 375, 675, true, RGB(255, 0, 255));
		//뒷배경
		IMAGEMANAGER->addImage("SCENE_selectMisakoBackground", "Resource/IMG/ui/scene/SelectScene_misako_background.bmp", 360, 563, true, RGB(255, 0, 255));

		//셀렉트씬 메뉴얼 버튼
		IMAGEMANAGER->addImage("SCENE_selectSceneManualButton", "Resource/IMG/ui/scene/SelectScene_manualButton.bmp", 650, 173, true, RGB(255, 0, 255));

#pragma endregion UI

		//////////////////////////////////////////////////////////////////////////======이펙트======//////////////////////////////////////////////////////////////////////////////
#pragma region EFFECTIMAGE

	//모든 피격 기본 배경
		EFFECTMANAGER->addEffect("EFFECT_attackBackground", "Resource/IMG/effect/attack.bmp", 612, 196, 204, 196, 1, 5.0f, 100);
		//기절
		EFFECTMANAGER->addEffect("EFFECT_stun", "Resource/IMG/effect/stun.bmp", 420, 54, 70, 54, 1, 5.0f, 100);

		//자판기 파괴
		EFFECTMANAGER->addEffect("EFFECT_objBreak", "Resource/IMG/effect/obj break.bmp", 3304, 248, 236, 248, 1, 5.0f, 100);
		//바닥균열 1번
		EFFECTMANAGER->addEffect("EFFECT_bossStand1", "Resource/IMG/effect/Boss stand2.bmp", 3388, 144, 484, 144, 1, 5.0f, 100);
		//바닥균열 2번
		EFFECTMANAGER->addEffect("EFFECT_groundbreak", "Resource/IMG/effect/groundbreak.bmp", 256, 128, 256, 128, 1, 5.0f, 100);
		//기둥 파괴(점프)
		EFFECTMANAGER->addEffect("EFFECT_bossEffect", "Resource/IMG/effect/boss_effect5.bmp", 800, 90, 114, 90, 1, 5.0f, 100);
		//기둥 파괴(숄더)
		EFFECTMANAGER->addEffect("EFFECT_dashAttack", "Resource/IMG/effect/dashAttackEffect.bmp", 400, 45, 57, 45, 1, 1.0f, 100);
		//화면 깨짐
		EFFECTMANAGER->addEffect("EFFECT_crush", "Resource/IMG/effect/crush.bmp", 190, 193, 190, 193, 1, 5.0f, 100);

		//플레이어 질주 frameY(2)
		EFFECTMANAGER->addEffect("EFFECT_run", "Resource/IMG/effect/run.bmp", 2544, 246, 212, 123, 1, 5.0f, 100);
		//좌측 질주
		EFFECTMANAGER->addEffect("EFFECT_runL", "Resource/IMG/effect/runL.bmp", 2784, 126, 232, 126, 1, 5.0f, 100);
		//우측 질주
		EFFECTMANAGER->addEffect("EFFECT_runR", "Resource/IMG/effect/runR.bmp", 2544, 123, 212, 123, 1, 5.0f, 100);
		//플레이어 타격
		EFFECTMANAGER->addEffect("EFFECT_blueAttack", "Resource/IMG/effect/blueAttack.bmp", 720, 80, 80, 80, 1, 5.0f, 100);
		//방망이 타격
		EFFECTMANAGER->addEffect("EFFECT_effectSpark", "Resource/IMG/effect/effect_spark.bmp", 512, 128, 128, 128, 1, 5.0f, 100);
		//플레이어 방어
		EFFECTMANAGER->addEffect("EFFECT_bossHowling", "Resource/IMG/effect/Boss howling.bmp", 1824, 165, 228, 165, 1, 5.0f, 100);
		//저스트 가드
		EFFECTMANAGER->addEffect("EFFECT_effecBlue", "Resource/IMG/effect/effec_blue.bmp", 720, 80, 80, 80, 1, 5.0f, 100);

		//플레이어 인식
		EFFECTMANAGER->addEffect("EFFECT_point", "Resource/IMG/effect/point.bmp", 560, 70, 70, 70, 1, 5.0f, 100);
		//애너미 타격1
		EFFECTMANAGER->addEffect("EFFECT_effectStar", "Resource/IMG/effect/effect_star.bmp", 900, 60, 60, 60, 1, 5.0f, 100);
		//애너미 타격2
		EFFECTMANAGER->addEffect("EFFECT_star", "Resource/IMG/effect/star.bmp", 1350, 90, 90, 90, 1, 5.0f, 100);
		//방망이 타격(중첩)
		EFFECTMANAGER->addEffect("EFFECT_spark", "Resource/IMG/effect/spark.bmp", 512, 128, 128, 128, 1, 5.0f, 100);
		//애너미 항복
		EFFECTMANAGER->addEffect("EFFECT_beg", "Resource/IMG/effect/beg.bmp", 368, 127, 184, 127, 1, 5.0f, 100);
		//동맹교섭
		EFFECTMANAGER->addEffect("EFFECT_shake", "Resource/IMG/effect/shake.bmp", 268, 127, 134, 127, 1, 5.0f, 100);

		//보스 대시시작점
		EFFECTMANAGER->addEffect("EFFECT_bossDash", "Resource/IMG/effect/Boss dash.bmp", 12480, 900, 1248, 900, 1, 1.0f, 100);
		//보스 대시시작점(중첩)
		EFFECTMANAGER->addEffect("EFFECT_explosion1", "Resource/IMG/effect/explosion1.bmp", 12480, 900, 1248, 900, 1, 5.0f, 100);
		//보스 타격
		EFFECTMANAGER->addEffect("EFFECT_explosion", "Resource/IMG/effect/explosion.bmp", 1701, 247, 243, 247, 1, 5.0f, 100);
		//보스 타격(중첩)
		EFFECTMANAGER->addEffect("EFFECT_explosion2", "Resource/IMG/effect/explosion2.bmp", 1701, 247, 243, 247, 1, 5.0f, 100);
		//보스 점프 공격
		EFFECTMANAGER->addEffect("EFFECT_bossMeteor", "Resource/IMG/effect/Boss meteor2.bmp", 2424, 320, 404, 196, 1, 1.0f, 100);
		//보스 점프 공격 frameY(2)
		EFFECTMANAGER->addEffect("EFFECT_bossMeteor1", "Resource/IMG/effect/Boss meteor.bmp", 1620, 640, 405, 320, 1, 5.0f, 100);
		//보스 숄더어택 피격
		EFFECTMANAGER->addEffect("EFFECT_bossSmash", "Resource/IMG/effect/Boss smash.bmp", 960, 89, 96, 89, 1, 1.0f, 100);
		//보스 숄더어택 피격(중첩)
		EFFECTMANAGER->addEffect("EFFECT_bossSmash1", "Resource/IMG/effect/et_boom_big.bmp", 960, 89, 96, 89, 1, 5.0f, 100);
		//보스 방어
		EFFECTMANAGER->addEffect("EFFECT_bossHowling1", "Resource/IMG/effect/Boss howling2.bmp", 416, 208, 208, 208, 1, 5.0f, 100);
		//보스가 일어설 때
		EFFECTMANAGER->addEffect("EFFECT_bossStand", "Resource/IMG/effect/Boss stand.bmp", 607, 55, 76, 55, 1, 5.0f, 100);
		//보스 라스트 페이즈
		EFFECTMANAGER->addEffect("EFFECT_bossPhase", "Resource/IMG/effect/Boss phase1.bmp", 300, 82, 100, 82, 1, 5.0f, 100);


		////모든 피격 기본 배경
		//EFFECTMANAGER->addEffect("EFFECT_attack", "Resource/IMG/effect/attack.bmp", 612, 196, 3, 1, true, RGB(255, 0, 255));

		////애너미 항복
		//EFFECTMANAGER->addEffect("EFFECT_beg", "Resource/IMG/effect/beg.bmp", 268, 127, 2, 1, true, RGB(255, 0, 255));
		////플레이어 타격
		//EFFECTMANAGER->addEffect("EFFECT_blueAttack", "Resource/IMG/effect/blueAttack.bmp", 720, 80, 9, 1, true, RGB(255, 0, 255));
		////보스 대시시작점
		//EFFECTMANAGER->addEffect("EFFECT_bossDash", "Resource/IMG/effect/Boss dash.bmp", 12480, 900, 10, 1, true, RGB(255, 0, 255));
		////플레이어 방어
		//EFFECTMANAGER->addEffect("EFFECT_bossHowling", "Resource/IMG/effect/Boss howling.bmp", 1821, 165, 8, 1, true, RGB(255, 0, 255));
		////보스 방어
		//EFFECTMANAGER->addEffect("EFFECT_bossHowling2", "Resource/IMG/effect/Boss howling2.bmp", 416, 208, 2, 1, true, RGB(255, 0, 255));
		////보스 점프 공격 frameY(2)
		//EFFECTMANAGER->addEffect("EFFECT_bossMeteor", "Resource/IMG/effect/Boss meteor.bmp", 1620, 640, 4, 2, true, RGB(255, 0, 255));
		////보스 점프 공격
		//EFFECTMANAGER->addEffect("EFFECT_bossMeteor2", "Resource/IMG/effect/Boss meteor2.bmp", 2424, 320, 6, 1, true, RGB(255, 0, 255));
		////보스 라스트 페이즈
		//EFFECTMANAGER->addEffect("EFFECT_bossPhase1", "Resource/IMG/effect/Boss phase1.bmp", 299, 82, 3, 1, true, RGB(255, 0, 255));
		////보스 숄더어택 피격
		//EFFECTMANAGER->addEffect("EFFECT_bossSmash", "Resource/IMG/effect/Boss smash.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255));
		////보스가 일어설 때
		//EFFECTMANAGER->addEffect("EFFECT_bossStand", "Resource/IMG/effect/Boss stand.bmp", 607, 55, 8, 1, true, RGB(255, 0, 255));
		////바닥균열 1번
		//EFFECTMANAGER->addEffect("EFFECT_bossStand2", "Resource/IMG/effect/Boss stand2.bmp", 3390, 144, 7, 1, true, RGB(255, 0, 255));
		////기둥 파괴(점프)
		//EFFECTMANAGER->addEffect("EFFECT_boss_effect5", "Resource/IMG/effect/boss_effect5.bmp", 800, 90, 7, 1, true, RGB(255, 0, 255));
		////화면 깨짐
		//EFFECTMANAGER->addEffect("EFFECT_crush", "Resource/IMG/effect/crush.bmp", 190, 193, 1, 1, true, RGB(255, 0, 255));
		////기둥 파괴(숄더)
		//EFFECTMANAGER->addEffect("EFFECT_dashAttackEffect", "Resource/IMG/effect/dashAttackEffect.bmp", 400, 45, 7, 1, true, RGB(255, 0, 255));
		////저스트 가드
		//EFFECTMANAGER->addEffect("EFFECT_effecBlue", "Resource/IMG/effect/effec_blue.bmp", 720, 80, 9, 1, true, RGB(255, 0, 255));
		////방망이 타격
		//EFFECTMANAGER->addEffect("EFFECT_effectSpark", "Resource/IMG/effect/effect_spark.bmp", 512, 128, 4, 1, true, RGB(255, 0, 255));
		////애너미 타격1
		//EFFECTMANAGER->addEffect("EFFECT_effectStar", "Resource/IMG/effect/effect_star.bmp", 900, 60, 15, 1, true, RGB(255, 0, 255));
		////보스 숄더어택 피격(중첩)
		//EFFECTMANAGER->addEffect("EFFECT_etBoomBig", "Resource/IMG/effect/et_boom_big.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255));
		////보스 타격
		//EFFECTMANAGER->addEffect("EFFECT_explosion", "Resource/IMG/effect/explosion.bmp", 1701, 247, 7, 1, true, RGB(255, 0, 255));
		////보스 대시시작점(중첩)
		//EFFECTMANAGER->addEffect("EFFECT_explosion1", "Resource/IMG/effect/explosion1.bmp", 12480, 900, 10, 1, true, RGB(255, 0, 255));
		////보스 타격(중첩)
		//EFFECTMANAGER->addEffect("EFFECT_explosion2", "Resource/IMG/effect/explosion2.bmp", 1701, 247, 7, 1, true, RGB(255, 0, 255));
		////바닥균열 2번
		//EFFECTMANAGER->addEffect("EFFECT_groundbreak", "Resource/IMG/effect/groundbreak.bmp", 256, 128, 1, 1, true, RGB(255, 0, 255));
		////자판기 파괴
		//EFFECTMANAGER->addEffect("EFFECT_objBreak", "Resource/IMG/effect/obj break.bmp", 3304, 248, 14, 1, true, RGB(255, 0, 255));
		////플레이어 인식
		//EFFECTMANAGER->addEffect("EFFECT_point", "Resource/IMG/effect/point.bmp", 560, 70, 8, 1, true, RGB(255, 0, 255));
		////플레이어 질주 frameY(2)
		//EFFECTMANAGER->addEffect("EFFECT_run", "Resource/IMG/effect/run.bmp", 2544, 246, 12, 2, true, RGB(255, 0, 255));
		////좌측 질주
		//EFFECTMANAGER->addEffect("EFFECT_runL", "Resource/IMG/effect/runL.bmp", 2784, 126, 12, 1, true, RGB(255, 0, 255));
		////우측 질주
		//EFFECTMANAGER->addEffect("EFFECT_runR", "Resource/IMG/effect/runR.bmp", 2544, 123, 12, 1, true, RGB(255, 0, 255));
		////동맹교섭
		//EFFECTMANAGER->addEffect("EFFECT_shake", "Resource/IMG/effect/shake.bmp", 268, 127, 2, 1, true, RGB(255, 0, 255));
		////방망이 타격(중첩)
		//EFFECTMANAGER->addEffect("EFFECT_spark", "Resource/IMG/effect/spark.bmp", 512, 128, 4, 1, true, RGB(255, 0, 255));
		////애너미 타격2
		//EFFECTMANAGER->addEffect("EFFECT_star", "Resource/IMG/effect/star.bmp", 1350, 90, 15, 1, true, RGB(255, 0, 255));
		////기절
		//EFFECTMANAGER->addEffect("EFFECT_stun", "Resource/IMG/effect/stun.bmp", 420, 54, 6, 1, true, RGB(255, 0, 255));



#pragma endregion EFFECTIMAGE

	//////////////////////////////////////////////////////////////////////////======ITEM======///////////////////////////////////////////////////////////////////////////////
#pragma region ITEM

	//알로에
		IMAGEMANAGER->addImage("ITEM_aloe", "Resource/IMG/item/aloe.bmp", 50, 76, true, RGB(255, 0, 255));
		//햄버거
		IMAGEMANAGER->addImage("ITEM_hamburger", "Resource/IMG/item/hamburger.bmp", 64, 55, true, RGB(255, 0, 255));
		//아이스크림
		IMAGEMANAGER->addImage("ITEM_icecream", "Resource/IMG/item/icecream.bmp", 55, 70, true, RGB(255, 0, 255));
		//돈까스
		IMAGEMANAGER->addImage("ITEM_meat", "Resource/IMG/item/meat.bmp", 60, 51, true, RGB(255, 0, 255));
		//새우튀김
		IMAGEMANAGER->addImage("ITEM_tempura", "Resource/IMG/item/tempura.bmp", 58, 60, true, RGB(255, 0, 255));
		//사과
		IMAGEMANAGER->addImage("ITEM_apple", "Resource/IMG/item/apple.bmp", 48, 50, true, RGB(255, 0, 255));

#pragma endregion ITEM

		//////////////////////////////////////////////////////////////////////////======OBJECT======/////////////////////////////////////////////////////////////////////////////
#pragma region OBJECT

	//오브젝트
	//사과
		IMAGEMANAGER->addImage("OBJECT_apple", "Resource/IMG/object/apple.bmp", 100, 100, true, RGB(255, 0, 255));
		//국수
		IMAGEMANAGER->addImage("OBJECT_chili", "Resource/IMG/object/chili.bmp", 100, 100, true, RGB(255, 0, 255));
		//치킨
		IMAGEMANAGER->addImage("OBJECT_hen", "Resource/IMG/object/hen.bmp", 100, 100, true, RGB(255, 0, 255));
		//책상
		IMAGEMANAGER->addImage("OBJECT_desk", "Resource/IMG/object/desk.bmp", 147, 162, true, RGB(255, 0, 255));
		//책상배열1
		IMAGEMANAGER->addImage("OBJECT_desk1", "Resource/IMG/object/desk1.bmp", 1174, 203, true, RGB(255, 0, 255));
		//책상배열2
		IMAGEMANAGER->addImage("OBJECT_desk2", "Resource/IMG/object/desk2.bmp", 936, 138, true, RGB(255, 0, 255));
		//교사 책상
		IMAGEMANAGER->addImage("OBJECT_teachers_desk", "Resource/IMG/object/teachers_desk.bmp", 83, 34, true, RGB(255, 0, 255));
		//테이블
		IMAGEMANAGER->addImage("OBJECT_table", "Resource/IMG/object/table.bmp", 339, 162, true, RGB(255, 0, 255));
		//수영장팬스
		IMAGEMANAGER->addImage("OBJECT_fence", "Resource/IMG/object/fence.bmp", 476, 71, true, RGB(255, 0, 255));
		//기둥(오른쪽)
		IMAGEMANAGER->addImage("OBJECT_RPillar", "Resource/IMG/object/stage02_pillar.bmp", 195, 864, true, RGB(255, 0, 255));
		//기둥(왼쪽)																					 
		IMAGEMANAGER->addImage("OBJECT_LPillar", "Resource/IMG/object/stage03_pillar.bmp", 195, 864, true, RGB(255, 0, 255));
		//기둥 파편1
		IMAGEMANAGER->addImage("OBJECT_particle1", "Resource/IMG/object/pillar_particle_1.bmp", 64, 64, true, RGB(255, 0, 255));
		//기둥 파편2																					 
		IMAGEMANAGER->addImage("OBJECT_particle2", "Resource/IMG/object/pillar_particle_2.bmp", 64, 64, true, RGB(255, 0, 255));
		//기둥 파편3																					
		IMAGEMANAGER->addImage("OBJECT_particle3", "Resource/IMG/object/pillar_particle_3.bmp", 64, 64, true, RGB(255, 0, 255));
		//동전
		IMAGEMANAGER->addFrameImage("OBJECT_gold", "Resource/IMG/object/gold_coin_spin.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));
		//지폐
		IMAGEMANAGER->addFrameImage("OBJECT_money", "Resource/IMG/object/money_green.bmp", 576, 432, 4, 4, true, RGB(255, 0, 255));
		//후방 기둥
		IMAGEMANAGER->addFrameImage("OBJECT_backPillar", "Resource/IMG/object/pillar.bmp", 390, 678, 2, 1, true, RGB(255, 0, 255));
		//전방 기둥
		IMAGEMANAGER->addFrameImage("OBJECT_firstPillar", "Resource/IMG/object/pillar_big.bmp", 390, 957, 2, 1, true, RGB(255, 0, 255));
		//소울
		IMAGEMANAGER->addFrameImage("OBJECT_pet", "Resource/IMG/object/pet.bmp", 576, 96, 6, 1, true, RGB(255, 0, 255));
		//방망이
		IMAGEMANAGER->addFrameImage("OBJECT_bat", "Resource/IMG/object/bat.bmp", 179, 104, 1, 2, true, RGB(255, 0, 255));
		//자판기
		IMAGEMANAGER->addFrameImage("OBJECT_vendingMachine", "Resource/IMG/object/vendingMachine.bmp", 525, 260, 2, 1, true, RGB(255, 0, 255));

#pragma endregion OBJECT

		//////////////////////////////////////////////////////////////////////////======STAGE======/////////////////////////////////////////////////////////////////////////////
#pragma region STAGE

	//보스 등장 전 스테이지
		IMAGEMANAGER->addImage("STAGE_boss1", "Resource/IMG/stage/boss1.bmp", 3116, 1215, true, RGB(255, 0, 255));
		//보스 등장 후 스테이지
		IMAGEMANAGER->addImage("STAGE_boss2", "Resource/IMG/stage/boss2.bmp", 3116, 1215, true, RGB(255, 0, 255));
		//보스 등장 전 스테이지(추가)
		IMAGEMANAGER->addImage("STAGE_bossStage1", "Resource/IMG/stage/boss_stage.bmp", 2769, 1080, true, RGB(255, 0, 255));
		//보스 등장 전 스테이지(추가)
		IMAGEMANAGER->addImage("STAGE_bossStage2", "Resource/IMG/stage/boss_stage2.bmp", 2769, 1080, true, RGB(255, 0, 255));
		//게임 시작 교실
		IMAGEMANAGER->addImage("STAGE_easy", "Resource/IMG/stage/easy.bmp", 2028, 678, true, RGB(255, 0, 255));
		//게임 시작 교실(추가)
		IMAGEMANAGER->addImage("STAGE_stage1", "Resource/IMG/stage/stage01.bmp", 2520, 840, true, RGB(255, 0, 255));
		//교내복도(위로)
		IMAGEMANAGER->addImage("STAGE_stage2", "Resource/IMG/stage/stage02.bmp", 2400, 864, true, RGB(255, 0, 255));
		//교내복도(밑으로)
		IMAGEMANAGER->addImage("STAGE_stage3", "Resource/IMG/stage/stage03.bmp", 2400, 865, true, RGB(255, 0, 255));
		//교무실
		IMAGEMANAGER->addImage("STAGE_stage4", "Resource/IMG/stage/stage04.bmp", 2112, 864, true, RGB(255, 0, 255));
		//수영장
		IMAGEMANAGER->addImage("STAGE_hard", "Resource/IMG/stage/hard.bmp", 2328, 1428, true, RGB(255, 0, 255));
		//편의점
		IMAGEMANAGER->addImage("STAGE_normal", "Resource/IMG/stage/normal.bmp", 2865, 837, true, RGB(255, 0, 255));
		//보스방 픽셀(추가본)
		IMAGEMANAGER->addImage("STAGE_bossPixel", "Resource/IMG/stage/boss_stage_pixel.bmp", 2769, 1080, true, RGB(255, 0, 255));
		//교실 픽셀(추가본)
		IMAGEMANAGER->addImage("STAGE_stagePixel1", "Resource/IMG/stage/stage01_pixel.bmp", 2520, 840, true, RGB(255, 0, 255));
		//복도1 픽셀
		IMAGEMANAGER->addImage("STAGE_stagePixel2", "Resource/IMG/stage/stage02_pixel.bmp", 2400, 864, true, RGB(255, 0, 255));
		//복도2 픽셀
		IMAGEMANAGER->addImage("STAGE_stage1Pixel3", "Resource/IMG/stage/stage03_pixel.bmp", 2400, 865, true, RGB(255, 0, 255));
		//교무실 픽셀
		IMAGEMANAGER->addImage("STAGE_stagePixel4", "Resource/IMG/stage/stage04_pixel.bmp", 2112, 864, true, RGB(255, 0, 255));
		//편의점 픽셀
		IMAGEMANAGER->addImage("STAGE_normalPixel", "Resource/IMG/stage/normal_pixel.bmp", 2865, 837, true, RGB(255, 0, 255));

		//테스트
		//IMAGEMANAGER->addImage("STAGE_stage1", "Resource/IMG/stage/stage01.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		//IMAGEMANAGER->addImage("STAGE_stagePixel1", "Resource/IMG/stage/stage01_pixel.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

#pragma endregion STAGE

#pragma endregion IMAGESOURCES
		//이렇게 안하면 눈에 보이지도 않아요
#pragma region SFXSOURCE

//플레이어 사운드
#pragma region PLAYERSFX

	//플레이어 기본 상태///////////////////////////////////////////////////////////////////////////////////////////////

	//걷는소리1
		SOUNDMANAGER->addSound("PLAYER_footStep1", "Resource/SFX/Player/player_footsteps_run_01.wav", false, false);
		//걷는소리2
		SOUNDMANAGER->addSound("PLAYER_footStep2", "Resource/SFX/Player/player_footsteps_run_02.wav", false, false);
		//걷는소리3
		SOUNDMANAGER->addSound("PLAYER_footStep3", "Resource/SFX/Player/player_footsteps_run_03.wav", false, false);

		//점프
		SOUNDMANAGER->addSound("PLAYER_jump", "Resource/SFX/Player/player_jump.wav", false, false);
		//착지
		SOUNDMANAGER->addSound("PLAYER_land", "Resource/SFX/Player/player_land.wav", false, false);

		//벽잡기
		SOUNDMANAGER->addSound("PLAYER_grabWall", "Resource/SFX/Player/player_grab_wall.wav", false, false);


		//무릎끓기
		SOUNDMANAGER->addSound("PLAYER_knee", "Resource/SFX/Player/DD2_knee.wav", false, false);


		//막기
		SOUNDMANAGER->addSound("PLAYER_block", "Resource/SFX/Player/player_block.wav", false, false);
		//맞았을떄 막기
		SOUNDMANAGER->addSound("PLAYER_getHitBlock", "Resource/SFX/Player/player_gethit_blocked.wav", false, false);
		//맞고쓰러지는소리
		SOUNDMANAGER->addSound("PLAYER_knockDown_01", "Resource/SFX/Player/gethit_knockdown_01.wav", false, false);


		//죽어서 떨어지는소리1
		SOUNDMANAGER->addSound("PLAYER_death", "Resource/SFX/Player/player_death_pitfall.wav", false, false);


		//공격//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//펀치1
		SOUNDMANAGER->addSound("PLAYER_punch1", "Resource/SFX/Player/player_punch_01.wav", false, false);
		//펀치2
		SOUNDMANAGER->addSound("PLAYER_punch2", "Resource/SFX/Player/player_punch_02.wav", false, false);
		//펀치3
		SOUNDMANAGER->addSound("PLAYER_punch3", "Resource/SFX/Player/player_punch_03.wav", false, false);

		//던지기
		SOUNDMANAGER->addSound("PLAYER_throw", "Resource/SFX/Player/player_throw.wav", false, false);

		//점프킥
		SOUNDMANAGER->addSound("PLAYER_jumpKick", "Resource/SFX/Player/player_jump_kick.wav", false, false);
		//점프펀치
		SOUNDMANAGER->addSound("PLAYER_jumpPunch", "Resource/SFX/Player/player_jump_punch.wav", false, false);
		//회전킥
		SOUNDMANAGER->addSound("PLAYER_rollKick", "Resource/SFX/Player/player_kyoko_roundhouse.wav", false, false);

		//글로발잡기
		SOUNDMANAGER->addSound("PLAYER_global_Catch", "Resource/SFX/Player/player_global_catch.wav", false, false);
		//잡기
		SOUNDMANAGER->addSound("PLAYER_grab", "Resource/SFX/Player/player_grab.wav", false, false);


		//머리 내려찍기////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//스킬시작
	//	SOUNDMANAGER->addSound("PLAYER_powerBomb_StartUp", "Resource/SFX/Player/player_misako_powerbomb_startup.wav.wav", false, false);
		//스킬떨어지는
		SOUNDMANAGER->addSound("PLAYER_powerBomb_falling", "Resource/SFX/Player/player_misako_powerbomb_falling.wav", false, false);
		//스킬착지
		SOUNDMANAGER->addSound("PLAYER_powerBomb_landing", "Resource/SFX/Player/player_misako_powerbomb_landing.wav.wav", false, false);

		//사다리////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//오르는소리1
		SOUNDMANAGER->addSound("PLAYER_climb1", "Resource/SFX/Player/player_climb_01.wav", false, false);
		//오르는소리2
		SOUNDMANAGER->addSound("PLAYER_climb2", "Resource/SFX/Player/player_climb_02.wav", false, false);

		//사다리내려와서 땅에닿았을떄
		SOUNDMANAGER->addSound("PLAYER_climb_Down_Ledge", "Resource/SFX/Player/player_climb_down_ledge.wav", false, false);
		//사다리내려와서 올라갔았을떄
		SOUNDMANAGER->addSound("PLAYER_climb_Up_Ledge", "Resource/SFX/Player/player_climb_up_ledge.wav", false, false);

		//무기/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//무거운무기들었을때
		SOUNDMANAGER->addSound("PLAYER_pickUpHeavy", "Resource/SFX/Player/player_global_pickup_weapon_heavy.wav", false, false);
		//가벼운무기들었을때
		SOUNDMANAGER->addSound("PLAYER_pickUpLight", "Resource/SFX/Player/player_global_pickup_weapon_light.wav", false, false);
		//무거운무기던졌었을때
		SOUNDMANAGER->addSound("PLAYER_throwHeavy", "Resource/SFX/Player/player_global_throw_weapon_heavy.wav", false, false);
		//가벼운무기던졌을때
		SOUNDMANAGER->addSound("PLAYER_throwLight", "Resource/SFX/Player/player_global_throw_weapon_light.wav", false, false);

		//상태 이상////////////////////////////////////////////////////////////////////////////////////////////////////////
		//스턴
		SOUNDMANAGER->addSound("PLAYER_dizzy", "Resource/SFX/Player/player_global_dizzy.wav", false, false);
		//해제
		SOUNDMANAGER->addSound("PLAYER_parry", "Resource/SFX/Player/player_global_parry.wav", false, false);
		//목소리///////////////////////////////////////////////////////////////////////////////////////////////////////////
		SOUNDMANAGER->addSound("PLAYER_combo1", "Resource/SFX/Player/Kyoko/vo_kyoko_effort_16.wav", false, false);
		SOUNDMANAGER->addSound("PLAYER_combo2", "Resource/SFX/Player/Kyoko/vo_kyoko_effort_18.wav", false, false);
		SOUNDMANAGER->addSound("PLAYER_combo3", "Resource/SFX/Player/Kyoko/vo_kyoko_effort_22.wav", false, false);
#pragma endregion PLAYERSFX




#pragma region MENUSFX
		//	SOUNDMANAGER->addSound("MENU_busUse", "Resource/SFX/menu/interface_bus_use.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_gameover", "Resource/SFX/menu/interface_game_over.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_mapMarker", "Resource/SFX/menu/interface_map_marker.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_wediditJingle", "Resource/SFX/menu/interface_wedidit_jingle.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_jingleMap1", "Resource/SFX/menu/jingle_map_01.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_jingleTutorial3", "Resource/SFX/menu/jingle_tutorial_03.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_levelUp", "Resource/SFX/menu/level_up_sequence.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_accessoryEquip", "Resource/SFX/menu/menu_accesory_equip.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_accessoryUnequip", "Resource/SFX/menu/menu_accesory_unequip.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_back", "Resource/SFX/menu/menu_back.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_cannot", "Resource/SFX/menu/menu_cannot.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_confirm", "Resource/SFX/menu/menu_confirm.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_cursor", "Resource/SFX/menu/menu_cursor.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_emptyAccessory", "Resource/SFX/menu/menu_empty_accessory.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_interact", "Resource/SFX/menu/menu_interact.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneBack", "Resource/SFX/menu/menu_phone_back2.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneCursor1", "Resource/SFX/menu/menu_phone_cursor_01.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneCursor2", "Resource/SFX/menu/menu_phone_cursor_02.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneCursor3", "Resource/SFX/menu/menu_phone_cursor_03.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phonePause", "Resource/SFX/menu/menu_phone_pause.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneRotate", "Resource/SFX/menu/menu_phone_rotate.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneSelect", "Resource/SFX/menu/menu_phone_select3.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneSliderTick", "Resource/SFX/menu/menu_phone_slider_tick.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_phoneUnpause", "Resource/SFX/menu/menu_phone_unpause.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_playerSelectFirst", "Resource/SFX/menu/menu_player_select_first.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_playerSelectLast", "Resource/SFX/menu/menu_player_select_last.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_notification", "Resource/SFX/menu/notification.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_uiChainsAppear", "Resource/SFX/menu/UI_chains_appear.wav", true, false);
		//	SOUNDMANAGER->addSound("MENU_uiChainsBreak", "Resource/SFX/menu/UI_chains_break.wav", true, false);
#pragma endregion MENUSFX

#pragma region GLOBAL & PICKUP

	//보스 클리어
		SOUNDMANAGER->addSound("GLOBAL_bossFinal", "Resource/SFX/global/boss_finalhit.wav", true, true);
		//보스 시작
		SOUNDMANAGER->addSound("GLOBAL_bossIntro", "Resource/SFX/global/boss_intro_placard", true, true);


		//습득 불가
		SOUNDMANAGER->addSound("PICKUP_cannot", "Resource/SFX/pickup/cannot_pickup.wav", true, true);
		//도전 고제 아이템 발견
		SOUNDMANAGER->addSound("PICKUP_confirm", "Resource/SFX/pickup/interface_item_pickup_confirm.wav", true, true);
		//도전 과제 아이템 획득
		SOUNDMANAGER->addSound("PICKUP_intro", "Resource/SFX/pickup/interface_item_pickup_intro.wav", true, true);
		//아이템 인트로 끝
		SOUNDMANAGER->addSound("PICKUP_outro", "Resource/SFX/pickup/interface_item_pickup_outro.wav", true, true);
		//청구서 습득
		SOUNDMANAGER->addSound("PICKUP_bill", "Resource/SFX/pickup/pickup_bill.wav", true, true);
		//다마고치 펫1
		SOUNDMANAGER->addSound("PICKUP_cat1", "Resource/SFX/pickup/pickup_cat_01.wav", true, true);
		//다마고치 펫2
		SOUNDMANAGER->addSound("PICKUP_cat2", "Resource/SFX/pickup/pickup_cat_02.wav", true, true);
		//다마고치 펫3
		SOUNDMANAGER->addSound("PICKUP_cat3", "Resource/SFX/pickup/pickup_cat_03.wav", true, true);
		//머니 습득
		SOUNDMANAGER->addSound("PICKUP_coin", "Resource/SFX/pickup/pickup_coin.wav", true, true);
		//음식 습득
		SOUNDMANAGER->addSound("PICKUP_food", "Resource/SFX/pickup/pickup_food.wav", true, true);
		//약 습득
		SOUNDMANAGER->addSound("PICKUP_med", "Resource/SFX/pickup/pickup_med_01.wav", true, true);

#pragma endregion GLOBAL & PICKUP

#pragma region ENVIRONMENT

		//벤치 부셔
		SOUNDMANAGER->addSound("ENVIRONMENT_benchBreak", "Resource/SFX/environment/environment_bench_break.wav", true, false);

		//화학실 책상 부셔
		SOUNDMANAGER->addSound("ENVIRONMENT_chemistryTableBreak", "Resource/SFX/environment/environment_chemistry_table_break.wav", true, false);

		//나무 부셔
		SOUNDMANAGER->addSound("ENVIRONMENT_woodSmash", "Resource/SFX/environment/environment_wood_smash.wav", true, false);
		SOUNDMANAGER->addSound("ENVIRONMENT_woodCrunch", "Resource/SFX/environment/environment_wood_crunch.wav", true, false);

		//돌 부셔
		SOUNDMANAGER->addSound("ENVIRONMENT_rockSmash", "Resource/SFX/environment/environment_rock_smash.wav", true, false);
		SOUNDMANAGER->addSound("ENVIRONMENT_rockCrunch", "Resource/SFX/environment/environment_rock_crunch.wav", true, false);

		//자판기 부셔
		SOUNDMANAGER->addSound("ENVIRONMENT_vendingmachinePunched", "Resource/SFX/environment/environment_vending_machine_punched.wav", true, false);
		SOUNDMANAGER->addSound("ENVIRONMENT_vendingmachineBreak", "Resource/SFX/environment/environment_vending_machine_break.wav", true, false);

		//쓰레기통 닫힘
		SOUNDMANAGER->addSound("ENVIRONMENT_dumpsterClose", "Resource/SFX/environment/environment_dumpster_close.wav", true, false);

		//쓰레기통 열림
		SOUNDMANAGER->addSound("ENVIRONMENT_dumpsterOpen", "Resource/SFX/environment/environment_dumpster_open.wav", true, false);

		//전기 바닥
		SOUNDMANAGER->addSound("ENVIRONMENT_electricfloorOn", "Resource/SFX/environment/environment_electricfloor_on.wav", true, false);

		//폭발물 카운트 다운
		SOUNDMANAGER->addSound("ENVIRONMENT_explosivesCountdownBeep", "Resource/SFX/environment/environment_explosives_countdown_beep.wav", true, false);

		//폭발물 카운트 다운 루프..? - 안쓸거같음
		SOUNDMANAGER->addSound("ENVIRONMENT_explosivesCountdownBeepLoop", "Resource/SFX/environment/environment_explosives_idle_beep_loop.wav", true, true);

		//폭발물 폭발
		SOUNDMANAGER->addSound("ENVIRONMENT_explosivesExplode", "Resource/SFX/environment/environment_explosives_explode.wav", true, false);
		SOUNDMANAGER->addSound("ENVIRONMENT_explosivesExplodePlant", "Resource/SFX/environment/environment_explosives_plant.wav", true, false);

		//폭발물 폭발 후 이명
		SOUNDMANAGER->addSound("ENVIRONMENT_explosivesRinging", "Resource/SFX/environment/environment_explosives_ringing.wav", true, false);

		//장난감 눌림
		SOUNDMANAGER->addSound("ENVIRONMENT_toysSqueek", "Resource/SFX/environment/environment_pattinson_toys_squeek.wav", true, false);

		//카메라 프로젝터 루프
		SOUNDMANAGER->addSound("ENVIRONMENT_projectorLoop", "Resource/SFX/environment/environment_projector_loop.wav", true, false);

#pragma endregion ENVIRONMENT




















		//무기 타격음

		SOUNDMANAGER->addSound("WEAPONS_bassball1_bat", "Resource/SFX/weapons/weapon_baseball_bat_hit.wav", true, false);			//야구방망이  둥
		SOUNDMANAGER->addSound("WEAPONS_bassball2_bat", "Resource/SFX/weapons/weapon_baseball_impact.wav", true, false);			//야구방망이2 탁 

		SOUNDMANAGER->addSound("WEAPONS_bench1", "Resource/SFX/weapons/weapon_bench_break.wav", true, false);				//벤치 부셔지는소리
		SOUNDMANAGER->addSound("WEAPONS_bench2", "Resource/SFX/weapons/weapon_bench_impact.wav", true, false);				//벤치 임팩트

		SOUNDMANAGER->addSound("WEAPONS_bicycle", "Resource/SFX/weapons/weapon_bicycle_impact.wav", true, false);				//자전거
		SOUNDMANAGER->addSound("WEAPONS_boomerang", "Resource/SFX/weapons/weapon_boomerang_throw.wav", true, false);			//부메랑
		SOUNDMANAGER->addSound("WEAPONS_chain", "Resource/SFX/weapons/weapon_chain_swing.wav", true, false);				//체인
		SOUNDMANAGER->addSound("WEAPONS_dodgeball", "Resource/SFX/weapons/weapon_dodgeball_impact.wav", true, false);			//피구공
		SOUNDMANAGER->addSound("WEAPONS_fish1", "Resource/SFX/weapons/weapon_fish_explode.wav", true, false);				//물고기1
		SOUNDMANAGER->addSound("WEAPONS_fish2", "Resource/SFX/weapons/weapon_fish_impact.wav", true, false);				//물고기2
		SOUNDMANAGER->addSound("WEAPONS_frying_pan", "Resource/SFX/weapons/weapon_frying_pan_impact2.wav", true, false);			//프라이펜

		SOUNDMANAGER->addSound("WEAPONS_guitar1", "Resource/SFX/weapons/weapon_guitar_impact_01.wav", true, false);			//기타1
		SOUNDMANAGER->addSound("WEAPONS_guitar2", "Resource/SFX/weapons/weapon_guitar_impact_02.wav", true, false);			//기타2
		SOUNDMANAGER->addSound("WEAPONS_guitar3", "Resource/SFX/weapons/weapon_guitar_impact_03.wav", true, false);			//기타3
		SOUNDMANAGER->addSound("WEAPONS_guitar4", "Resource/SFX/weapons/weapon_guitar_impact_04.wav", true, false);			//기타4

		SOUNDMANAGER->addSound("WEAPONS_lightSaber1", "Resource/SFX/weapons/weapon_light_saber_impact_01.wav", true, false);		//라이트세이버1
		SOUNDMANAGER->addSound("WEAPONS_lightSaber2", "Resource/SFX/weapons/weapon_light_saber_impact_02.wav", true, false);		//라이트세이버2
		SOUNDMANAGER->addSound("WEAPONS_lightSaber3", "Resource/SFX/weapons/weapon_light_saber_impact_03.wav", true, false);		//라이트세이버3

		SOUNDMANAGER->addSound("WEAPONS_lightSaverSwing1", "Resource/SFX/weapons/weapon_light_saber_swing_01.wav", true, false);		//라이트세이버스윙1
		SOUNDMANAGER->addSound("WEAPONS_lightSaverSwing2", "Resource/SFX/weapons/weapon_light_saber_swing_02.wav", true, false);		//라이트세이버스윙2
		SOUNDMANAGER->addSound("WEAPONS_lightSaverSwing3", "Resource/SFX/weapons/weapon_light_saber_swing_03.wav", true, false);		//라이트세이버스윙3
		SOUNDMANAGER->addSound("WEAPONS_lightSaverSwing4", "Resource/SFX/weapons/weapon_light_saber_swing_04.wav", true, false);		//라이트세이버스윙4

		SOUNDMANAGER->addSound("WEAPONS_chair", "Resource/SFX/weapons/weapon_metal_chair_impact.wav", true, false);			//금속의자
		SOUNDMANAGER->addSound("WEAPONS_shovel", "Resource/SFX/weapons/weapon_shovel_impact.wav", true, false);				//삽
		SOUNDMANAGER->addSound("WEAPONS_starBaton", "Resource/SFX/weapons/weapon_star_baton_impact.wav", true, false);			//별지팡이
		SOUNDMANAGER->addSound("WEAPONS_woodPlank", "Resource/SFX/weapons/weapon_wood_plank_impact.wav", true, false);			//나무판자
		SOUNDMANAGER->addSound("WEAPONS_wrench", "Resource/SFX/weapons/weapon_wrench_impact.wav", true, false);				//렌치
#pragma endregion SFXSOURCE
	
		loadingHelper->_currentCount++;
	}
	return 0;
}
