#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define CSV_FILENAME "data.csv"

typedef struct Record {
    char order_date[20];
    char time[20];
    char aging[10];
    char customer_id[20];
    char gender[10];
    char device_type[50];
    char customer_login_type[20];
    char product_category[50];
    char product[100];
    float sales;
    int quantity;
    float discount;
    float profit;
    float shipping_cost;
    char order_priority[20];
    char payment_method[20];
    struct Record *next;
} Record;

Record *linked_list_head = NULL;

// Function prototypes
void insert_into_linked_list(Record *record);
Record *search_in_linked_list(const char *customer_id);
void delete_from_linked_list(const char *customer_id);
void modify_record(Record *record);
void print_record(Record *record);
void free_record(Record *record);
void load_csv();
void save_to_csv();
void display_menu();
void clear_input_buffer();
char* parse_csv_field(char* line, int field);

int main() {
    int choice;
    char customer_id[20];
    Record *found_record = NULL;

    load_csv();

    do {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                Record *new_record = (Record *)malloc(sizeof(Record));
                if (!new_record) {
                    printf("Memory allocation failed.\n");
                    break;
                }

                printf("Enter Order Date (YYYY-MM-DD): ");
                scanf("%19s", new_record->order_date);
                printf("Enter Time (HH:MM:SS): ");
                scanf("%19s", new_record->time);
                printf("Enter Aging: ");
                scanf("%9s", new_record->aging);
                printf("Enter Customer ID: ");
                scanf("%19s", new_record->customer_id);
                printf("Enter Gender (M/F): ");
                scanf("%9s", new_record->gender);
                printf("Enter Device Type: ");
                scanf(" %49[^\n]", new_record->device_type);
                printf("Enter Customer Login Type: ");
                scanf("%19s", new_record->customer_login_type);
                printf("Enter Product Category: ");
                scanf(" %49[^\n]", new_record->product_category);
                printf("Enter Product Name: ");
                scanf(" %99[^\n]", new_record->product);
                printf("Enter Sales Amount: ");
                scanf("%f", &new_record->sales);
                printf("Enter Quantity: ");
                scanf("%d", &new_record->quantity);
                printf("Enter Discount (0.00-1.00): ");
                scanf("%f", &new_record->discount);
                printf("Enter Profit: ");
                scanf("%f", &new_record->profit);
                printf("Enter Shipping Cost: ");
                scanf("%f", &new_record->shipping_cost);
                printf("Enter Order Priority (Low/Medium/High): ");
                scanf("%19s", new_record->order_priority);
                printf("Enter Payment Method: ");
                scanf("%19s", new_record->payment_method);

                new_record->next = NULL;
                insert_into_linked_list(new_record);
                printf("Record inserted successfully.\n");
                clear_input_buffer();
                break;
            }

            case 2:
                printf("Enter Customer ID to search: ");
                scanf("%19s", customer_id);
                found_record = search_in_linked_list(customer_id);
                if (found_record) {
                    printf("Record found:\n");
                    print_record(found_record);
                } else {
                    printf("Record not found.\n");
                }
                break;

            case 3:
                printf("Enter Customer ID to delete: ");
                scanf("%19s", customer_id);
                delete_from_linked_list(customer_id);
                printf("Record deleted (if it existed).\n");
                break;

            case 4:
                printf("Enter Customer ID to modify: ");
                scanf("%19s", customer_id);
                found_record = search_in_linked_list(customer_id);
                if (found_record) {
                    modify_record(found_record);
                    printf("Record modified successfully.\n");
                } else {
                    printf("Record not found.\n");
                }
                break;

            case 5:
                save_to_csv();
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Free all remaining records
    Record *current = linked_list_head;
    while (current) {
        Record *next = current->next;
        free_record(current);
        current = next;
    }

    return 0;
}

// Function implementations

void insert_into_linked_list(Record *record) {
    record->next = linked_list_head;
    linked_list_head = record;
}

