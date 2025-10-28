#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "colors.h"

typedef struct {
    int*   data;
    int*   next;
    int*   prev;

    int    head;
    int    tail;
    int    free;

    size_t size;
} List_t;

void ListCtor (List_t* list, size_t size);
void ListDtor (List_t* list);

void ListAppendAfter(List_t* list, int index, int elem);
void ListAppendBefore(List_t* list, int index, int elem);
void ListDelete(List_t* list, int index);

void ListDumpImage (List_t* list);
void ListDumpWeb   (List_t* list);

void ListDataInit(List_t* list);
void ListNextInit(List_t* list);
void ListPrevInit(List_t* list);

#define FREE(point) free(point); point = NULL;

#define POISON 0xDEADDED

#define PRINT_IMAGE(...) fprintf(file_dump, __VA_ARGS__)
#define PRINT_HTM(...) fprintf(file_htm, __VA_ARGS__)

#define SET_GREEN_NODE ", fillcolor = \"#C0FFC0\""
#define SET_RED_NODE ", fillcolor = \"#FFC0C0\""
#define GREEN_NODE 1

#define PRINT_DEBUG(COLOR, ...) printf(COLOR, ":%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(RESET);

#endif
