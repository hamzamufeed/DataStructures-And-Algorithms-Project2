#ifndef UNSERVED_H_INCLUDED
#define UNSERVED_H_INCLUDED

void UnservedEnqueue(char Name[20],int id,unsigned PhoneNumber,char Manufacturer[20],char Model[20],char Color[10],int Year){
	QPos temp2 = (QPos)malloc(sizeof(struct Queue));
    strcpy(temp2->Name,Name);
    temp2->id = id;
    temp2->PhoneNumber = PhoneNumber;
    strcpy(temp2->Manufacturer,Manufacturer);
    strcpy(temp2->Model,Model);
    strcpy(temp2->Color,Color);
    temp2->Year = Year;
	temp2->Next = NULL;
	if(Front2 == NULL && Rear2 == NULL){
		Front2 = Rear2 = temp2;
	}
	else{
      Rear2->Next = temp2;
      Rear2 = temp2;
	}
}

void UnservedDequeue() {
	QPos temp2 = Front2;
	if(Front2 == NULL){
		printf("Unserved Queue is Empty\n");
		return;
	}
	if(Front2 == Rear2){
		Front2 = Rear2 = NULL;
	}
	else{
		Front2 = Front2->Next;
	}
	free(temp2);
}

QPos QUnservedFront(){
    QPos temp2 = Front2;
    if(Front2 == NULL) {
		printf("No Unserved Orders\n\n");
	}
	else{
	    strcpy(temp2->Name,Front2->Name);
        strcpy(temp2->Manufacturer,Front2->Name);
        strcpy(temp2->Color,Front2->Color);
        strcpy(temp2->Model,Front2->Model);
        temp2->id = Front2 ->id;
        temp2->PhoneNumber = Front2 ->PhoneNumber;
	}
	return temp2;
}

void PrintUnservedQueue(){
	QPos temp2 = Front2;
	if(temp2 == NULL){
        printf("Unserved Queue is Empty!\n\n");
	}
	while(temp2 != NULL) {
		printf("%s %d %d %s %s %s %d\n",temp2->Name,temp2->id,temp2->PhoneNumber,temp2->Manufacturer,
         temp2->Model,temp2->Color,temp2->Year);
		temp2 = temp2->Next;
	}
	printf("\n");
}

void PrintUnservedFront(QPos temp2) {
	if(temp2 != NULL)
		printf("%s %d %d %s %s %s %d\n",temp2->Name,temp2->id,temp2->PhoneNumber,temp2->Manufacturer,
         temp2->Model,temp2->Color,temp2->Year);
    else
        printf("Unserved Queue is Empty!\n\n");
	printf("\n");
}

void ServeOrders(List L, StackList SL){
    QPos q = QFront();
    QPos q2 = QUnservedFront();
    while(q2 != NULL){
        Pos p2 = Find(L,q2->Manufacturer,q2->Model,q2->Color,q2->Year);
        if(p2!=NULL){
            Push(SL,q2->Name,q2->id,q2->PhoneNumber,q2->Manufacturer,q2->Model,q2->Color,q2->Year,p2->Price);
            Delete(L,p2);
            UnservedDequeue();
            printf("Unserved Order Served\n\n");
        }
        else if(p2 == NULL){
            printf("Unserved Order Not Served\n\n");
        }
        q2 = q2->Next;
    }
    while(q != NULL){
        Pos p = Find(L,q->Manufacturer,q->Model,q->Color,q->Year);
        if(p!=NULL){
            Push(SL,q->Name,q->id,q->PhoneNumber,q->Manufacturer,q->Model,q->Color,q->Year, p->Price);
            Delete(L,p);
            Dequeue();
            printf("Order Served\n\n");
        }
        else if(p == NULL){
            UnservedEnqueue(q->Name,q->id,q->PhoneNumber,q->Manufacturer,q->Model,q->Color,q->Year);
            Dequeue();
            printf("Order Unserved\n\n");
        }
        q = q->Next;
    }
    if(q == NULL)
        printf("No Orders Left! Queue is Empty!\n\n");
    if(q2 == NULL)
        printf("No Unserved Orders Left!\n\n");
}

void LoadUnservedOrders(){
    FILE *inp;
    char Name[20];
    int id;
    unsigned PhoneNumber;
    char Manufacturer[20];
    char Model[20];
    char Color[10];
    int Year;
    QPos q;
    inp = fopen("Unserved.dat","r");
    while(fscanf(inp,"%s %d %d %s %s %s %d",Name,&id,&PhoneNumber,Manufacturer,Model,Color,&Year) != 1){
         if((feof(inp)))
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
	        if(Front2 == NULL && Rear2 == NULL){
	            Front2 = Rear2 = q;
	        }
	        else{
	            Rear2->Next = q;
	            Rear2 = q;
	        }
        }
    }
    fclose(inp);
}

void SaveUnserved(){
    FILE *out3;
    out3 = fopen("Unserved.dat","w");
	QPos temp2 = Front2;
	if(temp2 == NULL){
        return;
	}
	while(temp2 != NULL) {
		fprintf(out3,"%s %d %d %s %s %s %d\n",temp2->Name,temp2->id,temp2->PhoneNumber,temp2->Manufacturer,
         temp2->Model,temp2->Color,temp2->Year);
		temp2 = temp2->Next;
	}
	fclose(out3);
}

#endif // UNSERVED_H_INCLUDED
