#ifndef TASK_H
#define TASK_H

#define MAX_TITLE_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 256
#define MAX_PRIORITY_LENGTH 10
#define MAX_TASKS 100

typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char priority[MAX_PRIORITY_LENGTH];
    int completed;
} Task;

void list_tasks(const Task tasks[], int task_count);
void add_task(Task tasks[], int *task_count, int max_tasks);
void toggle_task_status(Task tasks[], int task_count);
void delete_task(Task tasks[], int *task_count);
void search_tasks(const Task tasks[], int task_count);

#endif