#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Cars.h"
#include "Orders.h"
#include "Served.h"
#include "Unserved.h"

void printMenu(){
    printf("----------------------------------------\n");
    printf("1- Load Cars and Orders\n");
    printf("2- Show Car Inventory\n");
    printf("3- Other Car/Order Options\n");
    printf("4- Serve Orders\n");
    printf("5- Unserved Orders\n");
    printf("6- Show Last Sold Car\n");
    printf("7- Update Orders and Car Information\n");
    printf("8- Exit\n");
    printf("----------------------------------------\n");
    printf("Choose what to do:");
}

void printMenu2(){
    printf("Other Car/Order Options\n");
    printf("----------------------------------------\n");
    printf("1- Insert a New Car\n");
    printf("2- Insert a New Order\n");
    printf("3- Modify an Order\n");
    printf("4- Show Orders Queue\n");
    printf("5- Back to Main Menu\n");
    printf("----------------------------------------\n");
    printf("Choose what to do:");
}

void LoadMenu2(List L){
    int x;
    printMenu2();
    scanf("%d",&x);
    printf("----------------------------------------\n");
    printf("\n");
    while(1){
        switch(x){
            case 1:Insert(L); break;
            case 2:Enqueue(); break;
            case 3:Update(); break;
            case 4: PrintQueue(); break;
            case 5: return; break;
            default:printf("\nInvalid Input! Try again:\n\n"); break;
        }
        printMenu2();
        scanf("%d", &x);
        printf("----------------------------------------\n");
        printf("\n");
    }
}

void UpdateFiles(List L,StackList SL){
    SaveOrders();
    SaveCars(L);
    SaveUnserved();
    printf("Data Updated to the Files\n\n");
}

int main(){
    printf("Welcome to the Car Agency\n");
    int x;
    printMenu();
    List L;
    L = MakeEmpty(NULL);
    StackList SL = CreateStack();
    Position S;
    scanf("%d", &x);
    printf("----------------------------------------\n");
    printf("\n");
    while(1){
        switch(x){
        case 1: LoadCars(L); LoadOrders(); LoadUnservedOrders(); LoadStack(SL); break;
        case 2: printList(L); break;
        case 3: LoadMenu2(L); break;
        case 4: ServeOrders(L,SL); break;
        case 5: PrintUnservedQueue(); break;
        case 6: S = Top(SL); PrintStack(S); break;
        case 7: UpdateFiles(L,SL); break;
        case 8: return 0; break;
        default:printf("\n\nInvalid Input! Try again: \n\n"); break;
        }
        printMenu();
        scanf("%d",&x);
        printf("----------------------------------------\n");
        printf("\n");
    }
}
