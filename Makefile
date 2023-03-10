SRCS =  srcs/main.c 								\
		srcs/error.c								\
		srcs/cmd/init_cmd.c 						\
		srcs/cmd/parse_redir_1.c					\
		srcs/cmd/parse_redir_2.c					\
		srcs/cmd/exe_redir.c						\
		srcs/cmd/here_document.c					\
		srcs/parser/parse_path.c 					\
		srcs/parser/lst_cmd_utils.c 				\
		srcs/parser/lexer.c							\
		srcs/parser/parser.c						\
		srcs/parser/ft_split_quote.c				\
		srcs/parser/remove_quote.c					\
		srcs/parser/ft_is_char.c					\
		srcs/parser/split_quote_utils.c 			\
		srcs/parser/ft_revers_split.c				\
		srcs/parser/ft_split_dollar.c				\
		srcs/parser/expand_var_env.c				\
		srcs/builtins/env.c							\
		srcs/builtins/lst_utils.c					\
		srcs/builtins/pwd.c 						\
		srcs/builtins/recover_cmd.c					\
		srcs/builtins/exit.c						\
		srcs/builtins/export.c						\
		srcs/builtins/unset.c						\
		srcs/builtins/export_utils.c				\
		srcs/builtins/print_utils.c					\
		srcs/signal.c								\
		srcs/builtins/echo.c						\
		srcs/builtins/cd.c							\
		srcs/builtins/env_utils.c					\
		srcs/builtins/export_alpha.c				\
		srcs/builtins/cd_utils.c					\
		srcs/pipe/pipe.c							\
		srcs/pipe/redir_pipe.c						\
		srcs/builtins/ret_utils.c					\
		srcs/builtins/ignore_env.c


OBJS = ${SRCS:.c=.o}

HEAD = include/minishell.h

INCLUDE =	-Iinclude

NAME = minishell

CC		= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAG =  -g3

.c.o:		${SRCS}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			make -C libft
			${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}
			@echo "\033[33;31mCOMPILED\t\t\tCONGRATS\033[0m"


debug:		${SRCS} ${HEAD}
			make -C libft
			@${CC} ${SRCS} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -Llibft -lft -lreadline -o ${NAME}
			@echo "\033[33mREADY TO DEBUG\t\t\tGOOD LUCK\033[0m"


all: 		${NAME}

clean:
			@rm -f ${OBJS}
			@make clean -C libft
			@echo "\033[33;34mCLEAN !\t\t\t\tBUT YOU CAN DO BETTER\033[0m"

fclean:		clean
			rm -f ${NAME}
			@make fclean -C libft
			rm -rf minishell.dSYM
			@echo "\033[33;32mALL CLEAN !\t\t\tYOU'RE VERY PROPER\033[0m"

re:			fclean all
			@echo "\033[33;36mRECOMPILED !\t\t\tIT'S WORK NOW ?\033[0m"

.PHONY:		all fclean clean re debug
