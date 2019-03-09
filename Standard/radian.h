#ifndef RADIAN_H
#define RADIAN_H



#include "point_base.h"
using namespace Point_Template;

class Radian
{
private:

protected:
	//PI*0 ~ PI*2
	double radian;
	virtual void Init();
public:
	//角度轉弧度
	static double GetDegreeFromRadian(const double&);
	//弧度轉角度
	static double GetRadianFromDegree(const double&);

	void SetRadian(const double&);
	double GetRadian();
	void ShfitRadian(const double&);

	double GetDegree();
	void SetDegree(const double& );
	void ShfitDegree(const double& );

	void SetDirectionUp();
	void SetDirectionDown();
	void SetDirectionLeft();
	void SetDirectionRight();

};

#endif