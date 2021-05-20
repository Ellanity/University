#include <iostream>
#include <vector>
#include <string>

using namespace std;

void point1(vector<string> A, vector<string> B);
void point2(vector<string> A, vector<string> B);
void point3(vector<string> A, vector<string> B);
void point4(vector<string> A, vector<string> B);
void point5(vector<string> A, vector<string> B);
void point6(vector<string> A, vector<string> B);
void point7(vector<string> A, vector<string> B);
void point8(vector<string> A);
void point9(vector<string> B);

pair <string, string> get_elements_tuple(string element);


int main()
{
    setlocale(LC_ALL, "Russian");

    vector <string> A, B; // Создание графиков.
    int na, nb; // Мощности графиков A и B.

    // Пользователь вводит мощность графика А.
    cout << "Введите мощность графика A [<15]: ";
    cin >> na;

       // Пользователь вводит элементы графика А.
    cout << "Введите график A: ";
    for (int i = 0; i < na; i++)
    {
        string element;
        cin >> element;
        A.push_back(element);
    }
    
    // Пользователь вводит мощность графика B.
    cout << "Введите мощность графика B [<15]: ";
    cin >> nb;

 

    // Пользователь вводит элементы графика B.
    cout << "Введите график B: ";
    for (int i = 0; i < nb; i++)
    {
        string element;
        cin >> element;
        B.push_back(element);
    }

    int choice = 0;
    // Программа будет выполняться до тех пор, пока пользователь не выберет пункт меню "Выход из программы".
    while (choice != 10)
    {
        // График А выводится на экран.
        cout << "график A: ";
        for (int i = 0; i < na; i++)
            cout << A[i] << " ";
        cout << "\n";
        // График B выводится на экран.
        cout << "график B: ";
        for (int i = 0; i < nb; i++)
            cout << B[i] << " ";
        cout << "\n";


        // Пользователь выбирает одну из предложенных операций.
        cout << "Какую операцию требуется выполнить? [Введите число]:\n" <<
            "1. Объединение\n" <<
            "2. Пересечение\n" <<
            "3. Разность A/B\n" <<
            "4. Разность B/A\n" <<
            "5. Симметрическая разность\n" <<
            "6. Композиция A&B\n" <<
            "7. Композиция B&A\n" <<
            "8. Инверсия A\n" <<
            "9. Инверсия B\n" <<
            "10. Выход из программы\n";

        cin >> choice;
        switch (choice)
        {
            // Если пользователь выбрал «Объединение», переходим к пункту 1.
        case 1:
            point1(A, B);
            break;
            // Если пользователь выбрал «Пересечение», переходим к пункту 2.
        case 2:
            point2(A, B);
            break;
            // Если пользователь выбрал «Разность А/В», переходим к пункту 3.
        case 3:
            point3(A, B);
            break;
            // Если пользователь выбрал «Разность В/А», переходим к пункту 4.
        case 4:
            point4(A, B);
            break;
            // Если пользователь выбрал «Симметрическая разность», переходим к пункту 5.
        case 5:
            point5(A, B);
            break;
            // Если пользователь выбрал «Дополнение А», переходим к пункту 6.
        case 6:
            point6(A, B);
            break;
            // Если пользователь выбрал «Дополнение В», переходим к пункту 7.
        case 7:
            point7(A, B);
            break;
            // Если пользователь выбрал «Произведение АхВ», переходим к пункту 8.
        case 8:
            point8(A);
            break;
            // Если пользователь выбрал «Произведение ВхА», переходим к пункту 9.
        case 9:
            point9(B);
            break;
            // Если пользователь выбрал «Выход из программы», происходит выход из цикла [завершение программы].
        case 10:
            cout << "[Exit]";
            break;
        default:
            choice = 10;
            break;
        }

        if (choice != 10)
        {
            system("pause");
            system("cls");
        }
    }

    // Выход из программы.
    return 0;
}


