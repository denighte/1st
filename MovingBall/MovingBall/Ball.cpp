#include "stdafx.h"
#include "Ball.h"
#include "DefineList.h"


bool MovingBall::CheckCursorCollision(int x, int y)
{
	return (x - x_)*(x - x_) + (y - y_)*(y - y_) <= MOVINGBALL_REACT_RADIUS * MOVINGBALL_REACT_RADIUS;
}

void MovingBall::CalculateDistance(int x, int y) { 
	distance_ = sqrt(static_cast<double>((x - x_)*(x - x_) + (y - y_)*(y - y_))); 
}

void MovingBall::CalculateAngle(int x, int y) {
	int deltaX = x - x_;
	int deltaY = y - y_;
	int sqdistance = deltaX*deltaX + deltaY*deltaY;

	cos_ = -static_cast<double>(deltaX) / sqdistance;  //calculating cos of direction angle
	sin_ = -static_cast<double>(deltaY) / sqdistance;	//calculating sin of direction angle

}

void MovingBall::CalculateAcceleration(int x, int y) { 
	a_ = (MOVINGBALL_REACT_RADIUS - distance_) / MOVINGBALL_REACT_RADIUS * MOVINGBALL_MAX_ACCELERATION;
}

void MovingBall::CalculateSpeed() {
	if (speedX_*speedX_ + speedY_*speedY_ < MOVINGBALL_MAX_SPEED * MOVINGBALL_MAX_SPEED) {
		speedX_ += a_*cos_;
		speedY_ += a_*sin_;
	}
}

void MovingBall::ChangePosition()
{
	x_ += speedX_;
	y_ += speedY_;
}

void MovingBall::React(int x, int y) {
	if (CheckCursorCollision(x, y)) {
		CalculateDistance(x, y);
		CalculateAngle(x, y);
		CalculateAcceleration(x, y);
		CalculateSpeed();
		ChangePosition();
	}

}

void MovingBall::Draw(CDC& dc) {
	dc.Ellipse(x_ - R_, y_ - R_, x_ + R_, y_ + R_);
}
