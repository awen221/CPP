#include "Character.h"


//protected
enum { defaultHP = 1000, };
int Character::GetDefaultHP()
{
	return defaultHP;
}

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



void Character::StepToCharacter(ActiveObject& targetCharacter)
{
	GameObject target = targetCharacter;
	//目標為雙方接觸點
	target.Step(*this, Size + targetCharacter.GetSize());
	Step(target, Speed);
}

//取得攻擊範圍中心點
PointBaseD Character::GetAttackCenter()
{
	Character pnt = *this;

	pnt.MoveToDirection(AttackCenterDistance, pnt.radian);
	return pnt;
}
//取得攻擊範圍距離
double Character::GetAttackRadius()
{
	return AttackRadius;
}


//近身攻擊
void Character::nearAttackAuto(Character& targetCharacter, int damage)
{
	PointBaseD pnt = GetAttackCenter();
	//取得攻擊範圍是否與對象角色重疊
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
	ActiveObject::Init();

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