#include <stdio.h>
#include <math.h>
float GT(int n)
{
    if (n == 1)
    {
        /* code */
        return 1;
    }
    return GT(n - 1) * n;
}

float LT(int x, int n)
{
}

float tinh(int x, float c)
{
    float sum = 0;
    int n = 1;
    while ((pow(x, n) / GT(n)) > c)
    {
        /* code */ 
        sum += 1 + pow(x, n) / GT(n);
        n++;
    }

    return sum;
}
int main()
{
    float c;
    int x;

    float resutl;
    printf("Nhập C: ");
    scanf("%f", &c);
    printf("Nhập X: ");
    scanf("%d", &x);
    printf("%f", tinh(x, c));
    return 0;
}