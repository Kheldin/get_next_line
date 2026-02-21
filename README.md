# get_next_line

> A C function that reads one line at a time from any file descriptor. Built without the standard library, using only a static variable to maintain state between calls.

---

## Overview

`get_next_line` implements a line-by-line reader for file descriptors in C. Each successive call returns the next line from the given fd, including the terminating `\n` character (except at end of file). It works on regular files, standard input, or any valid file descriptor.

The function is designed to be minimal and efficient: it reads only as much data as necessary on each call, never loading the entire file into memory.

---

## Key Constraints & Design Highlights

- **No standard library** — only `read`, `malloc`, and `free` are used
- **No global variables** — state is maintained through a single `static` variable
- **No `lseek()`** — fully sequential, forward-only reading
- **Configurable buffer size** — set at compile time via `-D BUFFER_SIZE=n`, works correctly with any value from `1` to `10000000`+
- **Bonus: multiple fd support** — simultaneous reading from several file descriptors without losing state on any of them

---

## Prototype

```c
char *get_next_line(int fd);
```

Returns the next line read from `fd`, or `NULL` if there is nothing left to read or an error occurred.

---

## Compilation

```bash
# With a custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# With default buffer size (defined in the header)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c

# Bonus — multiple fd support
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

---

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## Project Structure

```
get_next_line/
├── get_next_line.h             # Header — prototype + BUFFER_SIZE fallback
├── get_next_line.c             # Core function
├── get_next_line_utils.c       # Helper functions (strjoin, strchr, strlen...)
├── get_next_line_bonus.h       # Bonus header
├── get_next_line_bonus.c       # Bonus — multiple fd support
├── get_next_line_utils_bonus.c # Bonus helpers
└── README.md
```

---

## Algorithm & Design Choices

The implementation relies on a **static buffer (leftover)** to persist unprocessed data between calls. Here is how a single call unfolds:

1. **Check the leftover** : if a `\n` is already present in the data saved from the previous call, extract and return the line immediately without calling `read()` again.

2. **Read in chunks** : `read()` fills a temporary buffer of `BUFFER_SIZE` bytes. Each chunk is appended to the leftover via a custom `strjoin`. This continues until a `\n` is found or EOF is reached.

3. **Extract the line** : once a newline is found (or EOF), the portion up to and including `\n` is returned as the line. The remainder is saved back into the static variable for the next call.

4. **Cleanup on EOF** : when `read()` returns 0, any remaining content in the leftover is returned as the final line (without `\n`), then the static is freed and set to NULL.

This approach avoids reading the whole file upfront and works correctly regardless of `BUFFER_SIZE`, even with pathological values like `1` or `10000000`.

**Bonus — multiple file descriptors:** instead of a single `char *` static, the bonus uses a `char *` array indexed by fd (`static char *leftover[OPEN_MAX]`). Each fd gets its own independent leftover buffer, allowing interleaved reads across multiple descriptors without interference.

---

## Makefile Rules

| Rule | Description |
|------|-------------|
| `make` / `make all` | Compile mandatory part |
| `make bonus` | Compile bonus (multiple fd support) |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full rebuild |

---

## Resources

- [read(2) — Linux man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)

---

*This project was created as part of the 42 curriculum.*
