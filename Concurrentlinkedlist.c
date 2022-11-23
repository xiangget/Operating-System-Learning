#include<stdio.h>
#include<pthread.h>

typedef struct node_t{
    int   key;
    struct node_t *next;
}node_t;

typedef struct list_t{
    node_t *head;
    pthread_mutex_t  lock;
}list_t;

void List_Init(list_t *L){
    L->head=NULL;
    pthread_mutex_init(&L->lock,NULL);
}


void List_Inset(list_t *L,int key){
    
    node_t *new=malloc(sizeof(node_t));
    if(new==NULL){
        perror("malloc");
        return ;
    }
    pthread_mutex_lock(&L->lock);
    new->key=key;
    new->next=L->head;
    L->head=new;
    pthread_mutex_unlock(&L->lock);
    return ;
}

int List_Lookup(list_t *L,int key){
    int val=-1;
    pthread_mutex_lock(&L->lock);
    node_t *curr=L->head;
    while(curr){
        if(curr->key==key){
            val=0;
            break;
        }
        curr=curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    free(curr);
    return val;
}














