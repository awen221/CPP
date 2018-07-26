#ifndef _ARRAY_TEMPLATE_H_
#define _ARRAY_TEMPLATE_H_

class ArrayTemplate
{
public:
	template<class T>
	static T* AddObj(int& totalCount, int maxCount, T* pArray)
	{
		T* pObj = NULL;
		if (totalCount < maxCount)
		{
			pObj = &(pArray[totalCount]);
			totalCount++;
		}
		return pObj;
	}

	template<class T>
	static void RemoveObj(int index,int& totalCount,T* pArray)
	{
		totalCount--;
		for (int i = index; i < totalCount; i++)
			pArray[i] = pArray[i + 1];
	}
};


#endif
