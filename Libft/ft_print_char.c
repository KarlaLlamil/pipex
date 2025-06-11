/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:23:41 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/10 17:12:54 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, t_fmt_spcfy *format, int *count)
{
	char	ch;

	ch = (unsigned char)c;
	if (format->width > 1)
	{
		format->args_to_str = (char *)f_new_str((format->width) + 1, ' ');
		if (format->args_to_str != NULL)
		{
			if (format->flags[1] != '-' )
				format->args_to_str[format->width - 1] = ch;
			else if (format->flags[1] == '-')
				format->args_to_str[0] = ch;
		}
		*count += write(1, format->args_to_str, format->width);
		free(format->args_to_str);
	}
	else
		*count += write(1, &c, 1);
}

static void	f_fill_str(char *str, t_fmt_spcfy *format, int len)
{
	int		i;

	if (format->flags[1] != '-')
	{
		i = format->width - len;
		while (i < format->width)
		{
			format->args_to_str[i] = *str;
			++str;
			++i;
		}
	}
	else if (format->flags[1] == '-')
	{
		i = 0;
		while (i < len)
		{
			format->args_to_str[i] = *str;
			++str;
			++i;
		}
	}
}

void	ft_ptstr(char *str, t_fmt_spcfy *format, int *count)
{
	int			len;
	const char	*null_ = "(null)";

	len = 0;
	if (format->hxa == 'p')
		format->prcn = 5;
	else if (str == NULL)
		str = (char *)null_;
	if (str == null_ && (format->flags[3] == '.' && format->prcn < 6))
		str = (char *)"";
	len = fft_strlen(str);
	if (format->flags[3] == '.' && format->prcn >= 0 && format->prcn < len)
		len = format->prcn;
	if (format->width > len)
	{
		format->args_to_str = (char *)f_new_str((format->width) + 1, ' ');
		if (format->args_to_str != NULL)
			f_fill_str(str, format, len);
		*count += write(1, format->args_to_str, format->width);
		free(format->args_to_str);
	}
	else
		*count += write(1, str, len);
}
