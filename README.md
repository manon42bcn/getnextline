```
  @@@@@                                                    @@&&&&@#             
   @@@@                                                    @@    @#             
   @@@@@                                                   @@    @#             
   \@@@@                                                   @@    @#             
    @@@@@                                                  @@    @#             
    \@@@@         @@@@@@@@@@@@@@@@@,  @@@@@@@@@@@@@@@@@    @@    @#             
     @@@@&       @@               @@  @@@@@@@@@@@@@@@@@@   @@    @#             
      @@@@       @@     @@@@@,    @@  @@@@@@@@@@@@@@@@@@@  @@    @#             
      @@@@(      @@    @,    @    @@  @@@@@@@     @@@@@@@  @@    @#             
      @@@@@      @@    @     @    @@  @@@@@@@     @@@@@@@  @@    @#             
       @@@@,     @@    @     @    @@  @@@@@@@     @@@@@@@  @@    @#             
       @@@@@     @@    @     @    @@  @@@@@@@     @@@@@@@  @@    @#             
        @@@@     @@    @     @    @@  @@@@@@@     @@@@@@@  @@    @#             
        @@@@@    @@    @#    @    @@  @@@@@@@     @@@@@@@  @@    @#             
         @@@@    @@     @@@@@     @@  @@@@@@@     @@@@@@@  @@     @@@          
         @@@@@    @@              @@  @@@@@@@     @@@@@@@   @@      @          
          @@@@     @@@@@@@@@@@    @@  @@@@@@@     @@@@@@@     @@@@@@@          
                             @    @@                                            
                 @@@@@@@@   @@    @@  -------------------------------          
                  @@    @@@@@     @@  -------------------------------            
                   @@           @@    -------------------------------                                          
                     @@@@@@@@@@@@     -------------------------------     

whoAmI(campus=42barcelona, login=mporras-, mail=manuel.porras.ojeda@gmail.com)
Feel free to write!
```

# get_next_line

`get_next_line` is a C library designed to read lines from a file descriptor one at a time. This library is particularly useful for reading files line by line, such as configuration files or any textual data stream.
Keep in mind this is our second (or third) project of the common core. This code doesn't pretend to be the most optimal or faster approach, just my best shot at that point!
Please, use this code as reference. Is well documented to give you all the details of the code. Don't copy without understand!

Some functions have the exact same name that libft library, but libft was not available in this project.
Grade: 125%


## Table of Contents

