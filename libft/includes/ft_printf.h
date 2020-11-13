/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:21:43 by dfigg             #+#    #+#             */
/*   Updated: 2020/05/12 08:21:50 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FT_PRINTF_H
# define FT_PRINTF_FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>

# define B_SIZE 32

# define END "\x1b[0m"
# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

typedef struct	s_prn
{
	va_list		ap;
	int			fl_minus;
	int			fl_plus;
	int			fl_space;
	int			fl_sharp;
	int			fl_zero;
	int			width;
	int			precision;
	int			mod_h;
	int			mod_hh;
	int			mod_l;
	int			mod_ll;
	int			mod_l_up;
	int			size;
	int			sign;
	int			fd;
	int			size_symb;
	char		type;
}				t_prn;

typedef union	u_inf_nan
{
	double		d;
	uintmax_t	l;
}				t_inf_nan;

int				main();
int				ft_printf(const char *format, ...);
int				print_di(t_prn *prn);
int				print_s(t_prn *prn);
int				print_c(t_prn *prn);
int				print_p(t_prn *prn);
int				print_oux(t_prn *prn);
int				print_efg(t_prn *prn);

int				print_txt(const char *format, int size, t_prn *prn);
void			ft_print_type_csp(int size, int len, t_prn *prn, char *str);
int				strsub_to_int(const char *str, int st, int end);

void			ft_itoa16(uintmax_t num, char *rez, int base, char *basee);
void			ft_print_number(int len, int size, char *str, t_prn *prn);
void			ft_print_flags_numbertype(int len, char *str, t_prn *prn);
int				ft_count_len(int len, char *str, t_prn *prn);
intmax_t		ft_get_signed_mod_llhh(t_prn *prn);
void			set_str_values(char *str, char *values, int size);

int				find_type(const char *format, t_prn *prn);
int				set_flag(const char *format, t_prn *prn, int end);
int				set_width(const char *format, int i, t_prn *prn);
int				set_precision(const char *format, int i, t_prn *prn);
int				set_mod(const char *format, int i, t_prn *prn);
int				ft_find_count(const char *s, int c);

long double		get_nbr(t_prn *prn);
int				print_format(t_prn *prn, char *str);
int				ft_islower(int ch);
int				get_degree(long double *nbr);
void			cut_str(char *str, t_prn *prn);
void			add_exp(char *str, int degree, t_prn *prn);
int				ft_isnan(long double nbr);
int				ft_isinf(long double nbr);
int				nan_inf(long double nbr, t_prn *prn, char *str);
void			add_point(char *str, t_prn *prn, int degree);
int				correct_str(char *str, t_prn *prn, int degree);
int				ft_round9(char *str, int count, int degree);
void			move_under_one(char *str, int degree);

#endif
