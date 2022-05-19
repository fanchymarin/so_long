NAME = so_long
CFLAGS = -Wall -Wextra -Werror -Iinclude -O3
UNAME = $(shell uname)

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

ifeq ($(UNAME), Linux)
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lbsd
endif

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.c check_map.c utils.c render_map.c
OBJFILES = $(SRCFILES:.c=.o)

SRC = $(addprefix $(SRCDIR), $(SRCFILES))
SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

LIBFTLIB = -Llibft -lft

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) -C libft
	$(MAKE) clean -C libft
	gcc -o so_long $^ $(LIBFTLIB) $(MLXFLAGS) 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -g -c $(CFLAGS) $< -o $@ 

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
