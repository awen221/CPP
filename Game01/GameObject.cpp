#include "GameObject.h"

enum { defaultSize = 20, };
//protected
double GameObject::GetDefaultRadius() { return 0; }
//public
double GameObject::GetRadius() { return Radius; }
void GameObject::SetRadius(double value) { Radius = value; }

//public
bool GameObject::IsDestroyed() { return Destroyed; }

//public
GameObject::GameObject() :Destroyed(false) {}
GameObject::~GameObject() {}

void GameObject::Init() { Radius = GetDefaultRadius(); }

