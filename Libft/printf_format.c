/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:00:22 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/10 17:18:25 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	f_type(char	**str, va_list *args, t_fmt_spcfy *format, int *count)
{
	if (*str[1] != '\0')
	{
		if (*str[1] == 'c')
			ft_putchar(va_arg(*args, int), format, count);
		else if (*str[1] == '%')
			*count += write(1, "%", 1);
		else if (*str[1] == 's')
			ft_ptstr(va_arg(*args, char *), format, count);
		else if (*str[1] == 'd' || *str[1] == 'i')
			fft_itoa(va_arg(*args, int), format, count);
		else if (*str[1] == 'u')
			ft_utoa(va_arg(*args, unsigned int), format, count);
		else if (*str[1] == 'x' || *str[1] == 'X')
			f_hex(va_arg(*args, unsigned int), *str[1], format, count);
		else if (*str[1] == 'p')
			f_hex(va_arg(*args, unsigned long), *str[1], format, count);
		++str[1];
	}
	else
		*count = -1;
}

static void	f_point(char **str, va_list *args, t_fmt_spcfy *format, int *count)
{
	if (*str[1] == '.')
	{
		format->flags[3] = '.';
		++str[1];
		if (format->flags[1] == '0')
			format->flags[1] = 'A';
		if (*str[1] == '-')
		{
			*count += write(1, str[0], str[1] - str[0]);
			*count += write(1, "0", 1);
			return ;
		}
		if (*str[1] == '*')
		{
			format->prcn = (va_arg(*args, int));
			++str[1];
		}
		while (*str[1] >= '0' && *str[1] <= '9')
		{
			format->prcn = ((format->prcn) * 10 + *str[1] - '0');
			++str[1];
		}
	}
	f_type(str, args, format, count);
}

static void	f_wdth(char **str, va_list *args, t_fmt_spcfy *format, int *count)
{
	if (*str[1] == '\0')
		*count = -1;
	else if (*str[1] == '*')
	{
		format->width = (va_arg(*args, int));
		if (format->width < 0)
		{
			format->width = -1 * format->width;
			format->flags[1] = '-';
		}
		++str[1];
	}
	else
	{
		while (*str[1] >= '0' && *str[1] <= '9')
		{
			format->width = (format->width) * 10 + *str[1] - '0';
			++str[1];
		}
	}
	f_point(str, args, format, count);
}

void	f_flag(char **str, va_list *args, t_fmt_spcfy *format, int *count)
{
	if (*str[1] == '\0')
		*count = -1;
	while (*str[1] == '-' || *str[1] == '+' || *str[1] == '0'
		|| *str[1] == '#' || *str[1] == ' ')
	{
		if (*str[1] == '+')
			format->flags[0] = '+';
		else if (*str[1] == ' ' && format->flags[0] == 'A')
			format->flags[0] = ' ';
		else if (*str[1] == '-')
			format->flags[1] = '-';
		else if (*str[1] == '0' && format->flags[1] == 'A')
			format->flags[1] = '0';
		else if (*str[1] == '#')
			format->flags[2] = '#';
		++str[1];
	}
	f_wdth(str, args, format, count);
}
