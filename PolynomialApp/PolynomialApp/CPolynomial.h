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
	Segment & operator*=(const Segment & rhs);

	friend Segment operator+(const Segment & lhs, const Segment & rhs);
	friend Segment operator-(const Segment & lhs, const Segment & rhs);
	friend Segment operator*(const Segment & lhs, const Segment & rhs);

	class InequivalentDegreesException : std::exception {}; 
	//Exception class, throw itself in "+" and "-" operators
	//if dergees are not equal
};


class Polynomial {
private:
	std::list<Segment> _poly;
	void shrink_zeros();
public:
	Polynomial() : _poly(1, { 0, 0 }) {};
	~Polynomial() = default;
	Polynomial(const Polynomial & p) : _poly(p._poly) {};
	Polynomial operator=(const Polynomial & rhs);

	Polynomial operator+() const{ return *this; }
	Polynomial operator-() const;
	Polynomial & operator+=(const Segment & rhs);
	Polynomial & operator-=(const Segment & rhs);

	friend Polynomial operator+(const Polynomial & lhs, const Polynomial & rhs);
	friend Polynomial operator-(const Polynomial & lhs, const Polynomial & rhs);
	friend Polynomial operator*(const Polynomial & lhs, const Polynomial & rhs);
};

class PolynomialBuilder {
public:
	static Polynomial parse(std::string);
};