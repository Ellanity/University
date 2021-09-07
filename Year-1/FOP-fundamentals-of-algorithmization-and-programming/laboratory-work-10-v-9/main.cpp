#include <iostream>
#define uns unsigned

using namespace std;

void result(uns n);
double resultRec(uns n, uns a);

int main()
{
	uns n;
	cin >> n;
	
	result(n);

	double ans = resultRec(n, 0);
	cout << ans;
}

void result(uns n)
{
	double ans = 0;
	for (uns i = n; i > 0; i--)
		ans = sqrt(i + ans);
	cout << ans << '\n';
}

double resultRec(uns n, uns a)
{
	double ans = sqrt(a + 1);
	if (a <= n)
	{
		a++;
		if (a < n)
			ans = sqrt(a + resultRec(n, a));
		/*cout << ans << "\n";*/
	}
	return ans;
}