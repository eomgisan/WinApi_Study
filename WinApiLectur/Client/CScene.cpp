#include "pch.h"
#include "CScene.h"

#include "CObject.h"

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size();++j) {
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size();++j) {
			m_arrObj[i][j]->render(_hdc);
		}
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			delete m_arrObj[i][j];
		}
	}
}
