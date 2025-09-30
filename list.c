//Gilma Sebastian Mihai 315CA
#include "functions.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//functia pentru initializarea vectorului
page* vector_init(int n, FILE *in) {

    page* v = malloc(sizeof(page) * n);

    for(int i = 0; i < n; i++) {    
        int x;
        char s[100] = {0};
        
        fscanf(in, "%d", &x);
        fgets(s, 2, in);
        fgets(s, 99, in);
        
        v[i].id = x;
        
        strcpy(v[i].url, s);
        for(int i = 0; i < 99; i++) {
            if(s[i] == '\n')
                s[i] ='\0';
        }
        fgets(s, 99, in);
        for(int i = 0; i < 99; i++) {
            if(s[i] == '\n')
                s[i] ='\0';
        }
        
        v[i].description = malloc(99);
        strcpy(v[i].description, s);
    }

    return v;
}

//pagina default
page* def_page() 
{
    page* def = malloc(sizeof(page));
    def->id = 0;
    strcpy(def->url, "https://acs.pub.ro/\0");
    def->description = malloc(sizeof(char) * 100);
    strcpy(def->description, "Computer Science\0");
    return def;

}

//functia pentru a crea lista
list* create_list(int data_size)
{
    list* lista = malloc(sizeof(list));
    nod* sentinel = malloc(sizeof(nod));

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    sentinel->data = NULL;

    lista->header = sentinel;
    lista->size = 1;
    lista->data_size = data_size;

    return lista;
}

//functia de adaugare in lista
void add_to_list(list *list, void *new_datas)
{
    nod *new_nod = malloc(sizeof(nod));
    nod *search_front = list->header;
    nod *search_back = list->header->prev;

    
    new_nod->data = malloc(list->data_size);
    memcpy(new_nod->data, new_datas, list->data_size);

    new_nod->next = search_front;
    new_nod->prev = search_back;
    search_back->next = new_nod;
    search_front->prev = new_nod;
    list->size++;

}

//functia de eliminare din lista
void remove_nod(list *list, nod *curent_nod)
{
    nod *cautare = list->header;

    if(list->size == 1) {
        return; // daca lista nu contine elemente nu face nimic
    }
    if(list->size == 2) {
        list->header->next = list->header;
        list->header->prev = list->header;
        list->size--;
        return;
    }

    while(cautare != curent_nod) {
        cautare = cautare->next;
    }

    nod *back = cautare->prev;
    cautare->next->prev = back;
    back->next = cautare->next;
    list->size--;
}

void print_list(list* lista, int id, FILE* out) {
    if (lista == NULL || lista->header == NULL)
        return;

    nod* start = lista->header->next; // presupunem ca header este un nod santinela
    nod* found = NULL;

    // Cauta nodul cu id-ul dat
    while (start != lista->header) {
        if (start->data != NULL) {
            tab* t = (tab*)start->data;
            if (t->id == id) {
                found = start;
                break;
            }
        }
        start = start->next;
    }

    // Verifica si header-ul în caz că are date
    if (found == NULL && lista->header->data != NULL) {
        tab* t = (tab*)lista->header->data;
        if (t->id == id) {
            found = lista->header;
        }
    }

    // Afișează nodurile începând de la cel găsit
    nod* current = found;
    do {
        if (current->data != NULL) {
            tab* t = (tab*)current->data;
            // Afiseaza din structura tab id:
            fprintf(out,"%d ", t->id);
        }
        current = current->next;
    } while (current != found);
    fprintf(out,"\n");
    tab* afis = (tab*)found->data;
    fprintf(out,"%s\n", afis->currentpages->description);
}




