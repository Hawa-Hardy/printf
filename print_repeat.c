#include <stdarg.h>
#include <stdio.h>
#include "main.h"

/**
 * print_repeat - Prints a character x times
 * @c: The character
 * @n: Number of times character is to be printed
 */
void print_repeat(char c, int n)
{
	int i;

	for (i = 0; i < n; i++)
		_putchar(c);
}

/**
 * _putnchars - function prints multiple chars
 * @n: The number of characters to be printed
 */
void _putnchars(int n, ...)
{
	int i;
	va_list args;

	if (n <= 0)
		return;
	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		_putchar(va_arg(args, int));
	}
	va_end(args);
}

/**
 * is_letter - Checks if character is a letter
 * @c: The char to check
 *
 * Return: 0 or 1
 */
char is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? TRUE : FALSE);
}

/**
 * set_format_error - Sets the error after reading a format specifier
 * @format: The format string
 * @pos: Position in the format string
 * @len: Format specifier length
 * @last_token: The last token from the format specifier
 * @error: The error flag
 */
void set_format_error(const char *format, int *pos, int len,
	int last_token, int *error)
{
	char next_char = format[*pos + len + 1];
	int i;

	if (last_token == 1 && next_char == '\0')
	{
		*error = -1;
	}
	else if ((last_token == 2 || last_token == 3) && next_char == '\0')
	{
		*error = -1;
		(*pos) += len - 1;
	}
	else if (last_token == 4 && next_char == '\0')
	{
		*error = -1;
	}
	else
	{
		*error = 1;
	}
	if (next_char != '\0' && last_token != 5)
	{
		_putchar('%');
		for (i = 0; i <= len; i++)
		{
			if (!is_length(format[*pos + i]))
				_putchar(format[*pos + i]);
		}
		(*pos) += len;
	}
}

/**
 * put_num - Puts a number to the buffer
 * @zeros_count: Counts number of zeros to print
 * @num: The number
 * @str: Number as a string
 */
void put_num(int zeros_count, long num, char *str)
{
	int i;

	for (i = 0; i < zeros_count; i++)
		_putchar('0');
	for (i = num < 0 ? 1 : 0; *(str + i) != '\0'; i++)
		_putchar(*(str + i));
}
