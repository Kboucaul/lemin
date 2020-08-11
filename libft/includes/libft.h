/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:34:16 by kboucaul          #+#    #+#             */
/*   Updated: 2020/01/30 12:07:12 by kboucaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_count_occ(char const *s, char c);
char				*ft_strcdup(const char *s, char c);
int					free_tab(void **tab, int size);
int					str_is_full_of_digits(char *str);
int					ft_wordcount(const char *str, char del);
int					ft_count_occurrence(char *str, char c);
char				**create_an_array_with_gnl(int fd,
					int debut, int height);
int					abs_value(int x);
void				ft_swap(int *s1, int *s2);
int					*reverse_arr_num(int *num, int len);
int					num_delim(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2,
					int free1, int free2);
int					ft_isastring(char *str);
long long int		ft_ll_atoi(const char *str);
void				display_tab(int *arr, int size);
void				free_arr(char **str);
int					ft_isinteger(char *str);
char				*ft_strndup(const char *s, int n);
void				ft_lstdelone(t_list **lst);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src,
					size_t n);
void				*ft_memccpy(void *dst, const void *src,
					int c, size_t n);
void				ft_lstfree(void *ptr, size_t size);
void				ft_lstaddback(t_list **lst, t_list *new);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src,
					size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(long int n);
char				*itoa_base(long long int num, int base);
char				*ft_unsitoa_base(unsigned long long int num, int base);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(int fd, char c);
void				ft_putstr_fd(int fd, char *str);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstrev(t_list **alst);
size_t				ft_lstcount(t_list *lst);
long				ft_atol(char const *str);
#endif
