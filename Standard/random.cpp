#include "random.h"
#include <windows.h>

namespace RANDOM
{
	//RANDOM
	RANDOM_Class::RANDOM_Class()
	{
		//設置時間為亂數種子
		srand(GetTickCount());
		//注意，srand 正常而言一份程式碼(專案)只能執行一次，
		//如果它放在 for loop 裡，每次進行 rand 前就用 srand，
		//會發現每次取出來的亂數是同一個數字。
	}
	RANDOM_Class::~RANDOM_Class()
	{
	}
	int RANDOM_Class::GetRand()
	{
		int res = rand();
		return res;
	}
}