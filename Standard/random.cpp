#include "random.h"
#include <windows.h>

//RANDOM
RANDOM::RANDOM()
{
	//�]�m�ɶ����üƺؤl
	srand(GetTickCount());
	//�`�N�Asrand ���`�Ө��@���{���X(�M��)�u�����@���A
	//�p�G����b for loop �̡A�C���i�� rand �e�N�� srand�A
	//�|�o�{�C�����X�Ӫ��üƬO�P�@�ӼƦr�C
}
RANDOM::~RANDOM()
{
}
int RANDOM::GetRand()
{
	int res = rand();
	return res;
}