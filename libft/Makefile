NAME = libft.a

HEADER = libft.h

FUN = 	ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_bzero.c ft_itoa.c ft_putendl_fd.c \
		ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_tolower.c ft_split.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c \
		ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_toupper.c ft_strtrim.c ft_putchar_fd.c \
		ft_isalnum.c ft_isprint.c ft_memmove.c ft_strlcat.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_putstr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		get_next_line.c ft_malloc.c ft_strcmp.c  stock_addr.c ft_swap.c

REMOVE = rm -f

COMPILER = cc

SOBJECT = $(FUN:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADER)
	$(COMPILER) $(FLAGS) -c $<

all: $(NAME)

$(NAME): $(SOBJECT)
	ar -rc $(NAME) $(SOBJECT) 

clean:
	$(REMOVE) $(SOBJECT)

fclean: clean
	$(REMOVE) $(NAME)

re:  fclean all

