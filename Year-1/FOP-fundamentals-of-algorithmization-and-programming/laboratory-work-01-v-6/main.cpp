//comments only in the first laboratory for beginners
#include <bits/stdc++.h>  //����������� ����������

using namespace std;  //������������� ��������� ������������

double z1, z2, a, b, x, y, z;  //���������� ����������

void lab_1();
void lab_2();
void lab_3();
double chek_double(string s);
//��������� �������

int main()  //������� �������
{
    system("Color A");
    setlocale(LC_ALL, "Russian");

    string user_choice_1; //��������� ����������
    while(true)  //��������� ������ ������������ ������ ����� ����
    {
        system("cls");
        printf("!������� ������� ����:\n1. ������ �������;\n2. ������ �������;\n3. ������ �������.\n");
        cin >> user_choice_1;  //���� ������������ ������ ���������� ���� string

        if (user_choice_1 == "1")  //��� ����� 1
            lab_1();  //��������� ������� � ������ ��������� ����

        else if (user_choice_1 == "2")
            lab_2();

        else if (user_choice_1 == "3")
            lab_3();

        else  // ��� ������ �� ���������
            return 0; //���������� 0, �������� ���������

        system("pause");
    }
}

void lab_1() //������� �� ���������� �������� (void)
{
    printf("������� ���������� ��� ������� ������(a):\n");
    cin >> a;
    z1 = cos(a) + cos(2 * a) + cos(6 * a) + cos(7 * a);  //��������� �������� ������, �� ���������� ���������
    z2 = 4 * cos(a / 2) * cos(5 * a / 2) * cos(4 * a);
    printf("z1 = %.10f\nz2 = %.10f\n������ ������� ��������!\n", z1, z2);  //������� �����
}

void lab_2()
{
    printf("������� ���������� ��� ������� ������(a):\n");
    cin >> a;
    if (a >= 0) {
        double z1_p1_p1 = (3 * a + 2) * (3 * a + 2) - 24 * a;

        if(z1_p1_p1 >= 0) {
            double z1_p1 = sqrt(z1_p1_p1);
            double z1_p2 = 3 * sqrt(a) - 2 / sqrt(a);

            if(z1_p2 != 0)
                z1 = z1_p1 / z1_p2;
            else
                printf("���-�� ����� �� ���. �� ���� ������ ������.\n");
        }
        else
            printf("���-�� ����� �� ���. ������ �� �������������� ����� ������� ������.\n");

        z2 = - sqrt(a);
        printf("z1 = %.10f\nz2 = %.10f\n������ ������� ��������!\n", z1, z2);
    }
    else
        printf("���-�� ����� �� ���. ������ �� �������������� ����� ������� ������.\n");
        //������� �����������, ���������� ������ ������� � ������� main
}

void lab_3()
{
    printf("������� ���������� ��� �������� ������(x, y, z):\n");
    cin >> x >> y >> z;
    if(x >= 0) {
        if (z <= 1 && z >= -1) {

            double b_p1 = 10 * (double(pow(x, 1.0/3)) + double(pow(x, y + 2)));

            if (b_p1 >= 0) {
                double b_p1_e = sqrt(b_p1);
                double asinz = asin(z);
                double b_p2 = double(asinz * asinz) - abs(double(x - y));

                b = b_p1_e * b_p2;
                printf("%.10f\n������ ������� ��������!\n", b);
            }

            else
                printf("���-�� ����� �� ���. ������ �� �������������� ����� ������� ������.\n");
        }
        else
            printf("���-�� ����� �� ���. Z ������ ���� �� -1 �� 1.\n");
    }
    else
        printf("���-�� ����� �� ���. ������ �� �������������� ����� ������� ������.\n");
}

