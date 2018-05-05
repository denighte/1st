#pragma once
#define CMAINDLG_PARTICIPANT_1 _T("Student1")
#define CMAINDLG_PARTICIPANT_2 _T("Student2")
#define CMAINDLG_PARTICIPANT_3 _T("Student3")
#define CMAINDLG_PARTICIPANT_4 _T("Student4")
#define CMAINDLG_PARTICIPANT_5 _T("Student5")
#define CMAINDLG_PARTICIPANT_6 _T("Student6")

#define POINTER_POINTS_NUMBER  5  //number of points in ARROWHEAD
#define NUMBER_OF_PARTICIPANTS 6  //number of participants
#define COUNTER_GAME_TICKRATE 500

CONST POINT ARROWHEAD[POINTER_POINTS_NUMBER] = { { 0, 0 },{ -30, 230 },{ 0, 500 },{ 30, 230 },{ 0, 0 } };   //array, wich specifies the pointer
CONST POINT PARTICIPANTS_START_POINT = { 0, 600 };   //point, where the first student is to be drawn
CONST INT ROTATE_ANGLE = 360 / NUMBER_OF_PARTICIPANTS;

const std::wstring RESOURCES_CURRENT_FOLDER = L"\\Resources\\";   //Folder, where the resources are stored (relative to the current path)
const std::wstring RESOURCES_CURRENT_FULL_PATH = static_cast<std::wstring>(std::experimental::filesystem::current_path()) + RESOURCES_CURRENT_FOLDER;
const std::wstring RESOURCES_COUNTERS_FILE_NAME = L"Counters.txt";  //File, where counters are stored
const std::wstring RESOURCES_MUSIC_FILE_NAME = L"WrathOfTheGiants.mp3";  //Music file, plays whan winner is determined
const std::wstring PARTICIPANT_IMAGE_FILE_EXTENSION = L".bmp";  //the format of pictures
