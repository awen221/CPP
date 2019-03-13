#include "GameObject.h"

//protected
enum { defaultSize = 20, };
double GameObject::GetDefaultSize() { return defaultSize; }

//public
double GameObject::GetSize() { return Size; }
void GameObject::SetSize(double value) { Size = value; }

void GameObject::Init()
{
	Size = GetDefaultSize();
}

#include<time.h>
#include "random.h"
using Random = MATH::Random;
void GameObject::Rand(double xMin, double xMax, double yMin, double yMax)
{
	static Random random = Random(clock());
	int randX = random.GetRand();
	int randY = random.GetRand();

	double X_rand = xMin + randX % (int)(xMax - xMin);
	double Y_rand = yMin + randY % (int)(yMax - yMin);

	X = X_rand;
	Y = Y_rand;
}