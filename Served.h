#ifndef SERVED_H_INCLUDED
#define SERVED_H_INCLUDED
#include "Orders.h"

typedef struct Stack *Sptr;
typedef Sptr Position;
typedef Sptr StackList;
struct Stack{
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    char Date[20];
    double Price;
    int Year;
    Position Next;
};
StackList CreateStack(){
    StackList L=(Position)malloc(sizeof(struct Stack));
    L->Next=NULL;
    return L;
}

void Push(StackList L,char Name[20],int id,unsigned PhoneNumber,char Manufacturer[20],char Model[10],char Color[10],int Year, double Price){
	Position P =(Position)malloc(sizeof(struct Stack));
	FILE *out4;
	out4 = fopen("Served.dat","a");
	if(P == NULL){
        printf("Out of Memory");
	}
	else{
	    time_t now;
	    time(&now);
	    struct tm *local = localtime(&now);
        int day = local->tm_mday;
        int month = local->tm_mon + 1;
        int year = local->tm_year + 1900;
        char cday[5];
        char cmonth[5];
        char cyear[5];
        itoa(day,cday,10);
        itoa(month,cmonth,10);
        itoa(year,cyear,10);
        strcat(cday,"/");
        strcat(cmonth,"/");
        strcat(cday,cmonth);
        strcat(cday,cyear);
        printf("Date is: %s\n",cday);
        strcpy(P->Name,Name);
        P->id = id;
        P->PhoneNumber = PhoneNumber;
        strcpy(P->Manufacturer,Manufacturer);
        strcpy(P->Model,Model);
        strcpy(P->Color,Color);
        strcpy(P->Date,cday);
        P->Year = Year;
        P->Price = Price;
    	P->Next = NULL;
        P->Next = L->Next;
        L->Next = P;
        fprintf(out4,"%s %d %d %s %s %s %d %.2f %s\n",P->Name,P->id,P->PhoneNumber,P->Manufacturer,P->Model,P->Color,
                P->Year,P->Price,P->Date);
	}
	fclose(out4);
}

int IsEmptyStack(StackList L){
    return L->Next==NULL;
}

Position Pop(StackList L){
    Position temp = L->Next;
    if(IsEmptyStack(L))
        printf("Stack is Empty\n\n");
    else{
        L->Next=L->Next->Next;
        return temp;
    }
    return temp;
}

Position Top(StackList L){
    if(IsEmptyStack(L))
       printf("Stack is Empty\n\n");
    return L->Next;
}

void PrintStack(Position p){
    if(p != NULL){
        printf("Name  ID  Phone Number  Manufacturer  Model  Color  Year  Price  Date\n");
        printf("---------------------------------------------------------------------\n");
		printf("\n%s %d %d %s %s %s %d %.2f %s\n",p->Name,p->id,p->PhoneNumber,p->Manufacturer,
         p->Model,p->Color,p->Year, p->Price, p->Date);
    }
    else
        return;
	printf("\n");
}

void PushFromFile(StackList L,char Name[20],int id,unsigned PhoneNumber,char Manufacturer[20],char Model[10],char Color[10],int Year, double Price,char Date[20]){
	Position P =(Position)malloc(sizeof(struct Stack));
	if(P == NULL){
        printf("Out of Memory");
	}
	else{
        strcpy(P->Name,Name);
        P->id = id;
        P->PhoneNumber = PhoneNumber;
        strcpy(P->Manufacturer,Manufacturer);
        strcpy(P->Model,Model);
        strcpy(P->Color,Color);
        strcpy(P->Date,Date);
        P->Year = Year;
        P->Price = Price;
    	P->Next = NULL;
        P->Next = L->Next;
        L->Next = P;
	}
}

void LoadStack(StackList SL){
    FILE *inS;
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    char Date[20];
    int Year;
    double Price;
    inS = fopen("Served.dat","r");
    Position p;
    while(fscanf(inS,"%s %d %d %s %s %s %d %lf %s",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year,&Price,Date) != 1){
         if((feof(inS)))
           break;
        else
            p =(Position)malloc(sizeof(struct Stack));
            if(p == NULL){
                printf("Out of Memory");
            }
	        else{
                PushFromFile(SL,Name,PhoneNumber,id,Manufacturer,Model,Color,Year,Price,Date);
	        }
    }
    fclose(inS);
}

#endif // SERVED_H_INCLUDED