void point1(vector<string> A, vector<string> B)
{
    vector<string> C; // Программа создает пустой график С.

    // Выбирается первый элемент графика А.
    // Выбранный элемент графика А записывается в график С. 
    for (int i = 0; i < A.size(); i++)
        C.push_back(A[i]);

    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B.
    {
        for (int j = 0; j < A.size(); j++) // Выбираем первый элемент графика A.
        {
            if (B[i] == A[j]) // Если выбранный элемент графика А равен выбранному элементу графика В.
                break; // Выбираем следующий элемент графика B.

            // Если выбранный элемент графика А является последним и не равен выбранному элементу графика В.
            else if (j == A.size() - 1 && B[i] != A[j])
                C.push_back(B[i]); // Записываем выбранный элемент графика В в график С.

            // Если выбранный элемент графика А не равен выбранному элементу графика В, выбираем следующий элемент графика А. 
        }
        // Если выбранный элемент графика В является последним, выход из цикла.
    }

    // График С выводится на экран
    cout << "Объединение графиков A и B: ";
    for (int i = 0; i < C.size(); i++) // График С является объединением графиков А и В
        cout << C[i] << " ";
    cout << "\n";
}

void point2(vector<string> A, vector<string> B)
{
    vector<string> D; // Программа создает пустой график D.

    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B.
        for (int j = 0; j < A.size(); j++) // Выбираем элемент графика A.
            if (B[i] == A[j]) // Если выбранный элемент графика А равен выбранному элементу графика В.
                D.push_back(B[i]); // Выбранный элемент из графика В записывается в график D.

    // График D выводится на экран
    cout << "Пересечение графиков A и B: ";
    for (int i = 0; i < D.size(); i++) // График D является пересечением графиков А и В.
        cout << D[i] << " ";
    cout << "\n";
}

void point3(vector<string> A, vector<string> B)
{
    vector<string> E; // Программа создает пустой график E.

    for (int i = 0; i < A.size(); i++) // Выбираем элемент графика A.
    {
        for (int j = 0; j < B.size(); j++) // Выбираем элемент графика B.
        {
            if (A[i] == B[j]) // Если выбранный элемент графика А равен выбранному элементу графика В.
                break; // Выбираем следующий элемент графика A.

            // Если выбранный элемент графика А равен выбранному элементу графика В и не является последним
            else if (j == B.size() - 1 && B[j] != A[i])
                E.push_back(A[i]); // Записываем выбранный элемент графика В в график E.
        }
    }

    // График E выводится на экран
    cout << "Разность графиков A/B: ";
    for (int i = 0; i < E.size(); i++) // График Е является разностью графиков А и В.
        cout << E[i] << " ";
    cout << "\n";
}

void point4(vector<string> A, vector<string> B)
{
    vector<string> F; // Программа создает пустой график F.

    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B.
    {
        for (int j = 0; j < A.size(); j++) // Выбираем элемент графика A.
        {
            if (B[i] == A[j]) // Если выбранный элемент графика B равен выбранному элементу графика A.
                break; // Выбираем следующий элемент графика B.

            // Если выбранный элемент графика А равен выбранному элементу графика A и не является последним
            else if (j == A.size() - 1 && A[j] != B[i])
                F.push_back(B[i]); // Записываем выбранный элемент графика A в график F.
        }
    }

    // График F выводится на экран
    cout << "Разность графиков B/A: ";
    for (int i = 0; i < F.size(); i++) // График F является разностью графиков B и A
        cout << F[i] << " ";
    cout << "\n";
}

void point5(vector<string> A, vector<string> B)
{
    vector<string> G; // Программа создает пустой график G.

    for (int i = 0; i < A.size(); i++) // Выбираем элемент графика A.
    {
        for (int j = 0; j < B.size(); j++) // Выбираем элемент графика B.
        {
            if (A[i] == B[j]) // Если выбранный элемент графика А равен выбранному элементу графика В.
                break; // Выбираем следующий элемент графика A.

            // Если выбранный элемент графика А равен выбранному элементу графика В и не является последним
            else if (j == B.size() - 1 && B[j] != A[i])
                G.push_back(A[i]); // Записываем выбранный элемент графика В в график G.
        }
    }

    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B.
    {
        for (int j = 0; j < A.size(); j++) // Выбираем элемент графика A.
        {
            if (B[i] == A[j]) // Если выбранный элемент графика B равен выбранному элементу графика A.
                break; // Выбираем следующий элемент графика B.

            // Если выбранный элемент графика А равен выбранному элементу графика A и не является последним
            else if (j == A.size() - 1 && A[j] != B[i])
                G.push_back(B[i]); // Записываем выбранный элемент графика A в график G.
        }
    }

    // График G выводится на экран
    cout << "Симметрическая разность графиков A и B: ";
    for (int i = 0; i < G.size(); i++) // График G является разностью графиков B и A
        cout << G[i] << " ";
    cout << "\n";
}

