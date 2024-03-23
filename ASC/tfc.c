#include <stdio.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(linker, "/INCLUDE:_printf")
#pragma comment(linker, "/INCLUDE:_scanf")


void st(int *lenPoz, int *lenNeg, int nr_nega[], int nr_pozi[]);

int nr_pozi[50], nr_nega[50];

int main()
{
    int lenPoz, lenNeg;
    st(&lenPoz, &lenNeg, nr_nega, nr_pozi);
    printf("Numerele pozitive sunt : ");
    for (int i = 0; i < lenPoz; i++)
        printf("%d", nr_pozi[i]);
    printf("\nNumerele negative sunt : ");
    for (int i = 0; i < lenNeg; i++)
        printf("%d", nr_nega[i]);
    return 0;
}
