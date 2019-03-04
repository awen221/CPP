#include "Character.h"


enum { defaultHP = 1000, };
int Character::GetDefaultHP()
{
	return defaultHP; 
}
enum { defaultAttackDistance = 20, };
double Character::GetDefaultAttackDistance()
{
	return defaultAttackDistance; 
}
enum { defaultAttackRadius = 25, };
double Character::GetDefaultAttackRadius() 
{
	return defaultAttackRadius; 
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
	return HP <= 0;
}
PointBaseD Character::GetAttackCenterPoint()
{
	Character pnt = *this;

	pnt.MoveToCurrentDirection(pnt, AttackDistance);
	return pnt;
}
double Character::GetAttackRadius() 
{
	return AttackRadius; 
}
//近身攻擊
void Character::nearAttackAuto(Character& targetCharacter, int damage)
{
	PointBaseD pnt = GetAttackCenterPoint();
	//取得攻擊範圍是否與對象角色重疊
	if (pnt.GetDistance(targetCharacter) <= (targetCharacter.GetSize() + AttackRadius))
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
	AttackDistance = GetDefaultAttackDistance();
	AttackRadius = GetDefaultAttackRadius();

	action = ActionSystem();
	action.Init();
}

void Character::Work()
{
	action.Work();
}