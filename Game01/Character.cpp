#include "Character.h"


//protected
enum { defaultHP = 1000, };
int Character::GetDefaultHP()
{
	return defaultHP;
}
enum { defaultSpeed = 10, };
double Character::GetDefaultSpeed() { return defaultSpeed; }
enum { defaultAttackRangeCenterDistance = 20, };
double Character::GetDefaultAttackCenterDistance()
{
	return defaultAttackRangeCenterDistance;
}
enum { defaultAttackRangeDistance = 20, };
double Character::GetDefaultAttackRadius()
{
	return defaultAttackRangeDistance;
}


int Character::GetHP()
{
	return HP;
}
void Character::SetHP(int value)
{
	HP = value;
}
void Character::AddHP(int value)
{
	SetHP(HP + value);
}
void Character::SubHP(int value)
{
	SetHP(HP - value);
}
bool Character::IsDead()
{
	return bDead;
}

double Character::GetSpeed() { return Speed; }
void Character::SetSpeed(double value) { Speed = value; }

void Character::StepToCharacter(GameObject& targetCharacter)
{
	GameObject target = targetCharacter;
	//�ؼЬ����豵Ĳ�I
	target.Step(*this, Size + targetCharacter.GetSize());
	Step(target, Speed);
}

//���o�����d�򤤤��I
PointBaseD Character::GetAttackCenter()
{
	Character pnt = *this;

	pnt.MoveToDirection(AttackCenterDistance, pnt.radian);
	return pnt;
}
//���o�����d��Z��
double Character::GetAttackRadius()
{
	return AttackRadius;
}


//�񨭧���
void Character::nearAttackAuto(Character& targetCharacter, int damage)
{
	PointBaseD pnt = GetAttackCenter();
	//���o�����d��O�_�P��H���⭫�|
	if (pnt.GetDistance(targetCharacter) <= (targetCharacter.GetSize() + radian))
	{
		targetCharacter.SubHP(damage);
	}
}

int Character::GetCurAction()
{
	return action.GetCurAction();
}

void Character::Init()
{
	GameObject::Init();

	HP = GetDefaultHP();
	Speed = GetDefaultSpeed();
	AttackCenterDistance = GetDefaultAttackCenterDistance();
	AttackRadius = GetDefaultAttackRadius();

	action = ActionSystem();
	action.Init();
}

void Character::Work()
{
	action.Work();
	bDead = HP <= 0;
}