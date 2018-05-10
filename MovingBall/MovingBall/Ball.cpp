#include "stdafx.h"
#include "Ball.h"
#include "DefineList.h"
#include <cmath>


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
	//a_ = (MOVINGBALL_REACT_RADIUS - distance_) / MOVINGBALL_REACT_RADIUS * MOVINGBALL_MAX_ACCELERATION;
	if (distance_ < MOVINGBALL_REACT_RADIUS / 4) {
		a_ = MOVINGBALL_MAX_ACCELERATION_1;
	}
	else if (distance_ < MOVINGBALL_REACT_RADIUS / 2) {
		a_ = MOVINGBALL_MAX_ACCELERATION_2;
	}
	else if (distance_ < 3 * MOVINGBALL_REACT_RADIUS / 4) {
		a_ = MOVINGBALL_MAX_ACCELERATION_3;
	} 
	else if (distance_ < MOVINGBALL_REACT_RADIUS) {
		a_ = MOVINGBALL_MAX_ACCELERATION_4;
	}
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

void MovingBall::SlowDown() {
	bool xchange = false;
	bool ychange = false;
	if (std::abs(speedX_) < MOVINGBALL_SLOWDOWN_ACCELERATION / 2.0) {
		speedX_ = 0;
		xchange = true;
	}
	if (std::abs(speedY_) < MOVINGBALL_SLOWDOWN_ACCELERATION / 2.0) {
		speedY_ = 0;
		ychange = true;
	}

	if (!xchange) {
		double MotionCosine = speedX_ / sqrt(speedX_*speedX_ + speedY_*speedY_);
		speedX_ -= MOVINGBALL_SLOWDOWN_ACCELERATION * MotionCosine;

		/*if (speedX_ > 0)
			speedX_ -= MOVINGBALL_SLOWDOWN_ACCELERATION;
		else
			speedX_ += MOVINGBALL_SLOWDOWN_ACCELERATION;*/
	}

	if (!ychange) {
		double MotionSinus = speedY_ / sqrt(speedX_*speedX_ + speedY_*speedY_);
		speedY_ -= MOVINGBALL_SLOWDOWN_ACCELERATION * MotionSinus;

		/*if (speedY_ > 0)
			speedY_ -= MOVINGBALL_SLOWDOWN_ACCELERATION;
		else
			speedY_ += MOVINGBALL_SLOWDOWN_ACCELERATION;*/
	}
}

void MovingBall::TakeAccountBordersBump() {
	//double DeltaLeft = x_ - R_ - zone_.left;  // <0
	//double DeltaRight = x_ + R_ - zone_.right;  // >0
	//double DeltaTop = y_ + - R_ - zone_.top; // <0
	//double DeltaBottom = y_ + R_ - zone_.bottom; // >0
	
	if (x_ - R_ <= zone_.left) {
		speedX_ = -speedX_;
		x_ = zone_.left + R_ + 1;
	}
	else if (x_ + R_ >= zone_.right) {
		speedX_ = -speedX_;
		x_ = zone_.right - R_ - 1;
	}
	if (y_ - R_ <= zone_.top) {
		speedY_ = -speedY_;
		y_ = zone_.top + R_ + 1;
	}
	else if (y_ + R_ >= zone_.bottom) {
		speedY_ = -speedY_;
		y_ = zone_.bottom - R_ - 1;
	}
}

void MovingBall::InitMovementZone(const RECT & zone) {
	zone_.left = zone.left;
	zone_.top = zone.top;
	zone_.right = zone.right;
	zone_.bottom = zone.bottom;
}

void MovingBall::React(int x, int y) {
	if (CheckCursorCollision(x, y)) {
		CalculateDistance(x, y);
		CalculateAngle(x, y);
		CalculateAcceleration(x, y);
		CalculateSpeed();
		ChangePosition();
		TakeAccountBordersBump();
		
	}
	else {
		SlowDown();
		ChangePosition();
		TakeAccountBordersBump();
	}

}

void MovingBall::Draw(CDC& dc) {
	dc.Ellipse(x_ - R_, y_ - R_, x_ + R_, y_ + R_);
}

bool  MovingBall::Ñollision(int x, int y) {
	//shape equation: (x - x_)^2 + (y - y_)^2 = R_^2
	return (x - x_)*(x - x_) + (y - y_)*(y - y_) <= R_*R_;
}