#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

#define INPUT_BUFFER_SIZE 512

static void read_line(const char *prompt, char *buffer, size_t buffer_size);
static int read_integer(const char *prompt, int *value);
static int find_task_index_by_id(const Task tasks[], int task_count, int id);
static int contains_ignore_case(const char *text, const char *search_term);
static int is_valid_priority(const char *priority);
static void convert_to_uppercase(char *text);
static int get_next_task_id(const Task tasks[], int task_count);
static void display_task(const Task *task);

void list_tasks(const Task tasks[], int task_count)
{
    int i;

    if (task_count == 0) {
        printf("\nNo tasks found.\n");
        return;
    }

    printf("\n=== All Tasks ===\n");

    for (i = 0; i < task_count; i++) {
        display_task(&tasks[i]);
    }
}

void add_task(Task tasks[], int *task_count, int max_tasks)
{
    Task new_task;

    if (*task_count >= max_tasks) {
        printf("\nThe task list is full.\n");
        return;
    }

    printf("\n=== Add Task ===\n");
    new_task.id = get_next_task_id(tasks, *task_count);

    read_line("Title: ", new_task.title, sizeof(new_task.title));

    if (strlen(new_task.title) == 0) {
        printf("The title cannot be empty.\n");
        return;
    }

    read_line(
        "Description: ",
        new_task.description,
        sizeof(new_task.description)
    );

    do {
        read_line(
            "Priority (LOW, MEDIUM or HIGH): ",
            new_task.priority,
            sizeof(new_task.priority)
        );

        convert_to_uppercase(new_task.priority);

        if (!is_valid_priority(new_task.priority)) {
            printf("Invalid priority. Use LOW, MEDIUM or HIGH.\n");
        }
    } while (!is_valid_priority(new_task.priority));

    new_task.completed = 0;
    tasks[*task_count] = new_task;
    (*task_count)++;

    printf("Task added successfully with ID %d.\n", new_task.id);
}

void toggle_task_status(Task tasks[], int task_count)
{
    int id;
    int task_index;

    if (task_count == 0) {
        printf("\nThere are no tasks to update.\n");
        return;
    }

    list_tasks(tasks, task_count);

    if (!read_integer("\nEnter the task ID: ", &id)) {
        printf("Invalid ID. Please enter a whole number.\n");
        return;
    }

    task_index = find_task_index_by_id(tasks, task_count, id);

    if (task_index == -1) {
        printf("No task was found with ID %d.\n", id);
        return;
    }

    tasks[task_index].completed = !tasks[task_index].completed;

    if (tasks[task_index].completed) {
        printf("Task %d was marked as completed.\n", tasks[task_index].id);
    } else {
        printf("Task %d was marked as pending.\n", tasks[task_index].id);
    }
}

void delete_task(Task tasks[], int *task_count)
{
    int id;
    int task_index;
    int i;

    if (*task_count == 0) {
        printf("\nThere are no tasks to delete.\n");
        return;
    }

    list_tasks(tasks, *task_count);

    if (!read_integer("\nEnter the task ID to delete: ", &id)) {
        printf("Invalid ID. Please enter a whole number.\n");
        return;
    }

    task_index = find_task_index_by_id(tasks, *task_count, id);

    if (task_index == -1) {
        printf("No task was found with ID %d.\n", id);
        return;
    }

    for (i = task_index; i < *task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*task_count)--;
    printf("Task %d was deleted successfully.\n", id);
}

void search_tasks(const Task tasks[], int task_count)
{
    char search_term[INPUT_BUFFER_SIZE];
    int matches;
    int i;

    if (task_count == 0) {
        printf("\nThere are no tasks to search.\n");
        return;
    }

    printf("\n=== Search Tasks ===\n");
    read_line(
        "Enter a title or description: ",
        search_term,
        sizeof(search_term)
    );

    if (strlen(search_term) == 0) {
        printf("The search term cannot be empty.\n");
        return;
    }

    matches = 0;

    for (i = 0; i < task_count; i++) {
        if (contains_ignore_case(tasks[i].title, search_term) ||
            contains_ignore_case(tasks[i].description, search_term)) {
            display_task(&tasks[i]);
            matches++;
        }
    }

    if (matches == 0) {
        printf("No matching tasks were found.\n");
    } else {
        printf(
            "\n%d matching task%s found.\n",
            matches,
            matches == 1 ? "" : "s"
        );
    }
}

static void display_task(const Task *task)
{
    printf("\nID: %d\n", task->id);
    printf("Title: %s\n", task->title);
    printf("Description: %s\n", task->description);
    printf("Priority: %s\n", task->priority);
    printf("Status: %s\n", task->completed ? "Completed" : "Pending");
}

static void read_line(
    const char *prompt,
    char *buffer,
    size_t buffer_size
)
{
    size_t length;
    int character;

    printf("%s", prompt);

    if (fgets(buffer, (int) buffer_size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        while ((character = getchar()) != '\n' && character != EOF) {
            /* Discard excess input. */
        }
    }
}

static int read_integer(const char *prompt, int *value)
{
    char input[INPUT_BUFFER_SIZE];
    char *end_pointer;
    long parsed_value;

    read_line(prompt, input, sizeof(input));

    if (input[0] == '\0') {
        return 0;
    }

    parsed_value = strtol(input, &end_pointer, 10);

    if (*end_pointer != '\0') {
        return 0;
    }

    *value = (int) parsed_value;
    return 1;
}

static int find_task_index_by_id(
    const Task tasks[],
    int task_count,
    int id
)
{
    int i;

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            return i;
        }
    }

    return -1;
}

static int contains_ignore_case(
    const char *text,
    const char *search_term
)
{
    size_t text_index;
    size_t search_index;

    if (search_term[0] == '\0') {
        return 1;
    }

    for (text_index = 0; text[text_index] != '\0'; text_index++) {
        search_index = 0;

        while (
            text[text_index + search_index] != '\0' &&
            search_term[search_index] != '\0' &&
            tolower((unsigned char) text[text_index + search_index]) ==
            tolower((unsigned char) search_term[search_index])
        ) {
            search_index++;
        }

        if (search_term[search_index] == '\0') {
            return 1;
        }
    }

    return 0;
}

static int is_valid_priority(const char *priority)
{
    return strcmp(priority, "LOW") == 0 ||
           strcmp(priority, "MEDIUM") == 0 ||
           strcmp(priority, "HIGH") == 0;
}

static void convert_to_uppercase(char *text)
{
    size_t i;

    for (i = 0; text[i] != '\0'; i++) {
        text[i] = (char) toupper((unsigned char) text[i]);
    }
}

static int get_next_task_id(const Task tasks[], int task_count)
{
    int highest_id;
    int i;

    highest_id = 0;

    for (i = 0; i < task_count; i++) {
        if (tasks[i].id > highest_id) {
            highest_id = tasks[i].id;
        }
    }

    return highest_id + 1;
}
