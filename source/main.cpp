#include "main.h"

extern FILE* file_dump;
extern FILE* file_htm;

int main()
{
    fprintf(file_dump, "digraph {\n");
    
    List_t list = {};
    ListCtor(&list, 20);
    ListAppendAfter(&list, 0, 10);

    // ListDump(&list);

    ListAppendAfter(&list, 1, 30);
    ListAppendBefore(&list, 2, 20);
    ListAppendAfter(&list, 2, 40);
    ListAppendAfter(&list, 4, 50);
    ListAppendAfter(&list, 5, 60);
    
    
    ListAppendAfter(&list, 3, 91);
    ListDelete(&list, 1);

    ListDumpImage(&list);
    ListDumpWeb(&list);

    printf("%d\n", list.data[1]);

    ListDtor(&list);

    fprintf(file_dump, "}");
    fclose(file_dump);
}