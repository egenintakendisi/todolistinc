To-Do List Application
Description
This To-Do List application is designed to help you manage tasks effectively. It uses an advanced data structure, the linked list, to store and manage tasks. Linked lists are crucial in computer science for their efficient insertion and deletion operations, which are demonstrated in this application.

Features
Task Creation: Add new tasks with a title, description, deadline, status, priority, and progress percentage.
Task Viewing: Display the list of tasks.
Task Deletion: Remove tasks from the list.
Search and Filter: Search tasks by title, deadline, or priority.
Automatic Cleanup: Automatically remove tasks that have surpassed a certain time threshold.
Data Persistence: Save tasks to a file and load them upon startup.
Data Structure
This application uses a linked list to store tasks. A linked list is a data structure consisting of nodes where each node contains data and a reference to the next node in the sequence. This structure allows for efficient dynamic memory usage and easy insertion and deletion of nodes, which is ideal for managing a to-do list where tasks can be frequently added or removed.

How to Use
Clone the Repository:
git clone <repository-url>
cd <repository-directory>
Compile the Code:
Use a C compiler to compile the source code:
gcc -o todolist main.c
Run the Application:
Execute the compiled program:
./todolist

Interacting with the Application:

View List: View the current list of tasks.
Create Task: Add a new task by providing its title, description, deadline, status, priority, and progress.
Delete Task: Remove a specific task from the list.
Search and Filter: Search for tasks by title, deadline, or priority.
Save and Exit: Save the current list of tasks to a file and exit the application.

File Operations
Data File: Tasks are saved to 213ToDoList.txt. Ensure that this file is accessible for the application to read and write data.
Error Handling
The application handles errors related to file operations and invalid input. If any issue occurs, appropriate error messages are displayed.

License
This project is licensed under the MIT License 
