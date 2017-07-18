#pragma once

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)
public:
	~CSoundMgr(void);

private:
	FMOD_SYSTEM*				m_pSystem;		//FMod System Pointer
	FMOD_CHANNEL*				m_pEffectCh;	//Effect Sound Channel
	FMOD_CHANNEL*				m_pBgmCh;		//Main BGM Channel
	FMOD_CHANNEL*				m_pSkillCh;		//Skill Suond Channel
	FMOD_CHANNEL*				m_pMonsetr;		//Monster Sound Channel
	FMOD_RESULT					m_Result;		//FMOD Running Result

private:
	unsigned int				m_iVersion;
	map<TCHAR*, FMOD_SOUND*>	m_mapSound;

public:
	map<TCHAR*, FMOD_SOUND*>*	GetSoundMap(void) { return &m_mapSound; }

public: 
	void						Initialize(void);
	void						LoadSoundFile(void);
	void						Update_Sound(void);

public: //Play Sound
	void						Play_Bgm(TCHAR* szSoundKey);
	void						Play_EffectSound(TCHAR* szSoundKey);
	void						Play_SkillSound(TCHAR* szSoundkey);
	void						Play_MonsterSound(TCHAR* szSoundkey);	

public: //Stop Sound
	void						Stop_Bgm(void);
	void						Stop_SoundAll(void);

};