//Vinit More BT23CSE083 R4
//Jayesh Patil BT23CSE078 R4

#ifndef CAR_H
#define CAR_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_LEN 100
#define MONTHS 12
#define NUM_SHOWROOMS 3

// Car structure
typedef struct Car
{
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
    struct Customer *next;
} customer;

// Structure for Salesperson Details
typedef struct Salesperson
{
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

// Structure for Car Showroom
typedef struct Showroom
{
    car *car_list;
    customer *customer_list;
    salesperson *salesperson_list;
} showroom;

typedef struct ServiceBill
{
    int customer_id;
    char car_model[100];
    float labor_hours;      // Number of labor hours
    float labor_rate;       // Cost per hour
    float spare_parts_cost; // Total cost of spare parts
    float tax_rate;         // Tax percentage (e.g., 10% = 0.10)
} ServiceBill;

typedef struct SalesHistory
{
    char model_name[100];
    int sales[MONTHS]; // Sales data for the last 12 months
} SalesHistory;

car *insert_end(car *head, car *new_car);
customer *insert_customer_end(customer *head, customer *new_customer);
salesperson *insert_salesperson_end(salesperson *head, salesperson *new_sp);
void print_car_list(car *car_list);
int compare_dates(const char *date1, const char *date2);
int date_to_int(const char *date);
void set_sales_target(salesperson *sp, float target);
void check_sales_target(salesperson *sp);
int is_date_in_range(const char *date, const char *start_date, const char *end_date);
int find_sales(showroom *showrooms, int showroom_count, const char *model, const char *start_date, const char *end_date);
void calculate_next_service_date(const char *purchase_date, char *next_service_date);
int is_service_due(const char *next_service_date, const char *current_date);
void generate_service_alerts(customer *customer_list, const char *current_date);
int predict_next_month_sales(SalesHistory *history);
void display_prediction(SalesHistory *history, const char *next_month);
float calculate_service_bill(ServiceBill *bill);
void print_service_bill(ServiceBill *bill);
car *create_car(int car_id, const char *model_name, const char *color, const char *fuel_type, const char *car_type, float price, int sold_cars, int available_cars, int required_stock, const char *sold_date);
void load_car_data(const char *filename, car **head);
customer *create_customer(int customer_id, const char *name, int registration_no, int car_id,
    const char *mobile_no, const char *address,
    const char *prev_service_date, const char *next_service_date,
    double actual_amt_to_pay, double emi, const char *insurance_eval_date);
void load_customer_data(const char *filename, customer **head);
salesperson *create_salesperson(int salesperson_id, const char *name_salesperson, const char *DOB, const char *address,
    float sales_target, float sales_achieved, float commission, customer *customer_list);

void load_salesperson_data(const char *filename, salesperson **head, customer *customer_list);
void load_sales_history_data(const char *filename, SalesHistory sales_history[], int *num_models);
SalesHistory *find_sales_history(SalesHistory sales_history[], int num_models, const char *model_name);
void free_car_list(car *head);
void free_customer_list(customer *head);
void free_salesperson_list(salesperson *head);
void merge_sorted_car_lists(car **merged_list, car *list1, car *list2);
void merge_sorted_customer_lists(customer **merged_list, customer *list1, customer *list2);
void merge_sorted_salesperson_lists(salesperson **merged_list, salesperson *list1, salesperson *list2);
void merge_all_data(showroom *showrooms, car **all_cars, customer **all_customers, salesperson **all_salespersons);
void find_most_popular_car_model(car *all_cars, SalesHistory *sales_data, int num_models);
void find_top_salesperson(salesperson *all_salespersons);
void car_sold_date_split_list(car *source, car **front, car **back);
car *car_sold_date_sorted_merge(car *list1, car *list2);
void car_sold_date_merge_sort(car **head);
float get_total_loan_pending(salesperson *head, const char *salesperson_name);
float find_sales_figures(car *car_list, const char *model_name, const char *start_date, const char *end_date);
void save_salesperson_to_file(const char *filename, salesperson *sp);
void add_salesperson_to_showroom(showroom *showrooms);
void add_car_to_showroom(const char *filename);
void add_car();
void save_customer_to_file(const char *filename, customer *cust);
void add_customer_to_showroom(showroom *showrooms);


#endif