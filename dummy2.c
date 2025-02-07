#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_LEN 100
#define MONTHS 12
#define NUM_SHOWROOMS 3

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


// Structure for Car Showroom
typedef struct Showroom {
    car *car_list;
    customer *customer_list;
    salesperson *salesperson_list;
} showroom;

typedef struct ServiceBill {
    int customer_id;
    char car_model[100];
    float labor_hours;      // Number of labor hours
    float labor_rate;       // Cost per hour
    float spare_parts_cost; // Total cost of spare parts
    float tax_rate;         // Tax percentage (e.g., 10% = 0.10)
} ServiceBill;

typedef struct SalesHistory {
    char model_name[100];
    int sales[MONTHS]; // Sales data for the last 12 months
} SalesHistory;


// Function to insert a car at the end of the linked list
car *insert_end(car *head, car *new_car) {
    if (head == NULL) {
        return new_car;
    }
    car *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_car;
    return head;
}

// Function to insert a customer at the end of the linked list
customer *insert_customer_end(customer *head, customer *new_customer) {
    if (head == NULL) {
        return new_customer;
    }
    customer *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_customer;
    return head;
}

// Function to insert a salesperson at the end of the linked list
salesperson *insert_salesperson_end(salesperson *head, salesperson *new_sp) {
    if (head == NULL) {
        return new_sp;
    }
    salesperson *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_sp;
    return head;
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
void print_car_list(car *car_list) {
    if (car_list == NULL) {
        printf("No cars available.\n");
        return;
    }

    printf("Car ID | Model               | Price\n");
    printf("-------------------------------------\n");

    car *current = car_list;
    while (current != NULL) {
        printf("%-6d | %-20s | %.2f\n", current->car_id, current->model_name, current->price);
        current = current->next;
    }
}


// Function to convert date string to an integer (YYYYMMDD format)
int date_to_int(const char *date) {
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        return -1; // Return an invalid value if the format is incorrect
    }
    return year * 10000 + month * 100 + day;
}


// Function to set the sales target for a salesperson
void set_sales_target(salesperson *sp, float target) {
    if (sp) {
        sp->sales_target = target;
        printf("Sales target of %.2f set for Salesperson ID %d (%s)\n", target, sp->salesperson_id, sp->name_salesperson);
    } else {
        printf("Invalid salesperson.\n");
    }
}

// Function to check if the sales target is achieved
void check_sales_target(salesperson *sp) {
    if (sp) {
        if (sp->sales_achieved >= sp->sales_target) {
            printf("Salesperson ID %d (%s) has achieved the target!\n", sp->salesperson_id, sp->name_salesperson);
        } else {
            printf("Salesperson ID %d (%s) has not achieved the target. Sales Achieved: %.2f, Target: %.2f\n",
                   sp->salesperson_id, sp->name_salesperson, sp->sales_achieved, sp->sales_target);
        }
    } else {
        printf("Invalid salesperson.\n");
    }
}

int is_date_in_range(const char *date, const char *start_date, const char *end_date) {
    int date_int = date_to_int(date);
    int start_int = date_to_int(start_date);
    int end_int = date_to_int(end_date);

    return (date_int >= start_int && date_int <= end_int);
}

// Function to find the sales figures of a specific model within a date range
int find_sales(showroom *showrooms, int showroom_count, const char *model, const char *start_date, const char *end_date) {
    int total_sales = 0;
    for (int i = 0; i < showroom_count; i++) {
        car *current = showrooms[i].car_list;
        while (current) {
            if (strcmp(current->model_name, model) == 0 && is_date_in_range(current->sold_date, start_date, end_date)) {
                total_sales += current->sold_cars;
            }
            current = current->next;
        }
    }
    return total_sales;
}

// Function to calculate the next service date (6 months after purchase)
void calculate_next_service_date(const char *purchase_date, char *next_service_date) {
    int day, month, year;

    if (sscanf(purchase_date, "%d/%d/%d", &day, &month, &year) != 3) {
        strcpy(next_service_date, "Invalid Date");
        return;
    }

    month += 6; // Add six months
    if (month > 12) {
        month -= 12;
        year++; // Move to next year if needed
    }

    sprintf(next_service_date, "%02d/%02d/%04d", day, month, year);
}

