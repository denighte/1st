#include "CPolynomial.h"
Segment Segment::operator=(const Segment & rhs) {
	_coef = rhs._coef;
	_pow = rhs._pow;
}

Segment operator+(const Segment & lhs, const Segment & rhs) {
	if (lhs.Power() == rhs.Power())
		return Segment(lhs.Coef() + rhs.Coef(), lhs.Power());
	else
		throw Segment::InequivalentDegreesException();
}

Segment operator-(const Segment & lhs, const Segment & rhs) {
	if (lhs.Power() == rhs.Power())
		return Segment(lhs.Coef() - rhs.Coef(), lhs.Power());
	else
		throw Segment::InequivalentDegreesException();
}

CPolynomial CPolynomial::operator=(const CPolynomial & rhs) {
	_poly = rhs._poly;
	return CPolynomial(*this);
}

CPolynomial & CPolynomial::operator+=(const Segment & rhs) {
	// TODO: insert return statement here
}
