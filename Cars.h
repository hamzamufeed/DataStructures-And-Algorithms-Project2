#ifndef CARS_H_INCLUDED
#define CARS_H_INCLUDED

typedef struct Node * ptr;
typedef ptr List;
typedef ptr Pos;
struct Node{
    char Manufacturer[20];
    char Model[10];
    int Year;
    char Color[10];
    double Price;
    int NumOfCars;
    Pos Next;
};

void DeleteList(List L){
    Pos p, temp;
    p = L ->Next;
    L -> Next = NULL;
    while(p != NULL){
        temp = p ->Next;
        free(p);
        p = temp;
    }
}

List MakeEmpty(List L){
    if( L != NULL)
        DeleteList(L);
    L =(struct Node*)malloc(sizeof(struct Node));
    if(L == NULL)
        printf("Out of memory!!\n");
    else
        L ->Next = NULL;
    return L;
}

int IsEmpty(List L){
    return L ->Next == NULL;
}

int IsLast(Pos p, List L){
    return L ->Next == NULL;
}

int IsRepeated(List L,char Manufacturer[20],char Model[10],char Color[10],int Year,double Price,int NumOfCars){
    Pos p = L->Next;
    while(p!=NULL){
        if(strcasecmp(p->Manufacturer,Manufacturer)==0 && strcasecmp(p->Model,Model)==0 && strcasecmp(p->Color,Color)==0 &&
             p->Price == Price && p->Year == Year){
                 p->NumOfCars = p->NumOfCars + NumOfCars;
                return 1;
             }
        else if(p == NULL)
            return 0;
        else
            p = p->Next;
    }
    return 0;
}

int CountNodes(List L){
    Pos p = L;
    int count = -1;
    while(p!=NULL){
        p = p->Next;
        count++;
    }
    return count;
}

int getPosCount(List L,Pos p){
    Pos temp = L;
    int PosCount = 0;
    while(temp != NULL && temp != p){
        temp = temp->Next;
        PosCount++;
    }
    return PosCount;
}

void InsertFirst(List L){
    char Manufacturer[20];
    char Model[10];
    char Color[10];
    int Year;
    double Price;
    int NumOfCars;
    printf("Enter Manufacturer, Model, Color, Year, Price and Number of Cars\n");
    scanf("%s %s %s %d %lf %d", Manufacturer, Model, Color, &Year, &Price,&NumOfCars);
    if(!IsRepeated(L,Manufacturer,Model,Color,Year,Price,NumOfCars)){
        Pos temp = (Pos)malloc(sizeof(struct Node));
        if(temp != NULL){
            Pos head = L;
            strcpy(temp->Manufacturer,Manufacturer);
            strcpy(temp->Model,Model);
            strcpy(temp->Color,Color);
            temp ->Year = Year;
            temp ->Price = Price;
            temp ->NumOfCars = NumOfCars;
            temp ->Next = head ->Next;
            head ->Next = temp;
            printf("Inserted First\n");
        }
        else
          printf("Out of memory");
    }
    else
        printf("Car is already in the Inventory, Number Increased!\n");
    }

void InsertLast(List L){
    char Manufacturer[20];
    char Model[10];
    char Color[10];
    int Year;
    double Price;
    int NumOfCars;
    printf("Enter Manufacturer, Model, Color, Year, Price and Number of Cars\n");
    scanf("%s %s %s %d %lf %d", Manufacturer, Model, Color, &Year, &Price,&NumOfCars);
    if(!IsRepeated(L,Manufacturer,Model,Color,Year,Price,NumOfCars)){
        Pos p = malloc(sizeof(struct Node));
    if(p == NULL)
        printf("Out of memory!!");
    else{
        strcpy(p->Manufacturer,Manufacturer);
        strcpy(p->Model,Model);
        strcpy(p->Color,Color);
        p ->Year = Year;
        p ->Price = Price;
        p ->NumOfCars = NumOfCars;
        Pos t = L;
        while(t ->Next != NULL && t != NULL)
              t = t ->Next;
        t -> Next = p;
        p ->Next = NULL;
    }
    printf("Inserted Last\n");
    }
    else
        printf("Car is already in the Inventory, Number Increased!\n");
}

Pos getNode(List L,int num, int posNum){
    Pos p = L;
    for(int i=1;i<=posNum && p->Next!=NULL;i++)
        p = p->Next;
    return p;
}

void Insert(List L){
    Pos temp;
    int num = CountNodes(L);
    int posNum;
    printf("Number of Nodes is %d\n",num);
    printf("Enter the number of the position you want to insert after: ");
    scanf("%d", &posNum);
    if(posNum>num || posNum<0)
        printf("\nInsertion Failed! The Position you entered is Invalid!\n\n");
    else if(posNum == 0){
        InsertFirst(L);
    }
    else if(posNum == num){
        InsertLast(L);
    }
    else{
        Pos p = getNode(L,num,posNum);
        char Manufacturer[20];
        char Model[10];
        char Color[10];
        int Year;
        double Price;
        int NumOfCars;
        printf("\nEnter Manufacturer, Model, Color, Year, Price and Number of Cars\n");
        scanf("%s %s %s %d %lf %d", Manufacturer, Model, Color, &Year, &Price, &NumOfCars);
        if(!IsRepeated(L,Manufacturer,Model,Color,Year,Price,NumOfCars)){
            temp = malloc(sizeof(struct Node));
            if(temp == NULL)
               printf("Out of memory!!");
             else{
                strcpy(temp->Manufacturer,Manufacturer);
                strcpy(temp->Model,Model);
                strcpy(temp->Color,Color);
                temp ->Year = Year;
                temp ->Price = Price;
                temp ->NumOfCars = NumOfCars;
                temp ->Next = p ->Next;
                p ->Next = temp;
                printf("Inserted\n\n");
             }
        }
        else
            printf("Car is already in the Inventory, Number Increased!\n");
    }
}

