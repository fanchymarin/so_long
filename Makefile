NAME = so_long
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -O3
MLXFLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit

UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lbsd
endif

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.c check_map.c utils.c render_map.c load_assets.c hook_handlers.c
OBJFILES = $(SRCFILES:.c=.o)

SRC = $(addprefix $(SRCDIR), $(SRCFILES))
SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

LIBFTLIB = -Llibft -lft

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) bonus -C libft
	$(MAKE) clean -C libft
	$(MAKE) -C minilibx
	gcc -o so_long $^ $(LIBFTLIB) $(MLXFLAGS) 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -g -c $(CFLAGS) $< -o $@ 

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) clean -C minilibx
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
