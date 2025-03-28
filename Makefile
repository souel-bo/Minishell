NAME = minishell

CC = cc  #-fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror

MINISHELL_SRC = main.c helper.c builtins.c

LIBFT_SRC = LIBFT/ft_lstnew_bonus.c LIBFT/ft_putstr_fd.c LIBFT/ft_putchar_fd.c \
			LIBFT/ft_split.c LIBFT/ft_lstadd_back_bonus.c LIBFT/ft_strlen.c\
			LIBFT/ft_lstlast_bonus.c  LIBFT/ft_lstdelone_bonus.c LIBFT/ft_lstclear_bonus.c\
			LIBFT/ft_strdup.c LIBFT/ft_strncmp.c LIBFT/ft_atoi.c

MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(MINISHELL_OBJ) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) $(MINISHELL_OBJ) $(LIBFT_OBJ) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@

clean:
	rm -rf $(MINISHELL_OBJ)  $(LIBFT_OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: clean

re: fclean all

.SECONDARY: $(MINISHELL_OBJ) $(LIBFT_OBJ)