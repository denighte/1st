#include <iostream>
#include "CPolynomial.h"
// NOTE: string such as "x^5 + x - 1" can't be parsed correctly, you should type this like "1x^5 + 1x - 1"
int main() {
	std::string str_l;
	std::string str_r;

	std::cout << "Enter 2 polynomials" << std::endl;
	
	std::getline(std::cin, str_l);
	std::getline(std::cin, str_r);

	Polynomial a(PolynomialBuilder::parse(str_l));
	Polynomial b(PolynomialBuilder::parse(str_r));
	Polynomial res;
	std::cout << "Choose the operation (+,-,*,/):" << std::endl;
	char operation;
	bool stdin_flag = true;
	std::cin >> operation;

	switch (operation)
	{
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
		res = a * b;
		break;
	case '/':
		res = a / b;
		break;
	default:
		stdin_flag = false;
		break;
	}

	if (stdin_flag) {
		std::cout << "The result of the operation is:" << std::endl;
		std::cout << res.to_string() << std::endl;
	}
	else {
		std::cout << "Wrong operation!" << std::endl;
	}
	system("pause");
}