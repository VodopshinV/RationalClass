#include<iostream>
#include<exception>
using namespace std;

class Rational
{
public:
	Rational()
	{
		p = 0;
		q = 1;
	};
	Rational(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw invalid_argument("Invalid argument");
		}
		else
		{
			if (denominator < 0) {
				if (numerator < 0) {
					denominator = abs(denominator);
					numerator = abs(numerator);
				}
				else {
					denominator = abs(denominator);
					numerator = numerator - 2 * numerator;
				}
			}
			if (numerator == 0) {
				denominator = 1;
			}
			int nod = divider(abs(numerator), abs(denominator));
			p = numerator / nod;
			q = denominator / nod;
		}
	}

	int Numerator() const
	{
		return p;
	}

	int Denominator() const
	{
		return q;
	}

private:
	int p;
	int q;
	int divider(int a, int b)
	{
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		} 
		return a + b;
	}
};

const bool operator==(const Rational& lhs, const Rational& rhs)
{
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rational operator +(const Rational& lhs, const Rational& rhs)
{
	int p = (lhs.Numerator() * rhs.Denominator()) + (rhs.Numerator() * lhs.Denominator());
	int q = rhs.Denominator() * lhs.Denominator();
	return Rational(p,q);
}

Rational operator -(const Rational& lhs, const Rational& rhs)
{
	int p = (lhs.Numerator() * rhs.Denominator()) - (rhs.Numerator() * lhs.Denominator());
	int q = lhs.Denominator() * rhs.Denominator();
	return Rational(p, q);
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return Rational((lhs.Numerator() * rhs.Numerator()), (lhs.Denominator() * rhs.Denominator()));
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	if (rhs.Numerator() == 0)
	{
		throw domain_error("Division by zero");
	}
	else
	{
		return Rational((lhs.Numerator() * rhs.Denominator()), (rhs.Denominator() * lhs.Numerator()));
	}
}

istream& operator>>(istream& stream, Rational& rational)
{
	int p, q;
	char separ;
	if(stream >> p && stream>>separ && stream >> q && separ =='/')
	{
		if (!stream.fail())
		{
			rational = { p, q };
		}
		//stream.clear();
		
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << '/' << rational.Denominator();
	return stream;
}

bool operator>(Rational lhs, Rational rhs)
{
	return (lhs.Numerator() / (double)(lhs.Denominator()) > rhs.Numerator() / (double)(rhs.Denominator()));
}

bool operator<(Rational lhs, Rational rhs)
{
	return (lhs.Numerator() / (double)(lhs.Denominator()) < rhs.Numerator() / (double)(rhs.Denominator()));
}

int main() {
	try {
		Rational x, y;
		char operation;
		cin >> x >> operation >> y;

		switch (operation)
		{
		case '+': cout << x + y; break;

		case '-': cout << x - y; break;

		case '*': cout << x * y; break;

		case '/': cout << x / y; break;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}

	system("pause");
	return 0;
}