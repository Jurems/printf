#include "main.h"
/**
 * to_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed
 * @ind: ind
 * @buffer: Buffer array to handle print
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int to_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_char = -1;
	fmt_t fmt_types[] = {
		{'c', prnt_char}, {'s', prnt_string}, {'%', prnt_percent},
		{'i', prnt_int}, {'d', prnt_int}, {'b', prnt_binary},
		{'u', prnt_unsigned}, {'o', prnt_octal}, {'x', prnt_hexadecimal},
		{'X', prnt_hexa_upper}, {'p', prnt_pointer}, {'S', prnt_non_printable},
		{'r', prnt_reverse}, {'R', prnt_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_char);
}