- [Features](#features)
- [Workflow](#workflow)
- [Usage](#usage)
    - [Function Prototype](#function-prototype)
    - [Return Values](#return-values)
- [Auxiliary Functions](#auxiliary-functions)
- [Examples](#examples)
- [Doxygen documentation](#doxygen-documentation)

## Features

- Reads from a file descriptor one line at a time. A line can be defined as a char \* that ends with a newline (\nl) or EOF.
- Handles multiple file descriptors simultaneously (BONUS VERSION)
- Efficient memory management to ensure optimal performance.

### KEEP IN MIND

#### About versions

The only difference between mandatory and bonus version is the use of:

```c
static char	*buffer[256];
```
instead of
```c
static char	*buffer;
```

A great idea is to check:
```
man getrlimit; man FD_SETSIZE;
```
#### About read-size

On many systems, size_t is a typedef for an unsigned 64-bit integer (on 64-bit architectures) or a 32-bit integer (on 32-bit architectures). This means that, theoretically, you can request to read up to SIZE_MAX bytes in a single read() operation, where SIZE_MAX is a constant that represents the maximum value storable in a size_t.

However, a few things to keep in mind:

Memory: Even if you try to read SIZE_MAX bytes, you need to ensure that you have that much memory allocated for the buffer you're reading into.

File Size: The file you're reading from must be large enough to have SIZE_MAX bytes left to read.

Practical Considerations: You rarely, if ever, want to read SIZE_MAX bytes at once in a practical scenario. In most real-world use-cases, you'd typically read data in manageable chunks, such as 4KB, 8KB, etc.

Filesystem Limitations: Some filesystems may have limitations on the maximum size of a single file.

System Limitations: While you can theoretically request a read of SIZE_MAX bytes, the system might not actually allow you to read that many bytes in a single call due to various system and kernel limits.

In short, while you can technically request to read a very large number of bytes in a single read() call (up to SIZE_MAX), it's crucial to consider various practical and system-imposed limitations. Always check the return value of read() to see how many bytes were actually read and handle any errors appropriately.

#### Recommendation

Most of the headaches in gnl project come from memory leaks. You must follow your malloc-free 'moments' quite carefully. Remember, a memory leaks is the lost of a reference, meaning, you lost the track of an allocated var.
For example:
```c
char *foo = allocated_char();
//pointer of foo 0x01
// do something
foo = ft_join_str(foo);
//pointer of foo 0x05 ... 0x01 is lost!
```
The second assignation (assuming that ft_join_str does not free the original pointer) will give you leaks.
You are responsible only for the leaks during the process (inner gnl process), you return an allocated char \* and free it is user responsibility.

## Workflow

1. The `get_next_line` function first checks the validity of the given file descriptor.
2. It then verifies if there's any pre-existing data in the buffer.
3. If the buffer contains a newline character, the line is processed using `ft_line_proccess`.
4. If the buffer does not contain a newline character, the file descriptor is read in chunks (of `BUFFER_SIZE`) into the buffer until a newline character is found or the end of the file is reached.
5. The buffer is continually adjusted and the line is returned to the user.


Here's an ASCII representation of the workflow for `get_next_line`:

```
                         +-------------------------+
                         | Start get_next_line(fd) |
                         +-------------------------+
                                    |
                                    v
                      +------------------------------+
                      | Validate the file descriptor |
                      +------------------------------+
                                    |
                                    v
                        +---------------------------+
                        | Check existing buffer for |
                        |     newline character     |
                        +---------------------------+
                                 /           \
                               /               \
                           YES                NO
                             |                 |
                             v                 |
    +--------------------------------+        |
    | Process line using             |        |
    | ft_line_proccess & return line |        |
    +--------------------------------+        |
                             |                 |
                             |                 v
                             |      +------------------------+
                             |      | Allocate memory for    |
                             |      |        reader          |
                             |      +------------------------+
                             |                 |
                             |                 v
                             |     +---------------------------+
                             |     | Read fd into buffer until |
                             |     | newline is found or EOF   |
                             |     +---------------------------+
                             |                 |
                             |                 |
                             v                 |
         +------------------------------------------+
         | Return the line & adjust buffer if needed|
         +------------------------------------------+
                                    |
                                    v
                                End Function
```

## Usage

### Function Prototype

```c
char *get_next_line(int fd);
```

### Return Values

- Returns the line that has been read including the newline.
- Returns `NULL` when the end of the file is reached or if there's an error.

## Auxiliary Functions

- `ft_strlen`: Calculates the length of a string.
- `ft_substr`: Extracts a substring from a given string.
- `ft_strdup`: Duplicates a string up to a certain length.
- `ft_strjoin`: Concatenates two strings into a new string.
- `ft_memcpy`: Copies a certain amount of bytes from a source to a destination.

Refer to the source code for the detailed function signatures and their respective Doxygen-style comments for deeper insights.

## Examples

Here's a basic example demonstrating the usage:

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("sample.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
## Doxygen documentation

To generate detailed, and more friendly documentation for this project, follow the steps outlined below:

### Install Doxygen:

If you haven't already installed Doxygen, you can do so using your system's package manager.

* Debian/Ubuntu-based systems:

```bash
sudo apt-get install doxygen
```

* On macOS:

```bash
brew install doxygen
```

### Generate the Documentation:

From the root directory of the project, where the `Doxyfile` is located, run:

```bash
doxygen Doxyfile
```

### View the Documentation:

Once Doxygen completes the documentation generation, you can view it by opening the `html/index.html` file in your preferred web browser:

```bash
open docs/html/index.html   # On macOS
xdg-open docs/html/index.html   # On Linux systems
```