#pragma once
// 전방선언 : 최대한 컴파일 속도에 영향 안주려고
// 물론 헤더 include 하면 되지만 매번 변경때마다 확인해야하니 걍 이렇게 함
// 헤더가 헤더끼리 참조 안하게 하는게 좋음
// 물론 이렇게 하면 포인터타입으로만 접근가능함

class CObject;

class CScene
{
private:
	vector<CObject*> vecObj;

public:
	CScene();
	~CScene();

};

