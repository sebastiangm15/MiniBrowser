//Gilma Sebastian Mihai 315CA

#include "stdio.h"
#include "functions.h"
#include "stdlib.h"
#include "string.h"

int main(void)
{
    int n,k,id = 0,current_nr = 0;
    browser internet;
    FILE* in = fopen("tema1.in", "rt");
    FILE* out = fopen("tema1.out", "wt");
    page* def = def_page();
    list *tabs = create_list(sizeof(tab));
    tab* first_tab = new_tab(id, def);
    add_to_list(tabs, (void*)first_tab);

    internet.current = first_tab;
    
    fscanf(in, "%d", &n);
    page* v = vector_init(n, in);

    fscanf(in, "%d", &k);
    for (int i = 0; i < k; i++) {
        char s[30];
        fscanf(in,"%s",s);

        if (strstr(s,"NEW_TAB") != 0) {
            id++;          
            tab* best_tab = new_tab(id, def);
            add_to_list(tabs, (void*)best_tab);
            internet.current = best_tab;
            
            current_nr = id;
        }  

        if (strcmp(s,"PRINT") == 0) {
            print_list(tabs, current_nr, out); 
        }

        if (strcmp(s,"CLOSE") == 0) {

            nod * delete = get_id_nod(current_nr, tabs);
            tab* datas = (tab*)delete->prev->data;
            if(current_nr == 0) {
                fprintf(out ,"403 Forbidden\n");
                
            } else {
            current_nr = datas->id;
            remove_nod(tabs, delete);
            }
        }
        if (strcmp(s, "PREV") == 0) {
            nod * back_nod = get_id_nod(current_nr, tabs);
            if((tab*)back_nod->prev->data == NULL)
                back_nod = back_nod->prev;
            internet.current = (tab *)back_nod->prev->data; 
            tab *datas = (tab *)back_nod->prev->data;
            current_nr= datas->id;
        }
        if (strcmp(s, "NEXT") == 0) {
            nod * back_nod = get_id_nod(current_nr, tabs);
            if((tab*)back_nod->next->data == NULL)
                back_nod = back_nod->next;
            internet.current = (tab *)back_nod->next->data;
            tab *datas = (tab *)back_nod->next->data;
            current_nr= datas->id;
        }
        if (strcmp(s, "OPEN") == 0) {
            int nr_id;
            fscanf(in, "%d", &nr_id);
            nod * modif = get_id_nod(nr_id, tabs);
            if (modif == NULL) {
                fprintf(out ,"403 Forbidden\n");
                continue;
            }
            internet.current = (tab*)modif->data;
            current_nr = nr_id;
            
        }
        if (strcmp(s, "PAGE") == 0) {
            int nr_id, p;
            fscanf(in, "%d", &nr_id);
            if(n == 0) {
                fprintf(out ,"403 Forbidden\n");
                continue;
            }

            p = page_function(internet, nr_id, v, n);
            if(p == -1) {
                fprintf(out, "403 Forbidden\n");
                continue;
            }
            nod* modify = get_id_nod(internet.current->id, tabs);
            remodelate_nod(modify, v, p);
            internet.current->currentpages = v + p;//modific pozitia curenta
        }
        if (strcmp(s, "BACKWARD") == 0) {
            if(internet.current->stack_back->lista->size == 1) {
                fprintf(out, "403 Forbidden\n");
                continue;
            }
            nod* modify = get_id_nod(internet.current->id, tabs);
            
            internet.current->currentpages = backward_function(&internet);
            make_current_nod(internet, modify);
        }
        if (strcmp(s, "FORWARD") == 0) {
        if(internet.current->stack_forward->lista->size == 1) {
                fprintf(out,"403 Forbidden\n");
                continue;
            }
            forward_function(internet.current);
            nod* modify = get_id_nod(internet.current->id, tabs); //obtin nodul de la pozitia ceruta
            make_current_nod(internet, modify);// il modific
        }
        if (strcmp(s, "PRINT_HISTORY") == 0) {
            int nr_id;
            fscanf(in, "%d", &nr_id);
            nod * modif = get_id_nod(nr_id, tabs);
            if(modif == NULL) {
                fprintf(out, "403 Forbidden\n");
                continue;
            }
            tab * new_tab = (tab*)modif->data;
            print_history(new_tab, out);
        }
    }
    free_function(tabs, v, n);
    fclose(in);
    fclose(out);
    return 0;
}

