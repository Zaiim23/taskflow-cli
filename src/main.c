#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"
#include "task.h"

#define DATA_FILE "data/tasks.txt"
#define INPUT_BUFFER_SIZE 100

static void print_menu(void);
static int read_choice(void);

int main(void)
{
    Task tasks[MAX_TASKS];
    int task_count;
    int choice;
    int running;

    task_count = load_tasks(DATA_FILE, tasks, MAX_TASKS);

    if (task_count < 0) {
        printf(
            "Could not load tasks from %s. "
            "Starting with an empty task list.\n",
            DATA_FILE
        );
        task_count = 0;
    }

    printf("Welcome to TaskFlow CLI!\n");
    printf("%d task(s) loaded.\n", task_count);

    running = 1;

    while (running) {
        print_menu();
        choice = read_choice();

        switch (choice) {
            case 1:
                list_tasks(tasks, task_count);
                break;

            case 2:
                add_task(tasks, &task_count, MAX_TASKS);
                break;

            case 3:
                toggle_task_status(tasks, task_count);
                break;

            case 4:
                delete_task(tasks, &task_count);
                break;

            case 5:
                search_tasks(tasks, task_count);
                break;

            case 0:
                if (save_tasks(DATA_FILE, tasks, task_count)) {
                    printf("Tasks saved successfully.\n");
                } else {
                    printf("Could not save tasks to %s.\n", DATA_FILE);
                }

                printf("Goodbye!\n");
                running = 0;
                break;

            default:
                printf(
                    "Invalid choice. "
                    "Please choose a number from 0 to 5.\n"
                );
                break;
        }
    }

    return 0;
}

static void print_menu(void)
{
    printf("\n=== TaskFlow CLI ===\n");
    printf("1. View all tasks\n");
    printf("2. Add a task\n");
    printf("3. Change task status\n");
    printf("4. Delete a task\n");
    printf("5. Search tasks\n");
    printf("0. Save and exit\n");
}

static int read_choice(void)
{
    char input[INPUT_BUFFER_SIZE];
    char *end_pointer;
    long choice;

    printf("Enter your choice: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (input[0] == '\0') {
        return -1;
    }

    choice = strtol(input, &end_pointer, 10);

    if (*end_pointer != '\0') {
        return -1;
    }

    return (int) choice;
}
