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

### Compilation
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
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

### Bonus: Multiple File Descriptors

```c
static char *line[FD_MAX];  // Handles multiple FDs simultaneously
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
- **Book:** *Computer Systems: A Programmer's Perspective by David O'Hallaron and Randal Bryant
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
