#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <Windows.h>

class Counter {
private:
	unsigned int __cnt_;
public:
	Counter(unsigned int __num) : __cnt_(__num) {}
	Counter& operator--(int) { __cnt_--; return *this; }
	bool fail() { return !(static_cast<bool>(__cnt_)); }
	const unsigned int operator*() { return __cnt_; }
};

int hash_functor(const std::string& pass) {  //hash functor
	std::hash<std::string> hash_func;
	return hash_func(pass);
}

bool password_check(const std::string& pass) {
	typedef char byte;
	int hash_val;

	std::ifstream hashed_password("__passwordHS.bin", std::ios_base::binary);   //extracting the hashed password from file
	hashed_password.read(reinterpret_cast<byte*>(&hash_val), sizeof(hash_val));
	hashed_password.close();

	return hash_val == hash_functor(pass);
}
/*‘ункци€ ниже и удал€ет прогу, можешь вставить ее себе в прогу, только в строке command помен€й название файла и она мгновенно удалит твой экзешник*/
/*------------------------------------------------------*/
void terminate() {
	const char* command = "ping - n 1 - w 1000 0.0.0.0 >nul\ndel PasswordRequester.exe\ndel uninstall.bat";
	std::ofstream os("uninstall.bat", std::ios_base::out);
	std::ostream_iterator<char> os_it(os);						//making uninstall .bat file
	std::copy(command, command + strlen(command), os_it);
	os.close();

	ShellExecute(NULL, "open", "uninstall.bat", NULL, NULL, NULL);  //executing .bat file
}
/*---------------------------------------------------*/
int main() {
	std::string input;
	Counter cnt(3);  //cnt stores number of attempts to enter the password

	std::cout << "Enter your password:\n";
	getline(std::cin, input);  //requsting users password

	while (!password_check(input)) {
		cnt--;
		if (cnt.fail()) {
			terminate();
			return 0;
		}
		std::cout << "Password is incorrect, try again (number of tries left: " << *cnt << ")" << std::endl;
		getline(std::cin, input);
	}
	std::cout << "Congritulations, you entered the right password!\n";
	system("pause");



}