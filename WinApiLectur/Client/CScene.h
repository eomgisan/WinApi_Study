#pragma once

class CObject;
// 전방선언 : 최대한 컴파일 속도에 영향 안주려고
// 물론 헤더 include 하면 되지만 매번 변경때마다 확인해야하니 걍 이렇게 함
// 헤더가 헤더끼리 참조 안하게 하는게 좋음
// 물론 이렇게 하면 포인터타입으로만 접근가능함 ( 나중에 링크하면서 넘어가는거라 정확한 구조를 모르므로 포인터로만 가능 )



class CScene
{
private:
	// 오브젝트를 관리할건데 그룹별로 관리해보자 그룹은 define에서 정의

	// 포인터로 관리하는 이유 : 모든 오브젝트를 CObject의 포인터로 가르킬수 있으므로
	// CObject를 상속하며 오브젝트 객체를 만들거라
	
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName;						 // Scene 이름


protected:
	// 이와같이 헤더에 함수 선언하면 인라인 처리 되어서 함수 호출 비용 발생 X
	void AddObj(CObject* _pObj, GROUP_TYPE _eType)	{ m_arrObj[(UINT)_eType].push_back(_pObj); }

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }




	// 순수 가상함수 : 만약 클래스에 순수가상함수가 있다면 객체 생성 이 불가능
	// 즉 이것의 용도는 상속받으면서 이런 함수를 만들어야한다는거를 알려주고 이런게 있을거다!
	// 마지막에 = 0 을 붙이면 순수 가상함수 선언이 됨
	virtual void Enter() = 0; // 해당 Scene을 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene을 탈출 시 호출

	// 이는 모든 씬 공통 함수니깐 가상함수가 아님
	void update();
	void render(HDC _hdc);

public:
	CScene();

	// 아주중요!!!!!!!!!!!!!
	// 씬들을 모두 상속으로 하면서 관리할텐데 그러기 위해서는 소멸자를 가상함수로 설정해야함.
	// 씬들을 CScene* 로 관리하기 때문에 가상함수가 아니라면 부모의 소멸자가 호출되게됨 그러므로
	// 자식의 소멸자를 가상함수라고 선언해줘야함
	virtual ~CScene();

};

