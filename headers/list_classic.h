#ifndef _LIST_CLASSIC_
#define _LIST_CLASSIC_

#include <stdio.h>
#include <stdlib.h>


#define PRINT_IMAGE(...) fprintf(file_dump, __VA_ARGS__)
#define PRINT_HTM(...)   fprintf(file_htm, __VA_ARGS__)

typedef int List_data_t;

struct List_elem_t {
    List_data_t data;
    List_elem_t* next;
    List_elem_t* prev;
};

List_elem_t* ListElemCtor(List_data_t data);

List_elem_t* ListInsertAfter(List_elem_t* elem, List_data_t value);
List_elem_t* ListInsertBefore(List_elem_t* elem, List_data_t value);

void ListDumpElem(List_elem_t* elem, FILE* file_dump);
void ListDumpImage(List_elem_t* elem);
void ListDumpClassic (List_elem_t* elem, const char* text);

void ListDeleteElem(List_elem_t* elem);
void ListDtorClassic(List_elem_t* elem);
// вставка, удаление, уничтожение 

#endif