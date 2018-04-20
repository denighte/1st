#include "CPolynomial.h"
Segment Segment::operator=(const Segment & rhs) {
	_coef = rhs._coef;
	_pow = rhs._pow;
	return *this;
}

Segment Segment::operator-() const {
	return Segment(-_coef, _pow);
}

Segment & Segment::operator+=(const Segment & rhs) {
	if (this->Power() == rhs.Power()) {
		_coef += rhs._coef;
		return *this;
	}
	else {
		throw Segment::InequivalentDegreesException();
	}
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

CPolynomial CPolynomial::operator-() const{
	CPolynomial p;
	for (std::list<Segment>::const_iterator it = _poly.begin(); it != _poly.end(); it++) {
		p += -(*it);
	}
	return p;
}

CPolynomial & CPolynomial::operator+=(const Segment & rhs) {
	for (std::list<Segment>::iterator it = _poly.begin()++; it != _poly.end(); it++) {
		if (it->Power() < rhs.Power()) {
			_poly.insert(it, rhs);
			break;
		}
		if (it->Power() == rhs.Power()) {
			(*it) += rhs;
			break;
		}
	}
	return *this;
}

CPolynomial operator+(const CPolynomial & lhs, const CPolynomial & rhs)
{
	CPolynomial sum;
	for (std::list<Segment>::const_iterator it = lhs._poly.begin(); it != lhs._poly.end(); it++) {
		sum += (*it);
	}
	
	for (std::list<Segment>::const_iterator it = rhs._poly.begin(); it != rhs._poly.end(); it++) {
		sum += (*it);
	}

	return sum;
}

