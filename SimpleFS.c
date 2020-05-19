#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DIM 2048
#define JJJ 66000
#define PRIMACELLA 2
#define TRUE 1
#define FALSE 0
#define NICO 1500

typedef struct _nodo{
    int ampiezza;
    int file;   //TRUE o FALSE
    int spiazzamento;
    int key;
    bool used;
    int verifica;
    int hashing;
    char *nome;
    char *percorso;
    char *contenuto;
    struct _nodo *padre;
    struct _nodo *figliosx;
    struct _nodo *fratellodx; //quello dopo di me
    struct _nodo *fratellosx; //quello prima di me
}nodo;

typedef struct _s1{
    char *info;
    struct _s1 *next;
}LISTA;

typedef struct _s2{
    int ampiezza;
    int file;   //TRUE o FALSE
    int hashing;
    char *nome;
    char *percorso;
    char *contenuto;
    struct _nodo *padre;
    struct _nodo *figliosx;
    struct _nodo *fratellodx; //quello dopo di me
    struct _nodo *fratellosx; //quello prima di me
    struct _s2 *next;
}LISTA2;


unsigned hashfun (char *, int);
nodo *creadir (nodo *, int);
void visita (nodo *);
LISTA *cerca (char *, nodo *, LISTA *);
LISTA *inserisci (LISTA *, char *);

void rehash (nodo *);
LISTA2 *cloud (nodo *, LISTA2 *);
LISTA2 *reinserisci (nodo *, LISTA2 *, int);

void create (char *, nodo *);
void create_dir(char *, nodo *);
void read (char *, nodo *);
void write (char *, char *, nodo *);
void delet (char *, nodo *);
void delet_r (char *, nodo *);
void find (char *, nodo *);


