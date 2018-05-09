#pragma once
class MovingBall {
private:

	//Ball shape equation: (x - x_)^2 + (y - y_)^2 = R_^2
	int x_; //shape center position x
	int y_; //shape center position y

	int R_; //radius of a ball_

	double speedX_;  //current speed on the x-axis
	double speedY_; //current speed on the x-axis
	double a_; //vector of current acceleration

	double cos_;  //current direction cosinus
	double sin_;  //current direction sinus

	double distance_;
private:
	bool CheckCursorCollision(int x, int y);

	inline void CalculateDistance(int x, int y);
	void CalculateAngle(int x, int y);

	inline void CalculateAcceleration(int x, int y);
	void CalculateSpeed();
	inline void ChangePosition();

public:
	MovingBall() : R_(0), speedX_(0), speedY_(0) {}
	MovingBall(int x, int y, int Radius) : x_(x), y_(y), R_(Radius), speedX_(0), speedY_(0) {}
	void React(int x, int y);
	void Draw(CDC &dc);
};