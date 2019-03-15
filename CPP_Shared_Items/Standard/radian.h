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

		virtual void Init();
		virtual void Work();
		//�����੷��
		static double GetDegreeFromRadian(const double&);
		//�����ਤ��
		static double GetRadianFromDegree(const double&);

		double GetDegree();

		double GetRadian();
		void SetRadian(const double&);
		void ShfitRadian(const double&);
		void SetDirectionUp();
		void SetDirectionDown();
		void SetDirectionLeft();
		void SetDirectionRight();
		void SetDegree(const double&);
		void ShfitDegree(const double&);
	};
}
#endif