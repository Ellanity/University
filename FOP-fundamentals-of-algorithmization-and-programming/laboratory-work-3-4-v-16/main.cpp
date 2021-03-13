#include <bits/stdc++.h>
#define PI 3.1415926535
#define SCP 0.707107781186

using namespace std;

void Res_out(double ans1, double ans2, double ans3);

int main()
{
    system("Color A");
    setlocale(LC_ALL, "Russian");

    printf("Введите значения для лабараторной через пробел(a, b, h, n), где:\na - первоначальное значение x\nb - конечное значение x\nh - шаг значения x\nn - конечное значение аргумента суммы.\n");
    double a, b, h, n;
    cin >> a >> b >> h >> n;
    double x;
    for (x = a; x <= b; x += h)
    {
        double sx = 0, yx = 0;
        for(int k = 0; k <= n; k++)
        {
            long long factk = 1;
            for (int j = 1; j <= k; j++)
                factk *= j;
            sx += cos(k * PI / 4) * double(pow(x, k)) / factk;
        }

        yx = cos(x * SCP) * exp(x * SCP);

        Res_out(x, sx, yx);
        //printf("X = %.4f S(X) = %.4f Y(X) = %.4f |Y(X) - S(X)| = %.4f \n", x, sx, yx, abs(yx - sx));
    }
    return 0;
}

void Res_out(double ans1, double ans2, double ans3)
{
    printf("X = %.4f S(X) = %.4f Y(X) = %.4f |Y(X) - S(X)| = %.4f \n", ans1, ans2, ans3, abs(ans3 - ans2));
}
