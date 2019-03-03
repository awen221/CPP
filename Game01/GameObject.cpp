#include "GameObject.h"

#include "random.h"


enum RandomPos
{
	xMin = 0,
	xMax = 800,
	yMin = 0,
	yMax = 600,
};
enum Speed
{
	Default = 4,
};
enum Size
{
	SizeDefault = 20,
};

//protected
double GameObject::GetDefaultSpeed() { return Speed::Default; }
double GameObject::GetDefaultSize() { return Size::SizeDefault; }
//public
void GameObject::Rand(double xMin, double xMax, double yMin, double yMax)
{
	static RANDOM random = RANDOM();
	int randX = random.GetRand();
	int randY = random.GetRand();

	double X_rand = xMin + randX % (int)(xMax - xMin);
	double Y_rand = yMin + randY % (int)(yMax - yMin);

	X = X_rand;
	Y = Y_rand;
}
void GameObject::SetRandomPos()
{
	Rand(RandomPos::xMin, RandomPos::xMax, RandomPos::yMin, RandomPos::yMax);
}

double GameObject::GetSpeed() { return Speed; }
void GameObject::SetSpeed(double value) { Speed = value; }

void GameObject::StepToCharacter(const GameObject& targetCharacter, double speed)
{
	GameObject target = targetCharacter;
	//目標為雙方接觸點
	target.Step(*this, Size + targetCharacter.Size);
	Step(target, speed);
}

double GameObject::GetSize() { return Size; }
void GameObject::SetSize(double value) { Size = value; }

void GameObject::Init()
{
	SetRandomPos();
	Speed = GetDefaultSpeed();
	Size = GetDefaultSize();
}
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

