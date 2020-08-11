/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:03:25 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 16:38:05 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

/*
**				Print : Fonction affichant le caractere passe en premier
**				argument et stockant +1 dans le pointeur sur int a chaque
**				appel de la fonction.
*/

static void		print(const char c, int *nb_printed)
{
	ft_putchar(c);
	(*nb_printed)++;
}

/*
**				Manager : Fonction qui oriente vers la gestion des flags.
*/

static void		manager(t_format *form, char **str)
{
	manage_precision(*form, str);
	manage_plus_and_space(*form, str);
	if (form->width && form->hash && !form->precision_set &&
	form->zero && !form->moins)
	{
		manage_width(*form, str);
		if (form->nul_nb != -1)
			manage_hash(*form, str);
	}
	else
	{
		if (form->nul_nb != -1)
			manage_hash(*form, str);
		manage_width(*form, str);
	}
}

/*
**				Dispatch : Fonction prenant en parametre une structure
**				format initialisee et une va_list et retournant un int contenant
**				le nombre de caractere contenu dans une chaine.
**				(1) Si le type stockee n'apparrait pas dans la
**				chaine CONVERSION ("cspdiouxXf") on retourne 0.
**				(2) Sinon en fonction du type on appelle la fonction
**				correspondante.
**				(3) La chaine str stockera le resultat (un nombre, une
**				string, une addresse etc...).
**				(4) Ensuite on appliquera les differents flags. (+, -,
**				espace etc...).
**				(5) On affiche notre chaine, on la libere puis on renvoie
**				le nombre
**				de caractere
**				la composant pour le retour de ft_printf.
**
**				ex : ft_printf("%c", 82);
**					-> le type apparait dans la chaine "cspdiouxXf" (type c).
**					--> On appelle donc la fonction get_char (elle nous renvoie
**							"R").
**					---> On appliaue les flags (ici aucun).
**					----> On affiche "R".
**					-----> On renvoie la longueur de la chaine = 1.
*/

static int		dispatch_fonc(t_format *form, va_list args)
{
	char	*str;
	int		len;

	if (ft_strchr(CONVERS, form->type) == NULL)
		return (0);
	if (form->type == '%')
		str = ft_strdup("%");
	else if (form->type == 'c')
		str = get_char(args, form);
	else if (form->type == 's')
		str = get_str(args);
	else if (form->type == 'p')
		str = get_pointer(args);
	else if (ft_strchr("diouxXf", form->type))
		str = get_num(form, args);
	manager(form, &str);
	len = ft_strlen(str);
	ft_putstr(str);
	if (form->nul_char == 1)
	{
		ft_putchar('\0');
		len++;
	}
	free(str);
	return (len);
}

/*
**	Parse_and_dispatch : On initialise la structure format, on appelle
**		dispatch pour agir en fonction des flags, on incremente nb_printed
**		en fonction du retour de dispatch.
**		On return form.
*/

static t_format	parse_and_dispatch(const char **format, int *nb_printed,
		t_format *form, va_list args)
{
	*form = parse_format(format);
	*nb_printed = *nb_printed + dispatch_fonc(form, args);
	return (*form);
}

/*
**				Ft_printf : Fonction variadique affichant une chaine de
**				caractere et renvoyant le nombre de caracteres affiches.
**				(1) Tant que l'on ne trouve pas de '%', on affiche le
**				cararctere.
**				(2) Si on trouve un '%' suivi d'un autre '%' on affiche '%'.
**				(3) Sinon, si on cherche a connaitre le format (initialisation
**				de la structure form).
**				(4) On stock le nombre de caractere affiches.
**				(5) On recommence tant que la chaine n'est pas terminee.
*/

int				ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	form;
	int			nb_printed;

	nb_printed = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
			print(*format, &nb_printed);
		else
		{
			format++;
			if (*format == '%' || *format == '\n')
				print(*format, &nb_printed);
			else if (*format != '\0')
				form = parse_and_dispatch(&format, &nb_printed, &form, args);
		}
		if (*format != '\0')
			format++;
	}
	va_end(args);
	return (nb_printed);
}
