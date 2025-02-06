#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "car.h"

int main() {
    car *car_list = NULL;
    customer *customer_list = NULL;
    salesperson *salesperson_list = NULL;
    ModelSales *model_sales_map = NULL;
    SalesHistory sales_history[MAX_STRING_LEN];
    int num_models = 0;

    int choice;
    char filename[MAX_STRING_LEN];

    // Load data from files
    load_car_data("cars.txt", &car_list);
    load_customer_data("customers.txt", &customer_list);
    load_salesperson_data("salespersons.txt", &salesperson_list);
    load_model_sales_data("sales_data.txt", &model_sales_map);
    load_sales_history_data("sales_history.txt", sales_history, &num_models);

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
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Display all cars
                print_car_list(car_list);
                break;

            case 2:
                // Display all customers
                {
                    customer *temp = customer_list;
                    while (temp != NULL) {
                        printf("Customer ID: %d, Name: %s, Car ID: %d\n", temp->customer_id, temp->name, temp->car_id);
                        temp = temp->next;
                    }
                }
                break;

            case 3:
                // Display all salespersons
                {
                    salesperson *temp = salesperson_list;
                    while (temp != NULL) {
                        printf("Salesperson ID: %d, Name: %s, Sales Target: %.2f\n", temp->salesperson_id, temp->name_salesperson, temp->sales_target);
                        temp = temp->next;
                    }
                }
                break;

            case 4:
                // Find and display most popular car model
                find_most_popular_model();
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
                    salesperson *sp = salesperson_list;
                    while (sp != NULL && strcmp(sp->name_salesperson, salesperson_name) != 0) {
                        sp = sp->next;
                    }
                    if (sp) {
                        set_sales_target(sp, target);
                        check_sales_target(sp);
                    } else {
                        printf("Salesperson %s not found.\n", salesperson_name);
                    }
                }
                break;

            case 8:
                // Generate service alerts for customers
                {
                    char current_date[11];
                    printf("Enter current date (YYYY-MM-DD): ");
                    scanf("%s", current_date);
                    generate_service_alerts(customer_list, current_date);
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
                // Exit the program
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 10);

    // Free allocated memory
    free_sales_map();
    return 0;
}

