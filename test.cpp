#include <stdio.h>

int main()
{
    FILE *fp = fopen("test.txt", "a");
    if (!fp) return 1;

    fprintf(fp, "hello world\n");

    return 1;
}