// Function to check if the service is due
int is_service_due(const char *next_service_date, const char *current_date) {
    return date_to_int(current_date) >= date_to_int(next_service_date);
}

// Function to generate service alerts for customers
void generate_service_alerts(customer *customer_list, const char *current_date) {
    customer *cust = customer_list;

    printf("\n--- Service Due Alerts ---\n");
    while (cust) {
        char next_service_date[11];
        calculate_next_service_date(cust->next_service_date, next_service_date);

        if (is_service_due(next_service_date, current_date)) {
            printf("Alert: Customer %s (ID: %d) needs a service. Next service date: %s\n",
                   cust->name, cust->customer_id, next_service_date);
        }

        cust = cust->next;
    }
}

// Function to predict next month's sales using a simple moving average
int predict_next_month_sales(SalesHistory *history) {
    int total_sales = 0;

    // Sum up sales from the last 12 months
    for (int i = 0; i < MONTHS; i++) {
        total_sales += history->sales[i];
    }

    // Return the average as the predicted sales for the next month
    return total_sales / MONTHS;
}

// Function to display the prediction result
void display_prediction(SalesHistory *history, const char *next_month) {
    int predicted_sales = predict_next_month_sales(history);
    printf("Predicted sales for %s (Model: %s) = %d units\n", next_month, history->model_name, predicted_sales);
}

// Function to calculate total service bill
float calculate_service_bill(ServiceBill *bill) {
    float labor_cost = bill->labor_hours * bill->labor_rate;
    float total_before_tax = labor_cost + bill->spare_parts_cost;
    float tax_amount = total_before_tax * bill->tax_rate;
    float total_bill = total_before_tax + tax_amount;
    return total_bill;
}

// Function to print the service bill details
void print_service_bill(ServiceBill *bill) {
    float total = calculate_service_bill(bill);

    printf("\n------ SERVICE BILL ------\n");
    printf("Customer ID: %d\n", bill->customer_id);
    printf("Car Model: %s\n", bill->car_model);
    printf("Labor Cost: %.2f (%.2f hours @ %.2f per hour)\n",
           bill->labor_hours * bill->labor_rate, bill->labor_hours, bill->labor_rate);
    printf("Spare Parts Cost: %.2f\n", bill->spare_parts_cost);
    printf("Tax (%.2f%%): %.2f\n", bill->tax_rate * 100,
           (bill->labor_hours * bill->labor_rate + bill->spare_parts_cost) * bill->tax_rate);
    printf("Total Bill: %.2f\n", total);
    printf("--------------------------\n");
}

car *create_car(int car_id, const char *model_name, const char *color, const char *fuel_type, const char *car_type, float price) {
    car *new_car = (car *)malloc(sizeof(car));
    new_car->car_id = car_id;
    strcpy(new_car->model_name, model_name);
    strcpy(new_car->color, color);
    strcpy(new_car->fuel_type, fuel_type);
    strcpy(new_car->car_type, car_type);
    new_car->price = price;
    new_car->sold_cars = 0;
    new_car->available_cars = 0;
    new_car->required_stock = 0;
    strcpy(new_car->sold_date, "");
    new_car->next = NULL;
    return new_car;
}

// Function to load car data from a file
void load_car_data(const char *filename, car **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening car data file");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        int car_id;
        char model_name[MAX_STRING_LEN], color[MAX_STRING_LEN], fuel_type[MAX_STRING_LEN], car_type[MAX_STRING_LEN];
        float price;

        if (sscanf(buffer, "%d, %99[^,], %99[^,], %99[^,], %99[^,], %f",
                   &car_id, model_name, color, fuel_type, car_type, &price) == 6) {
            car *new_car = create_car(car_id, model_name, color, fuel_type, car_type, price);
            *head = insert_end(*head, new_car);
        }
    }

    fclose(file);
}

// Function to create a new customer node
customer *create_customer(int customer_id, const char *name, int registration_no, int car_id, const char *mobile_no, const char *address) {
    customer *new_customer = (customer *)malloc(sizeof(customer));
    new_customer->customer_id = customer_id;
    strcpy(new_customer->name, name);
    new_customer->registration_no = registration_no;
    new_customer->car_id = car_id;
    strcpy(new_customer->mobile_no, mobile_no);
    strcpy(new_customer->address, address);
    strcpy(new_customer->prev_service_date, "");
    strcpy(new_customer->next_service_date, "");
    new_customer->actual_amt_to_pay = 0.0;
    new_customer->emi = 0.0;
    strcpy(new_customer->insurance_eval_date, "");
    new_customer->next = NULL;
    return new_customer;
}

