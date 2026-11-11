*This project has been created as part of the 42 curriculum by mbelarab.*

# ft_printf

## Description

`ft_printf` is a C library that reproduces the mandatory conversions of `printf`, writing directly to standard output without implementing the original function's buffer management. The objective is to learn variadic argument handling, number conversion, and reliable output counting.

A variadic function accepts a variable number of arguments. Here, the format string determines how the arguments following it are interpreted.

```c
int ft_printf(const char *format, ...);
```

| Conversion | Output |
| --- | --- |
| `%c` | Single character |
| `%s` | Null-terminated string |
| `%p` | Pointer address in lowercase hexadecimal with `0x` prefix |
| `%d`, `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x`, `%X` | Unsigned hexadecimal integer, lowercase or uppercase |
| `%%` | Literal percent sign |

A null string prints `(null)`; a null pointer prints `(nil)`. The implementation covers the mandatory conversions only; flags, field widths, and precision are not implemented. It expects a non-null format string with valid, complete conversion specifications.

## Instructions

From the repository root, build `libftprintf.a` using `cc`, `make`, and `ar`:

```sh
make
```

Include `ft_printf.h` in your program, then link and run:

```sh
cc -Wall -Wextra -Werror -I. main.c libftprintf.a -o example
./example
```

Available rules: `all` (default) or `libftprintf.a` builds the library; `clean` removes object files; `fclean` also removes the library; `re` performs a full rebuild.

## Algorithm and Data Structure Explanation

### Format scanning and argument handling

`ft_printf` scans the null-terminated format string using an integer index. `ft_process` writes an ordinary character with `write(1, ..., 1)` and advances the index by one. At `%`, it passes the next character to `ft_conversion` and advances by two.

`va_list` represents the state needed to access the variable arguments. `va_start(args, format)` initializes it, and the list is passed through `ft_process` to `ft_conversion`. The dispatcher uses an `if`/`else if` chain and `va_arg` to retrieve the next argument with the required type: `int` for `%c`, `%d`, and `%i`; `unsigned int` for `%u`, `%x`, and `%X`; `char *` for `%s`; and `void *` for `%p`. `%c` retrieves an `int` because variadic character arguments undergo integer promotion. `%%` consumes no argument. `va_end` is called before both normal completion and an output-error return. No `va_copy` is used.

### Recursive number conversion

`ft_putnbr` copies its signed integer into a `long`, prints a minus sign when necessary, and makes the value positive. On the target Linux platform, the wider `long` allows the minimum `int` value to be negated safely. It recursively prints the quotient by 10 before printing the remainder, producing digits from left to right without a temporary digit buffer.

`ft_putnbr_base` shares the unsigned conversion logic between decimal and hexadecimal. A local `ft_strlen` determines the digit alphabet's length. The function recursively prints the quotient by that length, then selects the final digit using the remainder. The dispatcher supplies `0123456789`, `0123456789abcdef`, or `0123456789ABCDEF`. Zero reaches the final digit write directly and prints `0`.

`ft_putadrs` handles null pointers separately. Otherwise, it prints `0x`, casts the pointer to `unsigned long`, and calls the local recursive `ft_puthex` to emit lowercase hexadecimal digits. This representation assumes `unsigned long` can hold a pointer on the target platform.

### Output counting and organization

`ft_putchar` returns the result of a one-byte `write`. `ft_putstr` walks the string and calls it for each character. Numeric and pointer helpers add the counts returned by their recursive calls, prefixes, signs, and digits. `ft_printf` accumulates each processed element's count and returns the total number of bytes written.

Each output operation is checked for `-1`. A failure propagates through the helpers to `ft_printf`, which calls `va_end` and returns `-1`; bytes already written remain in the output.

The implementation uses the existing format and argument strings, fixed digit alphabets, scalar counters, a `va_list`, and recursive calls. It allocates no heap memory and builds no intermediate output buffer. Scanning is linear in the format length, string printing is linear in the string length, and number printing uses one recursive level per digit. These choices keep the conversion logic small and direct.

Separating scanning, dispatch, and output helpers keeps each function focused and supports Norminette's function-size constraints. Local implementation helpers (`ft_conversion`, `ft_process`, `ft_strlen`, and `ft_puthex`) are declared `static` to keep them private to their source files.

## Resources

- Official **ft_printf subject, version 12.1**.
- Unix/Linux manual pages: `man 3 printf`, `man 3 stdarg`, and `man 2 write`.
- Stack Overflow for technical questions and explanations.
- Google searches and general research for additional clarification.

### AI Usage

I used AI as a learning and conceptual explanation tool to better understand variadic functions and the behavior of `va_list`, `va_start`, `va_arg`, and `va_end`. I also used it to clarify specific technical questions, particularly why certain implementations work and others do not.
