#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
struct Player
{
    char *firstName;
    char *secondName;
    int points;
};
typedef struct Player player;
struct Team
{
    int nr_players;
    player *k;
    char *name_team;
    float rez;
    struct Team *next;
};
typedef struct Team team;
//1
void add_node(team **head,int *n,FILE *file_LAN)
{
    team *p;
    //int n;
    int c;
    char x[40];
    fscanf(file_LAN,"%d",n);
    printf("%d", *n);
   // while ((c=fgetc(file_LAN))!=EOF && c!='\n') {continue;}

    for(int j=0;j<*n;j++)
    {
    p=(team*)malloc(sizeof(team));
    p->name_team=(char*)malloc(40*sizeof(char));
    fscanf(file_LAN,"%d", &p->nr_players);
    //printf("%d\n", p->nr_players);
    fgetc(file_LAN);
    fgets(x,40,file_LAN);
    strcpy(p->name_team,x);
    p->k=(player*)malloc(sizeof(player)*(p->nr_players));
    for(int i=0;i<p->nr_players;i++)
    {
        p->k[i].firstName=(char*)malloc(20*sizeof(char));
        p->k[i].secondName=(char*)malloc(20*sizeof(char));
        fscanf(file_LAN,"%s %s %d", p->k[i].firstName, p->k[i].secondName, &(p->k[i].points));

        while ((c=fgetc(file_LAN))!=EOF && c!='\n') {continue;}

    }

    p->next=*head;
    *head=p;
    }
    
} 
//2
void delete_team(team **head)
{
    if (*head==NULL) {
        printf("Stack is empty!\n");
        return;
    }
    team *p,*aux,*temp;
    float min=INT_MAX,s;
    for(p=*head;p!=NULL;p=p->next)
    {
        s=0;
        for(int i=0;i<p->nr_players;i++)
            s=s+p->k[i].points;
        p->rez=s/p->nr_players;
        if(p->rez<min)
            min=p->rez;
    }
    for(p=*head;p!=NULL;p=p->next)
    {

        if(p->rez==min)
          {if(p==*head)
           {
            aux=*head;
            *head=(*head)->next;
            free(aux);
            break;

           }
            aux->next=p->next;
            free(p);
            break;
          }


     aux=p;

    }
}
//3
struct Elem_Queue
{  char *name_t;
   struct Elem_Queue *next ;

};
typedef struct Elem_Queue Queue_Node ;
struct Q
{
   Queue_Node * front ,* rear ;
};
typedef struct Q Queue ;
Queue* createQueue(){
	Queue *q;
	q=(Queue *)malloc(sizeof(Queue));
	if (q==NULL) return NULL;
	q->front=q->rear=NULL;
	return q;
}

 void enQueue(Queue*q, char v[]){
	Queue_Node* newNode=(Queue_Node*)malloc(sizeof(Queue_Node));
	newNode->name_t=(char*)malloc(40*sizeof(char));
    //printf("%s", v);
	strcpy(newNode->name_t,v);
	newNode->next=NULL;
	if (q->rear==NULL) q->rear=newNode;
	else{
		(q->rear)->next=newNode;
		(q->rear)=newNode;
	}
	if (q->front==NULL) q->front=q->rear;
}
int isEmpty_Queue(Queue*q){
	return (q->front==NULL);
}
char* deQueue(Queue*q) {
	Queue_Node* aux; char *d;
	if (isEmpty_Queue(q)) return INT_MIN;
    d=(char*)malloc(40*sizeof(char));
	aux=q->front;
	strcpy(d,aux->name_t);
	q->front=(q->front)->next;
	free(aux);
	return d;
}


void deleteQueue(Queue*q){
	Queue_Node* aux;
	while (!isEmpty_Queue(q)){
		aux=q->front;
		q->front=q->front->next;
		free(aux);
	}
	free(q);
}
struct Elem_Stack
{  char *name_t;
   struct Elem_Stack *next ;

};
typedef struct Elem_Stack Stack_Node ;

int isEmpty_Stack(Stack_Node*top){
    if( top==NULL )
	   return 0;
}
void push(Stack_Node**top, char v[]) {
	Stack_Node* newNode=(Stack_Node*)malloc(sizeof(Stack_Node));
	newNode->name_t=(char*)malloc(40*sizeof(char));
	strcpy(newNode->name_t,v);
	newNode->next=*top;
	*top=newNode;
}

char pop(Stack_Node**top) {
	if (isEmpty_Stack(*top)) return INT_MIN;
	Stack_Node *temp=(*top);
	char aux;
	strcpy(aux,temp->name_t);
	*top=(*top)->next;
	free(temp);
	return aux;
}