// Function to load customer data from a file
void load_customer_data(const char *filename, customer **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening customer data file");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        int customer_id, registration_no, car_id;
        char name[MAX_STRING_LEN], mobile_no[15], address[MAX_STRING_LEN];

        if (sscanf(buffer, "%d, %99[^,], %d, %d, %14[^,], %99[^\n]",
                   &customer_id, name, &registration_no, &car_id, mobile_no, address) == 6) {
            customer *new_customer = create_customer(customer_id, name, registration_no, car_id, mobile_no, address);
            *head = insert_customer_end(*head, new_customer);
        }
    }

    fclose(file);
}

// Function to create a new salesperson node
salesperson *create_salesperson(int salesperson_id, const char *name_salesperson, const char *DOB, const char *address, float sales_target, float sales_achieved, float commission) {
    salesperson *new_sp = (salesperson *)malloc(sizeof(salesperson));
    new_sp->salesperson_id = salesperson_id;
    strcpy(new_sp->name_salesperson, name_salesperson);
    strcpy(new_sp->DOB, DOB);
    strcpy(new_sp->address, address);
    new_sp->sales_target = sales_target;
    new_sp->sales_achieved = sales_achieved;
    new_sp->commission = commission;
    new_sp->list_customer = NULL;
    new_sp->next = NULL;
    return new_sp;
}

// Function to load salesperson data from a file
void load_salesperson_data(const char *filename, salesperson **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening salesperson data file");
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file)) {
        int salesperson_id;
        char name_salesperson[MAX_STRING_LEN], DOB[11], address[MAX_STRING_LEN];
        float sales_target, sales_achieved, commission;

        if (sscanf(buffer, "%d, %99[^,], %10[^,], %99[^,], %f, %f, %f",
                   &salesperson_id, name_salesperson, DOB, address, &sales_target, &sales_achieved, &commission) == 7) {
            salesperson *new_sp = create_salesperson(salesperson_id, name_salesperson, DOB, address, sales_target, sales_achieved, commission);
            *head = insert_salesperson_end(*head, new_sp);
        }
    }

    fclose(file);
}


// Function to load sales history data from a file
void load_sales_history_data(const char *filename, SalesHistory sales_history[], int *num_models) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening sales history file");
        return;
    }

    char buffer[512];
    *num_models = 0;
    while (fgets(buffer, sizeof(buffer), file) && *num_models < MAX_STRING_LEN) {
        char model_name[MAX_STRING_LEN];
        int sales[MONTHS];

        if (sscanf(buffer, "%99[^,], %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                   model_name, &sales[0], &sales[1], &sales[2], &sales[3], &sales[4], &sales[5], &sales[6], &sales[7], &sales[8], &sales[9], &sales[10], &sales[11]) == 13) {
            strcpy(sales_history[*num_models].model_name, model_name);
            for (int i = 0; i < MONTHS; i++) {
                sales_history[*num_models].sales[i] = sales[i];
            }
            (*num_models)++;
        }
    }

    fclose(file);
}

// Function to find sales history for a specific model
SalesHistory *find_sales_history(SalesHistory sales_history[], int num_models, const char *model_name) {
    for (int i = 0; i < num_models; i++) {
        if (strcmp(sales_history[i].model_name, model_name) == 0) {
            return &sales_history[i];
        }
    }
    return NULL; // Return NULL if the model is not found
}

// Function to free the car list
void free_car_list(car *head) {
    car *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to free the customer list
void free_customer_list(customer *head) {
    customer *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to free the salesperson list
void free_salesperson_list(salesperson *head) {
    salesperson *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void merge_sorted_car_lists(car **merged_list, car *list1, car *list2) {
    // Create a dummy node to simplify the merging process
    car dummy;
    car *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->car_id < list2->car_id) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // Attach any remaining elements from list1 or list2
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    // Set merged_list to point to the new sorted merged list
    *merged_list = dummy.next;
}

void merge_sorted_customer_lists(customer **merged_list, customer *list1, customer *list2) {
    customer dummy;
    customer *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->customer_id < list2->customer_id) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    *merged_list = dummy.next;
}

void merge_sorted_salesperson_lists(salesperson **merged_list, salesperson *list1, salesperson *list2) {
    salesperson dummy;
    salesperson *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->salesperson_id < list2->salesperson_id) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    *merged_list = dummy.next;
}

