#include "stdafx.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();

	for (iter; iter != m_mapSound.end(); ++iter)
	{
		m_Result = FMOD_Sound_Release(iter->second);
		delete[](iter->second);
	}
	m_mapSound.clear();

	m_Result = FMOD_System_Close(m_pSystem);
	m_Result = FMOD_System_Release(m_pSystem);
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
}

void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t		fd;
	long			handle;
	int				iResult = 1;

	handle = _findfirst("..\\Resource\\Sound\\*.*", &fd);	//폴더내 모든 파일을 찾는다.

	if (handle == -1)
		return;
	
	while (iResult != -1)
	{
		TCHAR szName[256];
		ZeroMemory(szName, sizeof(szName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fd.name, strlen(fd.name), szName, 256);

		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);

		char szFullName[256];
		strcpy_s(szFullName, "..\\Resource\\Sound\\");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND*	pSound;
		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName, FMOD_HARDWARE, 0, &pSound);

		if (m_Result == FMOD_OK)
			m_mapSound.insert(map<TCHAR*, FMOD_SOUND*>::value_type(pName, pSound));
		else
			delete[] pName;

		iResult = _findnext(handle, &fd);
	}
	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);
}

void CSoundMgr::Update_Sound(void)
{
	m_Result = FMOD_System_Update(m_pSystem);
}

//Play Sound
//--------------------------------------------------------------------------------------------------------
void CSoundMgr::Play_Bgm(TCHAR * szSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(szSoundKey));

	if (iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pBgmCh);
}

void CSoundMgr::Play_EffectSound(TCHAR * szSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(szSoundKey));

	if (iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pEffectCh);
}

void CSoundMgr::Play_SkillSound(TCHAR * szSoundkey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(szSoundkey));

	if (iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pSkillCh);
}

void CSoundMgr::Play_MonsterSound(TCHAR * szSoundkey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCompare(szSoundkey));

	if (iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);
	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE, iter->second, 0, &m_pMonsetr);
}
//--------------------------------------------------------------------------------------------------------

//Stop Sound
//--------------------------------------------------------------------------------------------------------
void CSoundMgr::Stop_Bgm(void)
{
	m_Result = FMOD_Channel_Stop(m_pBgmCh);
}

void CSoundMgr::Stop_SoundAll(void)
{
	m_Result = FMOD_Channel_Stop(m_pBgmCh);
	m_Result = FMOD_Channel_Stop(m_pMonsetr);
	m_Result = FMOD_Channel_Stop(m_pSkillCh);
	m_Result = FMOD_Channel_Stop(m_pEffectCh);
}
//--------------------------------------------------------------------------------------------------------