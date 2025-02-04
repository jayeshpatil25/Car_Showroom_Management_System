#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_LEN 100
#define CUSTOMERS 100
#define CARS 100

// Car structure
typedef struct Car
{
    int car_id; // Unique Car ID
    char model_name[MAX_STRING_LEN];
    char color[MAX_STRING_LEN];
    char fuel_type[MAX_STRING_LEN];
    char car_type[MAX_STRING_LEN];
    float price;
    int sold_cars;
    int available_cars;
    int required_stock;
    int sold_date; //consider dates as 1 through 12
    struct Car *next;
} car;

// Structure for Car Showroom
typedef struct Showroom
{
    car *car_list; 
    customer *customer_list;
    salesperson *salesperson_list;
} showroom;

// Structure for Customer Details
typedef struct Customer
{
    int customer_id;
    char name[MAX_STRING_LEN];
    int registration_no;
    int car_id;
    char mobile_no[15];
    char address[MAX_STRING_LEN];
    char prev_service_date[11];
    char next_service_date[11];
    float actual_amt_to_pay;
    float emi;
    char insurance_eval_date[11];
    struct Customer *next; // Pointer to the next customer
} customer;

// Structure for Salesperson Details
typedef struct Salesperson
{
    int salesperson_id; //total 10 ids
    char name_salesperson[MAX_STRING_LEN];
    char DOB[11]; // Format: DD/MM/YYYY
    char address[MAX_STRING_LEN];
    float sales_target;
    float sales_achieved;
    float commission;
    customer *list_customer;
    struct Salesperson *next; // Pointer to next salesperson
} salesperson;


void most_popular_car(showroom *showroom1, showroom *showroom2, showroom *showroom3)
{
    int cntA = 0, cntB = 0, cntC = 0;
    // for showroom1
    showroom* ptr= showroom1;
    int i=0;
    while(ptr!=NULL)
    {
        if (strcmp(ptr->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(ptr->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
        i++;
        ptr=ptr->next;
    }
    showroom* ptr2= showroom2;
    i=0;

    while(ptr2!=NULL)
    {
        if (strcmp(ptr2->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(ptr2->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
        i++;
        ptr2=ptr2->next;
    }

    i=0;
    showroom* ptr3= showroom3;

    while(ptr3!=NULL)
    {
        if (strcmp(ptr3->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(ptr3->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
        i++;
        ptr3=ptr3->next;
    }

    int maxCnt = fmax(cntA, fmax(cntB, cntC));

    if (maxCnt == cntA)
    {
        printf("Most Popluar car if ModelA");
    }
    else if (maxCnt == cntB)
    {
        printf("Most popular car is ModelB");
    }
    else
    {
        printf("Most popular car is ModelC");
    }
}

// Merge Databases Function
void mergeDB(showroom *showroom1, showroom *showroom2, showroom *showroom3)
{

}

void most_popular_salesperson(car_recognition cars[CARS])
{
    int a[10];

    for(int i=0; i<10; i++)
    {
        a[i]=0;
    }

    for(int i=0; i<CARS; i++)
    {
        a[cars[i].salesperson_id]++;
    }

    int max=a[0];
    int loc=0;

    for(int i=1; i<10; i++)
    {
        if(a[i]>max)
        {
            max=a[i];
            loc=i;
        }
    }

    printf("Most popular sales person is with id: %d", loc);
}


