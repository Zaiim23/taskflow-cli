#include <stdio.h>
#include <string.h>

#include "storage.h"
#include "task.h"

#define FILE_LINE_LENGTH 512

int load_tasks(
    const char *filename,
    Task tasks[],
    int max_tasks
)
{
    FILE *file;
    char line[FILE_LINE_LENGTH];
    int task_count;

    file = fopen(filename, "r");

    if (file == NULL) {
        return -1;
    }

    task_count = 0;

    while (
        task_count < max_tasks &&
        fgets(line, sizeof(line), file) != NULL
    ) {
        Task task;
        int fields_read;

        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '\0') {
            continue;
        }

        fields_read = sscanf(
            line,
            "%d|%99[^|]|%255[^|]|%9[^|]|%d",
            &task.id,
            task.title,
            task.description,
            task.priority,
            &task.completed
        );

        if (fields_read == 5) {
            tasks[task_count] = task;
            task_count++;
        }
    }

    fclose(file);
    return task_count;
}

int save_tasks(
    const char *filename,
    const Task tasks[],
    int task_count
)
{
    FILE *file;
    int i;

    file = fopen(filename, "w");

    if (file == NULL) {
        return 0;
    }

    for (i = 0; i < task_count; i++) {
        fprintf(
            file,
            "%d|%s|%s|%s|%d\n",
            tasks[i].id,
            tasks[i].title,
            tasks[i].description,
            tasks[i].priority,
            tasks[i].completed
        );
    }

    fclose(file);
    return 1;
}
