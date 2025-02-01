#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 100

// Structure for Car Stock Details
typedef struct Stock {
    int car_id;               // Unique Car ID
    char model_name[MAX_STRING_LEN];
    char color[MAX_STRING_LEN];
    char fuel_type[MAX_STRING_LEN];
    char car_type[MAX_STRING_LEN];
    int available_quantity;
    float price;
    struct Stock* next; // Pointer to the next stock item
}stock;

// Structure for Customer Details
struct Customer {
    int customer_id;
    char name[MAX_STRING_LEN];
    char mobile_no[15];
    char address[MAX_STRING_LEN];
    struct Customer* next; // Pointer to the next customer
};

// Structure for Salesperson Details
struct Salesperson {
    int salesperson_id;
    char name[MAX_STRING_LEN];
    char dob[11];  // Format: DD/MM/YYYY
    char address[MAX_STRING_LEN];
    float sales_target;
    float sales_achieved;
    float commission;
    struct Salesperson* next; // Pointer to next salesperson
};

// Structure for Sold Cars
struct Sold_Cars {
    int sale_id;
    int car_id;
    int customer_id;
    char sale_date[11];
    float sale_price;
    float emi_amount;
    char insurance_eval_date[11];
    struct Sold_Cars* next; // Pointer to next sale
};

// Structure for Service Details
struct Service {
    int car_id;
    char service_date[11];
    float service_cost;
    struct Service* next; // Pointer to next service
};

// Merge Databases Function
void mergeDatabases(struct Stock* showroom1, struct Stock* showroom2, struct Stock** mergedDatabase) {
    // Function to merge two linked lists of stock details
    struct Stock* temp = showroom1;
    while (temp != NULL) {
        struct Stock* new_node = (struct Stock*)malloc(sizeof(struct Stock));
        *new_node = *temp;
        new_node->next = *mergedDatabase;
        *mergedDatabase = new_node;
        temp = temp->next;
    }

    temp = showroom2;
    while (temp != NULL) {
        struct Stock* new_node = (struct Stock*)malloc(sizeof(struct Stock));
        *new_node = *temp;
        new_node->next = *mergedDatabase;
        *mergedDatabase = new_node;
        temp = temp->next;
    }
}

// Function to Display All Stock Items
void displayStock(struct Stock* stock) {
    struct Stock* temp = stock;
    while (temp != NULL) {
        printf("Car ID: %d, Model: %s, Color: %s, Type: %s, Fuel: %s, Quantity: %d, Price: %.2f\n", 
                temp->car_id, temp->model_name, temp->color, temp->car_type, temp->fuel_type, temp->quantity, temp->price);
        temp = temp->next;
    }
}

