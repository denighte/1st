#include <iostream>
#include "CPolynomial.h"
int main() {
	Polynomial a;
	a += {1, 1};
	a += {1, 2};
	Polynomial b;
	b += {1, 2};
	b += {-2, 1};
	b += {1, 0};

	Polynomial c = a * b;
	std::cout << "check" << std::endl;
}