#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//forward declaration so ForeignKey can refer to Table
typedef struct Table Table;

#define MAX_TABLES 100

Table* table_registry[MAX_TABLES];

int table_count = 0;

typedef struct{

    char* name;
    int type;  //0 = string, 1 = int

}Column;

typedef struct{

    int source_column;
    Table* target_table;
    int target_column;

}ForeignKey;

typedef struct{

    void** values; //allows to store different data types, really cool!

}Tuple;

struct Table{

    char* name;
    Column* columns;
    int column_count;

    Tuple** rows;
    int row_count;

    ForeignKey* foreign_keys;
    int foreign_key_count;

};


Table* create_table(char* name, int column_count){

    Table* table = malloc(sizeof(Table));
    table -> name = strdup(name); //good practice to just duplicate the string here instead
    table -> columns = NULL; 
    table -> column_count = column_count;
    table -> rows = NULL;
    table -> row_count = 0;
    table -> foreign_keys = NULL;
    table -> foreign_key_count = 0;
    return table;
}

Table* create_table_from_user_input(){

    char table_name[100];
    int column_count;

    printf("Enter table name: ");

    fgets(table_name, sizeof(table_name), stdin);
    table_name[strcspn(table_name, "\n")] = 0;

    printf("Enter number of columns: ");

    scanf("%d", &column_count);
    getchar(); //clear newline

    Table* table = create_table(table_name, column_count);
    table->columns = malloc(sizeof(Column) * column_count);

    for (int i = 0; i < column_count; i++) {
        char col_name[100];
        int type;

        printf("Column %d name: ", i + 1);
        fgets(col_name, sizeof(col_name), stdin);
        col_name[strcspn(col_name, "\n")] = 0;

        printf("Column %d type (0 = STRING, 1 = INT): ", i + 1);
        scanf("%d", &type);
        getchar(); // clear newline

        table->columns[i].name = strdup(col_name);
        table->columns[i].type = type;
    }

    // Register in global list
    table_registry[table_count++] = table;
    return table;
}

Tuple* create_tuple(Table* table){

    Tuple* tuple = malloc(sizeof(Tuple));
    tuple -> values = malloc(sizeof(void*) * table->column_count);
    return tuple;
}

void insert_tuple(Table* table, Tuple* tuple){

    //foreign key constraints
    for(int i = 0; i < table -> foreign_key_count; i++){

        ForeignKey* fk = &table -> foreign_keys[i];
        void* foreign_value = tuple -> values[fk -> source_column];

        int found = 0;
        for (int j = 0; j < fk -> target_table -> row_count; j++){

            void* target_value = fk -> target_table -> rows[j] -> values[fk -> target_column];

            if (strcmp(target_value, foreign_value) == 0){

                found = 1;
                break;
            }

        }

        if (found == 0){

            printf("[ERROR CODE 001] Foreign key constraint failed on column %d: tuple does not exist in target table '%s'\n", fk -> source_column, fk -> target_table->name);
            return; //don't insert

        }
    }

    // If valid, insert the tuple
    table->rows = realloc(table -> rows, sizeof(Tuple*) * (table -> row_count + 1));
    table->rows[table->row_count++] = tuple;

}


void add_foreign_key(Table* table, int column_index, Table* target, int target_column){

    table -> foreign_keys = realloc(table -> foreign_keys, sizeof(ForeignKey) * (table -> foreign_key_count + 1));

    ForeignKey fk;
    fk.source_column = column_index;
    fk.target_table = target;
    fk.target_column = target_column;

    table -> foreign_keys[table -> foreign_key_count] = fk;
    table -> foreign_key_count++;

}

Tuple* find_department(Table* departments, const char* name){

    for (int i = 0; i < departments->row_count; i++){

        Tuple* tuple = departments->rows[i];

        if (strcmp(tuple -> values[0], name) == 0){

            return tuple;
        }
    }

    return NULL;
}


void print_employees(Table* employees) {

    printf("Employees Table:\n");

    for (int i = 0; i < employees -> row_count; i++) {

        Tuple* emp = employees -> rows[i];
        char* name = emp -> values[0];
        Tuple* dept = emp -> values[1];
        char* dept_name = dept -> values[0];

        printf("Employee: %s, Department: %s\n", name, dept_name);

    }
}

void create_department(Table* departments, const char* dept_name){

    Tuple* new_dept = create_tuple(departments);
    new_dept->values[0] = strdup(dept_name);
    insert_tuple(departments, new_dept);

}

void read_input(char* buffer, int size){

    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  //remove newline

}

void show_tables(){

    printf("\n--- Tables ---\n");

    for (int t = 0; t < table_count; t++){

        Table* table = table_registry[t];
        printf("Table: %s\n", table->name);
        printf("Columns:\n");

        for (int c = 0; c < table->column_count; c++){

            char* type_str = (table->columns[c].type == 0) ? "STRING" : "INT";
            printf("  - %s (%s)", table->columns[c].name, type_str);

            // Check foreign keys
            for (int fk_i = 0; fk_i < table->foreign_key_count; fk_i++){

                ForeignKey* fk = &table->foreign_keys[fk_i];

                if (fk->source_column == c) {
                    printf("  [FK → %s.%s]",
                        fk->target_table->name,
                        fk->target_table->columns[fk->target_column].name
                    );
                }
            }

            printf("\n");
        }

        printf("\n");
    }
}

