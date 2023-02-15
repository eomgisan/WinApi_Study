#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object Ãß°¡
	CObject* pObj = new CPlayer;
	
	pObj->SetPos(Vec2(640.f,380.f));
	pObj->SetScale(Vec2(100.f,100.f));
	
	AddObj(pObj, GROUP_TYPE::PLAYER);




}

void CScene_Start::Exit()
{

}

