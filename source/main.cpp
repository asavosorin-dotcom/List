#include "main.h"

extern FILE* file_htm;

// проверка на зациклинность всех трех списков
// печать ошибочного элемента

int main()
{
    
    List_t list = {};
    LISTCTOR(list, 10)

    LISTAppendAfter(list, 0, 10);
    LISTAppendAfter(list, 1, 10);

    LISTAppendBefore(list, 1, 10);
    LISTAppendBefore(list, 1, 10);
    LISTAppendBefore(list, 1, 10);
    LISTAppendBefore(list, 1, 10);
    LISTAppendBefore(list, 1, 10);
    ListDump(&list, "After AppendBefore");

    LISTDelete(list, 1);
    LISTDelete(list, 3);
    LISTDelete(list, 5);

    ListDump(&list, "After Delete");

    ListDtor(&list);
    fclose(file_htm);

    return 0;
}