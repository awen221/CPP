#include "random.h"
#include "stdlib.h"

namespace MATH
{
	//RANDOM
	Random::Random(unsigned int i)
	{
		srand(i);
		//��ĳ�]�m�ɶ����üƺؤl
		//�`�N�Asrand ���`�Ө��@���{���X(�M��)�u�����@���A
		//�p�G����b for loop �̡A�C���i�� rand �e�N�� srand�A
		//�|�o�{�C�����X�Ӫ��üƬO�P�@�ӼƦr�C
	}
	Random::~Random()
	{
	}
	int Random::GetRand()
	{
		int res = rand();
		return res;
	}
}