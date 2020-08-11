# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kboucaul <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 11:51:02 by kboucaul          #+#    #+#              #
#    Updated: 2020/02/13 15:22:27 by kboucaul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	lem-in

LIB				=	-lft

CC				=	gcc

CFLAGS			+=	-Wall -Wextra -Werror

DIR				=	./srcs

SRCS			=	main.c 						\
					parse_datas.c 				\
					is_valid_type.c 			\
					room.c 						\
					tubes.c 					\
					others.c 					\
					add_datas.c 				\
					edmonds_karp.c 				\
					bfs.c 						\
					create_path_combination.c 	\
					path_tools.c 				\
					is_best_path.c 				\
					print_movements.c 			\
					free.c 						\
					print_others.c

OBJS			=	$(addprefix $(DIR)/, ${SRCS:.c=.o})

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -I ./libft/includes -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $@ $(OBJS) -I ./includes -L ./libft $(LIB)

clean:
	make -C libft clean
	$(RM) $(OBJS)

fclean:	clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY:            all clean fclean re
