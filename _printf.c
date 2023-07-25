#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - prints output
 * @format: specified format
 *
 * Return: number of characters function printed
 */
int _printf(const char *format, ...)
{
	int i = 0, tmp, processing_escape = FALSE, error = 1, last_token;
	fmt_info_t fmt_info;
	va_list args;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(args, format);
	write_to_buffer(0, -1);
	for (i = 0; format && *(format + i) != '\0'; i++)
	{
		if (processing_escape)
		{
			tmp = read_format_info(format + i, args, &fmt_info, &last_token);
			processing_escape = FALSE;
			set_format_error(format, &i, tmp, last_token, &error);
			if (is_specifier(fmt_info.spec))
				write_format(&args, &fmt_info);
			i += (is_specifier(fmt_info.spec) ? tmp : 0);
		}
		else
		{
			if (*(format + i) == '%')
				processing_escape = TRUE;
			else
				_putchar(*(format + i));
		}
	}
	write_to_buffer(0, 1);
	va_end(args);
	return (error <= 0 ? error : write_to_buffer('\0', -2));
}

/**
 * write_format - Writes data that is formatted
 * @args_list: arguments
 * @fmt_info: Format info parameters
 */
void write_format(va_list *args_list, fmt_info_t *fmt_info)
{
	int i;
	spec_printer_t spec_printers[] = {
		{'%', convert_fmt_percent},
		{'p', convert_fmt_p},
		{'c', convert_fmt_c},
		{'s', convert_fmt_s},
		{'d', convert_fmt_di},
		{'i', convert_fmt_di},
		{'X', convert_fmt_xX},
		{'x', convert_fmt_xX},
		{'o', convert_fmt_o},
		{'u', convert_fmt_u},
		/* #begin custom specifiers */
		{'b', convert_fmt_b},
		{'R', convert_fmt_R},
		{'r', convert_fmt_r},
		{'S', convert_fmt_S},
		/* #end */
		{'F', convert_fmt_fF},
		{'f', convert_fmt_fF},
	};

	for (i = 0; i < 23 && spec_printers[i].spec != '\0'; i++)
	{
		if (fmt_info->spec == spec_printers[i].spec)
		{
			spec_printers[i].print_arg(args_list, fmt_info);
			break;
		}
	}
}

/**
 * _putstr - writes a string to a buffer
 * @str: The string to be written
 *
 * Return: Success 1.
 * -1 (error) is returned, and errno is appropriately set
 */
int _putstr(char *str)
{
	int i, out;

	for (i = 0; str && *(str + i) != 0; i++)
		out = _putchar(*(str + i));
	return (out);
}

/**
 * _putchar - writes the char c to the buffer
 * @c: The char to be printed
 *
 * Return: On success 1
 * Error -1 is returned, and errno is appropriately set
 */
int _putchar(char c)
{
	return (write_to_buffer(c, 0));
}

/**
 * write_to_buffer - Writes a char to the buffer
 * @c: The char to be written
 * @action: Action to be performed (
 * -1-> reset all static variables
 * 0-> write character to the buffer
 * 1-> don't write char to the buffer
 * and empty buffer into stdout
 * -2-> the number of characters written to stdout)
 *
 * Return: 1 (Success)
 * On error, -1 is returned, and errno is appropriately set
 */
int write_to_buffer(char c, char action)
{
	static int i;
	static int chars_count;
	static char buffer[1024];
	static char out;

	if (i < 1024 && action == 0)
	{
		out = chars_count < 1 ? 1 : out;
		buffer[i] = c;
		i++;
		chars_count++;
	}
	if (i >= 1024 || action == 1)
	{
		out = write(1, buffer, i);
		fflush(stdout);
		i = 0;
		mem_set(buffer, 1024, 0);
	}
	if (action == -1)
	{
		i = 0;
		chars_count = 0;
		mem_set(buffer, 1024, 0);
	}
	if (action == -2)
	{
		return (chars_count);
	}
	return (out);
}
