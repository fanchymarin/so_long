NAME = so_long
CFLAGS = -Wall -Wextra -Werror -I include
MLXFLAGS = -framework OpenGL -framework AppKit

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.c check_map.c utils.c
OBJFILES = $(SRCFILES:.c=.o)

SRC = $(addprefix $(SRCDIR), $(SRCFILES))
SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

MLXLIB = /usr/local/lib/libmlx.a
LIBFTLIB = libft/libft.a

all: $(NAME)

$(NAME): $(SRCOBJ)
	#$(MAKE) -C minilibx
	$(MAKE) -C libft
	gcc -o so_long $(MLXFLAGS) $^ $(MLXLIB) $(LIBFTLIB)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -c $(CFLAGS) $< -o $@ 

clean:
	$(MAKE) clean -C minilibx
	$(MAKE) clean -C libft
	rm -rf $(OBJDIR)

fclean:
	$(MAKE) clean -C minilibx
	$(MAKE) fclean -C libft
	rm -rf $(OBJDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