int main(){

    int choice;

    // Pre-create Departments and Employees table dynamically
    Table* departments = create_table("Departments", 1);
    departments->columns = malloc(sizeof(Column));
    departments->columns[0].name = strdup("name");
    departments->columns[0].type = 0;
    table_registry[table_count++] = departments;

    Table* employees = create_table("Employees", 2);
    employees->columns = malloc(sizeof(Column) * 2);
    employees->columns[0].name = strdup("name");
    employees->columns[0].type = 0;
    employees->columns[1].name = strdup("department");
    employees->columns[1].type = 0;
    table_registry[table_count++] = employees;

    while(1==1){
        printf("\n==== MENU ====\n");
        printf("1. Add Department\n");
        printf("2. Add Employee\n");
        printf("3. Show Tables\n");
        printf("4. Add Foreign Key\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1){

            char dept_name[100];
            printf("Enter department name: ");
            fgets(dept_name, sizeof(dept_name), stdin);
            dept_name[strcspn(dept_name, "\n")] = 0;

            create_department(departments, dept_name);

        } 
        
        else if (choice == 2) {
            char emp_name[100], dept_name[100];

            printf("Enter employee name: ");
            fgets(emp_name, sizeof(emp_name), stdin);
            emp_name[strcspn(emp_name, "\n")] = 0;

            printf("Enter department name: ");
            fgets(dept_name, sizeof(dept_name), stdin);
            dept_name[strcspn(dept_name, "\n")] = 0;

            Tuple* dept_ptr = find_department(departments, dept_name);
            if (!dept_ptr) {
                printf("Department not found. Creating new department.\n");
                create_department(departments, dept_name);
                dept_ptr = find_department(departments, dept_name);
            }

            Tuple* new_emp = create_tuple(employees);
            new_emp->values[0] = strdup(emp_name);
            new_emp->values[1] = dept_ptr;

            insert_tuple(employees, new_emp);

        } 
        
        else if (choice == 3) {

            show_tables();

        } 
        
        else if (choice == 4) {
            // Add a foreign key from Employees[1] → Departments[0]
            add_foreign_key(employees, 1, departments, 0);
            printf("Foreign key added: Employees.department → Departments.name\n");

        } 
        
        else if (choice == 5){

            printf("Goodbye!\n");
            break;

        } 
        
        else{

            printf("Invalid choice.\n");
        }
    }

    return 0;

    /*Table* departments = create_table("Departments", 1);
    Table* employees = create_table("Employees", 2);

    // Link: employees.dept_ptr → departments.name
    add_foreign_key(employees, 1, departments, 0);

    char emp_name[100], dept_name[100], choice[10];

    while(1 == 1){

        printf("\n--- Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. View Departments\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;

        if(strcmp(choice, "1") == 0){

            printf("Enter employee name: ");
            fgets(emp_name, sizeof(emp_name), stdin);
            emp_name[strcspn(emp_name, "\n")] = 0;

            printf("Enter department name: ");
            fgets(dept_name, sizeof(dept_name), stdin);
            dept_name[strcspn(dept_name, "\n")] = 0;

            //check if department exists
            Tuple* dept_ptr = find_department(departments, dept_name);

            if (!dept_ptr){

                printf("Department not found. Creating new department: %s\n", dept_name);
                create_department(departments, dept_name);
                dept_ptr = find_department(departments, dept_name); //NOWW it exists

            }

            //Create and insert employee

            Tuple* new_emp = create_tuple(employees);
            new_emp->values[0] = strdup(emp_name);
            new_emp->values[1] = dept_ptr;
            insert_tuple(employees, new_emp);

            printf("Employee added.\n");

        } 
        
        else if (strcmp(choice, "2") == 0){
            print_employees(employees);

        } 
        
        else if (strcmp(choice, "3") == 0){

            printf("Departments:\n");

            for (int i = 0; i < departments->row_count; i++){

                char* dept = departments->rows[i]->values[0];
                printf("- %s\n", dept);
            }

        } 
        
        else if (strcmp(choice, "4") == 0){

            printf("Exiting.\n");
            break;

        }
        
        else{

            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;*/

    /*// Create Departments Table
    Table* departments = create_table("Departments", 1);

    Tuple* d1 = create_tuple(departments);
    d1->values[0] = strdup("Engineering");
    insert_tuple(departments, d1);

    Tuple* d2 = create_tuple(departments);
    d2->values[0] = strdup("HR");
    insert_tuple(departments, d2);

    // Create Employees Table (name, dept_ptr)
    Table* employees = create_table("Employees", 2);
    
    Tuple* e1 = create_tuple(employees);
    e1->values[0] = strdup("Alice");
    e1->values[1] = d1;  // points to Engineering
    insert_tuple(employees, e1);

    Tuple* e2 = create_tuple(employees);
    e2->values[0] = strdup("Bob");
    e2->values[1] = d2;  // points to HR
    insert_tuple(employees, e2);

    Tuple* e3 = create_tuple(employees);
    e3->values[0] = strdup("Charlie");
    e3->values[1] = (Tuple*)0xDEADBEEF; // Invalid pointer
    insert_tuple(employees, e3);

    print_employees(employees);

    // Cleanup omitted for brevity

    return 0;*/
}