void DeleteFirst(List L){
    if(L == NULL)
        printf("No Node to Delete!\n\n");
    else{
        Pos temp = L;
        temp = L->Next;
        if(temp->NumOfCars > 1){
            temp->NumOfCars--;
            printf("Car's Number Decremented!");
        }
        else{
            L ->Next = temp ->Next;
            free(temp);
            printf("First Node Deleted!\n");
        }
    }
}

void DeleteLast(List L){
    Pos p, temp;
    if(L == NULL)
        printf("No Nodes to Delete!\n");
    else{
        p = L;
        temp = L;
        while(p->Next !=NULL){
            temp = p;
            p = p->Next;
        }
        if(temp->NumOfCars > 1){
            temp->NumOfCars--;
            printf("Car's Number Decremented!");
        }
        else{
            if(p == L)
               L = NULL;
        else
            temp->Next = NULL;
        free(p);
        printf("\nLast Node Deleted!\n");
        }
    }
}

void Delete(List L,Pos p){
    Pos temp, temp2;
    temp = L;
    while(temp ->Next != NULL && temp ->Next != p)
        temp = temp->Next;
    if(temp ->Next->NumOfCars == 1 && temp ->Next == p){
        temp2 = temp ->Next;
        temp ->Next = temp2 ->Next;
        free(temp2);
        printf("Node Deleted!\n");
    }
    else if(temp ->Next->NumOfCars > 1 && temp ->Next == p){
        temp ->Next->NumOfCars--;
        printf("Car Number Decremented!\n");
    }
}

void DeletePos(List L,Pos p){
    int num, posNum;
    num = CountNodes(L);
    posNum = getPosCount(L,p);
    printf("%d\n",num);
    printf("%d\n",posNum);
    if(posNum < 1 || posNum > num)
        printf("Deletion Failed! Not Found!\n");
    else if(posNum == 1)
        DeleteFirst(L);
    else if(posNum == num)
        DeleteLast(L);
    else{
        Pos previous = getNode(L,num,posNum-1);
        Pos temp;
        temp = previous->Next;
        if(temp->NumOfCars > 1){
            temp->NumOfCars--;
            printf("Car's Number Decremented!");
        }
        else{
            previous ->Next = temp ->Next;
            free(temp);
            printf("Deleted!\n");
        }
    }
}

void printList(List L){
    Pos p = L ->Next;
    if(p == NULL){
        printf("Car Inventory is Empty!\n\n");
        return;
    }
    printf("Manufacturer  Model  Color  Year  Price  Number Of Cars\n");
    printf("-------------------------------------------------------\n");
    while(p != NULL){
        printf("%s %s %s %d %.2f %d\n", p->Manufacturer, p->Model, p->Color, p->Year, p->Price, p->NumOfCars);
        p = p ->Next;
    }
    printf("\n");
}

void LoadCars(List L){
    FILE *in;
    char Manufacturer[20];
    char Model[10];
    char Color[10];
    int Year;
    double Price;
    int NumOfCars;
    Pos p;
    in = fopen("Cars.dat","r");
    while(fscanf(in,"%s %s %s %d %lf %d", Manufacturer, Model, Color, &Year, &Price, &NumOfCars) != 1){
         if((feof(in)))
           break;
    else
        p = malloc(sizeof(struct Node));
    if(p == NULL)
       printf("Out of memory!!");
    else{
        strcpy(p->Manufacturer,Manufacturer);
        strcpy(p->Model,Model);
        strcpy(p->Color,Color);
        p ->Year = Year;
        p ->Price = Price;
        p ->NumOfCars = NumOfCars;
        Pos t = L;
        while(t ->Next != NULL && t != NULL)
              t = t ->Next;
        t -> Next = p;
        p ->Next = NULL;
    }
    }
    printf("Cars Loaded!\n\n");
    fclose(in);
}

Pos Find(List L,char Manufacturer[20],char Model[10],char Color[10],int Year){
    Pos p;
    p = L->Next;
    while(p != NULL){
        if((strcasecmp(p->Manufacturer,Manufacturer)==0&&strcasecmp(p->Model,Model)==0&&strcasecmp(p->Color,Color)==0&& p->Year == Year)){
            printf("Found!: %s %s %s %d %.2f %d\n\n", p->Manufacturer, p->Model, p->Color, p->Year, p->Price, p->NumOfCars);
            return p;
        }
        p = p->Next;
    }
    if(p == NULL)
        printf("Car Not Found!\n");
        return p;
}

void SaveCars(List L){
    FILE *out2;
    out2 = fopen("Cars.dat","w");
    Pos p = L ->Next;
    if(p == NULL){
        return;
    }
    while(p != NULL){
        fprintf(out2,"%s %s %s %d %.2f %d\n", p->Manufacturer, p->Model, p->Color, p->Year, p->Price, p->NumOfCars);
        p = p ->Next;
    }
    fclose(out2);
}

#endif // CARS_H_INCLUDED
