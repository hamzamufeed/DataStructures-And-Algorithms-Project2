#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED
#include "Served.h"

typedef struct Queue *Qptr;
typedef Qptr QPos;
typedef Qptr QList;
struct Queue{
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    int Year;
    QPos Next;
};

QPos Front = NULL;
QPos Rear = NULL;

QPos Front2 = NULL;
QPos Rear2 = NULL;

void Enqueue() {
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    int Year;
	QPos temp = (QPos)malloc(sizeof(struct Queue));
	printf("Enter Name, Id, Phone Number, Manufacturer, Model, Color and Year\n");
	scanf("%s %d %d %s %s %s %d",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year);
    strcpy(temp->Name,Name);
    temp->id = id;
    temp->PhoneNumber = PhoneNumber;
    strcpy(temp->Manufacturer,Manufacturer);
    strcpy(temp->Model,Model);
    strcpy(temp->Color,Color);
    temp->Year = Year;
	temp->Next = NULL;
	if(Front == NULL && Rear == NULL){
		Front = Rear = temp;
	}
	else{
      Rear->Next = temp;
      Rear = temp;
	}
	printf("Order Enqueued\n\n");
}

void Dequeue() {
	QPos temp = Front;
	if(Front == NULL){
		printf("Queue is Empty\n");
		return;
	}
	if(Front == Rear){
		Front = Rear = NULL;
	}
	else{
		Front = Front->Next;
	}
	free(temp);
}

QPos QFront() {
    QPos temp = Front;
    if(Front == NULL) {
		printf("Queue is Empty\n\n");
	}
	else{
	    strcpy(temp->Name,Front->Name);
        strcpy(temp->Manufacturer,Front->Manufacturer);
        strcpy(temp->Color,Front->Color);
        strcpy(temp->Model,Front->Model);
        temp->id = Front ->id;
        temp->PhoneNumber = Front ->PhoneNumber;
	}
	return temp;
}

void PrintQueue(){
	QPos temp = Front;
	if(temp == NULL){
        printf("Queue is Empty\n\n");
        return;
	}
	printf("Name  ID  Phone Number  Manufacturer  Model  Color  Year\n");
	printf("--------------------------------------------------------\n");
	while(temp != NULL) {
		printf("%s %d %d %s %s %s %d\n",temp->Name,temp->id,temp->PhoneNumber,temp->Manufacturer,
         temp->Model,temp->Color,temp->Year);
		temp = temp->Next;
	}
	printf("\n");
}

void PrintFront(QPos temp) {
	if(temp != NULL)
		printf("\n%s %d %d %s %s %s %d\n",temp->Name,temp->id,temp->PhoneNumber,temp->Manufacturer,
         temp->Model,temp->Color,temp->Year);
    else
        printf("Queue is Empty\n");
	printf("\n");
}

void LoadOrders(){
    FILE *inQ;
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    int Year;
    QPos q;
    inQ = fopen("Orders.dat","r");
    while(fscanf(inQ,"%s %d %d %s %s %s %d",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year) != 1){
         if((feof(inQ)))
           break;
        else
            q = (QPos)malloc(sizeof(struct Queue));
        if(q == NULL)
            printf("Out of memory");
        else{
            strcpy(q->Name,Name);
            strcpy(q->Manufacturer,Manufacturer);
            strcpy(q->Model,Model);
            strcpy(q->Color,Color);
            q ->Year = Year;
            q ->id = id;
            q ->PhoneNumber = PhoneNumber;
            q->Next = NULL;
	        if(Front == NULL && Rear == NULL){
	            Front = Rear = q;
	        }
	        else{
	            Rear->Next = q;
	            Rear = q;
	        }
        }
    }
    printf("Orders Loaded!\n\n");
    fclose(inQ);
}

void Update(){
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    int Year;
    QPos p = QFront();
    if(p == NULL)
        return;
    printf("\nEnter the Information of the Order you want to Modify:");
    scanf("%s %d %d %s %s %s %d",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year);
    p = p->Next;
    while(p != NULL && !(strcasecmp(p->Name,Name)==0&&strcasecmp(p->Manufacturer,Manufacturer)==0&&strcasecmp(p->Model,Model)==0&&strcasecmp(p->Color,Color)==0&&
            p->Year == Year && p->PhoneNumber == PhoneNumber && p->id == id)){
            p = p->Next;
        }
        if(p == NULL){
        printf("Order Not Found!\n");
        printf("The input you entered is Not Available!\n\n");
        }
        else{
             printf("Order Found!: %s %d %d %s %s %s %d\n\n",p->Name,p->id,p->PhoneNumber,p->Manufacturer, p->Model, p->Color, p->Year);
             printf("Enter the Updated Information of the Order: \n");
             scanf("%s %d %d %s %s %s %d",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year);
             strcpy(p->Name,Name);
             strcpy(p->Manufacturer,Manufacturer);
             strcpy(p->Model,Model);
             strcpy(p->Color,Color);
             p->id = id;
             p->PhoneNumber = PhoneNumber;
             p->Year = Year;
             printf("\nUpdated Order: %s %d %d %s %s %s %d\n\n",p->Name,p->id,p->PhoneNumber,p->Manufacturer, p->Model, p->Color, p->Year);
    }
}

void SaveOrders(){
    FILE *out1;
    QPos temp = Front;
    out1 = fopen("Orders.dat","w");
	if(temp == NULL){
        return;
	}
	while(temp != NULL){
		fprintf(out1,"%s %d %d %s %s %s %d\n",temp->Name,temp->id,temp->PhoneNumber,temp->Manufacturer,
         temp->Model,temp->Color,temp->Year);
		temp = temp->Next;
	}
	fclose(out1);
}


#endif // ORDERS_H_INCLUDED
