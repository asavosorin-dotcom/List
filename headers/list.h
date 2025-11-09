#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "colors.h"

// #define DEBUG_LIST

#ifdef DEBUG_LIST
    #define ONDEBUG_LIST(...) __VA_ARGS__
#else
    #define ONDEBUG_LIST(...) 
#endif

typedef struct {
    const char* name;
    const char* funcname;
    const char* filename;
    int   line;
} Passport_t;

typedef struct {
    int*   data;
    int*   next;
    int*   prev;

    int    free;

    int count_elem = 0;
    size_t size;

    Passport_t passport;
} List_t;

void ListCtor(List_t* list, size_t size, int line, const char* filename, const char* funcname);
void ListDtor (List_t* list);

#ifdef DEBUG_LIST
    int ListAppendAfter  (List_t* list, int index, int elem, const char* filename, int line);
    int ListAppendBefore (List_t* list, int index, int elem, const char* filename, int line);
    int ListDelete       (List_t* list, int index, const char* filename, int line);
#else
    int ListAppendAfter  (List_t* list, int index, int elem);
    int ListAppendBefore (List_t* list, int index, int elem);
    int ListDelete       (List_t* list, int index);
#endif

void ListLineal(List_t* list);

void ListDumpImage (List_t* list);
void ListDump (List_t* list, const char* text);

int ListVerify(List_t* list, int line, const char* funcname);
int ListIndexVerify(List_t* list, int index, const char* filename, int line);

void ListDataInit(List_t* list);
void ListNextInit(List_t* list);
void ListPrevInit(List_t* list);

void ListReallocUp(List_t* list);
void ListReallocDown(List_t* list);

#define FREE(point) free(point); point = NULL;

#define POISON 0xDEADDED

#define PRINT_IMAGE(...) fprintf(file_dump, __VA_ARGS__)
#define PRINT_HTM(...)   fprintf(file_htm, __VA_ARGS__)

#define PRINT_ERR(error) printf(RED "list name = %s\n made from = %s:%d\n %s:%d" RESET BOLD_RED" ERROR:" error, list->passport.name, list->passport.funcname, list->passport.line, funcname, line);
#define PRINT_ERR_INDEX(...) printf(BOLD_RED "%s:%d: in func %s ", filename, line, __func__); printf(__VA_ARGS__); printf(RESET);


#define LISTAppendAfter(name, index, value) ListAppendAfter(&name, index, value ONDEBUG_LIST(, __FILE__, __LINE__))
#define LISTAppendBefore(name, index, value) ListAppendBefore(&name, index, value  ONDEBUG_LIST(, __FILE__, __LINE__))
#define LISTDelete(name, index) ListDelete(&name, index ONDEBUG_LIST(, __FILE__, __LINE__))

#define SET_GREEN_NODE ", fillcolor = \"#C0FFC0\""
#define SET_RED_NODE ", fillcolor = gray"
#define GREEN_NODE 1


#define LISTCTOR(list_name, size) ListCtor(&list_name, size, __LINE__, __FILE__, __func__ ); list_name.passport.name = #list_name;

#define PRINT_DEBUG(COLOR, ...) printf(COLOR "%s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(RESET);

enum ListErr_t {
                OK             = 0, 
                ERR_LIST       = 1,
                ERR_INDEX      = 2,
                ERR_FREE       = 4, 
                ERR_CICLE_FREE = 8,
                ERR_CICLE_NEXT = 16, 
                ERR_CICLE_PREV = 32
                };

#endif