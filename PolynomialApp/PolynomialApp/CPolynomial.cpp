#include "CPolynomial.h"
#define POLYNOMIAL_POWER_SYMBOL '^'
#define POLYNOMIAL_VARIABLE 'x'
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

Segment & Segment::operator*=(const Tcoef & rhs) {
	_coef *= rhs;
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

Segment operator*(const Segment & lhs, const Segment & rhs){
	return Segment(lhs) *= rhs ;
}

Segment operator*(const Segment & lhs, const Tcoef & rhs)
{
	return Segment(lhs) *= rhs;
}

std::string Segment::to_string() const
{
	std::string result;
	if (!_pow) {
		if (_coef)
			return std::to_string(_coef);
		else
			return result;
	}
	else if (_pow == 1) {
		result += std::to_string(_coef);
		result += POLYNOMIAL_VARIABLE;
		return result;
	}
	else {
		result += std::to_string(_coef);
		result += POLYNOMIAL_VARIABLE;
		result += POLYNOMIAL_POWER_SYMBOL;
		result += std::to_string(_pow);
		return result;
	}
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
	if (rhs.Coef() == 0)
		return *this;

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

Polynomial & Polynomial::operator-=(const Segment & rhs) {
	return (*this += -rhs);
}

Polynomial & Polynomial::operator*=(const Segment & rhs) {
	if (rhs.Coef() == 0) {
		_poly.clear();
		_poly.push_front(Segment());
	}

	for (std::list<Segment>::iterator it = _poly.begin(); it != _poly.end(); it++) {
		(*it) *= rhs;
	}
	return *this;
}

Polynomial & Polynomial::operator*=(const Tcoef & rhs) {
	if (rhs == 0) {
		_poly.clear();
		_poly.push_front(Segment());
	}

	for (std::list<Segment>::iterator it = _poly.begin(); it != _poly.end(); it++) {
		(*it) *= rhs;
	}
	return *this;
}

std::string Polynomial::to_string() const
{
	std::string result;
	for (std::list<Segment>::const_iterator it = _poly.begin(); it != _poly.end(); it++) {
		if ((*it).Coef() > 0) {
			result += std::string("+") + (*it).to_string();
		}
		else {
			result += (*it).to_string();
		}
	}
	return result;
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

Polynomial operator*(const Polynomial & lhs, const Segment & rhs)
{
	Polynomial mul;
	if (rhs.Coef() == 0) {
		mul._poly.push_front(Segment());
		return mul;
	}

	for (std::list<Segment>::const_iterator it = lhs._poly.begin(); it != lhs._poly.end(); it++) {
		mul += (*it) * rhs;
	}
	return mul;
}

Polynomial operator*(const Polynomial & lhs, const Tcoef & rhs)
{
	if (rhs == 0)   //multiplication with zero is always zero
		return Polynomial();   //<=> return 0

	Polynomial mul;
	for (std::list<Segment>::const_iterator it = lhs._poly.begin(); it != lhs._poly.end(); it++) {
		mul += (*it)*rhs;
	}
	return mul;
}

Polynomial operator/(const Polynomial & lhs, const Polynomial & rhs)
{
	Polynomial div;
	Polynomial dividend(lhs);
	for (; dividend._poly.begin()->Power() >= rhs._poly.begin()->Power();) {
		//the multiplier on which the divisor multiplies on each step
		Segment multiplier((dividend._poly.begin()->Coef() / rhs._poly.begin()->Coef()),
							dividend._poly.begin()->Power() - rhs._poly.begin()->Power());
		dividend = dividend - (rhs * multiplier);
		div += multiplier;
	}
	return div;
}


//PolinomialBulilder class definition
Polynomial PolynomialBuilder::parse(const std::string &str)
{
	Polynomial p;
	std::string::size_type pos = 0;
	Token last_sign(Token::Type::action, "+");
	for (Token tk = Token::GetNextToken(str, pos); tk.type() != Token::Type::end; tk = Token::GetNextToken(str, pos)) {
		Tcoef coef;
		Tpow power;
		//check all avalible ways of getting the polynomial segment, if can't convert, throw exception
		if (tk.type() == Token::Type::numeric) {
			coef = stod(tk.value());
			tk = Token::GetNextToken(str, pos);
			if (tk.type() == Token::Type::variable) {
				tk = Token::GetNextToken(str, pos);
				if (tk.type() == Token::Type::power) {
					if (last_sign.value() == "-")
						coef = -coef;
					p += _SegmentFromPower(tk, str, pos, coef, power, last_sign);
				}
				else if (tk.type() == Token::Type::action || tk.type() == Token::Type::end) {
					power = 1;
					if (last_sign.value() == "-")
						coef = -coef;
					p += Segment(coef, power);
					if (tk.type() == Token::Type::action) {
						last_sign = tk;
					}
				}
				else {
					throw StringParseException();
				}
			}
			else if (tk.type() == Token::Type::action || tk.type() == Token::Type::end) {
				power = 0;
				if (last_sign.value() == "-")
					coef = -coef;
				p += Segment(coef, power);
				if (tk.type() == Token::Type::action) {
					last_sign = tk;
				}
			}
			else {
				throw StringParseException();
			}
		}
		else if (tk.type() == Token::Type::variable) {
			coef = 1;
			tk = Token::GetNextToken(str, pos);
			if (tk.type() == Token::Type::power) {
				if (last_sign.value() == "-")
					coef = -coef;
				p += _SegmentFromPower(tk, str, pos, coef, power, last_sign);
			}
			else if (tk.type() == Token::Type::action || tk.type() == Token::Type::end) {
				power = 1;
				if (last_sign.value() == "-")
					coef = -coef;
				p+= Segment(coef, power);
				if (tk.type() == Token::Type::action) {
					last_sign = tk;
				}
			}
			else {
				throw StringParseException();
			}
		}
		else if (tk.type() == Token::Type::action) {
			last_sign = tk;
		}
		else {
			throw StringParseException();
		}

	}
	return p;
}
//check all avalible ways to get power number
Segment PolynomialBuilder::_SegmentFromPower(Token & tk, const std::string &str, std::string::size_type &pos, Tcoef & coef, Tpow & power, Token & last_sign) {

	tk = Token::GetNextToken(str, pos);
	if (tk.type() == Token::Type::numeric) {
		power = stoi(tk.value());
	}
	else {
		throw StringParseException();
	}
	tk = Token::GetNextToken(str, pos);
	if (tk.type() == Token::Type::action || tk.type() == Token::Type::end) {
		if (tk.type() == Token::Type::action)
			last_sign = tk;
		return Segment(coef, power);
	}
	else {
		throw StringParseException();
	}


}


//Token class definition
Token::Token(Type t, const char &ch) : _t(t), _value() {
	_value.push_back(ch);
}

Token Token::operator=(const Token & tk) {
	_t = tk._t;
	_value = tk._value;
	return *this;
}

Token Token::GetNextToken(const std::string &str, std::string::size_type &pos) {
	std::string num;
	while (pos < str.length()) {
		char c = str.at(pos);
		if (c == ' ' || c == '*') {
			pos++;
		} else if (isdigit(c)) {
			num += c;
			pos++;
		} else {
			if (num.length() > 0) {
				return Token(Token::Type::numeric, num);
			} else {
				Token tk(determineType(c), c);
				pos++;
				return tk;
			}
		}
	}
	pos++;
	return num.length() > 0 ? Token(Token::Type::numeric, num) : Token(Token::Type::end, "");
}

Token::Type Token::determineType(char c) {
	if (c == POLYNOMIAL_POWER_SYMBOL)
		return Type::power;
	if (c == POLYNOMIAL_VARIABLE)
		return Type::variable;
	if (c == '+' || c == '-')
		return Type::action;
	if (isdigit(c))
		return Type::numeric;
	if (c == '\0')
		return Type::end;
}


//other staff
void SplitToVector(std::vector<std::string> &v, const std::string &src, const std::string &dlm) {
	std::string::size_type p, start = 0, len = src.length();

	v.clear();
	start = src.find_first_not_of(dlm);
	p = src.find_first_of(dlm, start);
	while (p != std::string::npos) {
		v.push_back(src.substr(start, p - start));
		start = src.find_first_not_of(dlm, p);
		p = src.find_first_of(dlm, start);
	}
	if (len>start)//rest
		v.push_back(src.substr(start, len - start));
}
