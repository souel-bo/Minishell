NAME = minishell

CC = cc  #-fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror

EXECUTION_SRC = excution/create_nodes.c

MINISHELL_SRC = main.c 

EXECUTION_OBJ = $(EXECUTION_SRC:.c=.o)

TOKENIZER = tokenizer/tokenizer.c parser/parser.c tokenizer/lexer.c

LIBFT_SRC = libft/ft_lstaddback.c  libft/ft_lstdelone.c  libft/ft_lstnew.c  libft/ft_strjoin.c  libft/ft_strlcpy.c  libft/ft_strndup.c\
						libft/ft_lstclear.c    libft/ft_lstlast.c    libft/ft_strchr.c  libft/ft_strlcat.c  libft/ft_strlen.c\
						libft/ft_putchar_fd.c libft/ft_putstr_fd.c  libft/ft_strncmp.c

MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

TOKENIZER_OBJ = $(TOKENIZER:.c=.o)

all: $(NAME)

$(NAME): $(MINISHELL_OBJ) $(LIBFT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ)
	$(CC) $^ -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@

clean:
	rm -rf $(MINISHELL_OBJ)  $(LIBFT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: clean

re: fclean all

.SECONDARY: $(MINISHELL_OBJ) $(LIBFT_OBJ) $(TOKENIZER_OBJ) $(EXECUTION_OBJ)
