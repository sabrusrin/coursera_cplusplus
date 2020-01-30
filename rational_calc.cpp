#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Rational	{
	public:
		Rational():numerator{0}, denominator{1}	{}
		Rational(int n, int d)	{
			int	gcd_num = 1;

			if (d == 0)
				throw invalid_argument("Invalid argument");
			else	{
				if (n == 0)	{
					numerator = n;
					denominator = 1;
				}
				else	{
					gcd_num = greatestCommonDivisor(n, d);
					numerator = abs(n / gcd_num);
					denominator = abs(d / gcd_num);
					if ((n < 0 && d > 0) || (n > 0 && d < 0))	{
						numerator *= -1;
					}
				}
			}
		}

		int Numerator() const	{
			return (numerator);
		}
		int Denominator() const	{
			return (denominator);
		}
	private:
		int	greatestCommonDivisor(int x, int y)	{
			int tmp;

			while (y != 0)	{
				tmp = y;
				y = x % y;
				x = tmp;
			}
			return (x);
		}

		int	numerator;
		int	denominator;
};

Rational operator+(const Rational& lhs, const Rational& rhs)	{
	int	numerator = lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator();
	int	denominator = lhs.Denominator() * rhs.Denominator();
	return Rational(numerator, denominator);
}

Rational operator-(const Rational& lhs, const Rational& rhs)	{
	int	numerator = lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator();
	int	denominator = lhs.Denominator() * rhs.Denominator();
	return Rational(numerator, denominator);
}

Rational operator*(const Rational& lhs, const Rational& rhs)	{
	return Rational(lhs.Numerator() * rhs.Numerator(), \
					lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)	{
	if (rhs.Numerator() == 0)
		throw domain_error("Division by zero");
	else
		return Rational(lhs.Numerator() * rhs.Denominator(), \
						lhs.Denominator() * rhs.Numerator());

}

bool operator==(const Rational& lhs, const Rational& rhs)	{
	if (lhs.Numerator() == rhs.Numerator() && \
		lhs.Denominator() == rhs.Denominator())
		return (true);
	else
		return (false);
}

bool operator<(const Rational& lhs, const Rational& rhs)	{
	double l, r;

	l = (double)lhs.Numerator() / lhs.Denominator();
	r = (double)rhs.Numerator() / rhs.Denominator();
	if (lhs == rhs)
		return (l < r);
	return (l < r);
}
istream& operator>>(istream& stream, Rational& r)	{
	int numerator;
	int	denominator;
	char op;

	if (stream)
		if (stream >> numerator && stream >> op && op == '/' && stream >> denominator)
			r = Rational(numerator, denominator);
	return (stream);
}

ostream& operator<<(ostream& stream, const Rational& r)	{
	stream << r.Numerator() << '/' << r.Denominator();
	return (stream);
}

int main() {
	Rational	lhs;
	Rational	rhs;
	char		op;

	try {
		cin >> lhs >> op >> rhs;
	}
	catch (invalid_argument& cause) {
		cout << cause.what();
		return (1);
	}

	switch(op)	{
		case '+':
				cout << lhs + rhs;
				break;
		case '-':
				cout << lhs - rhs;
				break;
		case '*':
				cout << lhs * rhs;
				break;
		case '/':
			try	{
				cout << lhs / rhs;
			}
			catch (domain_error& cause)	{
				cout << cause.what();
				return (2);
			}
			break;
		default:
			break;
	}

	return 0;
}
