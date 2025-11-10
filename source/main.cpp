#include "main.h"

extern FILE* file_htm;

FILE* file_test = fopen("test_time.txt", "w");

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

    // ListDump(elem0, "Before delete");

    // ListDump(elem0, "After delete");

    List_elem_t* elem0 = ListElemCtor(0);
    ListInsertAfter(elem0, 15);
    ListInsertAfter(elem0, 25);
    ListInsertAfter(elem0, 35);
    ListInsertAfter(elem0, 45);

    ListDumpClassic(elem0, "check");
    ListDtorClassic(elem0);


    // TestTime();

    fclose(file_htm);
    fclose(file_test);

    return 0;
}

void TestTime(void)
{
    List_t list = {};
    LISTCTOR(list, 10)

    // что выключал, что включал
    fprintf(file_test, "Counter takts my list: \n");

    unsigned long long start1 = 0;
    unsigned long long end1 = 0;

    for (int j = 0; j < 10; j++)
    {
        start1 = __rdtsc();

        for (int i = 0; i < 10000; i++)
        {
            LISTAppendAfter(list, 0, 10);
            LISTDelete(list, 1);
        }

        end1 = __rdtsc();

        fprintf(file_test, "%llu\n", end1 - start1);
}

    ListDtor(&list);


    List_elem_t* elem0 = ListElemCtor(0);
    
    fprintf(file_test, "Count takts classic: \n");
    unsigned long long start = 0;
    unsigned long long end = 0;

    for (int j = 0; j < 10; j++)
    {
        start = __rdtsc();
    
        for (int i = 0; i < 10000; i++)
        {
            ListInsertAfter(elem0, 1);    
            ListDeleteElem(elem0->next);
        }

        end = __rdtsc();
        fprintf(file_test, "%llu\n", end - start);
    }


    ListDtorClassic(elem0);
}