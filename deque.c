#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;
    
    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
            case push:
                scanf("%d", &X);
                if (!Push(X, D)) printf("Memory is Full!\n");
                break;
            case pop:
                X = Pop(D);
                if ( X==ERROR ) printf("Deque is Empty!\n");
                break;
            case inject:
                scanf("%d", &X);
                if (!Inject(X, D)) printf("Memory is Full!\n");
                break;
            case eject:
                X = Eject(D);
                if ( X==ERROR ) printf("Deque is Empty!\n");
                break;
            case end:
                PrintDeque(D);
                done = 1;
                break;
        }
    }
    return 0;
}

Operation GetOp()
{
    char ss[10];
    scanf("%s",ss);
    if (ss[2] == 's') return push;
    else if (ss[2] == 'p') return pop;
    else if (ss[2] == 'j') return inject;
    else if (ss[2] == 'e') return eject;
    else return end;
}

void PrintDeque(Deque D)
{
    while (D->Front != D->Rear)
    {
        printf("%d ",D->Front->Element);
        D->Front = D->Front->Next;
    }
    printf("%d\n",D->Front->Element);
}

Deque CreateDeque()
{
    struct DequeRecord *dd;
    
    dd = malloc(sizeof(struct DequeRecord));
    
    dd->Front = NULL;
    dd->Rear = NULL;
    
    return dd;
    
}

int Push( ElementType X, Deque D )
{
    struct Node *new;
    
    new = malloc(sizeof(struct Node));
    
    if (D->Front == NULL)
    {
        if (new == NULL) return 0;
        new->Element = X;
        new->Next = NULL;
        new->Last = NULL;
        D->Front = new;
        D->Rear = new;
        return 1;
    }
    else                 //if (new = malloc(sizeof(struct Node)))
    {
        if (new == NULL) return 0;
        
        new->Element = X;
        new->Next = D->Front;
        D->Front->Last = new;
        new->Last = NULL;
        D->Front = new;
        return 1;
    }
    
}

ElementType Pop( Deque D )
{
    
    if (D->Front == NULL)
    {
        return 1e5;
    }
    else if (D->Front == D->Rear)
    {
        free(D->Front);
        D->Front = NULL;
        D->Rear = NULL;
        return 1;
    }
    else
    {
        D->Front = D->Front->Next;
        free(D->Front->Last);
        D->Front->Last = NULL;
        return 1;
    }
}

int Inject( ElementType X, Deque D )
{
    struct Node *new;
    
    new = malloc(sizeof(struct Node));
    if (new == NULL) return 0;
    
    if (D->Rear == NULL)
    {
        D->Rear = new;
        D->Front = new;
        new->Element = X;
        new->Next = NULL;
        new->Last = NULL;
        
        return 1;
    }
    else            //if (new = malloc(sizeof(struct Node)))
    {
        new->Element = X;
        D->Rear->Next = new;
        new->Last = D->Rear;
        new->Next = NULL;
        D->Rear = D->Rear->Next;
        
        return 1;
    }
    
}

ElementType Eject( Deque D )
{
    if (D->Rear == NULL) return 1e5;
    else if (D->Front == D->Rear)
    {
        free(D->Rear);
        D->Rear = NULL;
        D->Front = NULL;
        
        return 1;
    }
    else
    {
        D->Rear = D->Rear->Last;
        free(D->Rear->Next);
        D->Rear->Next = NULL;
        return 1;
    }
}

