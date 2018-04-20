#include "CPolynomial.h"

//Segment class definition
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

Segment & Segment::operator*=(const Segment & rhs)
{
	_coef *= rhs._coef;
	_pow += rhs._pow;
	return *this;
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

Segment operator*(const Segment & lhs, const Segment & rhs)
{
	return Segment(lhs._coef * rhs._coef, lhs._pow + rhs._pow);
}


//CPolynomial class definition
Polynomial Polynomial::operator=(const Polynomial & rhs) {
	_poly = rhs._poly;
	return Polynomial(*this);
}

void Polynomial::shrink_zeros() {
	for (std::list<Segment>::iterator it = _poly.begin(); it != _poly.end();) {
		if ((*it).Power() > 0 && (*it).Coef() == 0)
			it = _poly.erase(it);
		else
			it++;
	}
}

Polynomial Polynomial::operator-() const {
	Polynomial p;
	for (std::list<Segment>::const_iterator it = _poly.begin(); it != _poly.end(); it++) {
		p += -(*it);
	}
	return p;
}

Polynomial & Polynomial::operator+=(const Segment & rhs) {
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

Polynomial & Polynomial::operator-=(const Segment & rhs)
{
	return (*this += -rhs);
}

Polynomial operator+(const Polynomial & lhs, const Polynomial & rhs) {
	Polynomial sum;
	for (std::list<Segment>::const_iterator it = lhs._poly.begin(); it != lhs._poly.end(); it++) {
		sum += (*it);
	}

	for (std::list<Segment>::const_iterator it = rhs._poly.begin(); it != rhs._poly.end(); it++) {
		sum += (*it);
	}

	sum.shrink_zeros();
	return sum;
}

Polynomial operator-(const Polynomial & lhs, const Polynomial & rhs) {
	Polynomial sub;
	for (std::list<Segment>::const_iterator it = lhs._poly.begin(); it != lhs._poly.end(); it++) {
		sub += (*it);
	}

	for (std::list<Segment>::const_iterator it = rhs._poly.begin(); it != rhs._poly.end(); it++) {
		sub += -(*it);
	}
	sub.shrink_zeros();
	return sub;
}

Polynomial operator*(const Polynomial & lhs, const Polynomial & rhs)
{
	Polynomial mul;
	for (std::list<Segment>::const_iterator lhs_it = lhs._poly.begin(); lhs_it != lhs._poly.end(); lhs_it++) {
		for (std::list<Segment>::const_iterator rhs_it = rhs._poly.begin(); rhs_it != rhs._poly.end(); rhs_it++) {
			mul += (*lhs_it) * (*rhs_it);
		}
	}
	mul.shrink_zeros();
	return mul;
}

