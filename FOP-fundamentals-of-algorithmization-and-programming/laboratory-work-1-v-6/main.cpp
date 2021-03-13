//comments only in the first laboratory for beginners
#include <bits/stdc++.h>  //подключение библиотеку

using namespace std;  //использование языкового пространства

double z1, z2, a, b, x, y, z;  //глобальные переменные

void lab_1();
void lab_2();
void lab_3();
double chek_double(string s);
//протатипы функций

int main()  //главная функция
{
    system("Color A");
    setlocale(LC_ALL, "Russian");

    string user_choice_1; //локальнае переменная
    while(true)  //постоянно просим пользователя ввести номер лабы
    {
        system("cls");
        printf("!Введите уровень лабы:\n1. Первый уровень;\n2. Второй уровень;\n3. Третий уровень.\n");
        cin >> user_choice_1;  //даем пользователю ввести переменную типа string

        if (user_choice_1 == "1")  //при вводе 1
            lab_1();  //запускаем функцию с первым вариантом лабы

        else if (user_choice_1 == "2")
            lab_2();

        else if (user_choice_1 == "3")
            lab_3();

        else  // для выхода из программы
            return 0; //возвращаем 0, завершая программу

        system("pause");
    }
}

void lab_1() //функция не возвращает значения (void)
{
    printf("Введите переменную для первого уровня(a):\n");
    cin >> a;
    z1 = cos(a) + cos(2 * a) + cos(6 * a) + cos(7 * a);  //вычисляем заданный пример, со введенными значением
    z2 = 4 * cos(a / 2) * cos(5 * a / 2) * cos(4 * a);
    printf("z1 = %.10f\nz2 = %.10f\nПервый уровень выполнен!\n", z1, z2);  //выводим ответ
}

void lab_2()
{
    printf("Введите переменную для второго уровня(a):\n");
    cin >> a;
    if (a >= 0) {
        double z1_p1_p1 = (3 * a + 2) * (3 * a + 2) - 24 * a;

        if(z1_p1_p1 >= 0) {
            double z1_p1 = sqrt(z1_p1_p1);
            double z1_p2 = 3 * sqrt(a) - 2 / sqrt(a);

            if(z1_p2 != 0)
                z1 = z1_p1 / z1_p2;
            else
                printf("Что-то пошло не так. На ноль делить НЕЛЬЗЯ.\n");
        }
        else
            printf("Что-то пошло не так. Корень из отрицательного числа вычесть НЕЛЬЗЯ.\n");

        z2 = - sqrt(a);
        printf("z1 = %.10f\nz2 = %.10f\nВторой уровень выполнен!\n", z1, z2);
    }
    else
        printf("Что-то пошло не так. Корень из отрицательного числа вычесть НЕЛЬЗЯ.\n");
        //функция завершилась, компилятор уходит обратно в функцию main
}

void lab_3()
{
    printf("Введите переменные для третьего уровня(x, y, z):\n");
    cin >> x >> y >> z;
    if(x >= 0) {
        if (z <= 1 && z >= -1) {

            double b_p1 = 10 * (double(pow(x, 1.0/3)) + double(pow(x, y + 2)));

            if (b_p1 >= 0) {
                double b_p1_e = sqrt(b_p1);
                double asinz = asin(z);
                double b_p2 = double(asinz * asinz) - abs(double(x - y));

                b = b_p1_e * b_p2;
                printf("%.10f\nТретий уровень выполнен!\n", b);
            }

            else
                printf("Что-то пошло не так. Корень из отрицательного числа вычесть НЕЛЬЗЯ.\n");
        }
        else
            printf("Что-то пошло не так. Z ДОЛЖЕН БЫТЬ от -1 до 1.\n");
    }
    else
        printf("Что-то пошло не так. Корень из отрицательного числа вычесть НЕЛЬЗЯ.\n");
}