Record *search_in_linked_list(const char *customer_id) {
    Record *current = linked_list_head;
    while (current) {
        if (strcmp(current->customer_id, customer_id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete_from_linked_list(const char *customer_id) {
    Record **indirect = &linked_list_head;
    while (*indirect) {
        Record *current = *indirect;
        if (strcmp(current->customer_id, customer_id) == 0) {
            *indirect = current->next;
            free_record(current);
            return;
        }
        indirect = &current->next;
    }
}

void modify_record(Record *record) {
    printf("\n--- Modifying Record for Customer ID: %s ---\n", record->customer_id);
    printf("Enter new Order Date (current: %s): ", record->order_date);
    scanf("%19s", record->order_date);
    printf("Enter new Time (current: %s): ", record->time);
    scanf("%19s", record->time);
    printf("Enter new Aging (current: %s): ", record->aging);
    scanf("%9s", record->aging);
    printf("Enter new Gender (current: %s): ", record->gender);
    scanf("%9s", record->gender);
    printf("Enter new Device Type (current: %s): ", record->device_type);
    scanf(" %49[^\n]", record->device_type);
    printf("Enter new Customer Login Type (current: %s): ", record->customer_login_type);
    scanf("%19s", record->customer_login_type);
    printf("Enter new Product Category (current: %s): ", record->product_category);
    scanf(" %49[^\n]", record->product_category);
    printf("Enter new Product (current: %s): ", record->product);
    scanf(" %99[^\n]", record->product);
    printf("Enter new Sales (current: %.2f): ", record->sales);
    scanf("%f", &record->sales);
    printf("Enter new Quantity (current: %d): ", record->quantity);
    scanf("%d", &record->quantity);
    printf("Enter new Discount (current: %.2f): ", record->discount);
    scanf("%f", &record->discount);
    printf("Enter new Profit (current: %.2f): ", record->profit);
    scanf("%f", &record->profit);
    printf("Enter new Shipping Cost (current: %.2f): ", record->shipping_cost);
    scanf("%f", &record->shipping_cost);
    printf("Enter new Order Priority (current: %s): ", record->order_priority);
    scanf("%19s", record->order_priority);
    printf("Enter new Payment Method (current: %s): ", record->payment_method);
    scanf("%19s", record->payment_method);
    clear_input_buffer();
}

void print_record(Record *record) {
    if (!record) return;
    printf("\n--- Customer Record ---\n");
    printf("Order Date: %s\n", record->order_date);
    printf("Time: %s\n", record->time);
    printf("Aging: %s\n", record->aging);
    printf("Customer ID: %s\n", record->customer_id);
    printf("Gender: %s\n", record->gender);
    printf("Device Type: %s\n", record->device_type);
    printf("Customer Login Type: %s\n", record->customer_login_type);
    printf("Product Category: %s\n", record->product_category);
    printf("Product: %s\n", record->product);
    printf("Sales: $%.2f\n", record->sales);
    printf("Quantity: %d\n", record->quantity);
    printf("Discount: %.2f%%\n", record->discount * 100);
    printf("Profit: $%.2f\n", record->profit);
    printf("Shipping Cost: $%.2f\n", record->shipping_cost);
    printf("Order Priority: %s\n", record->order_priority);
    printf("Payment Method: %s\n", record->payment_method);
    printf("----------------------\n");
}

void free_record(Record *record) {
    free(record);
}

char* parse_csv_field(char* line, int field) {
    char* result = malloc(MAX_LINE_LENGTH);
    int i = 0;
    int in_quotes = 0;
    int current_field = 0;
    int result_index = 0;

    while (line[i] != '\0' && current_field <= field) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
            i++;
            continue;
        }

        if (!in_quotes && line[i] == ',') {
            current_field++;
            i++;
            if (current_field == field) {
                while (line[i] != '\0' && line[i] != ',' && (in_quotes || line[i] != '"')) {
                    if (line[i] == '"') {
                        in_quotes = !in_quotes;
                        i++;
                        continue;
                    }
                    result[result_index++] = line[i++];
                }
                result[result_index] = '\0';
                return result;
            }
            continue;
        }

        if (current_field == field) {
            result[result_index++] = line[i];
        }
        i++;
    }

    result[result_index] = '\0';
    return result;
}

void load_csv() {
    FILE *file = fopen(CSV_FILENAME, "r");
    if (!file) {
        printf("Warning: Could not open %s. Starting with empty database.\n", CSV_FILENAME);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int is_first_line = 1;

    while (fgets(line, sizeof(line), file)) {
        if (is_first_line) {
            is_first_line = 0;
            continue;
        }

        line[strcspn(line, "\n")] = 0;
        Record *record = (Record *)malloc(sizeof(Record));
        if (!record) {
            printf("Memory allocation failed.\n");
            continue;
        }

        // Parse each field
        char* field;
        
        field = parse_csv_field(line, 0);
        strncpy(record->order_date, field, sizeof(record->order_date));
        free(field);
        
        field = parse_csv_field(line, 1);
        strncpy(record->time, field, sizeof(record->time));
        free(field);
        
        field = parse_csv_field(line, 2);
        strncpy(record->aging, field, sizeof(record->aging));
        free(field);
        
        field = parse_csv_field(line, 3);
        strncpy(record->customer_id, field, sizeof(record->customer_id));
        free(field);
        
        field = parse_csv_field(line, 4);
        strncpy(record->gender, field, sizeof(record->gender));
        free(field);
        
        field = parse_csv_field(line, 5);
        strncpy(record->device_type, field, sizeof(record->device_type));
        free(field);
        
        field = parse_csv_field(line, 6);
        strncpy(record->customer_login_type, field, sizeof(record->customer_login_type));
        free(field);
        
        field = parse_csv_field(line, 7);
        strncpy(record->product_category, field, sizeof(record->product_category));
        free(field);
        
        field = parse_csv_field(line, 8);
        strncpy(record->product, field, sizeof(record->product));
        free(field);
        
        field = parse_csv_field(line, 9);
        record->sales = atof(field);
        free(field);
        
        field = parse_csv_field(line, 10);
        record->quantity = atoi(field);
        free(field);
        
        field = parse_csv_field(line, 11);
        record->discount = atof(field);
        free(field);
        
        field = parse_csv_field(line, 12);
        record->profit = atof(field);
        free(field);
        
        field = parse_csv_field(line, 13);
        record->shipping_cost = atof(field);
        free(field);
        
        field = parse_csv_field(line, 14);
        strncpy(record->order_priority, field, sizeof(record->order_priority));
        free(field);
        
        field = parse_csv_field(line, 15);
        strncpy(record->payment_method, field, sizeof(record->payment_method));
        free(field);

        record->next = NULL;
        insert_into_linked_list(record);
    }

    fclose(file);
    printf("Data loaded from %s\n", CSV_FILENAME);
}

void save_to_csv() {
    FILE *file = fopen(CSV_FILENAME, "w");
    if (!file) {
        printf("Error: Could not open %s for writing\n", CSV_FILENAME);
        return;
    }

    // Write CSV header
    fprintf(file, "Order_Date,Time,Aging,Customer_Id,Gender,Device_Type,Customer_Login_type,");
    fprintf(file, "Product_Category,Product,Sales,Quantity,Discount,Profit,Shipping_Cost,");
    fprintf(file, "Order_Priority,Payment_method\n");

    // Write all records
    Record *current = linked_list_head;
    while (current) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%.2f,%d,%.2f,%.2f,%.2f,%s,%s\n",
                current->order_date,
                current->time,
                current->aging,
                current->customer_id,
                current->gender,
                current->device_type,
                current->customer_login_type,
                current->product_category,
                current->product,
                current->sales,
                current->quantity,
                current->discount,
                current->profit,
                current->shipping_cost,
                current->order_priority,
                current->payment_method);
        current = current->next;
    }

    fclose(file);
    printf("Data saved to %s\n", CSV_FILENAME);
}

void display_menu() {
    printf("\n===== Sales Records Management System =====\n");
    printf("1. Add New Record\n");
    printf("2. Search Record by Customer ID\n");
    printf("3. Delete Record\n");
    printf("4. Modify Record\n");
    printf("5. Save All Changes to CSV\n");
    printf("6. Exit Program\n");
    printf("=========================================\n");
}

void clear_input_buffer() {
    while (getchar() != '\n');
}