# sql-on-c
A very wanky RDBMS on C, completely vibe coded for a college DS course. 

## Building SQL (or a pretty similar RDBMS Application) on C

## Abstract 

SQL, or Structed Query Language, is a backend Database Management System with relational logic and operands which allow for streamlined data management. SQL just seems like something that can briefly be built on C, so that's what I tried.

## Problem Description 

A pretty common problem when big tech just came into the picture - lack of logical organization of data. This occurs especially when the quantity of data exponentially increases, i.e., the age of information. The introduction of web3, AI, and the birth of big data made us require alot of this efficient storing techniques. From the Data Structures course, we can now build pretty relevant storage systems where we can store our data efficiently and even use them for more complex algorithms. So, with this project, big data can be stored extremely efficiently. 

## Implementation Details 

There's a handful of features - firstly, 2 default tables: Employees{char (string in SQL terms) name} and Department {char dept}. With these as the base, hardcoded, a lot of user choice and "interactive" features were implemented. The unique aspect of this project is the usage of foreign keys, a pointer field links two seperate tables, which can be visualized as vertices/nodes of their own. This builds the relational aspect of it. Further, since this is a DS course, I implemented an undo feature using stacks which I thought was necessary after I messed up testing the system quite alot. 

## Challenges Faced

I thought of adding the undo feature way too late and I had to thoroughly tweak many different parts of the program for all features to integrate with a feature like undo which requires a pre-requiste operation. I was also very tempted to hardcode all the tables and just show the final product, but, user interface and interactiveness was something I needed to improve on. I also didn't know how to implement a few complex features, for which I vibe-coded (used A.I. for reference) and learnt on my own. 

## Conclusion and Learnings 

To conclude, this was a lovely learning project for someone who appreciated SQL prior to the DS course; decomplexifying and removing the abstraction of SQL that I previously knew. I learnt how to translate general logical understanding into code for any language, design and appreciate RDBMS (since it was so painful), and improve on my programming skills like focusing on user quality of life by adding interactive features. And, ofcourse, also to establish a feature like undo prior to everything else, foundational features and workflow matter!

## Data Structures used

1) Linked Lists, 2) Stacks

 Was planning on using graphs, but I started the project before graphs were started during the lectures.

# EXAMPLE WORKING IN THE TERMINAL

sh-5.2$ cd "/home/abhi/Documents/Code/LearnC/ds_course/basic-data-structures-main/" && gcc sql_on_c.c -o sql_on_c && "/home/abhi/Documents/Code/LearnC/ds_course/basic-data-structures-main/"sql_on_c

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 3

--- Tables ---
Table: Departments
Columns:
  - name (STRING)

Table: Employees
Columns:
  - name (STRING)
  - department (STRING)


==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 1
Enter department name: Salary
[System] Operation recorded for undo (Stack size: 1)

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 7
[System] Undoing: Add Department

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 1
Enter department name: Salary
[System] Operation recorded for undo (Stack size: 1)

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 3

--- Tables ---
Table: Departments
Columns:
  - name (STRING)

Table: Employees
Columns:
  - name (STRING)
  - department (STRING)


==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 6
Enter table name: Salary
Enter number of columns: 2
Column 1 name: amount
Column 1 type (0 = STRING, 1 = INT): 1
Column 2 name: type
Column 2 type (0 = STRING, 1 = INT): 0
[System] Operation recorded for undo (Stack size: 2)
Custom table 'Salary' created with 2 columns.

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 3

--- Tables ---
Table: Departments
Columns:
  - name (STRING)

Table: Employees
Columns:
  - name (STRING)
  - department (STRING)

Table: Salary
Columns:
  - amount (INT)
  - type (STRING)


==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 6
Enter table name: Employee Transfer
Enter number of columns: 2
Column 1 name: name
Column 1 type (0 = STRING, 1 = INT): 0
Column 2 name: branchoftransfer
Column 2 type (0 = STRING, 1 = INT): 0
[System] Operation recorded for undo (Stack size: 3)
Custom table 'Employee Transfer' created with 2 columns.

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 4

Available Tables:
1. Departments
2. Employees
3. Salary
4. Employee Transfer

Select source table (1-4): 2

Columns in Employees:
1. name
2. department

Select source column (1-2): 1

Select target table (1-4): 4

Columns in Employee Transfer:
1. name
2. branchoftransfer

Select target column (1-2): 1
[System] Operation recorded for undo (Stack size: 4)
Foreign key added: Employees.name → Employee Transfer.name

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 3

--- Tables ---
Table: Departments
Columns:
  - name (STRING)

Table: Employees
Columns:
  - name (STRING)  [FK → Employee Transfer.name]
  - department (STRING)

Table: Salary
Columns:
  - amount (INT)
  - type (STRING)

Table: Employee Transfer
Columns:
  - name (STRING)
  - branchoftransfer (STRING)


==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 7
[System] Undoing: Add Foreign Key

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 2 
Enter employee name: Jim Halpert
Enter department name: Sales
Department not found. Creating new department.
[System] Operation recorded for undo (Stack size: 4)

==== MENU ====
1. Add Department
2. Add Employee
3. Show Tables
4. Add Foreign Key
5. Exit
6. Create Custom Table
7. Undo Last Operation
Choice: 5
Goodbye!
