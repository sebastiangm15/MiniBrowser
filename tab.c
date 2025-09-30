//Gilma Sebastian Mihai 315CA
#include "stdio.h"
#include "functions.h"
#include "stdlib.h"
#include "string.h"


tab* new_tab(int id, page* def)
{
    tab *new = malloc(sizeof(tab));

    memset(new, 0, sizeof(tab));

    new->id = id;
    new->currentpages = def;
    new->stack_back = create_stack();
    new->stack_forward = create_stack();

    return new;
}
