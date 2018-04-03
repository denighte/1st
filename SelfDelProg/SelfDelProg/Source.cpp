#include <iostream>
#include <thread>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
# define FILE_FLAG_DELETE_ON_CLOSE
int main() {
	std::cout << "that's gonna dissapear";
	//fs::path("text.txt");
	//fs::remove(fs::path("SelfDelProg.exe"));
}