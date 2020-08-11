/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:23:54 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 17:02:49 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define FLAGS "hlL#0-+ "
# define CONVERS "cspdiouxXf%"

/*
**		hash --> La valeur doit être conroomie en une autre forme.
**				-> Pour la conversion o le premier caractère de la chaîne de
**				sortie vaudra zéro (en ajoutant un préfixe 0 si ce n'est pas
**				déjà un zéro).
**				-> Pour les conversions x et X une valeur non nulle reçoit le
**				préfixe « 0x » (ou « 0X » pour l'indicateur X).
**				-> Pour les conversions a, A, e, E, f, F, g, et G le résultat
**				contiendra toujours un point décimal même si aucun chiffre ne
**				le suit (normalement, un point décimal n'est présent avec ces
**				conversions que si des décimales le suivent).
**				-> Pour les conversions g et G les zéros en tête ne sont pas
**				éliminés, contrairement au comportement habituel.
**				-> Pour les autres conversions, cet attribut n'a pas d'effet.
**		zero --> remplissage a gauche avec des zeros
**		moins --> La valeur doit être justifiée sur la limite gauche du champ
**				(par défaut elle l'est à droite). Sauf pour la conversion n,
**				les valeurs sont complétées à droite par des espaces, plutôt
**				qu'à gauche par des zéros ou des blancs. Un attribut -
**				surcharge un attribut 0 si les deux sont fournis.
**		plus --> Ll doit toujours avoir un signe affiche avant le nombre
**		space --> il doit avoir un espace vide devant le nombre (sauf si
**				l'option '+' est activee)
**		l --> La conversion entière suivante correspond à un long int ou
**				unsigned long int, ou la conversion n suivante correspond à
**				un pointeur sur un long int, ou la conversion c suivante
**				correspond à un argument wint_t, ou encore la conversion s
**				suivante correspond à un pointeur sur un wchar_t.
**		ll --> La conversion entière suivante correspond à un long long int,
**				ou unsigned long long int, ou la conversion n suivante
**				correspond à un pointeur sur un long long int.
**		h --> La conversion entière suivante correspond à un short int ou
**				unsigned short int, ou la conversion n suivante correspond
**				à un argument pointeur sur un short int.
**		hh --> La conversion entière suivante correspond à un signed char ou
**				unsigned char, ou la conversion n suivante correspond à un
**				argument pointeur sur un signed char.
**		l_up --> La conversion a, A, e, E, f, F, g, ou G suivante correspond
**				à un argument long double. (C99 autorise %LF mais pas SUSv2).
**		precision_set --> 1 si la precision est activee
**		precision --> Correspond au numero de la precision
**		type --> Correspond a la conversion (cspdiouxXf)
*/

typedef struct		s_format
{
	int				hash;
	int				zero;
	int				moins;
	int				plus;
	int				space;
	int				l;
	int				ll;
	int				h;
	int				hh;
	int				l_up;
	int				precision_set;
	int				width;
	int				precision;
	char			type;
	int				nul_char;
	int				nul_nb;
}					t_format;

/*
**		Ft_printf.c
*/

int					ft_printf(const char *format, ...);

/*
**		Parser.c
*/

t_format			parse_format(const char **format);

/*
**		Get_char.c
*/

char				*get_char(va_list args, t_format *form);

/*
**		Get_str.c
*/

char				*get_str(va_list args);

/*
**		Get_pointer.c
*/

char				*get_pointer(va_list args);

/*
**		Get_num.c
*/

char				*get_num(t_format *form, va_list args);

/*
**		Get_deci.c
*/

char				*get_deci(va_list args, t_format form);

/*
**		Get_octal.c
*/

char				*get_octal(va_list args, t_format form);

/*
**		Get_unsigned_int.c
*/

char				*get_unsigned_int(va_list args, t_format form);

/*
**		Get_hexa.c
*/

char				*get_hexa(t_format *form, va_list args);

/*
**		Get_float.c
*/

char				*get_float(va_list args, t_format form);

/*
**		Manage_plus_and_space.c
*/

void				manage_plus_and_space(t_format form, char **str);

/*
**		Manage_width.c
*/

void				manage_width(t_format form, char **str);

/*
**		Manage_zero.c
*/

void				manage_zero(t_format form, char **str, char *new, int len);

/*
**		Manage_hash.c
*/

void				manage_hash(t_format form, char **str);

/*
**		Manage_precision.c
*/

void				manage_precision(t_format form, char **str);

/*
**		Manage_precision_float.c
*/

void				precision_float(t_format *form, char **str, int len);

/*
**		ft_ftoa.c
*/

char				*ft_ftoa(long double num, unsigned int precision);

#endif
