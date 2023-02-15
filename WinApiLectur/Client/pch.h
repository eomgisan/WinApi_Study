#pragma once

// 미리 컴파일된 헤더 -> 프로젝트 속성에서 설정가능함 모든 파일은 이 헤더를 미리 컴파일 해야함
// 사용이유 : 컴파일 시스템 올리기위함
// 이미 완성된 구문이면 컴파일 필요 없어
// 그러므로 일단 모두 여기에 올려서 필요한거를 여기에 추가시키는거야

#include <Windows.h>
#include <iostream>

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

#include "define.h"
#include "struct.h"