void merge_all_data(showroom *showrooms, car **all_cars, customer **all_customers, salesperson **all_salespersons) {
    for (int i = 0; i < NUM_SHOWROOMS; i++) {
        merge_sorted_car_lists(all_cars, *all_cars, showrooms[i].car_list);
        merge_sorted_customer_lists(all_customers, *all_customers, showrooms[i].customer_list);
        merge_sorted_salesperson_lists(all_salespersons, *all_salespersons, showrooms[i].salesperson_list);
    }
}

void find_most_popular_car_model(car *all_cars, SalesHistory *sales_data, int num_models) {
    char most_popular_model[MAX_STRING_LEN];
    int max_sales = 0;
    
    for (int i = 0; i < num_models; i++) {
        int total_sales = 0;
        for (int j = 0; j < MONTHS; j++) {
            total_sales += sales_data[i].sales[j];
        }
        
        if (total_sales > max_sales) {
            max_sales = total_sales;
            strcpy(most_popular_model, sales_data[i].model_name);
        }
    }
    
    printf("Most popular car model: %s with %d total sales.\n", most_popular_model, max_sales);
}


// Function to find the most successful salesperson
void find_top_salesperson(salesperson *all_salespersons) {
    salesperson *top_salesperson = NULL;
    int max_sales = 0;
    
    salesperson *current = all_salespersons;
    while (current != NULL) {
        if (current->sales_achieved > max_sales) {
            max_sales = current->sales_achieved;
            top_salesperson = current;
        }
        current = current->next;
    }
    
    if (top_salesperson) {
        printf("Most successful salesperson: %s with %d cars sold.\n", top_salesperson->name_salesperson, max_sales);
    } else {
        printf("No salesperson data available.\n");
    }
}


