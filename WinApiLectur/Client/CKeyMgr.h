#pragma once



// getasynckeystate를 통해 키 입력을 받을수도 있지만

// 기능적으로 지원되는게 많이 없고, 여기서 키들에 상태값을 부여하고 키매니저를 통해 윈도우 포커싱 없을때
// 키입력 무시하는 기능도 추가해보자

// GetAsyncKeyState 함수를 통하면 if구문을 들어가서 확인해야 알수있어
// 만약 1프레임 진행과정에서 키 입력 상태가 바뀌었는데 getasynckeystate는 이를 키입력 상태 바뀐거를 알려줘
// 그러므로 1프레임 안에서 키입력 상태가 바뀔수 있다는것이야.
// 이는 프레임 동기화가 이루어지지 않았다고 말해

// keymanager이 해줄것을 프레임 동기화 작업이야
// 한 프레임에서 발생된 키입력은 동일한 상태를 해야한다는것이야  즉 1프레임당 키 입력을 fix 시켜둬야해


// 해야할일
// 1. 프레임 동기화
// 2. 키입력 이벤트 처리 : tap, hold, away
// 3. 포커스 처리
// -> 만약 갑자기 윈도우의 포커스가 풀리면 tap에서 바로 none으로 가면 away시에 발새해야하는 구문이 동작안하니깐.
// -> 모든 키는 tap -> away -> none // hold -> away -> none 으로 진행해야한다.


enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,
	ALT,
	CTRL,
	LSHIFT,

	ENTER,
	SPACE,
	ESC,
	

	LAST,			// 끝
};


enum class KEY_STATE {
	TAP,			// 막 누른 시점
	HOLD,			// 누르고 있는 상태
	AWAY,			// 막 땐 상태
	NONE,			// 눌리지 않고, 이전에도 눌리지 않은 상태
};

struct tKeyInfo {
	KEY_STATE	eState;			// 해당 키의 상태
	bool		bPrevPush;			// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();

	// 매 프레임마다 키 상태 업데이트
	void update();

	KEY_STATE GetKeyState(KEY _key);


};

