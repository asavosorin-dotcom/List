#include "list.h"
FILE* file_htm  = fopen("Logfile.htm", "w");


static int index_png = 0;

void ListCtor(List_t* list, size_t size, int line, const char* filename, const char* funcname)
{
    assert(list);

    list->size = size;
    
    ListDataInit(list);
    ListNextInit(list);
    ListPrevInit(list);
    
    list->free = 1;

    list->passport.line     = line;
    list->passport.filename = filename;
    list->passport.funcname = funcname;
}

void ListDtor(List_t* list)
{
    // free(list->priv);
    free(list->data);
    free(list->next);
    free(list->prev);


    list->free = 1;
}

int ListAppendAfter (List_t* list, int index, int elem, ONDEBUG_LIST(const char* filename), ONDEBUG_LIST(int line))
{    
    int err = OK;
    int nextfree = 0; 

    ONDEBUG_LIST(ListVerify(list, __LINE__, __func__));

    ONDEBUG_LIST(ListIndexVerify(list, index, filename, line));


    // printf("old_free = %d\n", list->free);
    list->data[list->free] = elem;
    nextfree = list->next[list->free];

    // printf("next_free = [%d]\n", nextfree);

    list->next[list->free] = list->next[index];

    list->prev[list->free] = index;

    // printf("list->next[%d] = %d\n", list->free, list->next[index]);

    list->prev[list->next[index]] = list->free;
    list->next[index] = list->free;
        
    // printf("next[%d] %d\n", index, list->next[index]);
    list->free = nextfree;

    list->count_elem++;

    return err;
}

int ListAppendBefore (List_t* list, int index, int elem, ONDEBUG_LIST(const char* filename), ONDEBUG_LIST(int line))
{    
    int err = OK;
    int nextfree = 0; 
    
    ONDEBUG_LIST(ListVerify(list, __LINE__, __func__));
    ONDEBUG_LIST(ListIndexVerify(list, index, filename, line));
    
    #ifdef DEBUG_LIST
        if (index >= (int) list->size || index < 0)
        {
            PRINT_DEBUG(BOLD_RED, "ERROR: index out of range!\n");
            return ERR_INDEX;
        }
    #endif

    // printf("old_free = %d\n", list->free);
    list->data[list->free] = elem;
    nextfree = list->next[list->free];

    // printf("next_free = [%d]\n", nextfree);

    list->next[list->free] = index;

    list->prev[list->free] = list->prev[index];

    list->next[list->prev[index]] = list->free;
    list->prev[index] = list->free;

    // PRINT_DEBUG(BOLD_BLUE, "tail = [%d]\n", list->tail);
    
    list->free = nextfree;
    list->count_elem++;

    return err;
}

int ListDelete(List_t* list, int index, ONDEBUG_LIST(const char* filename), ONDEBUG_LIST(int line))
{
    int err = OK;
    
    ONDEBUG_LIST(ListVerify(list, __LINE__, __func__));
    ONDEBUG_LIST(ListIndexVerify(list, index, filename, line));    ListVerify(list, __LINE__, __func__);

    #ifdef DEBUG_LIST
        if (index >= (int) list->size || index < 0)
        {
            PRINT_DEBUG(BOLD_RED, "ERROR: index out of range!\n");
            return ERR_INDEX;
        }
    #endif

    list->data[index] = 0;

    list->next[list->prev[index]] = list->next[index];
    list->prev[list->next[index]] = list->prev[index];

    list->next[index] = list->free;
    list->free = index;

    list->count_elem--;

    return err;
}

void ListDataInit(List_t* list)
{
    assert(list);
    
    list->data = (int*) calloc(list->size, sizeof(int));
    
    for (size_t i = 0; i < list->size; i++)
    {
        list->data[i] = 0;
    }
    
}

void ListNextInit(List_t* list)
{
    assert(list);
    
    list->next = (int*) calloc(list->size, sizeof(int));
    
    for (size_t i = 1; i < list->size - 1; i++)
    {
        list->next[i] = (int) i + 1;
    }

    list->next[list->size - 1] = 0;
}

