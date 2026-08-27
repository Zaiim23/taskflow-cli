# TaskFlow CLI

TaskFlow CLI is a simple command-line task manager written in C. It allows users to create, view, search, update, and delete tasks while storing the data in a local text file.

The project was created to practise core C programming concepts such as structs, arrays, pointers, file handling, input validation, and modular program design.

## Features

- View all saved tasks
- Add new tasks with a title, description, and priority
- Change a task between pending and completed
- Delete tasks by ID
- Search tasks by title or description
- Case-insensitive search
- Save tasks to a local text file
- Load saved tasks when the program starts
- Validate menu choices, task IDs, and priorities

## Project Structure

```text
taskflow/
├── data/
│   └── tasks.txt
├── include/
│   ├── storage.h
│   └── task.h
├── src/
│   ├── main.c
│   ├── storage.c
│   └── task.c
├── .gitattributes
├── .gitignore
├── Makefile
└── README.md
```

### Source files

- `src/main.c` contains the main program loop and menu.
- `src/task.c` contains the task management functions.
- `src/storage.c` handles loading and saving tasks.

### Header files

- `include/task.h` defines the `Task` structure and task functions.
- `include/storage.h` declares the file storage functions.

### Data file

- `data/tasks.txt` stores tasks between program sessions.

## Task Format

Each task contains:

- A unique ID
- A title
- A description
- A priority
- A completion status

The available priority levels are:

```text
LOW
MEDIUM
HIGH
```

Tasks are stored in `data/tasks.txt` using the following format:

```text
ID|Title|Description|Priority|Completed
```

Example:

```text
1|Finish C assignment|Review the remaining exercises|HIGH|0
```

The completion value is stored as:

- `0` for pending
- `1` for completed

## Requirements

To build the project, you need:

- A C compiler with C11 support
- GCC or another compatible compiler
- A terminal such as PowerShell, MSYS2, or a Unix-compatible shell

## Build Instructions

Open a terminal in the project directory and compile the program with GCC:

```bash
gcc -Wall -Wextra -pedantic -std=c11 src/main.c src/task.c src/storage.c -Iinclude -o taskflow.exe
```

The warning options are used to help identify possible problems during compilation.

## Running the Program

### Windows PowerShell

```powershell
.\taskflow.exe
```

### MSYS2 or another Unix-compatible shell

```bash
./taskflow.exe
```

## Menu

When the program starts, the following menu is displayed:

```text
=== TaskFlow CLI ===
1. View all tasks
2. Add a task
3. Change task status
4. Delete a task
5. Search tasks
0. Save and exit
```

Changes are saved to `data/tasks.txt` when the program is closed using option `0`.

## Search

The search function checks both task titles and descriptions.

Searches are case-insensitive, which means the following search terms are treated equally:

```text
github
GitHub
GITHUB
```

## Status Changes

The status function works as a toggle:

```text
Pending -> Completed
Completed -> Pending
```

This allows a completed task to be reopened if its status was changed by mistake.

## Input Limitations

The `|` character should not be used inside task titles or descriptions because it is used as the field separator in the data file.

The current version supports up to 100 tasks.

## What I Learned

Through this project, I practised:

- Organising a C project across multiple source and header files
- Creating and using structs
- Passing arrays and pointers to functions
- Reading from and writing to text files
- Validating user input
- Searching strings without case sensitivity
- Separating program logic into smaller functions
- Compiling a multi-file C project with GCC

## Possible Future Improvements

Possible improvements for future versions include:

- Editing existing tasks
- Adding due dates
- Sorting tasks by priority
- Filtering tasks by status
- Saving changes immediately after each operation
- Adding automated tests
- Supporting a configurable data file

## Author

Zaiim Islam