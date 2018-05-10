#pragma once
//MainDlg.cpp
#define CMAINDIALOG_FRAME_RATE 100 // WM_TIMER constant

#define CMAINDIALOG_LEFT_BORDER 0
#define CMAINDIALOG_TOP_BORDER 400
#define CMAINDIALOG_RIGHT_BORDER 800
#define CMAINDIALOG_BOTTOM_BORDER 0

#define MOVINGBALL_START_POSITION_X 400
#define MOVINGBALL_START_POSITION_Y 200
#define MOVINGBALL_START_RADIUS 25

//ball.cpp
#define MOVINGBALL_REACT_RADIUS 200
#define MOVINGBALL_MAX_SPEED 200  //max speed of the ball_ (pixels/sec)

//#define MOVINGBALL_MAX_ACCELERATION 40  //max acceleration (pixels/sec)
//max accelerations depending on the distance between shape center and pointer (pixels/sec)
#define MOVINGBALL_MAX_ACCELERATION_1 20
#define MOVINGBALL_MAX_ACCELERATION_2 25
#define MOVINGBALL_MAX_ACCELERATION_3 40
#define MOVINGBALL_MAX_ACCELERATION_4 50



#define MOVINGBALL_SLOWDOWN_ACCELERATION 0.2  //the value, which speed on x AND y projection will be reduced by 