void deleteStack(Stack_Node**top){
	Stack_Node *temp;
	while (!isEmpty_Stack(*top))
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
void match(int *ok,team *head,Queue **r,FILE *file_TEAMS)
{
    int i,k,l,j;
    team *q;
    Queue_Node *rc;
    Stack_Node *top1=NULL,*top2=NULL,*st;
    float s1=0,s2=0,rez1,rez2;
    fprintf(file_TEAMS,"--- ROUND N0:%d",*ok);
    fputc('\n',file_TEAMS);
    if ((*r)->front == NULL) {
    printf("Coada este goală.\n");
    }
    for(rc=(*r)->front,i=1;rc!=NULL;rc=rc->next,i++)
    {fputs(rc->name_t,file_TEAMS);
     //printf("%s\n", rc->name_t);
     if(i%2==1)
        {
            l=33-strlen((rc->next)->name_t);
            k=33-strlen(rc->name_t)-1;
            for(j=1;j<=k;j++)
               fputc(' ',file_TEAMS);
            fputc('-',file_TEAMS);
            for(j=1;j<=l;j++)
               fputc(' ',file_TEAMS);
        }
    else fputc('\n',file_TEAMS);
    }
    
    fprintf(file_TEAMS,"WINNERS OF THE ROUND NO:%d",*ok);
    fputc('\n',file_TEAMS);
    for(rc=(*r)->front;rc!=NULL;rc=rc->next)
        {for(q=head;q!=NULL;q=q->next)
           if(strcmp(rc->name_t,q->name_team)==0)
              {rez1=q->rez;
               break;
              }
        for(q=head;q!=NULL;q=q->next)
            if(strcmp((rc->next)->name_t,q->name_team)==0)
               {rez2=q->rez;
                break;
               }
        if(rez1>=rez2)
          {push(&top1,rc->name_t);
           push(&top2,(rc->next)->name_t);
           k=34-strlen(rc->name_t)-1;
           fputs(rc->name_t,file_TEAMS);
           for(j=1;j<=k;j++)
               fputc(' ',file_TEAMS);
            fputc('-',file_TEAMS);
            for(j=1;j<=2;j++)
               fputc(' ',file_TEAMS);
           for(q=head;q!=NULL;q=q->next)
             if(strcmp(rc->name_t,q->name_team)==0)
                {fprintf(file_TEAMS,"%f",q->rez);
                 break;
                 }
           fputc('\n',file_TEAMS);
          }
        else {push(&top1,(rc->next)->name_t);
           push(&top2,rc->name_t);
           k=34-strlen((rc->next)->name_t);
           fputs((rc->next)->name_t,file_TEAMS);
           for(j=1;j<=k;j++)
               fputc(' ',file_TEAMS);
            fputc('-',file_TEAMS);
            for(j=1;j<=2;j++)
               fputc(' ',file_TEAMS);
           for(q=head;q!=NULL;q=q->next)
             if(strcmp((rc->next)->name_t,q->name_team)==0)
                {fprintf(file_TEAMS,"%f",q->rez);
                 break;
                }
           fputc('\n',file_TEAMS);
          }
        rc=rc->next;
        }
    deleteStack(&top2);
    for(st=top1;st!=NULL;st=st->next)
        for(q=head;q!=NULL;q=q->next)
           if(strcmp(st->name_t,q->name_team)==0)
              {q->rez=q->rez+1;
               break;
              }
    deleteQueue(&r);
    (*r)=createQueue();
    for(st=top1;st!=NULL;st=st->next)
       enQueue(&r,st->name_t);
    deleteStack(&top1);
    (*ok)++;
} 
int main(int argc, char* argv[])
{
    
    int a,n,m,i,j;
    team *head=NULL,*q,*first8=NULL,*ql=NULL;
   Queue *r=NULL;
   Queue_Node *rc;
    int cerinte[5];
    FILE *f;
    FILE *file_LAN;
    f=fopen(argv[1], "rt");
    if(f==NULL){
      printf("ERROR \n");
      exit(1);
    }
    for(i=0;i<5;i++){
        fscanf(f,"%d",&cerinte[i]);
        }
    fclose(f);
    if(cerinte[0]==1){

        file_LAN=fopen(argv[2], "rt");
        if(file_LAN==NULL){
            printf("ERROR \n");
            exit(1);
            }
             FILE *file_TEAMS;
             file_TEAMS=fopen(argv[3], "w");
             if(file_TEAMS==NULL){
                printf("ERROR \n");
                exit(1);
             }
        add_node(&head,&n,file_LAN);
        for(q=head;q!=NULL;q=q->next){
            fprintf(file_TEAMS,"%s",q->name_team);
        }
        fclose(file_LAN);
        fclose(file_TEAMS);
            } 
    if(cerinte[1]==1)
    {
        FILE *file_TEAMS;
        file_TEAMS=fopen(argv[3], "wt");
        if(file_TEAMS==NULL){
            printf("ERROR \n");
            exit(1);
            }
    a=2;
    while(a<n)
      a=a*2;
    m=a/2;
    for(i=0;i<(n-m);i++)
      delete_team(&head);
    for(q=head;q!=NULL;q=q->next)
    {//printf("%s\n", q->name_team); merge
     fprintf(file_TEAMS,"%s",q->name_team);
    }
    fclose(file_TEAMS);
    }
    
    if(cerinte[2]==1)
    {
        FILE *file_TEAMS;
        file_TEAMS=fopen(argv[3], "at");
        if(file_TEAMS==NULL){
            printf("ERROR \n");
            exit(1);
            }
    
    r=createQueue();
    for(q=head;q!=NULL;q=q->next)
       {enQueue(r,q->name_team);
       //printf("%s",q->name_team);
       }
    int ok=1;
    for(j=m;j>=8;j=j/2)
       match(&ok,head,&r,file_TEAMS);
    for(rc=r->front;rc!=NULL;rc=rc->next)
       for(q=head;q!=NULL;q=q->next)
         if(strcmp(rc->name_t,q->name_team)==0)
    {
        ql=q;
        ql->next=first8;
        first8=ql;
    }
    for(j=8;j>=1;j=j/2)
        match(&ok,head,&r,file_TEAMS);
    fclose(file_TEAMS);
    }
  











}
