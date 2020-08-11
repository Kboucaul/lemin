/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:01:43 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 12:28:42 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

/*
**		Check_h : Fonction qui recherche la presence de
**		flag de modification h et hh. (short int ou signed char).
**		(1) Si on trouve un h et le caractere suivant est h egalement.
**			-> On note le flag hh dans la structure.
**		(2) Si on trouve un h "seul".
**			-> On note le flag h dans la structure.
*/

static void		check_h(const char **format, t_format *form)
{
	if ((*(*format + 1) == 'h'))
	{
		form->hh = 1;
		(*format)++;
	}
	else
		form->h = 1;
}

/*
**		Check_l : Fonction qui recherche les flags
**		de modification l et ll (long int et long long int).
**		Meme principe qu'au dessus.
**		(1) Si on trouve un l et que le caractere suivant est l.
**			->On note le flag ll dans la structure.
**		(2) Sinon, si on trouve un l "seul".
**			->On note le flag l dans la structure.
*/

static void		check_l(const char **format, t_format *form)
{
	if ((*(*format + 1) == 'l'))
	{
		form->ll = 1;
		(*format)++;
	}
	else
		form->l = 1;
}

/*
**		Set_numbers : Fonction qui recherche la presence
**		d'info sur la precision ou la largeur.
**		(1) Si on n'a pas trouve de precision, alors on
**		cherche la presence de largeur avec ft_atoi.
**		(2) Sinon, si on saitv la presence de precision,
**		on cherche la valeur de cette precision avec ft_atoi.
*/

static void		set_numbers(const char **format, t_format *form)
{
	if (form->precision_set == 0)
		form->width = ft_atoi(*format);
	else
		form->precision = ft_atoi(*format);
}

/*
**		Set_flag : Fonction qui rempli la structure en
**		fonction des flags trouvés dans la chaine format.
**		(1) Ainsi on avance dans la chaine, et on note
**		la presence de flag (1) ou non (0).
**		CAS PARTICULIER : Le flag 0 s'annule si presence du flag - .
*/

static void		set_flag(const char **format, t_format *form)
{
	if (**format == 'h')
		check_h(format, form);
	else if (**format == 'l')
		check_l(format, form);
	else if (**format == 'L')
		form->l_up = 1;
	else if (**format == '#')
		form->hash = 1;
	else if (**format == '0' && (form->precision_set == 0))
		form->zero = 1;
	else if (**format == '-')
		form->moins = 1;
	else if (**format == '+')
		form->plus = 1;
	else if (**format == ' ')
		form->space = 1;
}

/*
**		Parse_Format : Fonction qui retourne une structure
**		contenant la liste des formats prehas_been_sents.
**		(1) Initialisation des champs de la structure.
**		(2) On remplie la structure avec les flags prehas_been_sents.
**		(3) Ensuite on recherche le type de variable (c, s, p etc...).
**		(4) Si on trouve la presence de nombre dans les flags
**		on recherche leur nature (precision ou width).
**		(5) Si on trouve la presence de '.' on note la presence
**		du flag precision.
**		(6) On retourne la structure.
*/

t_format		parse_format(const char **format)
{
	t_format	form;

	form = (t_format){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	while (**format)
	{
		if (ft_strchr(FLAGS, **format))
			set_flag(format, &form);
		else if ((ft_isalpha(**format) && **format != 'l'
			&& **format != 'L' && **format != 'h') || **format == '%')
		{
			form.type = **format;
			return (form);
		}
		else if (ft_isdigit(**format))
		{
			set_numbers(format, &form);
			while (ft_isdigit(**format))
				(*format)++;
			(*format)--;
		}
		else if (**format == '.')
			form.precision_set = 1;
		(*format)++;
	}
	return (form);
}
