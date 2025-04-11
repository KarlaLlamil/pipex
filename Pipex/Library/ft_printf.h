/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:46:13 by karlarod          #+#    #+#             */
/*   Updated: 2025/04/10 17:17:06 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_specifier
{
	char	flags[5];
	int		width;
	int		prcn;
	char	*args_to_str;
	char	hxa;
}				t_fmt_spcfy;

void	fft_itoa(int n, t_fmt_spcfy *format, int *count);
void	*f_new_str(size_t buff, char c);
void	f_hex(unsigned long nmb, char c, t_fmt_spcfy *format, int *count);
int		fft_strlen(const char *str);
void	ft_putchar(int c, t_fmt_spcfy *format, int *count);
void	ft_ptstr(char *str, t_fmt_spcfy *format, int *counter);
void	ft_utoa(unsigned int n, t_fmt_spcfy *format, int *counter);
int		ft_printf(const char *str, ...);
int		ft_int_len(long n);
int		ft_int_len(long n);
int		ft_hex_len(unsigned long n);
void	f_flag(char **str, va_list *args, t_fmt_spcfy *format, int *count);

#endif
