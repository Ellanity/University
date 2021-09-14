#include <iostream>
#include <math.h>
#define uns unsigned
#define dbl double

using namespace std;

void result(dbl left, dbl right, dbl e, dbl dec);
double resultRec(dbl left, dbl right, dbl e, dbl dec);
double func(dbl x);

int main()
{
	dbl e;
	cin >> e;
	
	dbl left = 2, right = 6, dec = e / 20;
	 
	result(left, right, e, dec);
	dbl ans = resultRec(left, right, e, dec);
	cout << "The minimum of the func with recursion: " << ans;
}

double func(dbl x)
{
	return 7 * pow(sin(x), 2);
}

void result(dbl left, dbl right, dbl e, dbl dec)
{
	dbl x1 = ((left + right) / 2) + dec;
	dbl x2 = ((left + right) / 2) - dec;
	dbl f1 = func(x1);
	dbl f2 = func(x2);

	while ((f1 / e > dec) && (f2 / e > dec))
	{
		x1 = ((left + right) / 2) + dec;
		x2 = ((left + right) / 2) - dec;

		f1 = func(x1);
		f2 = func(x2);

		if (f1 < f2)
			left = x1;
		else
			right = x2;
		//cout << "left: " << left << " right: " << right << " dec: " << dec << " min-func: " << min(f1, f2) << "\n";
	}

	cout << "The minimum of the func without recursion: " << min(f1, f2) << "\n";
}

double resultRec(dbl left, dbl right, dbl e, dbl dec)
{
	dbl x1 = ((left + right) / 2) + dec;
	dbl x2 = ((left + right) / 2) - dec;
	dbl f1 = func(x1);
	dbl f2 = func(x2);

	dbl ans = min(f1, f2);

	if ((f1 / e > dec) && (f2 / e > dec))
	{
		if (f1 < f2)
			left = x1;
		else
			right = x2;
		//cout << "left: " << left << " right: " << right << " dec: " << dec << " min-func: " << min(f1, f2) << "\n";
		ans = resultRec(left, right, e, dec);
		//cout << ans << "\n";
	}
	return ans;
}