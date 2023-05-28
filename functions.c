#include "main.h"

/************************* PRINT CHAR (c) *************************/

/**
 * prnt_char - Prints a char
 * @types: List of arguments
 * @buffer: array to handle print
 * @flags:  active flags
 * @width: Width of output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prnt_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING (s) *************************/
/**
 * prnt_string - Prints a string
 * @types: List of arguments
 * @buffer: array to handle print
 * @flags: active flags
 * @width: width of output
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prnt_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int lent = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[lent] != '\0')
		lent++;
	if (precision >= 0 && precision < lent)
		lent = precision;
	if (width > lent)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lent);
			for (i = width - lent; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - lent; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], lent);
			return (width);
		}
	}
	return (write(1, str, lent));
}
/************************* PRINT PERCENT SIGN (%) *************************/
/**
 * prnt_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: array to handle print
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prnt_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT (d) *************************/
/**
 * prnt_int - Print integer
 * @types: List of arguments
 * @buffer: array to handle print
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prnt_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_neg = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num = num / 10;
	}

	i++;

	return (write_number(is_neg, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * prnt_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: array to handle print
 * @flags: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int prnt_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum = sum + a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

