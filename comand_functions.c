//Gilma Sebastian Mihai 315CA

#include "stdio.h"
#include "functions.h"
#include "stdlib.h"
#include "string.h"

//functia de cautare a unui nod cu un id specific
nod*  get_id_nod(int id, list* tabs)
{
    
    nod *iterate = tabs->header->next;
    tab *my_tab = (tab*)iterate->data;
    int curent = my_tab->id;
    int nr = 0;
    while(id != curent && nr <= 2 * tabs->size) {
        nr++;
        if (iterate->next == tabs->header) {
            return NULL;
        }
        iterate = iterate->next;
        my_tab = (tab*)iterate->data;
        curent = my_tab->id;
    }
    if (nr == (2 * tabs->size)+ 1)
        iterate = NULL;
    return iterate;
}

//adauga in stiva si se gaseste idul cautat pentru a fi pus ca pagina curenta
int page_function(browser internet , int nr_id, page* v, int n)
{
    int p = -1;
    for(int i = 0; i < n; i++) {
        if(nr_id == v[i].id)
            p = i;
    }
    void * copie;
    copie = malloc(sizeof(page));
    memcpy(copie, internet.current->currentpages, sizeof(page));
    add_to_stack(internet.current->stack_back, copie);

    return p;
}

//functia de free la finalul programului
void free_function(list *tabs, page *v, int n)
{
    for (int i = 0; i < n; i++) {
        free(v[i].description);
    }

    free(v);
    nod *current = tabs->header->next;
    while (current != tabs->header) {
        nod *next = current->next;
        
        free(current->data);
        free(current);

        current = next;
    }
}

//functia de backward adauga in stiva forward si elimina de pe stiva backward
page * backward_function(browser *internet)
{
    nod *back_nod = get_from_stack(internet->current->stack_back);
    remove_from_stack(internet->current->stack_back);
    
    void * copie;
    copie = malloc(sizeof(page));
    memcpy(copie, back_nod->data, sizeof(page));
    add_to_stack(internet->current->stack_forward, internet->current->currentpages);

    return (page*)copie;

}

//functia de forward elimina de pe stiva forward si adauga pe stiva backward
void forward_function(tab *current)
{
    nod *back_nod = get_from_stack(current->stack_forward);
    remove_from_stack(current->stack_forward);
    void * copie;
    copie = malloc(sizeof(page));
    memcpy(copie, current->currentpages, sizeof(page));
    add_to_stack(current->stack_back, copie);

    current->currentpages = (page*)back_nod->data;
    
}

//afiseaza istoricul taburilor 
void print_history(tab *current, FILE* out)
{
    nod *forward_nod = current->stack_forward->lista->header->next;
    //incepe cu stiva forward o afisam
    int i = 0;
    while(forward_nod->data != NULL) {
        i++;
        page* new_page = (page*)forward_nod->data;
        fprintf(out ,"%s\n", new_page->url);
        forward_nod = forward_nod->next;
    }
    //afisam paginea curenta

    fprintf(out ,"%s\n", current->currentpages->url);
    nod* new_nod = get_from_stack(current->stack_back);
    
    //afisam la final stiva backward
    while (current->stack_back->lista->size >= 2) {
        if (new_nod == NULL || new_nod->data == NULL) {
            break;
        }
        page* new_page = (page*)new_nod->data;
        fprintf(out ,"%s\n", new_page->url);
        new_nod = new_nod->prev;
    }
   

}

//modifica tabul curent si in lista
void modify_current(list *tabs, int id, page* v)
{
    nod *iterate = tabs->header->next;
    tab *my_tab = (tab*)iterate->data;
    int curent = my_tab->id;
    
    while (id != curent) {
        iterate = iterate->next;
        my_tab = (tab*)iterate->data;
        curent = my_tab->id;
    }
    my_tab->currentpages = &v[id];
}

void remodelate_nod(nod * modify, page * v,int p)
{
    tab* my_tab = modify->data;
  
    my_tab->currentpages = v + p;
    memcpy(modify->data, my_tab, sizeof(tab));
}

void make_current_nod(browser internet, nod * new_nod)
{
    void * p = malloc(sizeof(tab));
    memcpy(p, internet.current, sizeof(tab));
    new_nod->data = p;
}