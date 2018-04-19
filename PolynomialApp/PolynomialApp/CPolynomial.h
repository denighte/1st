#pragma once
#include <forward_list>
#include <exception>

typedef int Tpow;
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

	friend Segment operator+(const Segment & lhs, const Segment & rhs);
	friend Segment operator-(const Segment & lhs, const Segment & rhs);

	class InequivalentDegreesException : std::exception{}
};


class CPolynomial {
private:
	std::forward_list<Segment> _poly;
public:
	CPolynomial() = default;
	~CPolynomial() = default;
	CPolynomial(const CPolynomial & p) : _poly(p._poly) {};
	CPolynomial operator=(const CPolynomial & rhs);

	CPolynomial & operator+=(const Segment & rhs);
};