/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:20:43 by karlarod          #+#    #+#             */
/*   Updated: 2025/03/14 15:57:10 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	f_new_format(t_fmt_spcfy *format)
{
	int		i;

	i = 0;
	format->args_to_str = NULL;
	format->width = 0;
	format->prcn = 0;
	format->hxa = 'A';
	while (i < 4)
		format->flags[i++] = 'A';
	format->flags[4] = '\0';
}

static void	f_parse(char **str, va_list *args, int *count)
{
	int			size_buff;
	t_fmt_spcfy	format;

	size_buff = 0;
	while (*str[1])
	{
		while (*str[1] != '%' && *str[1] != '\0' )
		{
			++size_buff;
			++str[1];
		}
		if (*str[1] == '%')
		{
			if (size_buff != 0)
				*count += write(1, (str[1] - size_buff), size_buff);
			str[0] = str[1];
			++str[1];
			f_new_format(&format);
			f_flag(str, args, &format, count);
			size_buff = 0;
		}
		else
			*count += write(1, (str[1] - size_buff), size_buff);
	}
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;
	char	**ptr_str;

	count = 0;
	if (str == NULL)
		return (0);
	ptr_str = malloc(2 * sizeof(char *));
	ptr_str[0] = NULL;
	ptr_str[1] = (char *)str;
	va_start(args, str);
	f_parse(ptr_str, &args, &count);
	va_end(args);
	free(ptr_str);
	return (count);
}