int main () {

    char *comando=NULL;
    char *percorso=NULL;
    char *cont=NULL;
	char *ptt=NULL;
	char *input=NULL;
    struct _nodo *p=NULL;


    if ((p = (nodo*)calloc(DIM,sizeof(nodo))) == NULL){
        printf("errore calloc\n");
        return 0;
    }
    p->verifica = 91;
    p->hashing = DIM;

    /*FILE *fp;
    if ((fp = fopen("C:\\Users\\Matteo\\Desktop\\file progetto\\cactus.in", "r")) == NULL){
        printf("errore apertura file\n");
        exit(EXIT_FAILURE);
    }      freopen("6.out", "a+", stdout);*/


    do{
        if ((input = (char*)calloc((JJJ+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return 0;
        }
        fgets (input, JJJ, stdin);
        if ((input = (char*)realloc(input, (strlen(input)+1)*sizeof(char))) == NULL){
            printf("errore realloc\n");
            return 0;
        }
        if ((ptt = strtok (input, "\n")) == NULL)
            return 0;
        if ((ptt = strtok(input, " ")) == NULL)
            return 0;
        if ((comando = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return 0;
        }
        strcpy(comando, ptt);

        if(strcmp(comando,"create")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            create(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"create_dir")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            create_dir(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"read")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            read(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"write")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            if ((ptt=strtok(NULL, "\"")) == NULL)
                return 0;
            if ((cont = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(cont, ptt);
            write(percorso, cont, p);
            free (input);
            free (comando);
            free (percorso);
            free (cont);
            input = NULL;
            comando = NULL;
            percorso = NULL;
            cont = NULL;
        }
        else if(strcmp(comando,"delete")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            delet(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"delete_r")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            delet_r(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"find")==0){
            if ((ptt=strtok(NULL, " ")) == NULL)
                return 0;
            if ((percorso = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return 0;
            }
            strcpy(percorso, ptt);
            find(percorso, p);
            free (input);
            free (comando);
            free (percorso);
            input = NULL;
            comando = NULL;
            percorso = NULL;
        }
        else if(strcmp(comando,"exit")==0){
            break;
        }
        else{
            ;
        }
    } while (1);

	return 0;
}

void create_dir (char *percorso, nodo *p){

    int temp, i=0, slash=0, x, lperc, SIZE, pos=0, fck=0, fck2=0, jal;
    char *ptt=NULL;
    char *name=NULL;
    char *perc=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    if (slash > 255){
        printf("no\n");
        return;
    }

    ptt = strtok(percorso, "/");
    while (ptt != NULL){
        if(strlen(ptt) > 255){
            printf("no\n");
            return;
        }
        jal = NICO;
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
        }
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL){
            strcpy(name, (p+temp)->nome);
        }
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0 || (p+temp)->file == TRUE){
                printf("no\n");
                if (p->padre == NULL)
                    break;
                p = p->padre;
                p->ampiezza--;
                break;
            }
            else {
                if (slash == 1){
                    (p+temp)->ampiezza++;
                    if((p+temp)->ampiezza > 1024){
                        printf("no\n");
                        (p+temp)->ampiezza--;
                        return;
                    }
                    if((p+temp)->ampiezza >= ((p+temp)->hashing)/2){
                        (p+temp)->hashing = ((p+temp)->hashing)*2;
                        rehash(p+temp);
                       // dim = (p+temp)->hashing;
                    }
                }
                p = (p+temp)->figliosx;
            }
        }

        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){        //se lo trovi ed è una cartella
                        if (slash == 1){                                            //se sei la penultima risorsa
                            (p+temp)->ampiezza++;
                            if((p+temp)->ampiezza > 1024){
                                printf("no\n");
                                (p+temp)->ampiezza--;
                                return;
                            }
                            if((p+temp)->ampiezza >= ((p+temp)->hashing)/2){
                                (p+temp)->hashing = ((p+temp)->hashing)*2;
                                rehash(p+temp);
                                //dim = (p+temp)->hashing;
                            }
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;          //non so
                        }
                        else {                                                  //se hai ancora risorse dopo di te
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;
                        }
                    }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (fck == 0){
                    printf("no\n");
                    return;
                }
                fck = 0;
            }

            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strlen(name) == 0){
                        pos = temp;
                        fck2 = 1;
                    }
                    if (strcmp(name, ptt) == 0){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (p->verifica == 91){
                    p->ampiezza++;
                    if (p->ampiezza > 1024){
                        printf("no\n");
                        p->ampiezza--;
                        return;
                    }
                }
                if (fck2 == 0)
                    pos = temp;
                fck2 = 0;
                if (((p+pos)->nome = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                    printf("errore malloc\n");
                    return;
                }
                if (((p+pos)->percorso = (char*)calloc((lperc+1),sizeof(char))) == NULL){
                    printf("errore malloc\n");
                    return;
                }
                strcpy((p+pos)->nome, ptt);
                strcpy((p+pos)->percorso, perc);
                (p+pos)->file = FALSE;
                (p+pos)->key = pos;
                (p+pos)->used = 1;
                (p+pos)->hashing = 16;
                if (p->spiazzamento == 0){
                    p->spiazzamento = pos;
                    p->file = PRIMACELLA;
                    p->fratellodx = (p+pos);
                    (p+pos)->fratellosx = p;
                    (p+pos)->fratellodx = NULL;
                }
                else{
                    x = p->spiazzamento;
                    (p+pos)->fratellosx = (p+x);
                    (p+pos)->fratellodx = NULL;
                    (p+x)->fratellodx = (p+pos);
                    p->spiazzamento = pos;
                }
                SIZE = (p+pos)->hashing;
                creadir(p+pos, SIZE);
                printf("ok\n");
            }
        }

    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void create (char *percorso, nodo *p){

    int temp, slash=0, i=0, x, lperc, SIZE, pos=0, fck=0, fck2=0, jal;
    char *name=NULL;
    char *perc=NULL;
    char *ptt=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    if (slash > 255){
        printf("no\n");
        return;
    }
    ptt = strtok (percorso, "/");
    while (ptt != NULL){
        if(strlen(ptt) > 255){
            printf("no\n");
            return;
        }
        jal = NICO;
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return;
        }
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL)
            strcpy(name, (p+temp)->nome);
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0 || (p+temp)->file == TRUE){
                printf("no\n");
                if (p->padre == NULL)
                    break;
                p = p->padre;
                p->ampiezza--;
                break;
            }
            else {
                if(slash == 1){
                    (p+temp)->ampiezza++;
                    if((p+temp)->ampiezza > 1024){
                        printf("no\n");
                        (p+temp)->ampiezza--;
                        return;
                    }
                    if((p+temp)->ampiezza >= ((p+temp)->hashing)/2){
                        (p+temp)->hashing = ((p+temp)->hashing)*2;
                        rehash(p+temp);

                    }
                }
                p = (p+temp)->figliosx;
            }
        }

        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){        //se lo trovi ed è una cartella
                        if (slash == 1){                                            //se sei la penultima risorsa
                            (p+temp)->ampiezza++;
                            if((p+temp)->ampiezza > 1024){
                                printf("no\n");
                                (p+temp)->ampiezza--;
                                return;
                            }
                            if((p+temp)->ampiezza >= ((p+temp)->hashing)/2){
                                (p+temp)->hashing = ((p+temp)->hashing)*2;
                                rehash(p+temp);
                            }
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;          //non so
                        }
                        else {                                                  //se hai ancora risorse dopo di te
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;
                        }
                    }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (fck == 0){
                    printf("no\n");
                    return;
                }
                fck = 0;
            }

            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strlen(name) == 0){
                        pos = temp;
                        fck2 = 1;
                    }
                    if (strcmp(name, ptt) == 0){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (p->verifica == 91){
                    p->ampiezza++;
                    if (p->ampiezza > 1024){
                        printf("no\n");
                        p->ampiezza--;
                        return;
                    }
                }
                if (fck2 == 0)
                    pos = temp;
                fck2 = 0;
                if (((p+pos)->nome = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
                    printf("errore malloc\n");
                    return;
                }
                if (((p+pos)->percorso = (char*)calloc((lperc+1),sizeof(char))) == NULL){
                    printf("errore malloc\n");
                    return;
                }
                strcpy((p+pos)->nome, ptt);
                strcpy((p+pos)->percorso, perc);
                (p+pos)->file = TRUE;
                (p+pos)->key = pos;
                (p+pos)->used = 1;
                (p+pos)->hashing = 16;
                //(p+pos)->padre = p->padre;
                if (p->spiazzamento == 0){
                    p->spiazzamento = pos;
                    p->file = PRIMACELLA;
                    p->fratellodx = (p+pos);
                    (p+pos)->fratellosx = p;
                    (p+pos)->fratellodx = NULL;
                }
                else{
                    x = p->spiazzamento;
                    (p+pos)->fratellosx = (p+x);
                    (p+pos)->fratellodx = NULL;
                    (p+x)->fratellodx = (p+pos);
                    p->spiazzamento = pos;
                }
                printf("ok\n");
            }
        }
    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void read (char *percorso, nodo *p){

    int temp, slash=0, i, lperc, SIZE, fck=0, jal;
    char *name=NULL;
    char *perc=NULL;
    char *ptt=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    ptt = strtok (percorso, "/");
    while (ptt != NULL){
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return;
        }
        jal = NICO;
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL)
            strcpy(name, (p+temp)->nome);
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0 && (p+temp)->file == TRUE){
                if ((p+temp)->contenuto == NULL){
                    printf("contenuto \n");
                    return;
                }
                else{
                    printf("contenuto %s\n",(p+temp)->contenuto);
                    return;
                }
            }
            else if(slash > 0 && (p+temp)->file == FALSE){
                p = (p+temp)->figliosx;
            }
            else {
                printf("no\n");
                return;
            }
        }
        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){
                        p = (p+temp)->figliosx;
                        fck = 1;
                        break;
                    }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (fck == 0){
                    printf("no\n");
                    return;
                }
                fck = 0;
            }
            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp (name, ptt) == 0 && (p+temp)->file == 0){
                        printf("no\n");
                        return;
                    }
                    else if (strcmp (name, ptt) == 0 && (p+temp)->file == 1){
                        if ((p+temp)->contenuto == NULL){
                            printf("contenuto \n");
                            return;
                        }
                        else{
                            printf("contenuto %s\n",(p+temp)->contenuto);
                            return;
                        }
                    }
                    temp++;
                    if ((temp) == (p->hashing))
                        (temp) = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                printf("no\n");
            }
        }

    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void write (char *percorso, char *cont, nodo *p){

    char *ptt=NULL;
    int temp, i, slash=0, lperc, lcont, SIZE, fck=0, jal;
    char *name=NULL;
    char *perc=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    lcont = strlen(cont);
    ptt = strtok(percorso, "/");
    while (ptt != NULL){
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return;
        }
        jal = NICO;
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL)
            strcpy(name, (p+temp)->nome);
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0 && (p+temp)->file == TRUE){
                if (((p+temp)->contenuto = (char*)calloc((lcont+1),sizeof(char))) == NULL){
                    printf("errore malloc\n");
                    return;
                }
                strcpy((p+temp)->contenuto, cont);
                printf("ok %d\n", lcont);
                return;
            }
            else if(slash > 0 && (p+temp)->file == FALSE){
                p = (p+temp)->figliosx;
            }
            else {
                printf("no\n");
                return;
            }
        }

        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){
                        p = (p+temp)->figliosx;
                        fck = 1;
                        break;
                    }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                if (fck == 0){
                    printf("no\n");
                    return;
                }
                fck = 0;
            }
            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp (name, ptt) == 0 && (p+temp)->file == 0){
                        printf("no\n");
                        return;
                    }
                    else if (strcmp (name, ptt) == 0 && (p+temp)->file == 1){
                        if (((p+temp)->contenuto = (char*)calloc((lcont+1),sizeof(char))) == NULL){
                            printf("errore malloc\n");
                            return;
                        }
                        strcpy((p+temp)->contenuto, cont);
                        printf("ok %d\n", lcont);
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
                printf("no\n");
            }
        }

    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void delet (char *percorso, nodo *p){

    char *ptt=NULL;
    int temp, slash=0, i=0, lperc, SIZE, fck=0, jal;
    char *name=NULL;
    struct _nodo *np = NULL;
    struct _nodo *xy = NULL;
    char *perc=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    ptt = strtok(percorso, "/");
    while (ptt != NULL){
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return;
        }
        jal = NICO;
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL)
            strcpy(name, (p+temp)->nome);
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0){
                if ((p+temp)->file == TRUE){            //se è un file
                    if(p->padre != NULL){
                        np = p->padre;
                        np->ampiezza--;
                    }
                    if(p->verifica == 91){
                        p->ampiezza--;
                    }
                    free((p+temp)->nome);
                    free((p+temp)->percorso);
                    (p+temp)->nome = NULL;
                    (p+temp)->percorso = NULL;
                    if ((p+temp)->contenuto != NULL){
                        free((p+temp)->contenuto);
                        (p+temp)->contenuto = NULL;
                    }
                    (p+temp)->file = FALSE;
                    (p+temp)->key = 0;
                    np = (p+temp)->fratellosx;
                    xy = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    if ((p+temp)->fratellodx != NULL){
                        xy->fratellosx = (p+temp)->fratellosx;
                    }
                    else {
                        if (np->file == 2){
                            np->spiazzamento = 0;
                        }
                        else {
                            p->spiazzamento = np->key;
                        }
                    }
                    printf("ok\n");
                    break;
                }
                else if ((p+temp)->ampiezza == 0){      //se è una directory
                    if(p->padre != NULL){
                        np = p->padre;
                        np -> ampiezza--;
                    }
                    if(p->verifica == 91){
                        p->ampiezza--;
                    }
                    free((p+temp)->nome);
                    free((p+temp)->percorso);
                    (p+temp)->nome = NULL;
                    (p+temp)->percorso = NULL;
                    (p+temp)->key = 0;
                    np = (p+temp)->fratellosx;
                    xy = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    if ((p+temp)->fratellodx != NULL){
                        xy->fratellosx = (p+temp)->fratellosx;
                    }
                    else {
                        if (np->file == 2){
                            np->spiazzamento = 0;
                        }
                        else {
                            p->spiazzamento = np->key;
                        }
                    }
                    p = (p+temp)->figliosx;
                    free(p);
                    printf("ok\n");
                    break;
                }
                else {
                    printf("no\n");
                    break;
                }
            }
            else {
                if ((p+temp)->file == 0){
                    p = (p+temp)->figliosx;
                }
                else{
                    printf("no\n");
                    return;
                }
            }
        }

        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){        //se lo trovi ed è una cartella
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;
                        }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
            }
            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0){
                        fck = 1;
                        break;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
            }
            if (fck == 0){
                printf("no\n");
                return;
            }
            fck = 0;
            if ((p+temp)->file == TRUE){            //se è un file
                if(p->padre != NULL){
                    np = p->padre;
                    np->ampiezza--;
                }
                if(p->verifica == 91){
                    p->ampiezza--;
                }
                free((p+temp)->nome);
                free((p+temp)->percorso);
                (p+temp)->nome = NULL;
                (p+temp)->percorso = NULL;
                if ((p+temp)->contenuto != NULL){
                    free((p+temp)->contenuto);
                    (p+temp)->contenuto = NULL;
                }
                (p+temp)->file = FALSE;
                (p+temp)->key = 0;
                np = (p+temp)->fratellosx;
                xy = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                if ((p+temp)->fratellodx != NULL){
                    xy->fratellosx = (p+temp)->fratellosx;
                }
                else {
                    if (np->file == 2){
                        np->spiazzamento = 0;
                    }
                    else {
                        p->spiazzamento = np->key;
                    }
                }
                printf("ok\n");
                break;
            }
            else if ((p+temp)->ampiezza == 0 && (p+temp)->file == 0){      //se è una directory vuota
                if(p->padre != NULL){
                    np = p->padre;
                    np -> ampiezza--;
                }
                if(p->verifica == 91){
                    p->ampiezza--;
                }
                free((p+temp)->nome);
                free((p+temp)->percorso);
                (p+temp)->nome = NULL;
                (p+temp)->percorso = NULL;
                (p+temp)->key = 0;
                np = (p+temp)->fratellosx;
                xy = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                if ((p+temp)->fratellodx != NULL){
                    xy->fratellosx = (p+temp)->fratellosx;
                }
                else {
                    if (np->file == 2){
                        np->spiazzamento = 0;
                    }
                    else {
                        p->spiazzamento = np->key;
                    }
                }
                p = (p+temp)->figliosx;
                free(p);
                printf("ok\n");
                break;
            }
        }
    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void delet_r (char *percorso, nodo *p){

    int temp, slash=0, i=0, lperc, SIZE, fck=0, jal;
    struct _nodo *np = NULL;
    struct _nodo *xy = NULL;
    char *perc=NULL;
    char *name=NULL;
    char *ptt=NULL;

    lperc = strlen(percorso);
    if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
        printf("errore malloc\n");
        return;
    }
    strcpy(perc, percorso);
    for(i=0; i<=lperc || perc[i] == '\0'; i++){
        if (perc[i] == '/')
            slash++;
    }
    ptt = strtok(percorso, "/");
    while (ptt != NULL){
        if ((name = (char*)calloc((strlen(ptt)+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return;
        }
        jal = NICO;
        slash--;
        SIZE = p->hashing;
        temp = hashfun(ptt, SIZE);
        if ((p+temp)->nome != NULL)
            strcpy(name, (p+temp)->nome);
        else
            strcpy(name, "\0");
        if (strcmp(name, ptt) == 0){
            if (slash == 0){
                if ((p+temp)->file == TRUE){            //se è un file
                    if (p->padre != NULL){
                        np = p->padre;
                        np->ampiezza--;
                    }
                    if(p->verifica == 91){
                        p->ampiezza--;
                    }
                    free((p+temp)->nome);
                    free((p+temp)->percorso);
                    (p+temp)->nome = NULL;
                    (p+temp)->percorso = NULL;
                    if ((p+temp)->contenuto != NULL){
                        free((p+temp)->contenuto);
                        (p+temp)->contenuto = NULL;
                    }
                    (p+temp)->file = FALSE;
                    (p+temp)->key = 0;
                    np = (p+temp)->fratellosx;
                    xy = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    if ((p+temp)->fratellodx != NULL){
                        xy->fratellosx = (p+temp)->fratellosx;
                    }
                    else {
                        if (np->file == 2){
                            np->spiazzamento = 0;
                        }
                        else {
                            p->spiazzamento = np->key;
                        }
                    }
                    printf("ok\n");
                    break;
                }
                else if ((p+temp)->ampiezza == 0){      //se è una directory vuota
                    if (p->padre != NULL){
                        np = p->padre;
                        np -> ampiezza--;
                    }
                    if(p->verifica == 91){
                        p->ampiezza--;
                    }
                    free((p+temp)->nome);
                    free((p+temp)->percorso);
                    (p+temp)->nome = NULL;
                    (p+temp)->percorso = NULL;
                    (p+temp)->key = 0;
                    np = (p+temp)->fratellosx;
                    xy = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    if ((p+temp)->fratellodx != NULL){
                        xy->fratellosx = (p+temp)->fratellosx;
                    }
                    else {
                        if (np->file == 2){
                            np->spiazzamento = 0;
                        }
                        else {
                            p->spiazzamento = np->key;
                        }
                    }
                    p = (p+temp)->figliosx;
                    free(p);
                    printf("ok\n");
                    break;
                }
                else if ((p+temp)->ampiezza > 0){      //se è una directory piena
                    if (p->padre != NULL){
                        np = p->padre;
                        np -> ampiezza--;
                    }
                    if(p->verifica == 91){
                        p->ampiezza--;
                    }
                    free((p+temp)->nome);
                    free((p+temp)->percorso);
                    (p+temp)->nome = NULL;
                    (p+temp)->percorso = NULL;
                    (p+temp)->ampiezza = 0;
                    (p+temp)->padre = NULL;
                    (p+temp)->key = 0;
                    np = (p+temp)->fratellosx;
                    xy = (p+temp)->fratellodx;
                    np->fratellodx = (p+temp)->fratellodx;
                    if ((p+temp)->fratellodx != NULL){
                        xy->fratellosx = (p+temp)->fratellosx;
                    }
                    else {
                        if (np->file == 2){
                            np->spiazzamento = 0;
                        }
                        else {
                            p->spiazzamento = np->key;
                        }
                    }
                    p = (p+temp)->figliosx;
                    visita(p);
                    printf("ok\n");
                    break;
                }
                else {
                    printf("no\n");
                    break;
                }
            }
            else {
                p = (p+temp)->figliosx;
            }
        }

        else {
            if (slash > 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0 && (p+temp)->file == 0){        //se lo trovi ed è una cartella
                            p = (p+temp)->figliosx;
                            fck = 1;
                            break;
                        }
                    else if (strcmp(name, ptt) == 0 && (p+temp)->file == 1){
                        printf("no\n");
                        return;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
            }
            if (slash == 0){
                while ((p+temp)->used == 1){
                    if ((p+temp)->nome != NULL)
                        strcpy (name, (p+temp)->nome);
                    else
                        strcpy (name, "\0");
                    if (strcmp(name, ptt) == 0){
                        fck = 1;
                        break;
                    }
                    temp++;
                    if (temp == (p->hashing))
                        temp = 1;
                    jal--;
                    if (jal == 0){
                        printf("no\n");
                        return;
                    }
                }
            }
            if (fck == 0){
                printf("no\n");
                return;
            }
            fck = 0;
            if ((p+temp)->file == TRUE){            //se è un file
                if(p->padre != NULL){
                    np = p->padre;
                    np->ampiezza--;
                }
                if(p->verifica == 91){
                    p->ampiezza--;
                }
                free((p+temp)->nome);
                free((p+temp)->percorso);
                (p+temp)->nome = NULL;
                (p+temp)->percorso = NULL;
                if ((p+temp)->contenuto != NULL){
                    free((p+temp)->contenuto);
                    (p+temp)->contenuto = NULL;
                }
                (p+temp)->file = FALSE;
                (p+temp)->key = 0;
                np = (p+temp)->fratellosx;
                xy = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                if ((p+temp)->fratellodx != NULL){
                    xy->fratellosx = (p+temp)->fratellosx;
                }
                else {
                    if (np->file == 2){
                        np->spiazzamento = 0;
                    }
                    else {
                        p->spiazzamento = np->key;
                    }
                }
                printf("ok\n");
                break;
            }
            else if ((p+temp)->ampiezza == 0 && (p+temp)->file == 0){      //se è una directory vuota
                if(p->padre != NULL){
                    np = p->padre;
                    np -> ampiezza--;
                }
                if(p->verifica == 91){
                    p->ampiezza--;
                }
                free((p+temp)->nome);
                free((p+temp)->percorso);
                (p+temp)->nome = NULL;
                (p+temp)->percorso = NULL;
                (p+temp)->key = 0;
                np = (p+temp)->fratellosx;
                xy = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                if ((p+temp)->fratellodx != NULL){
                    xy->fratellosx = (p+temp)->fratellosx;
                }
                else {
                    if (np->file == 2){
                        np->spiazzamento = 0;
                    }
                    else {
                        p->spiazzamento = np->key;
                    }
                }
                p = (p+temp)->figliosx;
                free(p);
                printf("ok\n");
                break;
            }
            else if ((p+temp)->ampiezza > 0 && (p+temp)->file == 0){      //se è una directory piena
                if(p->padre != NULL){
                    np = p->padre;
                    np -> ampiezza--;
                }
                if(p->verifica == 91){
                    p->ampiezza--;
                }
                free((p+temp)->nome);
                free((p+temp)->percorso);
                (p+temp)->nome = NULL;
                (p+temp)->percorso = NULL;
                (p+temp)->key = 0;
                (p+temp)->ampiezza = 0;
                (p+temp)->padre = NULL;
                np = (p+temp)->fratellosx;
                xy = (p+temp)->fratellodx;
                np->fratellodx = (p+temp)->fratellodx;
                if ((p+temp)->fratellodx != NULL){
                    xy->fratellosx = (p+temp)->fratellosx;
                }
                else {
                    if (np->file == 2){
                        np->spiazzamento = 0;
                    }
                    else {
                        p->spiazzamento = np->key;
                    }
                }
                p = (p+temp)->figliosx;
                visita(p);
                printf("ok\n");
                break;
            }
        }
    free (name);
    name = NULL;
    ptt = strtok(NULL, "/");
    }
    free(perc);
    perc=NULL;
}

void find (char *risorsa, nodo *p){

    int cont=0;
    LISTA *h=NULL, *stmp=NULL;

    h = cerca(risorsa, p, h);

	for(stmp=h; stmp; stmp=stmp->next){
            cont++;
			printf("ok %s\n",stmp->info);
	}
	if(cont == 0)
        printf("no\n");

    free (h);
    h = NULL;

}

LISTA *cerca (char *risorsa, nodo *p, LISTA *h){

    int lperc=0, num=0;
    char *name=NULL;
    char *perc=NULL;

    if (p == NULL)
        return h;

    h = cerca (risorsa, p->figliosx, h);
    if (p->nome != NULL){
        num = strlen(p->nome);
        if ((name = (char*)calloc((num+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return NULL;
        }
        strcpy (name, p->nome);
    }
    else{
        num = 1;
        if ((name = (char*)calloc((num+1),sizeof(char))) == NULL){
            printf("errore malloc\n");
            return NULL;
        }
        strcpy (name, "\0");
    }
    if(strcmp(risorsa, name) == 0){
        if (p->percorso != NULL){
            lperc = strlen(p->percorso);
            if ((perc = (char*)calloc((lperc+1),sizeof(char))) == NULL){
                printf("errore malloc\n");
                return NULL;
            }
            strcpy (perc, p->percorso);
        }
        h = inserisci(h, perc);
        free (perc);
        perc = NULL;
    }
    h = cerca (risorsa, p->fratellodx, h);

    free (name);
    name = NULL;
    return h;

}

void visita (nodo *p){

    if (p == NULL)
        return;

    visita(p->figliosx);
    free(p->figliosx);
    p->figliosx = NULL;
    visita(p->fratellodx);

    if (p->nome != NULL){
    free(p->nome);
        p->nome = NULL;
    }
    if (p->percorso != NULL){
    free(p->percorso);
        p->percorso = NULL;
    }
    if (p->contenuto != NULL){
    free(p->contenuto);
        (p->contenuto) = NULL;
    }

}

LISTA *inserisci(LISTA *h, char *perc){

	LISTA *newel=NULL, *prec=NULL, *curr=NULL;
	int i=0, num;

	curr = h;
	num = strlen (perc);

	if(!h){
		if((newel=(LISTA*)calloc(1,sizeof(LISTA))) != NULL){
            if((newel->info=(char*)calloc((num+1),sizeof(char))) != NULL){
            strcpy(newel->info, perc);
            newel->next=NULL;
            h=newel;
            curr=h;
            }
		}
		else
            return NULL;
	}
	else {
        while (i < num && curr != NULL){
            if(perc[i] == curr->info[i]){
                i++;
            }
            else if(perc[i] > curr->info[i]){
                prec = curr;
                curr = curr->next;
                i=0;
            }
            else {
                break;
            }
        }
        if((newel=(LISTA*)calloc(1,sizeof(LISTA))) != NULL){
            if((newel->info=(char*)malloc(num+1)) != NULL){
                strcpy (newel->info, perc);
                newel->next = curr;
                if (prec != NULL)
                    prec->next = newel;
                else
                    h = newel;
            }
        }
        else
            return NULL;
	}
	return h;
}

void rehash (nodo *p){

    struct _nodo *np=NULL;
    struct _nodo *np2=NULL;
    int SIZE, temp=0, x=0;
    struct _nodo *newel=NULL;

    SIZE = p->hashing;
    np2 = p->figliosx;
    if ((newel = (nodo*)calloc(SIZE, sizeof(nodo))) != NULL){
        newel->padre = p;
        p->figliosx = newel;
    }
    else {
        printf ("no\n");
    }
    newel->ampiezza = np2->ampiezza;
    newel->file = np2->file;
    newel->verifica = np2->verifica;
    newel->hashing = SIZE;

    for (np = np2->fratellodx; np != NULL; np = np->fratellodx) {
        temp = hashfun(np->nome, SIZE);   //devo caricare in un vettore?
        while ((newel+temp)->used == 1){
            temp ++;
            if (temp == (newel->hashing))
                temp = 1;
        }
        (newel+temp)->ampiezza = np->ampiezza;
        (newel+temp)->file = np->file;
        (newel+temp)->hashing = np->hashing;
        (newel+temp)->used = 1;
        (newel+temp)->padre = np->padre;        //serve? se è null?
        if (np->figliosx != NULL)
            (newel+temp)->figliosx = np->figliosx;
        if(((newel+temp)->nome=(char*)malloc((strlen(np->nome)+1)*sizeof(char))) == NULL){
            printf("errore\n");
            return;
        }
        strcpy((newel+temp)->nome, np->nome);
        if(((newel+temp)->percorso=(char*)malloc((strlen(np->percorso)+1)*sizeof(char))) == NULL){
            printf("errore\n");
            return;
        }
        strcpy((newel+temp)->percorso, np->percorso);
        if (np->contenuto != NULL){
            if(((newel+temp)->contenuto=(char*)malloc((strlen(np->contenuto)+1)*sizeof(char))) == NULL){
                printf("errore\n");
                return;
            }
            strcpy((newel+temp)->contenuto, np->contenuto);
        }
        if (newel->spiazzamento == 0){
            newel->spiazzamento = temp;
            newel->fratellodx = (newel+temp);
            (newel+temp)->fratellosx = newel;
            (newel+temp)->fratellodx = NULL;
        }
        else{
            x = newel->spiazzamento;
            (newel+temp)->fratellosx = (newel+x);
            (newel+temp)->fratellodx = NULL;
            (newel+x)->fratellodx = (newel+temp);
            newel->spiazzamento = temp;
        }
    }
    free (np2);
    np2 = NULL;

}

unsigned hashfun(char *s, int SIZE){

    unsigned value;
    for (value = 0;*s!= '\0'; s++){
        value = *s + 31 * value;
    }
    value = value%SIZE;
    if (value == 0)
        value++;
    return (value);
}

nodo *creadir (nodo *p, int SIZE){

    struct _nodo *newel=NULL;
    if ((newel = (nodo*)calloc(SIZE,sizeof(nodo))) != NULL){
        newel->padre = p;
        p->figliosx = newel;
        newel->hashing = SIZE;
    }
    else {
        printf ("no\n");
    }
    return p;
}
