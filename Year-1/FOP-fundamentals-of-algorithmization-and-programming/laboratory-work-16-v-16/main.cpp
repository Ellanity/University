#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

double eps = 1e-7, h = 0.01;

// Функция 
double func(double x) {
	return ( (0.1 * pow(x, 3)) + pow(x, 2) - (10 * sin(x)) - 8 );
}

// Производная 1 порядка
double func1(double x) {
	return ( (0.3 * pow(x, 2)) + (2 * x) - (10 *cos(x)) );
}

// Производная 2 порядка
double func2(double x) {
	return ( (0.6 * x) + (10 * sin(x)) + 2 );
}

void root(vector <double>* ansv, double a, double b);

int main() {
	setlocale(LC_ALL, "Russian");
	double a = -4.0, b = 4.0;
	
	vector <double> ansv;

	for (double i = a; i <= b; i = i + h)
		if (func(i) * func(i + h) < 0)
			root(&ansv, i, i + h);

	for (int i = 0; i < ansv.size(); i++)
		cout << "Корень: " << ansv[i] << "\nЗначение функции: " << func(ansv[i]) << "\n";

	return 0;
}


// | 16.	| 0.1x^3 + x^2 - 10sin(x) -8	| –4 | 4 | Метод Ньютона(касательных)	|
// | func =	(1/10)*(x^3)+x^2-10*sin(x)-8	|	func1 = 0.3*x^2 + 2*x - 10*cos(x)	| func2 = 0.6*x+10*sin(x)+2 |
void root(vector <double>* ansv, double a, double b) {
	
	double x0 = a, x = b;
	int i = 1;
	
	/*if (func(a) * func2(a) > 0)
		x0 = a; // для выбора начальной точки проверяем func(x0)*func2(x0)>0 ?
	else
		x0 = b;*/

	x = x0 - func(x0) / func1(x0); // считаем первое приближение

	//cout << "Итерация " << i << "\tx0: " << x0 << "\tx: " << x << "\n";

	while (fabs(x0 - x) > eps){
		i++;
		x0 = x;
		x = x0 - func(x) / func1(x);
		//cout << "Итерация " << i << "\tx0: " << x0 << "\tx: " << x << "\n";
	}
	//cout << "\n";
	ansv->push_back(x);
}

// Literature
//https://www.youtube.com/watch?v=GxnUbUNS9NM
//http://statistica.ru/branches-maths/chislennye-metody-resheniya-uravneniy/#s3b
//https://e-maxx.ru/algo/roots_newton
//https://pastebin.com/9SEYP91p