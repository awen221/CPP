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
	//�ؼЬ����豵Ĳ�I
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
//���o�P���w�y�Ф�����
double GameObject::GetRadianFromPoint(PointBaseD target)
{
	double radian;

	//�åd��y�Шt(�Ĥ@�H��)����
	radian = atan2(target.GetY() - Y, target.GetX() - X);
	//�নWindows�y�Шt(�ĤT�H��)�n�[�t��
	radian = -radian;

	return radian;
}
bool GameObject::IsDead() { return bDead; }

