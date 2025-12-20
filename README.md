# get_next_line

This project has been created as part
of the 42 curriculum by <okorkech>


## Description
**get_next_line** is a project at 42 School that requires us to create a function capable of reading a file descriptor one line at a time. The function must handle varying buffer sizes and ensure no memory leaks occur.

The goal is to learn about **static variables**, **file descriptor management**, **dynamic memory allocation** .

## Instructions

### Prototype
```c
char *get_next_line(int fd);
```

### Files Structure

**Mandatory:**
```c
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

**Bonus:**
```c
get_next_line_bonus.c
get_next_line_bonus_utils.c
get_next_line_bonus.h
```

### Usage Example
#### For mandatory part.
- **main.c**
```c
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}
```
#### For bonus part

- Run this commands first to create files with content.
```bash
echo -e "File 1 - Line 1\nFile 1 - Line 2" > test1.txt
echo -e "File 2 - Line 1\nFile 2 - Line 2" > test2.txt
echo -e "File 3 - Line 1\nFile 3 - Line 2" > test3.txt
```

- **main.c**
```c
#include "get_next_line_bonus.h" 

void print_line(char *line, int fd)
{
    if (line)
        printf("FD %d: %s", fd, line);
    else
        printf("FD %d: (null)\n", fd);
    free(line);
}

int main(void)
{
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    int fd3 = open("test3.txt", O_RDONLY);
    char *line;

    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        printf("Error opening files\n");
        return (1);
    }

    printf("--- Round 1: Reading Line 1 from everyone ---\n");
    print_line(get_next_line(fd1), fd1); // Should print "File 1 - Line 1"
    print_line(get_next_line(fd2), fd2); // Should print "File 2 - Line 1"
    print_line(get_next_line(fd3), fd3); // Should print "File 3 - Line 1"

    printf("\n--- Round 2: Reading Line 2 from everyone ---\n");
    print_line(get_next_line(fd1), fd1); // Should print "File 1 - Line 2"
    print_line(get_next_line(fd2), fd2); // Should print "File 2 - Line 2"
    print_line(get_next_line(fd3), fd3); // Should print "File 3 - Line 2"

    printf("\n--- Round 3: Reading EOF (should be null) ---\n");
    print_line(get_next_line(fd1), fd1);
    print_line(get_next_line(fd2), fd2);
    print_line(get_next_line(fd3), fd3);

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
```
### Compilation
- Place the example of the *main.c* file in the root of the directory and compile with the command bellow .
- For the bonus make sure you compile with the **_bonus.c* files .
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

---

## Algorithm

### Selected Approach: Read-Ahead Buffering with Static Persistence

#### Strategy

Read data in chunks of `BUFFER_SIZE` bytes, accumulate until `\n` is found, store excess in a **static variable** for the next call.

#### Flow

```
┌─────────────────────────────────┐
│   get_next_line(fd) called      │
└──────────────┬──────────────────┘
               ▼
┌─────────────────────────────────┐
│ Check static buffer for '\n'    │
└──────────────┬──────────────────┘
        ┌──────┴──────┐
    No '\n'       Has '\n'
        ▼             ▼
┌──────────────┐      │
│ Read chunk   │      │
│ BUFFER_SIZE  │      │
└──────┬───────┘      │
       ▼              │
┌──────────────┐      │
│ Append to    │      │
│ buffer       │      │
└──────┬───────┘      │
       └──────┬───────┘
              ▼
┌─────────────────────────────────┐
│ Extract line up to '\n'         │
└──────────────┬──────────────────┘
               ▼
┌─────────────────────────────────┐
│ Save remainder in static buffer │
└──────────────┬──────────────────┘
               ▼
┌─────────────────────────────────┐
│ Return extracted line            │
└─────────────────────────────────┘
```

#### Implementation Details

**Core Functions:**

- `get_next_line(fd)` - Entry point, validates fd and BUFFER_SIZE
- `get_line(fd, &pre_line)` - Reads and accumulates data until '\n' or EOF
- `process(pre_line)` - Extracts one line, saves remainder

**Key Variables:**

- `static char *line[FD_MAX]` - Persistent buffer array (bonus)
- `BUFFER_SIZE` - Defined at compile time
- `FD_MAX` - Maximum file descriptors (typically 1024)

#### Justification

**Why this algorithm?**

- **System Call Efficiency:** Reads chunks instead of byte-by-byte
- **Memory Usage:** Only stores necessary data between calls
- **Simplicity:** Clean separation of reading vs processing
- **Flexibility:** Works with any BUFFER_SIZE (1 to infinity)
- **Robustness:** Handles edge cases (empty files, no newlines, multiple FDs)


## Resources

### Documentation

- [read(2) man page](https://man7.org/linux/man-pages/man2/read.2.html) - System call reference
- [open(2) man page](https://man7.org/linux/man-pages/man2/open.2.html) - File descriptor operations
- [malloc(3) man page](https://man7.org/linux/man-pages/man3/malloc.3.html) - Memory allocation
- **Book:** Computer Systems: A Programmer's Perspective by David O'Hallaron and Randal Bryant
- **Youtube:**- https://www.youtube.com/watch?v=-Mt2FdJjVno&t=618s


### AI Usage

**AI was used for:**

- Code review 
- README structure and documentation writing
- Algorithm visualization
- Edge case discussion

**AI was NOT used for:**

- Writing the core implementation
- Solving the algorithm
- Debugging the actual code
