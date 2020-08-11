/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:03:31 by kboucaul          #+#    #+#             */
/*   Updated: 2019/03/27 17:23:56 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Ft_power : fonction retournant un nombre (num) mis a la puissance (pow).
**	(1) Mult permet de garder le nombre d'origine qui va varier dans la boucle.
**	(2) Gestion des cas particuliers (puissance nulle ou nombre egal a 1).
**	(3) Tant que notre puissance est superieur a 1 on multiplie notre nombre
**	par lui meme (num = num x mult).
**	(4) On retourne le resultat apres la sortie de boucle.
*/

static unsigned long long int	ft_power(long long int num, int pow)
{
	unsigned long long int		mult;

	mult = num;
	if (pow == 0 || num == 1)
		return (1);
	while (pow > 1)
	{
		num *= mult;
		pow--;
	}
	return (num);
}

/*
**	Absol : fontion prenant un nombre et une string en parametre.
**	(1) Si le nombre est negatif, un concatene la str avec
**	un '-' et on prend l'oppose du nombre.
*/

static char						*absol(long double *num, char *str)
{
	if (*num < 0)
	{
		ft_strcat(str, "-");
		*num = -*num;
	}
	return (str);
}

/*
**	Zero_fill : Tant que la taille de la chaine est inferieure a la
**	precision,on ajoute des zeros a la suite.
*/

static char						*zero_fill(int tmp_len,
								unsigned int precision, char *str, char **tmp)
{
	while ((unsigned int)tmp_len < precision)
	{
		ft_strcat(str, "0");
		tmp_len++;
	}
	ft_strcat(str, *tmp);
	free(*tmp);
	return (str);
}

/*
**	Ft_ftoa : fonction prenant un reel et une precision qui lui sera
**	appliquee et qui retourne ce dit nombre sous forme de chaine de caracteres.
**
**	(1) On alloue une chaine de la taille d'un long double.
**
**					|Partie entiere|
**
**	(2) Si on a un nombre negatif le premier caractere de notre chaine sera '-'.
**		(2bis) Passage de negatif a positif.
**	(3) La variable ent_part stockera la partie entiere duu nombre
**			(ex : 5.12 --> 5)
**		(3bis) La variable frac_part stockera la partie decimale
**			(ex : (5.12 - 5) --> 0.12)
**	(4) On stock notre partie entiere dans tmp sous forme de chaine.
**			(5) On copie notre tmp a la suite de str.
**
**					|Partie decimale|
**
**	(6) Si notre precision est differente de 0, on traite la partie decimale.
**	(7) On ajoute un '.' a la suite de notre partie entiere dans str.
**	(8) On fait passer notre partie decimale en entier avec ft_power.
**		ex : 0.1252 (precision 2) --> 12.52
**	(9) On regarde si l'arrondi est necessaire
**		ex : 12.52 --> 0.52 >= 0.5 ? --> OUI --> donc on arrondis.
**	(9bis) Si arrondis necessaire on increment notre frac_part de 1.
**	(10) On recuppere grace a ft_atoi une chaine de caracteres contenant
**			notre partie decimale.
**	(11) Si la precision est superieur a la taille de notre chaine tmp :
**			--> (on ajoute autant de zero que necessaire a la suite).
**	(12) On copie les deux bouts de chaine ((signe + entier) + (decimale)).
**	(13) Liberation de notre variable tmp.
**	(14) On renvoie notre chaine.
**					|EX : |
**	nb = 14.5268 (precision = 2)
**			----> ent_part = 14  et  frac_part = 0.5268
**			----> pas de '-' dans str[0]
**			---->str = "14."
**			---->precision != 0
**				--> donc frac_part = 0.5268 x (10 exposant 2)
**					--> 52.68
**						0.68 > 0.5 ==> arrondis
**			---->tmp = "53"
**			---->len >= precision --> pas de remplissage de 0.
**			---->str = "14.53"
*/

char							*ft_ftoa(long double num,
								unsigned int precision)
{
	unsigned long long int		ent_part;
	long double					frac_part;
	char						*str;
	char						*tmp;
	int							tmp_len;

	if (!(str = ft_strnew(39)))
		return (ft_strdup("0"));
	str = absol(&num, str);
	ent_part = (unsigned long long int)num;
	frac_part = num - ent_part;
	tmp = ft_unsitoa_base(ent_part, 10);
	ft_strcat(str, tmp);
	free(tmp);
	if (precision != 0)
	{
		ft_strcat(str, ".");
		frac_part = frac_part * ft_power(10, precision);
		tmp = (frac_part - (unsigned long long int)frac_part) >= 0.5 ?\
			ft_unsitoa_base(frac_part + 1, 10) :\
			ft_unsitoa_base(frac_part, 10);
		tmp_len = ft_strlen(tmp);
		str = zero_fill(tmp_len, precision, str, &tmp);
	}
	return (str);
}
