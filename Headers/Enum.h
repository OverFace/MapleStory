#ifndef Enum_h__
#define Enum_h__

enum eObjType
{
	OBJ_BACKGROUND,			//��� ������Ʈ
	OBJ_MAP,				//Map
	OBJ_PLAYER,				//Player
	OBJ_MONSTER,			//Monster
	OBJ_ITEM,				//Item
	OBJ_PROP,				//Stage Object(����, ��ֹ�) 
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
	SCENE_LOGO,					//���� ���� ȭ��
	SCENE_SGININ,				//���� ȸ������ ȭ��
	SCENE_LOGIN,				//���� �α��� ȭ��
	SCENE_PLAYERSELECT,			//���� ĳ���� ���� ȭ��
	SCENE_STAGE1,				//����
	SCENE_STAGE2,				//����� 1
	SCENE_STAGE3,				//����� 2
	SCENE_BOSS,					//����
	SCENE_EDIT,					//Map Tool ȭ��
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

//Render ������ ���� ����ü.
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
