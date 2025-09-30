//Gilma Sebastian Mihai 315CA
#include "stdio.h"

typedef struct nod nod;
struct nod
{
    void* data;
    nod* next;
    nod* prev;
};


typedef struct page{
    int id;
    char url[50];
    char *description;
}page;

typedef struct {
    nod* header;
    int size;
    int data_size;
    
}list;

typedef struct stack{
    list* lista;
}stack;


typedef struct tab tab;
struct tab {
    int id;
    page *currentpages;
    stack *stack_back;
    stack *stack_forward;
};

typedef struct {
    tab *current;
    
}browser;

list* create_list(int data_size);

page* def_page();

page* vector_init(int n, FILE *in);

void add_to_list(list *list, void *new_datas);

void remove_nod(list *list, nod *curent_nod);

stack* create_stack();

void remove_from_stack(stack* stiva);

void add_to_stack(stack* stiva, void* informatie);

nod* get_from_stack(stack* stack);

tab* new_tab(int id, page* def);

void print_list(list* lista, int id, FILE* out);

void close_function();

nod*  get_id_nod(int id, list* tabs);


int page_function(browser internet , int nr_id, page* v, int n);

void free_function(list * tabs, page *v, int n);

page * backward_function(browser *internet);

void forward_function(tab *current);

void print_history(tab *current, FILE* out);

void modify_current(list *tabs, int id, page* v);

void remodelate_nod(nod * modify, page * v,int p);

void make_current_nod(browser internet, nod * new_nod);

stack* init_stack();

page* vector_init();