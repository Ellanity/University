#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>

#define PI 3.1415926535
#define SCP 0.707107781186

using namespace std;

int main()
{
    system("Color A");
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    printf("Введите размер одномерного массива:\n");
    int lenth;
    cin >> lenth;

    int arr[lenth];

    printf("Ввести значения элементов:\n1. Вручную с клавиатуры\n2. Случайно программно\n");
    int choice;
    cin >> choice;

    int minmin = lenth + 99, maxmin = -1;

    if(choice == 1)

        for (int i = 0; i < lenth; i++)
        {
            cin >> arr[i];

            if (arr[i] < 0)
            {
                if(i < minmin)
                    minmin = i;
                if(i > maxmin)
                    maxmin = i;
            }
        }


    else if(choice == 2)

        for (int i = 0; i < lenth; i++)
        {
            arr[i] = rand();
            int sign = rand();

            if (sign % 2 == 1)
                arr[i] = -arr[i];

            if (arr[i] < 0)
            {
                if(i < minmin)
                    minmin = i;
                if(i > maxmin)
                    maxmin = i;
            }
        }

    else
        return 0;

    if (minmin == lenth + 99 || maxmin == -1)
    {
        printf("В массиве меньше двух отрицательных элементов.\n");
        return 0;
    }

    if (abs(minmin - maxmin) == 1)
    {
        printf("Между первым и последним отрицательными элементами массива нет элементов.\n");
        return 0;
    }

    printf("Первый отрицательный элемент в массиве с индексом %d равен %d\nПоследний отрицательный элемент в массиве с индексом %d равен %d\n", minmin + 1, arr[minmin], maxmin + 1, arr[maxmin]);

    if(choice == 2)
        printf("Имеющийся одномерный массив:\n");

    long long product = 1;

    for (int i = 0; i < lenth; i++)
    {
        if (i < maxmin && i > minmin)
            product *= arr[i];
        if(choice == 2)
        {
            printf("%d ", arr[i]);
            if (i == lenth - 1)
                printf("\n");
        }
    }

    printf("Ответ: %lld\n", product);

    return 0;
}
