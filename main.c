// Vinit More BT23CSE083 R4
// Jayesh Patil BT23CSE078 R4

#include "car.h"

int main()
{
    showroom showrooms[NUM_SHOWROOMS] = {0}; // Initialize all showrooms
    SalesHistory sales_history[MAX_STRING_LEN];
    int num_models = 0;
    car *all_cars = NULL;
    customer *all_customers = NULL;
    salesperson *all_salespersons = NULL;

    // Load data for each showroom
    for (int i = 0; i < NUM_SHOWROOMS; i++)
    {
        char car_file[50], customer_file[50], salesperson_file[50];
        sprintf(car_file, "showroom%d_cars.txt", i + 1);
        sprintf(customer_file, "showroom%d_customers.txt", i + 1);
        sprintf(salesperson_file, "showroom%d_salesperson.txt", i + 1);

        load_car_data(car_file, &showrooms[i].car_list);
        load_customer_data(customer_file, &showrooms[i].customer_list);
        load_salesperson_data(salesperson_file, &showrooms[i].salesperson_list, showrooms[i].customer_list);
    }

    load_sales_history_data("sales_history.txt", sales_history, &num_models);

    int choice;
    do
    {
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
        printf("12. Sort according to car sold date\n");
        printf("13. Find total loan amount pending for a salesperson\n");
        printf("14. Sales of specific model in given duration of dates\n");
        printf("15. Add Salesperson\n");
        printf("16. Add Car\n");
        printf("17. Add Customer\n");
        printf("18. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Display all cars
            for (int i = 0; i < NUM_SHOWROOMS; i++)
            {
                printf("\nShowroom %d Cars:\n", i + 1);
                print_car_list(showrooms[i].car_list);
            }
            break;

        case 2:
            // Display all customers
            for (int i = 0; i < NUM_SHOWROOMS; i++)
            {
                printf("\nShowroom %d Customers:\n", i + 1);
                customer *temp = showrooms[i].customer_list;
                while (temp != NULL)
                {
                    printf("Customer ID: %d, Name: %s, Car ID: %d\n", temp->customer_id, temp->name, temp->car_id);
                    temp = temp->next;
                }
            }
            break;

        case 3:
            // Display all salespersons
            for (int i = 0; i < NUM_SHOWROOMS; i++)
            {
                printf("\nShowroom %d Salespersons:\n", i + 1);
                salesperson *temp = showrooms[i].salesperson_list;
                while (temp != NULL)
                {
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
                if (history)
                {
                    printf("Sales history for model %s:\n", history->model_name);
                    for (int i = 0; i < MONTHS; i++)
                    {
                        printf("Month %d: %d units sold\n", i + 1, history->sales[i]);
                    }
                }
                else
                {
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

                for (int i = 0; i < NUM_SHOWROOMS; i++)
                {
                    salesperson *sp = showrooms[i].salesperson_list;
                    while (sp != NULL && strcmp(sp->name_salesperson, salesperson_name) != 0)
                    {
                        sp = sp->next;
                    }
                    if (sp)
                    {
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
                for (int i = 0; i < NUM_SHOWROOMS; i++)
                {
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
                if (history)
                {
                    int predicted_sales = predict_next_month_sales(history);
                    printf("Predicted sales for next month: %d units\n", predicted_sales);
                }
                else
                {
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
            // Sort cars based on sold date
            merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);
            car_sold_date_merge_sort(&all_cars);
            printf("\nCars sorted by sold date:\n");
            print_car_list(all_cars);
            break;

        case 13:
        {
            char salesperson_name[MAX_STRING_LEN];
            printf("Enter salesperson name: ");
            scanf("%s", salesperson_name);

            merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);
            float total_loan = get_total_loan_pending(all_salespersons, salesperson_name);

            if (total_loan != -1)
                printf("Total loan amount pending for %s: %.2f\n", salesperson_name, total_loan);
        }
        break;

        case 14:
        {
            char model_name[MAX_STRING_LEN];
            char start_date[11], end_date[11];

            printf("Enter car model name: ");
            scanf("%s", model_name);
            printf("Enter start date (YYYY/MM/DD): ");
            scanf("%s", start_date);
            printf("Enter end date (YYYY/MM/DD): ");
            scanf("%s", end_date);

            // merge_all_data(showrooms, &all_cars, &all_customers, &all_salespersons);
            float total_sales = find_sales_figures(showrooms[0].car_list, model_name, start_date, end_date);

            printf("Total sales for %s from %s to %s: $%.2f\n", model_name, start_date, end_date, total_sales);
        }
        break;

        case 15:
            add_salesperson_to_showroom(showrooms);
            break;

        case 16:
            add_car();
            break;
        
        case 17:
            add_customer_to_showroom(showrooms, 3);
            break;

        case 18:
            // Exit the program
            printf("Exiting the program.\n");
            choice = 10;
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 10);

    // Free allocated memory
    for (int i = 0; i < NUM_SHOWROOMS; i++)
    {
        free_car_list(showrooms[i].car_list);
        free_customer_list(showrooms[i].customer_list);
        free_salesperson_list(showrooms[i].salesperson_list);
    }

    return 0;
}
