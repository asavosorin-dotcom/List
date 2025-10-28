#include "list.h"

FILE* file_dump = fopen("text.txt", "w");
FILE* file_htm  = fopen("Logfile.htm", "w");

void ListCtor(List_t* list, size_t size)
{
    list->size = size;

    
    ListDataInit(list);
    ListNextInit(list);
    ListPrevInit(list);
    
    list->head = 1;
    list->tail = 1;
    list->free = 1;
}

void ListDtor(List_t* list)
{
    // free(list->priv);
    free(list->data);
    free(list->next);
    free(list->prev);

    list->head = 1;
    list->tail = 1;
    list->free = 1;
}

void ListAppendAfter (List_t* list, int index, int elem)
{    
    int nextfree = 0; 
    static int count_append = 0;

    printf("old_free = %d\n", list->free);
    list->data[list->free] = elem;
    nextfree = list->next[list->free];

    printf("next_free = [%d]\n", nextfree);

    // if (count_append == 0)
    // {
    //     // list->head = index
    //     // list->next[index + 1] = 0;
    // }

    list->next[list->free] = list->next[index];

    list->prev[list->free] = index;

    printf("list->next[%d] = %d\n", list->free, list->next[index]);

    list->prev[list->next[index]] = list->free;
    list->next[index] = list->free;
        
    printf("next[%d] %d\n", index, list->next[index]);
    list->free = nextfree;

    count_append++;
}

void ListAppendBefore (List_t* list, int index, int elem)
{    
    int nextfree = 0; 
    static int count_append = 0;

    printf("old_free = %d\n", list->free);
    list->data[list->free] = elem;
    nextfree = list->next[list->free];

    printf("next_free = [%d]\n", nextfree);

    list->next[list->free] = index;

    list->prev[list->free] = list->prev[index];

    list->next[list->prev[index]] = list->free;
    list->prev[index] = list->free;

    PRINT_DEBUG(BOLD_BLUE, "tail = [%d]\n", list->tail);
    
    printf("next[%d] %d\n", index, list->next[index]);
    list->free = nextfree;

    count_append++;
}

void ListDelete(List_t* list, int index)
{
    list->data[index] = 0;

    list->next[list->prev[index]] = list->next[index];
    list->prev[list->next[index]] = list->prev[index];

    list->next[index] = list->free;
    list->free = index;
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

void ListDumpImage (List_t* list) // сделать Dump, который будет делать много картинок
{    
    PRINT_IMAGE("\trankdir=LR;\n\n");

    PRINT_IMAGE("\tnode0[label = \" index = 0 | %d | {prev = %d | next = %d}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", list->data[0], list->prev[0], list->next[0]);

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
    PRINT_IMAGE("\t{\n \tedge[color = blue, weight = 1];\n");

    PRINT_IMAGE("\tnode0 -> node%d\n", list->next[0]);
    for (int i = list->next[0]; i != 0; i = list->next[i])
    {
        PRINT_IMAGE("\tnode%d -> node%d\n", i, list->next[i]);
    }

    PRINT_IMAGE("\t}\n");
    //---------------------------------------------------------------------------------------------------

    //--------------------------------------------------PREV---------------------------------------------
    PRINT_IMAGE("\t{\n \tedge[color = red, weight = 1];\n");

    for (int i = list->prev[0]; i != 0; i = list->prev[i])
    {
        // PRINT_DEBUG(BOLD_BLUE, "[%zu]", i);
        PRINT_IMAGE("\tnode%d -> node%d\n", i, list->prev[i]);
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

    free(arr_colors_node);
}

void ListDumpWeb   (List_t* list)
{
    PRINT_HTM("<pre>\n");
    PRINT_HTM("\t<h3>DUMP</h3>\n");

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

    PRINT_HTM("\tHEAD: %d\n", list->head);
    PRINT_HTM("\tTAIL: %d\n", list->tail);

    PRINT_HTM("Image: \n <img src= \"text.png\" width = \"4000\" height = \"200\">");
    PRINT_HTM("</pre>");
}

// int List_get_elem(List_t* list, int index)
// {
//    
// }