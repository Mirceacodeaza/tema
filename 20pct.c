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
    int c;
    char x[40];
    fscanf(file_LAN,"%d",n);
    for(int j=0;j<*n;j++)
    {
    p=(team*)malloc(sizeof(team));
    fscanf(file_LAN,"%d", &p->nr_players);
    fgetc(file_LAN);
    fscanf(file_LAN,"%[^\n]", x);
    //fgets(x,40,file_LAN);
    p->name_team=(char*)malloc(strlen(x)*sizeof(char)+1);
    strcpy(p->name_team,x);
    //strcat(x,"\0");
    p->k=(player*)malloc(sizeof(player)*(p->nr_players));
    for(int i=0;i<p->nr_players;i++)
    {
        p->k[i].firstName=(char*)malloc(strlen(x)*sizeof(char)+1);
        p->k[i].secondName=(char*)malloc(strlen(x)*sizeof(char)+1);
        fscanf(file_LAN,"%s", x);
        p->k[i].firstName=(char*)malloc(20*sizeof(char));
        strcpy(p->k[i].firstName,x);
        fscanf(file_LAN,"%s", x);
        p->k[i].secondName=(char*)malloc(strlen(x)*sizeof(char)+1);
        fscanf(file_LAN,"%d", &(p->k[i].points));
        strcpy(p->k[i].secondName,x);
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
        p->rez=s/p->nr_players;               //calcularea punctajelor pentru fiecare echipa
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
            free(aux);               //eliminarea echipei cu punctaj minim
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
	newNode->name_t=(char*)malloc(strlen(v)*sizeof(char)+1);
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
char deQueue(Queue*q) {
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
	return (top==NULL);
}
char top(Stack_Node *top){
	if (isEmpty_Stack(top)) return INT_MIN;
	return top->name_t;
}

void push(Stack_Node**top, char v[]) {
	Stack_Node* newNode=(Stack_Node*)malloc(sizeof(Stack_Node));
	newNode->name_t=(char*)malloc(strlen(v)*sizeof(char)+1);
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
		{temp=*top;
		*top=(*top)->next;
		free(temp);
        }
	}
void match(int *ok,team *head,Queue **r,FILE *file_TEAMS,int x)
{
    int i,k,l,j;
    team *q;
    Queue_Node *rc;
    Stack_Node *top1=NULL,*top2=NULL,*st;
    float s1=0,s2=0,rez1,rez2;
    fprintf(file_TEAMS,"--- Round N0.%d",*ok);
    fputc('\n',file_TEAMS);
    for(rc=(*r)->front,i=1;rc!=NULL;rc=rc->next,i++)
    {fputs(rc->name_t,file_TEAMS);
     if(i%2==1)
        {
            l=33-strlen((rc->next)->name_t);          //calculul de spatii ce trebuie puse intre numele echipelor si - 
            k=33-strlen(rc->name_t)-1;                
            for(j=1;j<=k;j++)
               fputc(' ',file_TEAMS);
            fputc('-',file_TEAMS);
            for(j=1;j<=l;j++)
               fputc(' ',file_TEAMS);
        }
    else fputc('\n',file_TEAMS);
    }
    fprintf(file_TEAMS,"WINNERS OF THE ROUND NO.%d:",*ok);
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
        if(rez1>=rez2)                                    //compararea punctajelor celor 2 echipe care se dueleaza
          {push(&top1,rc->name_t);
           push(&top2,(rc->next)->name_t);
           k=34-strlen(rc->name_t)-1;                   //calculul de spatii ce trebuie puse intre numele echipei castigatoare si -
           fputs(rc->name_t,file_TEAMS);
           for(j=1;j<=k;j++)
               fputc(' ',file_TEAMS);
            fputc('-',file_TEAMS);
            for(j=1;j<=2;j++)
               fputc(' ',file_TEAMS);
           for(q=head;q!=NULL;q=q->next)
             if(strcmp(rc->name_t,q->name_team)==0)
                {fprintf(file_TEAMS,"%.2f",q->rez);
                 break;
                 }
           fputc('\n',file_TEAMS);
          }                                           //adaugarea in stive a echipelor castigatoare respectiv pierzatoare
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
                {fprintf(file_TEAMS,"%.2f",q->rez);
                 break;
                }
           fputc('\n',file_TEAMS);
          }
          if(x==4)                 //dupa scrierea echipei castigatoare functia trebuie incheiata
              return;
        rc=rc->next;
        }
    deleteStack(&top2);           //stergerea echipelor pierzatoare
    for(st=top1;st!=NULL;st=st->next)
        for(q=head;q!=NULL;q=q->next)
           if(strcmp(st->name_t,q->name_team)==0)
              { 
                
                q->rez=q->rez+1;                 //cresterea punctajului de echipa dupa victoarie
               break;
               
              }
    deleteQueue(*r);
    (*r)=createQueue();
    for(st=top1;st!=NULL;st=st->next)
       enQueue(*r,st->name_t);                 //reumplerea cozii cu echipe castigatoare
    deleteStack(&top1);                     //stergerea echipelor castigatoare
    (*ok)++;
    
    
} 
int main(int argc, char* argv[])
{
    
    int a,n,m,i,j;
    team *head=NULL,*q,*first8=NULL,*ql=NULL;
    Queue *r;
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
            fprintf(file_TEAMS,"%s\n",q->name_team);
            //fputc(' ',file_TEAMS);
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
    m=a/2;                              //aflarea celei mai mari puteri a lui 2, mai mica decat numarul initial de echipe
    for(i=0;i<(n-m);i++)
      delete_team(&head);
    for(q=head;q!=NULL;q=q->next)
    {
     fprintf(file_TEAMS,"%s\n",q->name_team);
       //fputc(' ',file_TEAMS);
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
       enQueue(r,q->name_team);
    int ok=1;
    for(j=m;j>=8;j=j/2)
       match(&ok,head,&r,file_TEAMS,j);
    for(rc=r->front;rc!=NULL;rc=rc->next)          //memorarea ultimelor 8 echipe
       for(q=head;q!=NULL;q=q->next)
         if(strcmp(rc->name_t,q->name_team)==0)
    {
        ql=q;
        ql->next=first8;
        first8=ql;
    }
    for(j=8;j>2;j=j/2)
        match(&ok,head,&r,file_TEAMS,j);
    fclose(file_TEAMS);
    }
   












}