void point6(vector<string> A, vector<string> B)
{
    vector<string> H; // Программа создает пустой график Н.

    for (int i = 0; i < A.size(); i++) // Выбираем элемент графика A. 
    {
        for (int j = 0; j < B.size(); j++) // Выбираем элемент графика B. 
        {
            // Если второй элемент выбранного кортежа графика A
            // равен первому элементу выбранного кортежа графика B. 
            if (get_elements_tuple(A[i]).second == get_elements_tuple(B[j]).first) {
                // Создаем кортеж из нужных элементов
                string el;
                // Первый элемент кортежа графика A
                el += "<" + get_elements_tuple(A[i]).first;
                // Второй элемент кортежа графика B
                el += "," + get_elements_tuple(B[j]).second + ">";

                //cout << A[i] << " & " << B[j] << " = " << el << "\n";

                bool was = false;
                for (int h = 0; h < H.size(); h++) {
                    if (H[h] == el) {
                        was = true; break;
                    }
                }
                if (!was)
                    H.push_back(el); // Элемент записывается в Н.
            }
        }
    }

    // График Н выводится на экран.
    cout << "Композиция графиков A&B: ";
    for (int i = 0; i < H.size(); i++) // График Н является композицией графиков A&B.
        cout << H[i] << " ";
    cout << "\n";
}

void point7(vector<string> A, vector<string> B)
{
    vector<string> I; // Программа создает пустой график I.

    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B. 
    {
        for (int j = 0; j < A.size(); j++) // Выбираем элемент графика A. 
        {
            // Если второй элемент выбранного кортежа графика B
            // равен первому элементу выбранного кортежа графика A. 
            if (get_elements_tuple(B[i]).second == get_elements_tuple(A[j]).first) {
                // Создаем кортеж из нужных элементов
                string el;
                // Первый элемент кортежа графика B
                el += "<" + get_elements_tuple(B[i]).first;
                // Второй элемент кортежа графика A
                el += "," + get_elements_tuple(A[j]).second + ">";

                bool was = false;
                for (int k = 0; k < I.size(); k++) {
                    if (I[k] == el) {
                        was = true; break;
                    }
                }
                if (!was)
                    I.push_back(el); // Элемент записывается в Н.
            }
        }
    }

    // График I выводится на экран.
    cout << "Композиция графиков B&A: ";
    for (int i = 0; i < I.size(); i++) // График I является композицией графиков B&A.
        cout << I[i] << " ";
    cout << "\n";
}

void point8(vector<string> A)
{
    vector <string> J;
    for (int i = 0; i < A.size(); i++) // Выбираем элемент графика A.
    {
        // Инвертируем элемент графика A
        string el;
        el += "<" + get_elements_tuple(A[i]).second;
        el += "," + get_elements_tuple(A[i]).first + ">";
        J.push_back(el); // Добавляем кортеж в график J.
    }

    // график J Выводится на экран.
    cout << "Инверсия графика A: ";
    for (int i = 0; i < J.size(); i++) // график J является инверсией графика A
        cout << J[i] << " ";
    cout << "\n";
}

void point9(vector<string> B)
{
    vector <string> K;
    for (int i = 0; i < B.size(); i++) // Выбираем элемент графика B.
    {
        // Инвертируем элемент графика B
        string el;
        el += "<" + get_elements_tuple(B[i]).second;
        el += "," + get_elements_tuple(B[i]).first + ">";
        K.push_back(el); // Добавляем кортеж в график K.
    }

    // график K Выводится на экран.
    cout << "Инверсия графика B: ";
    for (int i = 0; i < K.size(); i++) // график K является инверсией графика B
        cout << K[i] << " ";
    cout << "\n";
}

pair <string, string> get_elements_tuple(string element) {
    pair <string, string> el;
    bool separated = false;
    for (int i = 1; i < element.size() - 1; i++) {
        // В зависимости от того встретил ли цикл запятую
        if (element[i] == ',')
            separated = true;
        // Добавляем символ к первому элементу  
        else if (!separated)
            el.first += element[i];
        // Добавляем символ ко второму элементу
        else if (separated)
            el.second += element[i];
    }
    return el;
}

/*
3 3
<1,2> <2,3> <3,4>
<2,5> <2,3> <4,6>
*/

// Куча говнокода, работает только если все 
// элементы в графиках - это кортежи ровно по 2 простых элемента
