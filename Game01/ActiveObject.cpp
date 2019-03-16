#include "ActiveObject.h"

enum { defaultSpeed = 10, };
double ActiveObject::GetDefaultSpeed() { return defaultSpeed; }

ActiveObject::ActiveObject()
{
}
ActiveObject::~ActiveObject()
{
}
double ActiveObject::GetSpeed() { return Speed; }
void ActiveObject::SetSpeed(double value) { Speed = value; }

void ActiveObject::MoveToCurrentDirection()
{
	PointBaseD::MoveTo(radian, Speed);
}