void ListPrevInit(List_t* list)
{   
    assert(list);

    list->prev = (int*) calloc(list->size, sizeof(int));
    
    for (size_t i = 1; i < list->size; i++)
    {
        list->prev[i] = (int) i - 1;
        // printf("list_next[%d] = [%d]\n", i, list->next[i]);
    }

    // list->prev[0] = 1;
}

#ifdef DEBUG_LIST
int ListVerify(List_t* list, int line, const char* funcname)
{
    if (list == NULL) 
    {
        PRINT_ERR("pointer list is NULL\n")
        return ERR_LIST;
    }
    
    if (list->free == 0)
    {
        PRINT_ERR("list overflow\n")
        return ERR_FREE;
    }
    
    if (list->next == NULL) 
    {
        PRINT_ERR("pointer next is NULL\n")
        return ERR_LIST;
    }
    if (list->prev == NULL) 
    {
        PRINT_ERR("pointer prev is NULL\n")
        return ERR_LIST;
    }
    if (list->data == NULL) 
    {
        PRINT_ERR("pointer data is NULL\n")
        return ERR_LIST;
    }

    if (list->next[0] == list->free)
    {
        PRINT_ERR("cicle list free\n")
        return ERR_CICLE_FREE;
    }

    int counter = 0;

    for (int index = list->next[0]; index != 0; index = list->next[index], counter++)
    {
        if (counter > list->count_elem || index >= (int) list->size)
        {
            PRINT_ERR("no cicle list next\n");
            return ERR_CICLE_NEXT;
        }
    }

    if (counter != list->count_elem)
    {
        PRINT_ERR("count elem in list != count elem in next\n");
    }

    counter = 0;

    for (int index = list->prev[0]; index != 0; index = list->prev[index], counter++)
    {
        if (counter > list->count_elem || index >= (int) list->size)
        {
            PRINT_ERR("no cicle list prev\n");
            return ERR_CICLE_PREV;
        }
    }

    counter = 0;

    for (int index = list->free; index != 0; index = list->next[index], counter++)
    {
        if (counter > list->count_elem || index >= (int) list->size)
        {
            PRINT_ERR("no cicle list prev\n");
            return ERR_CICLE_PREV;
        }
    }

    if (counter != (int) list->size - list->count_elem)
    {
        PRINT_ERR("wrong count elem in free\n");
        return ERR_CICLE_FREE;
    }

    return OK;
}

int ListIndexVerify(List_t* list, int index, const char* filename, int line)
{
    if (index >= (int) list->size || index < 0)
        {
            PRINT_ERR_INDEX("ERROR: index out of range!\n");
            return ERR_INDEX;
        }

    for (int index_in_free = list->free; index_in_free != 0; index_in_free = list->next[index_in_free])
    {
        if (index_in_free == index)
        {
            PRINT_ERR_INDEX("ERROR: index out of range!\n");
            return ERR_INDEX;
        }
    }

    return OK;
}

#endif

