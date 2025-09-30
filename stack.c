//Gilma Sebastian Mihai 315CA
#include "stdio.h"
#include "functions.h"
#include "stdlib.h"

stack* create_stack()
{
    stack* stiva = malloc(sizeof(stack));
    stiva->lista = create_list(sizeof(page));
    stiva->lista->data_size = sizeof(page);
    return stiva;
}

void remove_from_stack(stack* stiva) 
{
    remove_nod(stiva->lista,stiva->lista->header->prev);

}

void add_to_stack(stack* stiva, void* informatie)
{    
    add_to_list(stiva->lista, informatie);
}

nod* get_from_stack(stack* stack)
{
    return stack->lista->header->prev;
}
