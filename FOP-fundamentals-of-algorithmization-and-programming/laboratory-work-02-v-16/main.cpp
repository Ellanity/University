#include <bits/stdc++.h>

using namespace std;

void lab_(int num_of_func);

int main()
{
    setlocale(LC_ALL, "Russian");
    system("Color A");
    while(true)
    {
        system("cls");
        printf("Выберите функцию для вычисления:\n1. 2X\n2. X^2\n3. X/3\n*Введите только цифру\n");
        short int func;
        cin >> func;

        if (func == 1)
            lab_(1);
        else if (func == 2)
            lab_(2);
        else if (func == 3)
            lab_(3);
        else
            return 0;

        system("pause");
    }
}

void lab_(int fun_num)
{
    printf("Введите аргумент Z:\n");
    double z, x;
    cin >> z;
    if (z > 1)
    {
        x = 1 / sqrt(z - 1);
        printf("1) Так как значение Z больше 1, X будет равен X = 1 / sqrt(Z - 1)\n X = %.10f\n", x);
    }
    else
    {
        x = z * z + 1;
        printf("1) Так как значение Z больше 1, X будет равен X = Z * Z + 1\n X = %.10f\n", x);
    }
    double a, c;
    printf("Введите дополнительные аргументы A и C:\n");
    cin >> a >> c;
    if (fun_num == 1)
    {
        printf("2) Вы выбрали f(X) = 2X \n\n");
        double ans = a * log(abs(x)) + exp(x);
        double ans_p2 = (2 * x) * (2 * x) - 1;
        if(ans_p2 <= 1 && ans_p2 >= -1)
        {
            double sinf = sin(ans_p2);
            ans += c * sinf * sinf * sinf;
            printf("Ответ: %.10f\n", ans);
        }
        else
            printf("Невозможно вычислить\n", ans);
    }
    if (fun_num == 2)
    {
        printf("2) Вы выбрали f(X) = X^2 \n\n");
        double ans = a * log(abs(x)) + exp(x);
        double ans_p2 = (x * x) * (x * x) - 1;
        if(ans_p2 <= 1 && ans_p2 >= -1)
        {
            double sinf = sin(ans_p2);
            ans += c * sinf * sinf * sinf;
            printf("Ответ: %.10f\n", ans);
        }
        else
            printf("Невозможно вычислить\n", ans);
    }
    if (fun_num == 3)
    {
        printf("2) Вы выбрали f(X) = X^2 \n\n");
        double ans = a * log(abs(x)) + exp(x);
        double ans_p2 = (x / 3) * (x / 3) - 1;
        if(ans_p2 <= 1 && ans_p2 >= -1)
        {
            double sinf = sin(ans_p2);
            ans += c * sinf * sinf * sinf;
            printf("Ответ: %.10f\n", ans);
        }
        else
            printf("Невозможно вычислить\n", ans);
    }
}
