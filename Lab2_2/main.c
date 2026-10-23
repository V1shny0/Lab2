#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ecs 0.00001

void EnterData(double *wa, double *wb, int *wn, int *wvar);
double F(double x);
double LeftRectangl(double a, double b, int n);
double RightRectangl(double a, double b, int n);
double Trapeze(double a, double b, int n);
double Parabola(double a, double b, int n);
void Delta(double a, double b, double (*Method)(double, double, int));
void PrintRow();
void Var5(double *wa, double *wb, int num);
void Table(int num, double a, double b, int n);
void Header();

int main()
{
    double a, b, h, In;
    int n, var;

    EnterData(&a, &b, &n, &var);

    switch(var)
    {
        case 1:
            In = LeftRectangl(a, b, n);

            system("cls");

            printf("In = %lf  n = %d", In, n);

            Delta(a, b, LeftRectangl);

            break;

        case 2:
            In = RightRectangl(a, b, n);

            system("cls");

            printf("In = %lf  n = %d", In, n);

            Delta(a, b, RightRectangl);

            break;

        case 3:
            In = Trapeze(a, b, n);

            system("cls");

            printf("In = %lf  n = %d", In, n);

            Delta(a, b, Trapeze);

            break;

        case 4:
            In = Parabola(a, b, n);

            system("cls");

            printf("In = %lf  n = %d", In, n);

            Delta(a, b, Parabola);

            break;

        case 5:
            double a2, b2, a3, b3, a4, b4;

            Var5(&a2, &b2, 2);
            Var5(&a3, &b3, 3);
            Var5(&a4, &b4, 4);

            system("cls");

            Header();
            PrintRow();
            Table(1, a, b, n);
            PrintRow();
            Table(2, a2, b2, n);
            PrintRow();
            Table(3, a3, b3, n);
            PrintRow();
            Table(4, a4, b4, n);
            PrintRow();
    }


    return 0;
}

////////////////////////////////////////////////////////////////////////////////////

void EnterData(double *wa, double *wb, int *wn, int *wvar)
{
    printf("Enter a:");
    scanf("%lf", wa);
    printf("Enter b:");
    scanf("%lf", wb);

    while (*wa >= *wb || (*wa <= 1 && *wb >= 1) || (*wa <= -1 && *wb >= -1))
    {
            printf("Interval can not contain 1 or -1, and b must be more and not be equal to a");
            printf("\nEnter a again:");
            scanf("%lf", wa);
            printf("Enter b again:");
            scanf("%lf", wb);
    }

    printf("Enter n:");
    scanf("%d", wn);

    while (*wn == 0 || *wn % 2 != 0)
    {
        printf("n must be more then 0 and even, try again:");
        scanf("%d", wn);
    }

    printf("Enter method:");
    scanf("%d", wvar);

    while(*wvar < 1 || *wvar > 5)
    {
        printf("Here only 4 methods, try again:");
        scanf("%d", wvar);
    }
}

////////////////////////////////////////////////////////////////////////////////////

double F(double x)
{
    return 1 / (pow(x, 2) - 1);
}

////////////////////////////////////////////////////////////////////////////////////

double LeftRectangl(double a, double b, int n)
{
    double x, h, sum;
    h = (b - a) / n;
    sum = 0;
    x = a;

    for(int i = 0; i <= n - 1; i++)
    {
        sum += F(x);
        x += h;
    }

    return h * sum;
}

////////////////////////////////////////////////////////////////////////////////////

double RightRectangl(double a, double b, int n)
{
    double x, h, sum;
    h = (b - a) / n;
    sum = 0;
    x = a;

    for(int i = 1; i <= n; i++)
    {
        x += h;
        sum += F(x);
    }

    return h * sum;
}

////////////////////////////////////////////////////////////////////////////////////

double Trapeze(double a, double b, int n)
{
    double x, h, sum;
    h = (b - a) / n;
    x = a;
    sum = (F(x) + F(b)) / 2;

    for(int i = 1; i <= n -1; i++)
    {
        x += h;
        sum += F(x);
    }

    return h * sum;
}

////////////////////////////////////////////////////////////////////////////////////

double Parabola(double a, double b, int n)
{
    double x, h, sum;
    h = (b - a) / n;
    x = a;
    sum = F(x) + F(b);

    for(int i = 1; i <= n - 1; i++)
    {
        x += h;
        if(i % 2 == 0)
        {
            sum += 2 * F(x);
        }
        else
        {
            sum += 4 * F(x);
        }
    }

    return (h * sum) / 3;
}

////////////////////////////////////////////////////////////////////////////////////

void Delta(double a, double b, double (*Method)(double, double, int))
{
    double In1, In2;
    int n1, n2;

    n1 = 2;
    do
    {
        In1 = Method(a, b, n1);
        n2 = n1 + 2;
        In2 = Method(a, b, n2);
        n1 += 2;
    }while(fabs(In2 - In1) > ecs);

    printf("\nIn1 = %lf  n1 = %d", In1, n1 - 2);
    printf("\nIn2 = %lf  n2 = %d", In2, n2);
}

////////////////////////////////////////////////////////////////////////////////////

void PrintRow()
{
    printf("\n+---------------+---------------+---------------+---------------+---------------+");
}

////////////////////////////////////////////////////////////////////////////////////

void Var5(double *wa, double *wb, int num)
{
    printf("Interval %d, enter a:", num);
    scanf("%lf", wa);
    printf("Interval %d, enter b:", num);
    scanf("%lf", wb);

    while (*wa >= *wb || (*wa <= 1 && *wb >= 1) || (*wa <= -1 && *wb >= -1))
    {
            printf("Interval can not contain 1 or -1, and b must be more and not be equal to a");
            printf("\nInterval %d, enter a again:", num);
            scanf("%lf", wa);
            printf("Interval %d, enter b again:", num);
            scanf("%lf", wb);
    }
}

////////////////////////////////////////////////////////////////////////////////////

void Table(int num, double a, double b, int n)
{
    int W;

    W = 15;

    printf("\n|%*d|%*lf|%*lf|%*lf|%*lf|", W, num, W, LeftRectangl(a, b, n), W, RightRectangl(a, b, n), W, Trapeze(a, b, n), W, Parabola(a, b, n));
}

////////////////////////////////////////////////////////////////////////////////////

void Header()
{
    printf("+---------------+---------------+---------------+---------------+---------------+");
    printf("\n|       N       | Left Rectangl |Right Rectangl |    Trapeze    |   Parabola    |");
}
