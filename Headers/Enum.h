#ifndef Enum_h__
#define Enum_h__

enum eObjType
{
	OBJ_BACKGROUND,			//배경 오브젝트
	OBJ_MAP,				//Map
	OBJ_PLAYER,				//Player
	OBJ_MONSTER,			//Monster
	OBJ_ITEM,				//Item
	OBJ_PROP,				//Stage Object(물건, 장애물) 
	OBJ_UI,
	OBJ_END					
};

enum eDirection
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_END
};

enum eSceneType
{
	SCENE_LOGO,					//게임 시작 화면
	SCENE_SGININ,				//게임 회원가입 화면
	SCENE_LOGIN,				//게임 로그인 화면
	SCENE_PLAYERSELECT,			//게임 캐릭터 선택 화면
	SCENE_STAGE1,				//마을
	SCENE_STAGE2,				//사냥터 1
	SCENE_STAGE3,				//사냥터 2
	SCENE_BOSS,					//보스
	SCENE_EDIT,					//Map Tool 화면
	SCENE_END				
};

enum ePlayerState
{
	STATE_STAND = 0,
	STATE_WALK,
	STATE_ATT,
	STATE_SKILL,
	STATE_HIT,
	STATE_DEAD,
	STATE_END
};

//Render 순서를 위한 열거체.
enum eRenderType
{
	RENDER_BACKGROUND = 0,
	RENDER_MAP,
	RENDER_WORLDOBJ,
	RENDER_EFFECT,
	RENDER_UI,
	RENDER_END
};

//User Interface
enum eUiType
{
	UI_INVEN,
	UI_EQUIP,
	UI_SKILL,
	UI_STORE,
	UI_STAT,
	UI_STATUS,
	UI_END
};

#endif // !Enum_h__
