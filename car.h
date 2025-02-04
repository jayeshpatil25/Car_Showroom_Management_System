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
    char sold_date[11];
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


// Function to insert a car at the end of the list
car *insert_end(car *head, car *new_car)
{
    if (head == NULL)
        return new_car;
    
    car *current = head;
    while (current->next != NULL)
        current = current->next;
    
    current->next = new_car;
    return head;
}

// Function to split a linked list into two halves
void split_list(car *source, car **front, car **back)
{
    car *fast = source->next;
    car *slow = source;
    
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Function to merge two sorted lists
car *sorted_merge(car *a, car *b)
{
    if (!a) return b;
    if (!b) return a;
    
    car *result = NULL;
    if (a->car_id <= b->car_id)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b);
    }
    return result;
}

// Merge sort function
void merge_sort(car **head_ref)
{
    if (!*head_ref || !(*head_ref)->next)
        return;
    
    car *head = *head_ref;
    car *a;
    car *b;
    
    split_list(head, &a, &b);
    
    merge_sort(&a);
    merge_sort(&b);
    
    *head_ref = sorted_merge(a, b);
}

// Function to merge three unsorted car lists and sort them
car *merge_and_sort_car_databases(car *list1, car *list2, car *list3)
{
    car *merged_list = NULL;
    car *temp;

    while (list1)
    {
        temp = list1;
        list1 = list1->next;
        temp->next = NULL;
        merged_list = insert_end(merged_list, temp);
    }
    while (list2)
    {
        temp = list2;
        list2 = list2->next;
        temp->next = NULL;
        merged_list = insert_end(merged_list, temp);
    }
    while (list3)
    {
        temp = list3;
        list3 = list3->next;
        temp->next = NULL;
        merged_list = insert_end(merged_list, temp);
    }
    
    merge_sort(&merged_list);
    return merged_list;
}

// Function to calculate total pending loan amount for a salesperson
float calculate_pending_loan(salesperson *head, char *salesperson_name) {
    salesperson *sp = head;
    
    while (sp != NULL) {
        if (strcmp(sp->name_salesperson, salesperson_name) == 0) {
            float total_pending = 0.0;
            customer *cust = sp->list_customer;
            
            while (cust != NULL) {
                total_pending += cust->actual_amt_to_pay;
                cust = cust->next;
            }

            return total_pending;
        }
        sp = sp->next;
    }

    return -1; // Return -1 if salesperson is not found
}

// Function to print car details
void print_car_list(car *head)
{
    while (head != NULL)
    {
        printf("Car ID: %d, Model: %s, Color: %s, Price: %.2f\n",
               head->car_id, head->model_name, head->color, head->price);
        head = head->next;
    }
}

// Function to create a new car node
car *create_car(int id, char *model, char *color, float price)
{
    car *new_car = (car *)malloc(sizeof(car));
    if (!new_car)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_car->car_id = id;
    strcpy(new_car->model_name, model);
    strcpy(new_car->color, color);
    new_car->price = price;
    new_car->next = NULL;
    return new_car;
}

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


