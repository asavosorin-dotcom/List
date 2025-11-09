#include "main.h"

extern FILE* file_htm;



// линеаризация
// классический список
// сравнить скорость 
// лучше переписывать в другой блок памяти (так быстрее)
// реалокация вверх 
// реалокация вниз 

int main()
{
    
    // List_t list = {};
    // LISTCTOR(list, 10)

    // LISTAppendAfter(list, 0, 10);
    // LISTAppendAfter(list, 1, 10);

    // LISTAppendBefore(list, 1, 10);
    // LISTAppendBefore(list, 2, 20);
    // LISTAppendBefore(list, 3, 30);
    // LISTAppendBefore(list, 4, 40);
    // LISTAppendBefore(list, 5, 50);
    
    // ListDump(&list, "List 5 elements");

    // LISTDelete(list, 3);

    // ListDump(&list, "List after delete");
    
    
    // ListLineal(&list);
    // ListDump(&list, "List after lineal");

    // LISTAppendBefore(list, 2, 20);
    // LISTAppendBefore(list, 3, 30);
    // LISTAppendBefore(list, 4, 40);
    // LISTAppendBefore(list, 5, 50);

    // ListDump(&list, "List after realloc");

    // LISTDelete(list, 1);
    // LISTDelete(list, 2);
    // LISTDelete(list, 4);
    // LISTDelete(list, 5);
    // LISTDelete(list, 6);
    // LISTDelete(list, 7);


    // ListDump(&list, "List after realloc");

    // // list.next[0] = list.free;
    // // ListVerify(&list, __LINE__, __func__);

    // // ListDump(&list, "List cicle free"); 
    // // LISTAppendBefore(list, 1, 10);

    // // LISTDelete(list, 1);
    // // LISTDelete(list, 3);
    // // LISTDelete(list, 5);

    // // ListDump(&list, "After Delete");

    // // free(lin_data);
    // ListDtor(&list);

    // start = ... число тактов
    // end = ... xbckj nfrnjd
    // два момента их разность число тактов

    // ListDump(elem0, "Before delete");


    // ListDump(elem0, "After delete");

    TestTime();

    fclose(file_htm);

    return 0;
}

void TestTime(void)
{
    List_t list = {};
    LISTCTOR(list, 10)

    // что выключал, что включал

    unsigned long long start1 = __rdtsc();
    LISTAppendAfter(list, 0, 10);
    LISTAppendAfter(list, 1, 10);
    LISTAppendBefore(list, 1, 10);
    LISTAppendBefore(list, 2, 20);
    LISTAppendBefore(list, 3, 30);
    LISTDelete(list, 5);
    LISTDelete(list, 4);
    LISTDelete(list, 3);
    LISTDelete(list, 2);
    LISTDelete(list, 1);

    unsigned long long end1 = __rdtsc();

    ListDtor(&list);

    printf("Counter takts = %llu\n", end1 - start1);

    List_elem_t* elem0 = ListElemCtor(0);

    unsigned long long start = __rdtsc();
    ListInsertAfter(elem0, 1);    
    ListInsertAfter(elem0, 2);
    ListInsertAfter(elem0, 3);
    ListInsertAfter(elem0, 4);
    ListInsertAfter(elem0, 5);
    ListDeleteElem(elem0->next);
    ListDeleteElem(elem0->next);
    ListDeleteElem(elem0->next);
    ListDeleteElem(elem0->next);
    unsigned long long end = __rdtsc();

    printf("Count classic takts = %llu\n", end - start);

    ListDtor(elem0);
}