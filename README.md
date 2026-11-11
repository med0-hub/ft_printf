*This project has been created as part of the 42 curriculum by mbelarab.*

# ft_printf

**A small formatting library, one byte at a time.**

![C](https://img.shields.io/badge/language-C-00599C)
![1337 / 42](https://img.shields.io/badge/school-1337%20%2F%2042-222222)

## Description

A recreation of the mandatory `printf` conversions from the 42/1337 subject, version 12.1. It builds `libftprintf.a`, a static library: compiled functions that can be linked into another program.

```c
int ft_printf(const char *format, ...);
```

- Writes to standard output using `write(1, ..., 1)`.
- Returns the number of bytes written, or `-1` on a write failure.
- Uses recursion for numbers; no heap allocation or Libft dependency.
- Implements the mandatory part only: no flags, width, or precision.

## Supported conversions

| Format | Argument type | Purpose | Example output |
| --- | --- | --- | --- |
| `%c` | `int` | One character | `A` |
| `%s` | `char *` | String | `hello` |
| `%p` | `void *` | Pointer address | `0x...` |
| `%d`, `%i` | `int` | Signed decimal | `-42` |
| `%u` | `unsigned int` | Unsigned decimal | `42` |
| `%x` | `unsigned int` | Lowercase hexadecimal | `ff` |
| `%X` | `unsigned int` | Uppercase hexadecimal | `FF` |
| `%%` | None | Literal percent | `%` |

**Special cases:** null `%s` prints `(null)`; null `%p` prints `(nil)`. An empty string prints nothing. `%c` with value zero writes one invisible zero byte and counts it.

## Project files

```text
ft_printf/
|-- Makefile           Build and clean libftprintf.a
|-- ft_printf.h        Shared declarations
|-- ft_printf.c        Main loop, parser, dispatcher
|-- ft_putchar.c       Write one byte
|-- ft_putstr.c        Print strings
|-- ft_putnbr.c        Print signed decimal numbers
|-- ft_putnbr_base.c   Print unsigned decimal and hex
`-- ft_putadrs.c       Print pointer addresses
```

## How it works

The parser advances one position for ordinary text and two for a conversion such as `%d`.

```text
                    ft_printf
                        |
                    ft_process
                        |
             +----------+-----------+
             |                      |
         ordinary byte          % + specifier
             |                      |
       write(1, ..., 1)         ft_conversion
             |                      |
             |                printing helper
             |                      |
             +----------+-----------+
                        |
                 count or error
```

The dispatcher selects the helper and retrieves one argument for each supported conversion. `%%` consumes no argument.

### Variadic arguments

A **variadic function** accepts a variable number of arguments through `...`.

| Tool | Role |
| --- | --- |
| `va_list` | Holds argument-traversal state |
| `va_start` | Initializes traversal |
| `va_arg` | Retrieves the next argument and advances |
| `va_end` | Finishes traversal |

```c
ft_printf("%d %s", 42, "hi");
```

```text
Conversion       Retrieved value
   %d       ---> 42       (int)
   %s       ---> address  (char *)
```

The format determines the expected types. Wrong types or missing arguments generally cause undefined behavior: C provides no guaranteed result.

`%c` retrieves `int` because ordinary character arguments undergo **promotion**, an automatic conversion to a wider integer type. `va_list` hides the platform's argument layout; it is not necessarily a pointer walking the stack.

### Numbers: divide, recurse, print

**Recursion** means calling the same function with a smaller problem.

```text
Printing 123 in decimal:

Call:      123 / 10 = 12
            12 / 10 = 1
             1       = stop recursing

Return:     '1'   then   '2'   then   '3'
Output:                     123
```

- Division finds the earlier digits; remainder finds the final digit.
- `ft_putnbr` prints a minus sign for negative values.
- It converts `int` to `long` before negation, handling `INT_MIN` when `long` has a wider range.
- `ft_putnbr_base` uses a digit table: decimal or lowercase/uppercase hexadecimal.

For hexadecimal, `255 / 16 = 15` and `255 % 16 = 15`. Both digits select index `15`, producing `ff` or `FF`.

This approach prints digits in order without a temporary digit buffer. Each recursive call returns its own byte count.

### Strings and pointers

A **pointer** holds an address. `%s` reads characters at that address; `%p` prints the address itself.

```text
String pointer
      |
      v
   +-----+-----+------+
   | 'h' | 'i' | '\0' |
   +-----+-----+------+
      write      stop
      h, i
```

`ft_putstr` advances byte by byte until `\0`, the zero terminator. It prints neither the terminator nor a copy of the pointer.

`ft_putadrs` prints `0x`, then calls its internal `ft_puthex` with an `unsigned long` address value. A separate helper avoids narrowing addresses to `unsigned int` on the tested 64-bit platform.

### Counts and errors

```text
Helper result       Caller action
-------------       --------------------------
  0 or more         Add to the byte count
     -1             Return -1 immediately
```

Errors travel back through the helper calls. `ft_printf` calls `va_end` and stops. Already written bytes remain visible; a failure cannot undo earlier output.

## Instructions

Build with `cc`, `make`, and `ar` in a POSIX environment such as Linux:

```sh
make          # Build libftprintf.a
make clean    # Remove object files
make fclean   # Remove objects and library
make re       # Rebuild
```

The Makefile uses `-Wall -Wextra -Werror` and archives the compiled objects with `ar rcs`. An unchanged second `make` does no extra work.

Create `main.c` beside the header:

```c
#include "ft_printf.h"

int	main(void)
{
	if (ft_printf("Hello, %s! %d %X %%\n", "1337", 42, 255u) == -1)
		return (1);
	return (0);
}
```

Compile and run:

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o demo
./demo
```

```text
Hello, 1337! 42 FF %
```

Use unsigned arguments such as `255u` for `%u`, `%x`, and `%X`; use `(void *)&object` for `%p`.

## Checks and known limits

**Verified during documentation preparation:** 191 focused checks passed on x86-64 Linux with GCC 14.2.0 and glibc 2.41. They covered output bytes, return counts, integer boundaries, mixed arguments, and write failures. The temporary harness is not included; this is not an official evaluation result.

- **Trailing `%`:** a separate memory-checking run confirmed a read beyond the format string.
- **Unknown conversions:** the parser skips the pair; `A%qB` becomes `AB`.
- **Portability:** sharing `va_list` through the current helper signatures is platform-dependent. Integer and pointer handling also rely on suitable `long` ranges.
- **Input and size limits:** null format strings and invalid string pointers are unguarded; counters have no overflow checks.
- **Write behavior:** one request per byte; failures are not retried. Norminette was not run during this review.

## Resources

- Official 42/1337 **ft_printf subject, version 12.1**.
- [`printf(3)`](https://man7.org/linux/man-pages/man3/printf.3.html): formatting and return values.
- [`stdarg(3)`](https://man7.org/linux/man-pages/man3/stdarg.3.html): variadic arguments.
- [`write(2)`](https://man7.org/linux/man-pages/man2/write.2.html): output and errors.

**AI usage:** AI helped explain variadic functions and specific C concepts. It also assisted with this README and its verification checks; the C implementation was supplied by the author.
