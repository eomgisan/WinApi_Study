#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

private:
	
	CScene*			m_arrScene[(UINT)SCENE_TYPE::END];
	CScene*			m_pCurScene;

public:
	void update();
	void render(HDC _hDc);
	void init();
};



