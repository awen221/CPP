#ifndef RADIAN_H
#define RADIAN_H

#include "Point_Template.h"

namespace MATH
{
	class Radian
	{
	protected:
		//PI*0 ~ PI*2
		double radian;
	public:
		Radian();
		~Radian();

		double GetRadian();

		void SetRadian(const double&);
		void SetDirectionUp();
		void SetDirectionDown();
		void SetDirectionLeft();
		void SetDirectionRight();

		void ShfitRadian(const double&);
		

		////�����੷��
		//static double ConvertingDegreeFrom(const double&);
		////�����ਤ��
		//static double ConvertingRadianFrom(const double&);

		//double GetDegree();
		//void SetDegree(const double&);
		//void ShfitDegree(const double&);
	};
}
#endif