#ifndef Enum_h__
#define Enum_h__

enum eObjType
{
	OBJ_BACKGROUND,			//��� ������Ʈ
	OBJ_MAP,				//Map
	OBJ_PLAYER,				//Player
	OBJ_MONSTER,			//Monster
	OBJ_NPC,				//Npc
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
	SCENE_EDIT_LINE,			//Line Tool ȭ��
	SCENE_END				
};

enum ePlayerState
{
	STATE_STAND = 0,
	STATE_WALK,
	STATE_ATT,
	STATE_SKILL,
	STATE_HIT,
	STATE_UP,
	STATE_JUMP,
	STATE_DOWN,
	STATE_DEAD,
	STATE_END
};

//Monsetr State
enum eMonsterState
{
	MSTATE_STAND = 0,
	MSTATE_WALK,
	MSTATE_ATTACK,
	MSTATE_HIT,
	MSTATE_DEAD,
	MSTATE_END
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
	UI_QUICKSLOT,
	UI_END
};

//Equip Type
enum eEquipType
{
	EQUIP_RING,
	EQUIP_HELMET,
	EQUIP_ARMOR,
	EQUIP_PANTS,
	EQUIP_GLOVES,
	EQUIP_SHOES,
	EQUIP_WEAPON,
	EQUIP_END
};

//Item 
enum eItemType
{
	ITEM_WEAPON,
	ITEM_SUBWEAPON,
	ITEM_ARMOR,
	ITEM_TOP,
	ITEM_PANTS,
	ITEM_HELMET,
	ITEM_GLOVES,
	ITEM_NECKLACE,
	ITEM_RING,
	ITEM_SHOES,
	ITEM_BELT,
	ITEM_HP_POTION,
	ITEM_MP_POTION,
	ITEM_MESSO,
	ITEM_EXP,
	ITEM_END
};

//Npc
enum eNpcType
{
	NPC_STORE,
	NPC_QUEST,
	NPC_END
};

//BackGround
enum eBGType
{
	BG_BACK,
	BG_MAP,
	BG_END
};

//Skill CutDonw Key
enum eCutDown_Key
{
	CK_1,
	CK_2,
	CK_3,
	CK_4,
	CK_A,
	CK_D,		
	CK_F,
	CK_G,
	CK_END
};

#endif // !Enum_h__
