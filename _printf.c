#include "main.h"

void output_buffer(char buffer[], int *buff_indx);

/**
 * _printf - Printf function by Jenna and Kenile
 * @format: the string that contains the text to be written
 * Return: Printed items
*/
int _printf(const char *format, ...)
{
	int i, printed_item = 0, printed_char = 0;
	int flags, width, precision, size, buff_indx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_indx++] = format[i];
			if (buff_indx == BUFF_SIZE)
				output_buffer(buffer, &buff_indx);
			/* write(1, &format[i], 1);*/
			printed_char++;
		}
		else
		{
			output_buffer(buffer, &buff_indx);
			flags = _flags(format, &i);
			width = _width(format, &i, list);
			precision = _precision(format, &i, list);
			size = _size(format, &i);
			++i;
			printed_item = to_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed_item == -1)
				return (-1);
			printed_char = printed_char + printed_item;
		}

	}

	output_buffer(buffer, &buff_indx);

	va_end(list);

	return (printed_char);
}

/**
 * output_buffer - Prints the contents of the buffer
 * @buffer: An array of chars
 * @buff_indx: Index to add next char aka the length
*/
void output_buffer(char buffer[], int *buff_indx)
{
	if (*buff_indx > 0)
		write(1, &buffer[0], *buff_indx);

	*buff_indx = 0;
}
