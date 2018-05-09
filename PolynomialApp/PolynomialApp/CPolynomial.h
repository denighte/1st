#pragma once
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <exception>
#define DEFAULT_POS -1;

typedef unsigned int Tpow;
typedef double Tcoef;
class Segment {
private:
	Tcoef _coef;
	Tpow _pow;
public:
	Segment() : _coef(0), _pow(0) {}
	~Segment() = default;
	Segment(Tcoef coef, Tpow power) : _coef(coef), _pow(power) {}
	Segment(const Segment & obj) : _coef(obj._coef), _pow(obj._pow) {}
	Segment operator=(const Segment & rhs);

	Tcoef Coef() const { return _coef; }
	Tpow Power() const { return _pow; }

	Segment operator+() const { return *this; }
	Segment operator-() const;
	Segment & operator+=(const Segment & rhs);
	Segment & operator*=(const Segment & rhs);
	Segment & operator*=(const Tcoef & rhs);

	friend Segment operator+(const Segment & lhs, const Segment & rhs);
	friend Segment operator-(const Segment & lhs, const Segment & rhs);
	friend Segment operator*(const Segment & lhs, const Segment & rhs);
	friend Segment operator*(const Segment & lhs, const Tcoef & rhs);
	friend Segment operator*(const Tcoef & lhs, const Segment & rhs) { return rhs * lhs; }

	std::string to_string() const;
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
	Polynomial & operator*=(const Segment & rhs);
	Polynomial & operator*=(const Tcoef & rhs);

	friend Polynomial operator+(const Polynomial & lhs, const Polynomial & rhs);
	friend Polynomial operator-(const Polynomial & lhs, const Polynomial & rhs);

	friend Polynomial operator*(const Polynomial & lhs, const Polynomial & rhs);
	friend Polynomial operator*(const Polynomial & lhs, const Segment & rhs);
	friend Polynomial operator*(const Segment & lhs, const Polynomial & rhs) { return rhs * lhs; }
	friend Polynomial operator*(const Polynomial & lhs, const Tcoef & rhs);
	friend Polynomial operator*(const Tcoef & lhs, const Polynomial & rhs) { return rhs * lhs; }
	friend Polynomial operator/(const Polynomial & lhs, const Polynomial & rhs);

	std::string to_string() const;
};

class Token {
public:
	static enum Type { numeric, variable, power, action, end };
private:
	Type _t;
	std::string _value;
public:
	Token() = delete;
	~Token() = default;
	Token(Type t, const std::string &str) : _value(str), _t(t) {}
	Token(Type t, const char &ch);
	Token(const Token & tk) : _t(tk._t), _value(tk._value) {}
	Token operator=(const Token & tk);

	bool same_type(const Token & tk) const { return _t == tk._t; }
	const std::string & value() const { return _value; }
	const Type & type() const { return _t; }

	static Token GetNextToken(const std::string &str, std::string::size_type &pos);
	static Type determineType(char c);
};

class PolynomialBuilder {
private:
	static std::regex exp;
	static Segment _SegmentFromPower(Token & tk, const std::string &str, std::string::size_type &pos, Tcoef & coef, Tpow & pow, Token & last_sign);
public:
	static Polynomial parse(const std::string &str);
	class StringParseException : std::exception {};
};


void SplitToVector(std::vector<std::string> &v, const std::string &src, const std::string &dlm);
