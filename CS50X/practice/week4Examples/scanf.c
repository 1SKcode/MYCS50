#include <stdio.h>

int main(int argc, char* argv[])
{
    int a;
    printf("Input: ");
    scanf("%d", &a);
    printf("%d\n", a);


    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);

    char* str = "2345resxc";
    printf("%s\n", str);
    return 0;
}
