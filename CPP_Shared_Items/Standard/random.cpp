#include "random.h"
#include "stdlib.h"

namespace RANDOM
{
	//RANDOM
	RANDOM_Class::RANDOM_Class(unsigned int i)
	{
		srand(i);
		//��ĳ�]�m�ɶ����üƺؤl
		//�`�N�Asrand ���`�Ө��@���{���X(�M��)�u�����@���A
		//�p�G����b for loop �̡A�C���i�� rand �e�N�� srand�A
		//�|�o�{�C�����X�Ӫ��üƬO�P�@�ӼƦr�C
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