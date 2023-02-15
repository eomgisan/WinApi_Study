#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr() :
	m_arrScene{},
	m_pCurScene(nullptr){
}

CSceneMgr::~CSceneMgr(){
	// Scene ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i) {
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];
	}
}


void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start_Scene");
	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_1] = new CScene_Stage_1;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_2] = new CScene_Stage_2;


	// ���� Scene ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

	// �� ���� ������Ʈ �߰��۾�
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
}

void CSceneMgr::render(HDC _hDc)
{
	m_pCurScene->render(_hDc);
}