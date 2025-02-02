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
    int salesperson_id;
    int sold_date;
} car;

typedef struct Showroom
{
    stock stock_list;
    car car_list[CARS];
} showroom;

// Structure for Car Stock Details
typedef struct Stock
{
    int stock_id;
    car car_list;
    int available_cars;
    int required_stock;
    struct Stock *next; // Pointer to the next stock item
} stock;

// Structure for Customer Details
typedef struct Customer
{
    int customer_id;
    char name[MAX_STRING_LEN];
    char mobile_no[15];
    char address[MAX_STRING_LEN];
    struct Customer *next; // Pointer to the next customer
} customer;

// Structure for Salesperson Details
typedef struct Salesperson
{
    int salesperson_id;
    char name_salesperson[MAX_STRING_LEN];
    char DOB[11]; // Format: DD/MM/YYYY
    char address[MAX_STRING_LEN];
    float sales_target;
    float sales_achieved;
    float commission;
    customer list_customer[CUSTOMERS];
    struct Salesperson *next; // Pointer to next salesperson
} Salesperson;

typedef struct car_recognition
{
    car car_list;
    customer customer_details;
    int registration_num;
    char previous_service[20]; // date
    char next_service[20];     // date
    float emi_amount;
    float actual_amount;
    char insurance_eval_date[11];
    struct car_recognition *next; // Pointer to next sale
} car_recognition;

void most_popular_car(showroom *showroom1, showroom *showroom2, showroom *showroom3)
{
    int cntA = 0, cntB = 0, cntC = 0;
    // for showroom1

    for (int i = 0; i < CARS; i++)
    {
        if (strcmp(showroom1->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(showroom1->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
    }

    for (int i = 0; i < CARS; i++)
    {
        if (strcmp(showroom2->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(showroom2->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
    }

    for (int i = 0; i < CARS; i++)
    {
        if (strcmp(showroom3->car_list[i].model_name, "modelA")==0)
        {
            cntA++;
        }
        else if (strcmp(showroom3->car_list[i].model_name, "modelB")==0)
        {
            cntB++;
        }
        else
        {
            cntC++;
        }
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
void mergeDatabases(struct Stock *showroom1, struct Stock *showroom2, struct Stock **mergedDatabase)
{
    // Function to merge two linked lists of stock details
    struct Stock *temp = showroom1;
    while (temp != NULL)
    {
        struct Stock *new_node = (struct Stock *)malloc(sizeof(struct Stock));
        *new_node = *temp;
        new_node->next = *mergedDatabase;
        *mergedDatabase = new_node;
        temp = temp->next;
    }

    temp = showroom2;
    while (temp != NULL)
    {
        struct Stock *new_node = (struct Stock *)malloc(sizeof(struct Stock));
        *new_node = *temp;
        new_node->next = *mergedDatabase;
        *mergedDatabase = new_node;
        temp = temp->next;
    }
}

// Function to Display All Stock Items
void displayStock(struct Stock *stock)
{
    struct Stock *temp = stock;
    while (temp != NULL)
    {
        printf("Car ID: %d, Model: %s, Color: %s, Type: %s, Fuel: %s, Quantity: %d, Price: %.2f\n",
               temp->car_id, temp->model_name, temp->color, temp->car_type, temp->fuel_type, temp->quantity, temp->price);
        temp = temp->next;
    }
}
