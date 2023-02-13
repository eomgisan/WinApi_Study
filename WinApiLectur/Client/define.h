#pragma once

// 매크로 함수
// 주의점 : 연산 우선순위 꼭 생각해야함 왜냐면 이것은 코드를 바꿔주는거지 값을 반환하는것이 아니다.


// Singleton 매크로
#define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}\
					 private: type(); ~type();

// 아래와 같다. 즉 엔터를 치고 싶으면 마지막에 역슬레시 \ 를 추가해줘야함
/*
#define SINGLE(tpye) static type* GetInst()\
 {\
	static type mgr; \
	return &mgr;\
 }
 */

// Delta Time 매크로
#define fDT CTimeMgr::GetInst()->GetfDt()


enum class GROUP_TYPE {
	DEFAULT,

	PLAYER,

	MISSILE,

	MONSTER,


	END = 32,
};