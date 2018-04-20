#pragma once
#include <list>
#include <algorithm>
#include <exception>

typedef unsigned int Tpow;
typedef double Tkoef;
class Segment {
private:
	Tkoef _coef;
	Tpow _pow;
public:
	Segment() = delete;
	~Segment() = default;
	Segment(Tkoef coef, Tpow power) : _coef(coef), _pow(power) {};
	Segment(const Segment & obj) : _coef(obj._coef), _pow(obj._pow) {};
	Segment operator=(const Segment & rhs);

	Tkoef Coef() const { return _coef; }
	Tpow Power() const { return _pow; }

	Segment operator+() const { return *this; }
	Segment operator-() const;
	Segment & operator+=(const Segment & rhs);

	friend Segment operator+(const Segment & lhs, const Segment & rhs);
	friend Segment operator-(const Segment & lhs, const Segment & rhs);

	class InequivalentDegreesException : std::exception {};
};


class CPolynomial {
private:
	std::list<Segment> _poly;
	void shrink_zeros();
public:
	CPolynomial() : _poly(1, { 0, 0 }) {};
	~CPolynomial() = default;
	CPolynomial(const CPolynomial & p) : _poly(p._poly) {};
	CPolynomial operator=(const CPolynomial & rhs);

	CPolynomial operator+() const{ return *this; }
	CPolynomial operator-() const;
	CPolynomial & operator+=(const Segment & rhs);

	friend CPolynomial operator+(const CPolynomial & lhs, const CPolynomial & rhs);
	friend CPolynomial operator-(const CPolynomial & lhs, const CPolynomial & rhs);
};
