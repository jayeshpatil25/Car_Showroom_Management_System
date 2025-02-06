#ifndef CAR_H
#define CAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "uthash.h"

#define MAX_STRING_LEN 100
#define MONTHS 12

// Car structure
typedef struct Car {
    int car_id;
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

// Structure for Customer Details
typedef struct Customer {
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
    struct Customer *next;
} customer;

// Structure for Salesperson Details
typedef struct Salesperson {
    int salesperson_id;
    char name_salesperson[MAX_STRING_LEN];
    char DOB[11];
    char address[MAX_STRING_LEN];
    float sales_target;
    float sales_achieved;
    float commission;
    customer *list_customer;
    struct Salesperson *next;
} salesperson;

// Hashmap structure for tracking car sales
typedef struct HashMap {
    char model_name[MAX_STRING_LEN];
    int total_sold;
    UT_hash_handle hh;
} ModelSales;

// Structure for Car Showroom
typedef struct Showroom {
    car *car_list;
    customer *customer_list;
    salesperson *salesperson_list;
} showroom;

typedef struct ServiceBill {
    int customer_id;
    char car_model[100];
    float labor_hours;     // Number of labor hours
    float labor_rate;      // Cost per hour
    float spare_parts_cost; // Total cost of spare parts
    float tax_rate;        // Tax percentage (e.g., 10% = 0.10)
} ServiceBill;

typedef struct SalesHistory {
    char model_name[100];
    int sales[MONTHS]; // Sales data for the last 12 months
} SalesHistory;

extern ModelSales *model_sales_map;

// Function prototypes
void add_to_sales_map(const char *model, int sold);
void find_most_popular_model();
void free_sales_map();
car *insert_end(car *head, car *new_car);
void split_list(car *source, car **front, car **back);
car *sorted_merge(car *a, car *b);
void merge_sort_showroom_DB(car **head_ref);
car *merge_and_sort_car_databases(car *list1, car *list2, car *list3);
float calculate_pending_loan(salesperson *head, char *salesperson_name);
void print_car_list(car *head);
car *create_car(int car_id, const char *model_name, const char *color, const char *fuel_type, const char *car_type, float price);

void mergeSort_car_date(car **head);
void set_sales_target(salesperson *sp, float target);
void check_sales_target(salesperson *sp);
int find_sales(showroom *showrooms, int showroom_count, const char *model, const char *start_date, const char *end_date);
void generate_service_alerts(customer *customer_list, const char *current_date);
int predict_next_month_sales(SalesHistory *history);
void display_prediction(SalesHistory *history, const char *next_month);
float calculate_service_bill(ServiceBill *bill);
void print_service_bill(ServiceBill *bill);
// Additional function prototypes for file handling
void load_car_data(const char *filename, car **head);
void load_customer_data(const char *filename, customer **head);
void load_salesperson_data(const char *filename, salesperson **head);
void load_sales_history_data(const char *filename, SalesHistory sales_history[], int *num_models);
SalesHistory* find_sales_history(SalesHistory sales_history[], int num_models, const char* model_name);
void load_model_sales_data(const char *filename, ModelSales **hashmap);
customer* insert_customer_end(customer* head, customer* new_customer);
customer* create_customer(int customer_id, const char* name, int registration_no, int car_id, const char* mobile_no, const char* address);
void load_customer_data(const char *filename, customer **head);
customer* insert_customer_end(customer* head, customer* new_customer) ;
salesperson* create_salesperson(int salesperson_id, const char* name_salesperson, const char* DOB, const char* address, float sales_target, float sales_achieved, float commission);
salesperson* insert_salesperson_end(salesperson* head, salesperson* new_sp);



#endif // CAR_H