int main() {
    showroom showrooms[NUM_SHOWROOMS] = {0}; // Initialize all showrooms
    SalesHistory sales_history[MAX_STRING_LEN];
    int num_models = 0;
    car *all_cars = NULL;
    customer *all_customers = NULL;
    salesperson *all_salespersons = NULL;

    // Load data for each showroom
    for (int i = 0; i < NUM_SHOWROOMS; i++) {
        char car_file[50], customer_file[50], salesperson_file[50];
        sprintf(car_file, "showroom%d_cars.txt", i + 1);
        sprintf(customer_file, "showroom%d_customers.txt", i + 1);
        sprintf(salesperson_file, "showroom%d_salesperson.txt", i + 1);

        load_car_data(car_file, &showrooms[i].car_list);
        load_customer_data(customer_file, &showrooms[i].customer_list);
        load_salesperson_data(salesperson_file, &showrooms[i].salesperson_list);
    }

    load_sales_history_data("sales_history.txt", sales_history, &num_models);

    
    int choice;
    do {
        // Display menu
        printf("\n===== Car Showroom Management System =====\n");
        printf("1. Display all cars\n");
        printf("2. Display all customers\n");
        printf("3. Display all salespersons\n");
        printf("4. Find and display most popular car model\n");
        printf("5. Display sales history for a specific model\n");
        printf("6. Calculate service bill\n");
        printf("7. Set and check salesperson target\n");
        printf("8. Generate service alerts for customers\n");
        printf("9. Predict next month's sales for a model\n");
        printf("10. Display merged list across three showrooms\n");
        printf("11. Find Top Salesperson\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Display all cars
                for (int i = 0; i < NUM_SHOWROOMS; i++) {
                    printf("\nShowroom %d Cars:\n", i + 1);
                    print_car_list(showrooms[i].car_list);
                }
                break;

            case 2:
                // Display all customers
                for (int i = 0; i < NUM_SHOWROOMS; i++) {
                    printf("\nShowroom %d Customers:\n", i + 1);
                    customer *temp = showrooms[i].customer_list;
                    while (temp != NULL) {
                        printf("Customer ID: %d, Name: %s, Car ID: %d\n", temp->customer_id, temp->name, temp->car_id);
                        temp = temp->next;
                    }
                }
                break;

            case 3:
                // Display all salespersons
                for (int i = 0; i < NUM_SHOWROOMS; i++) {
                    printf("\nShowroom %d Salespersons:\n", i + 1);
                    salesperson *temp = showrooms[i].salesperson_list;
                    while (temp != NULL) {
                        printf("Salesperson ID: %d, Name: %s, Sales Target: %.2f\n", temp->salesperson_id, temp->name_salesperson, temp->sales_target);
                        temp = temp->next;
                    }
                }
                break;

            case 4:
                // Find and display most popular car model
                merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);
                find_most_popular_car_model(all_cars, sales_history, num_models);
                break;

            case 5:
                // Display sales history for a specific model
                {
                    char model_name[MAX_STRING_LEN];
                    printf("Enter car model name: ");
                    scanf("%s", model_name);
                    SalesHistory *history = find_sales_history(sales_history, num_models, model_name);
                    if (history) {
                        printf("Sales history for model %s:\n", history->model_name);
                        for (int i = 0; i < MONTHS; i++) {
                            printf("Month %d: %d units sold\n", i + 1, history->sales[i]);
                        }
                    } else {
                        printf("Sales history for model %s not found.\n", model_name);
                    }
                }
                break;

            case 6:
                // Calculate service bill
                {
                    ServiceBill bill;
                    printf("Enter customer ID: ");
                    scanf("%d", &bill.customer_id);
                    printf("Enter car model: ");
                    scanf("%s", bill.car_model);
                    printf("Enter labor hours: ");
                    scanf("%f", &bill.labor_hours);
                    printf("Enter labor rate: ");
                    scanf("%f", &bill.labor_rate);
                    printf("Enter spare parts cost: ");
                    scanf("%f", &bill.spare_parts_cost);
                    printf("Enter tax rate: ");
                    scanf("%f", &bill.tax_rate);

                    float total_bill = calculate_service_bill(&bill);
                    printf("Total service bill: %.2f\n", total_bill);
                }
                break;

            case 7:
                // Set and check salesperson target
                {
                    char salesperson_name[MAX_STRING_LEN];
                    float target;
                    printf("Enter salesperson name: ");
                    scanf("%s", salesperson_name);
                    printf("Enter new sales target: ");
                    scanf("%f", &target);

                    for (int i = 0; i < NUM_SHOWROOMS; i++) {
                        salesperson *sp = showrooms[i].salesperson_list;
                        while (sp != NULL && strcmp(sp->name_salesperson, salesperson_name) != 0) {
                            sp = sp->next;
                        }
                        if (sp) {
                            set_sales_target(sp, target);
                            check_sales_target(sp);
                            break;
                        }
                    }
                }
                break;

            case 8:
                // Generate service alerts for customers
                {
                    char current_date[11];
                    printf("Enter current date (YYYY-MM-DD): ");
                    scanf("%s", current_date);
                    for (int i = 0; i < NUM_SHOWROOMS; i++) {
                        generate_service_alerts(showrooms[i].customer_list, current_date);
                    }
                }
                break;

            case 9:
                // Predict next month's sales for a model
                {
                    char model_name[MAX_STRING_LEN];
                    printf("Enter car model name: ");
                    scanf("%s", model_name);
                    SalesHistory *history = find_sales_history(sales_history, num_models, model_name);
                    if (history) {
                        int predicted_sales = predict_next_month_sales(history);
                        printf("Predicted sales for next month: %d units\n", predicted_sales);
                    } else {
                        printf("Sales history for model %s not found.\n", model_name);
                    }
                }
                break;

            case 10:
                merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);

                // Display merged car list
                printf("\nMerged Car List:\n");
                print_car_list(all_cars);
                break;

            case 11:
                merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);
                find_top_salesperson(all_salespersons);
                break;

            case 12:
                // Exit the program
                printf("Exiting the program.\n");
                choice=10;
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 10);

    // Free allocated memory
    for (int i = 0; i < NUM_SHOWROOMS; i++) {
        free_car_list(showrooms[i].car_list);
        free_customer_list(showrooms[i].customer_list);
        free_salesperson_list(showrooms[i].salesperson_list);
    }
   
    return 0;
}