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
	//�ؼЬ����豵Ĳ�I
	target.Step(*this, Size + targetCharacter.Size);
	Step(target, Speed);
}

double GameObject::GetSize() { return Size; }
void GameObject::SetSize(double value) { Size = value; }


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