void ListDumpImage (List_t* list) // сделать Dump, который будет делать много картинок
{    
    
    const char* filename = "graph_code.txt";
    FILE* file_dump = fopen(filename, "w");
    assert(file_dump);

    fprintf(file_dump, "digraph {\n");
    
    PRINT_IMAGE("\trankdir=LR;\n\n");

    PRINT_IMAGE("\tnode0[label = \" index = 0 | %d | {prev = %d | next = %d}\", shape = Mrecord, style = \"filled\", fillcolor = \"#FFC0C0\"]\n", list->data[0], list->prev[0], list->next[0]);

    char* arr_colors_node = (char* ) calloc(list->size, sizeof(char));

    for (int i = list->next[0]; i != 0; i = list->next[i]) /*fontcolor для цвета текста*/
    {
        arr_colors_node[i] = GREEN_NODE;
    }
    
    for (size_t i = 1;  i < list->size; i++)
    {
        PRINT_IMAGE("\tnode%zu[label = \" index = %zu | %d | {prev = %d | next = %d}\", shape = Mrecord, style = \"filled\"", i, i, list->data[i], list->prev[i], list->next[i]);
        (arr_colors_node[i]) ?  PRINT_IMAGE(SET_GREEN_NODE) : PRINT_IMAGE(SET_RED_NODE);
        PRINT_IMAGE("]\n");
    }

    //------------------------------------------------WHITE----------------------------------------------
    PRINT_IMAGE("\t{\n \tedge[color = white, weight = 1000];\n");

    for (size_t i = 0; i < list->size - 1; i++)
    {
        PRINT_IMAGE("\tnode%zu -> node%zu\n", i, i + 1);
    }

    PRINT_IMAGE("\t}\n");
    //---------------------------------------------------------------------------------------------------
    
    //--------------------------------------------------NEXT---------------------------------------------
    PRINT_IMAGE("\t{\n \tedge[constraint = false, color = gray, weight = 1, dir = both];\n");

    PRINT_IMAGE("\tnode0 -> node%d\n", list->next[0]);

    for (int i = list->next[0]; i != 0; i = list->next[i])
    {
        if (list->prev[list->next[i]] != i)
        {
            PRINT_IMAGE("\t}\n");
            PRINT_IMAGE("node%d -> node%d [color = blue]\n", i, list->next[i]);
            PRINT_IMAGE("nodeERR[label = \"%d\", shape = octagon, fontcolor = \"red\", color = \"red\"]\n", list->prev[list->next[i]]);
            PRINT_IMAGE("node%d -> nodeERR [color = \"red\"]\n", list->next[i]);
            PRINT_IMAGE("\t{\n \tedge[constraint = false, color = gray, weight = 1, dir = both];\n");
        }
        else
            PRINT_IMAGE("\tnode%d -> node%d\n", i, list->next[i]);

    }

    PRINT_IMAGE("\t}\n");
    //---------------------------------------------------------------------------------------------------


    //-------------------------------------------------FREE----------------------------------------------
    PRINT_IMAGE("\t{\n \tedge[color = green, weight = 1, constraint=false];\n");
    

    for (int i = list->free; i != 0; i = list->next[i])
    {
        // PRINT_DEBUG(BOLD_BLUE, "[%zu]", i);
        PRINT_IMAGE("\tnode%d -> node%d\n", i, list->next[i]);
    }
    
    PRINT_IMAGE("\t}\n");
    //---------------------------------------------------------------------------------------------------

    fprintf(file_dump, "}"); 
    
    char command[100] = "";
    fclose(file_dump);

    sprintf(command, "dot \"%s\" -T png -o pictures/graph%d.png", filename, index_png);
    // printf("command = %s\n", command);
    system(command);

    index_png++;

    free(arr_colors_node);
}

void ListDump (List_t* list, const char* text)
{
    PRINT_HTM("<pre>\n");
    PRINT_HTM("\t<h3>DUMP %s</h3>\n", text);

    PRINT_HTM("\t      ");

    for (size_t i = 0; i < list->size; i++)
    {
    PRINT_HTM("%3zu ", i);
    }

    PRINT_HTM("\n");
    PRINT_HTM("\tDATA: ");

    for (size_t i = 0; i < list->size; i++)
    {
        PRINT_HTM("%3d ", list->data[i]);
    }

    PRINT_HTM("\n");

    PRINT_HTM("\tNEXT: ");

    for (size_t i = 0; i < list->size; i++)
    {
        PRINT_HTM("%3d ", list->next[i]);
    }

    PRINT_HTM("\n");

    PRINT_HTM("\tPREV: ");

    for (size_t i = 0; i < list->size; i++)
    {
        PRINT_HTM("%3d ", list->prev[i]);
    }

    PRINT_HTM("\n");

    ListDumpImage(list);

    PRINT_HTM("Image: \n <img src= \"pictures/graph%d.png\" width = \"1000\" height = \"200\">", index_png - 1);

    PRINT_HTM("</pre>");

}

// int List_get_elem(List_t* list, int index)
// {
//    
// }