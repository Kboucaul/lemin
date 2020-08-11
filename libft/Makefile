# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 16:26:54 by kboucaul          #+#    #+#              #
#    Updated: 2020/02/13 15:22:40 by kboucaul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =			free_tab.c			\
			./str_is_full_of_digits.c	\
			./ft_strcdup.c			\
			./add_line.c			\
			./ft_wordcount.c		\
			./ft_abs.c			\
			./ft_isastring.c 	\
			./free_arr.c 			\
			./ft_count_occurrence.c			\
		./create_an_array_with_gnl.c				\
		./ft_putchar_fd.c					\
		./ft_putstr_fd.c					\
		./arr_numdup.c						\
		./ft_swap.c						\
		./ft_ll_atoi.c						\
		./ft_lstnew.c 					\
		./ft_strjoin_free.c					\
		./ft_lstaddback.c 					\
		./ft_isinteger.c 					\
		./num_delim.c						\
		./ft_lstfree.c 						\
		./reverse_arr_num.c					\
		./ft_lstdelone.c 					\
		./display_tab.c						\
		./get_next_line.c					\
		./ft_atol.c							\
		./ft_atoi.c 						\
		./ft_bzero.c 						\
		./ft_isalnum.c 						\
		./ft_isalpha.c 						\
		./ft_isdigit.c 						\
		./ft_itoa.c 						\
		./ft_itoa_base.c					\
		./ft_unsitoa_base.c 				\
		./ft_memalloc.c 					\
		./ft_isprint.c						\
		./ft_memccpy.c 						\
		./ft_memchr.c 						\
		./ft_memcmp.c 						\
		./ft_memcpy.c 						\
		./ft_memdel.c 						\
		./ft_memmove.c 						\
		./ft_memset.c 						\
		./ft_putchar.c 						\
		./ft_putnbr.c 						\
		./ft_putstr.c 						\
		./ft_strcat.c 						\
		./ft_strchr.c 						\
		./ft_strclr.c 						\
		./ft_strcmp.c 						\
		./ft_strcpy.c 						\
		./ft_strdel.c 						\
		./ft_strdup.c 						\
		./ft_strequ.c 						\
		./ft_striter.c 						\
		./ft_striteri.c 					\
		./ft_strjoin.c 						\
		./ft_strlcat.c 						\
		./ft_strlen.c 						\
		./ft_strmap.c 						\
		./ft_strmapi.c 						\
		./ft_strncat.c 						\
		./ft_strncmp.c 						\
		./ft_strncpy.c 						\
		./ft_strnequ.c 						\
		./ft_strnew.c 						\
		./ft_strnstr.c 						\
		./ft_strrchr.c 						\
		./ft_strsplit.c 					\
		./ft_strstr.c 						\
		./ft_strsub.c 						\
		./ft_strtrim.c 						\
		./ft_tolower.c 						\
		./ft_toupper.c						\
		./ft_ftoa.c							\
		./ft_strndup.c						\
		./ft_printf/get_char.c				\
		./ft_printf/get_str.c				\
		./ft_printf/manage_precision.c		\
		./ft_printf/get_deci.c				\
		./ft_printf/get_unsigned_int.c		\
		./ft_printf/get_float.c				\
		./ft_printf/manage_width.c			\
		./ft_printf/get_hexa.c				\
		./ft_printf/manage_zero.c			\
		./ft_printf/get_num.c				\
		./ft_printf/parser.c				\
		./ft_printf/get_octal.c				\
		./ft_printf/manage_hash.c			\
		./ft_printf/ft_printf.c				\
		./ft_printf/get_pointer.c			\
		./ft_printf/manage_plus_and_space.c	\

OBJS = $(SRCS:%.c=%.o)

INC = ./includes

CC = gcc

CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(INC) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INC)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
