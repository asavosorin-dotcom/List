#include "list_classic.h"

// фиктивный нулевой элемент
// 
FILE* file_htm  = fopen("Logfile.htm", "w");
static int index_png = 0;


List_elem_t* ListElemCtor(List_data_t data)
{
    List_elem_t* elem = (List_elem_t* ) calloc(1, sizeof(List_elem_t));

    elem->data = data;
    elem->prev = elem;
    elem->next = elem;

    return elem;
}

List_elem_t* ListInsertAfter(List_elem_t* elem, List_data_t value)
{
    List_elem_t* new_elem = ListElemCtor(value);
    
    new_elem->prev = elem;
    (elem->next)->prev = new_elem;
    
    new_elem->next = elem->next;  
    elem->next = new_elem;

    return new_elem;
}

List_elem_t* ListInsertBefore(List_elem_t* elem, List_data_t value)
{
    return ListInsertAfter(elem->prev, value);
}

void ListDeleteElem(List_elem_t* elem)
{
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;

    free(elem);
}

void ListDumpElem(List_elem_t* elem, FILE* file_dump)
{
    static List_elem_t* elem_zero = elem; 
 
    if (elem->next != elem_zero)
    {
        PRINT_IMAGE("\tnode%p[label = \"%p | %d | {%p | %p}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", elem , elem, elem->data, elem->prev, elem->next);
        ListDumpElem(elem->next, file_dump);
        PRINT_IMAGE("\tnode%p -> node%p [color = \"gray\", dir = both]\n ", elem, elem->next);
    }
    

}

void ListDumpImage(List_elem_t* elem)
{
    const char* filename = "listclassic_dump.txt";
    FILE* file_dump = fopen(filename, "w");
    
    PRINT_IMAGE("digraph {\n");
    PRINT_IMAGE("\trankdir=LR;\n\n");

    PRINT_IMAGE("node%p[label = \"%p | %d | {%p | %p}\", shape = Mrecord, style = \"filled\", fillcolor = \"#FFC0C0\"]\n", elem , elem, elem->data, elem->prev, elem->next);
    PRINT_IMAGE("node%p -> node%p [color = \"gray\", dir = both]", elem, elem->next);
    ListDumpElem(elem->next, file_dump);

    PRINT_IMAGE("}");
    
    char command[100] = "";
    fclose(file_dump);
    
    sprintf(command, "dot \"%s\" -T png -o pictures_classic/graph%d.png", filename, index_png);
    // printf("command = %s\n", command);
    system(command);

    index_png++;
}

void ListDumpClassic (List_elem_t* elem, const char* text)
{
    PRINT_HTM("<pre>\n");
    PRINT_HTM("\t<h3>DUMP Classic %s</h3>\n", text);

    ListDumpImage(elem);

    PRINT_HTM("Image: \n <img src= \"pictures_classic/graph%d.png\">", index_png - 1);
    PRINT_HTM("</pre>");
}

void ListDtorClassic(List_elem_t* elem)
{
    for (List_elem_t* element = elem->next; element != elem; )
    {
        element = element->next;
        free(element->prev);
    }

    free(elem);
}