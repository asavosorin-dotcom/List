#include "main.h"

extern FILE* file_htm;

// линеаризация

// классический список next
// сравнить скорость 
// лучше переписывать в другой блок памяти (так быстрее)
// реалокация вверх 
// реалокация вниз 

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

    ListDump(&list, "List OK");
        
    // list.next[0] = list.free;
    // ListVerify(&list, __LINE__, __func__);

    // ListDump(&list, "List cicle free");
    // LISTAppendBefore(list, 1, 10);

    // LISTDelete(list, 1);
    // LISTDelete(list, 3);
    // LISTDelete(list, 5);

    // ListDump(&list, "After Delete");

    ListDtor(&list);
    fclose(file_htm);

    return 0;
}