#ifndef STORAGE_H
#define STORAGE_H

#include "task.h"

int load_tasks(const char *filename, Task tasks[], int max_tasks);
int save_tasks(const char *filename, const Task tasks[], int task_count);

#endif