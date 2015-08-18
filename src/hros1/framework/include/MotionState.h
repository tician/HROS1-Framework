#ifndef MOTIONSTATE_H_
#define MOTIONSTATE_H_

class MotionState
{
public:
	MotionState();
	MotionState(double T, double X, double V);
	~MotionState(){};

	void set(double X, double V);

	double t;
	double x;
	double v;
	double a;
};

#endif /* MOTIONSTATE_H_ */
