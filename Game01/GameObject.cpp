#include "GameObject.h"

#include "random.h"
using RANDOM_Class = RANDOM::RANDOM_Class;

//protected
double GameObject::GetDefaultSpeed() { return 0; }
double GameObject::GetDefaultSize() { return 0; }

//public
void GameObject::Init()
{
	Speed = GetDefaultSpeed();
	Size = GetDefaultSize();
}

void GameObject::Rand(double xMin, double xMax, double yMin, double yMax)
{
	static RANDOM_Class random = RANDOM_Class();
	int randX = random.GetRand();
	int randY = random.GetRand();

	double X_rand = xMin + randX % (int)(xMax - xMin);
	double Y_rand = yMin + randY % (int)(yMax - yMin);

	X = X_rand;
	Y = Y_rand;
}


double GameObject::GetSpeed() { return Speed; }
void GameObject::SetSpeed(double value) { Speed = value; }

void GameObject::StepToCharacter(const GameObject& targetCharacter)
{
	GameObject target = targetCharacter;
	//目標為雙方接觸點
	target.Step(*this, Size + targetCharacter.Size);
	Step(target, Speed);
}

double GameObject::GetSize() { return Size; }
void GameObject::SetSize(double value) { Size = value; }


//取得與指定座標之夾角
double GameObject::GetRadianFromPoint(PointBaseD target)
{
	double radian;

	//笛卡兒座標系(第一象限)公式
	radian = atan2(target.GetY() - Y, target.GetX() - X);
	//轉成Windows座標系(第三象限)要加負號
	radian = -radian;

	return radian;
}
bool GameObject::IsDead() { return bDead; }

