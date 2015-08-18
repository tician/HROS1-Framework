#include "MotionState.h"

MotionState::MotionState()
{
	t = 0;
	x = 0;
	v = 0;
	a = 0;
}

MotionState::MotionState(double T, double X, double V)
{
	this->t = T;
	this->x = X;
	this->v = V;
	a = 0;
}

void MotionState::set(double X, double V)
{
	this->x = X;
	this->v = V;
	a = 0;
}

