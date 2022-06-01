NAME = so_long
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx -O3
MLXFLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit
KEYS = KEY_S=1 KEY_A=0 KEY_W=13 KEY_D=2 KEY_ESC=53
SPEED = C_SPEED=10 E_SPEED=5 P_SPEED=0 END_SPEED=20

UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	MLXFLAGS = -lmlx -lXext -lX11 -lm -lbsd
	KEYS = KEY_S=115 KEY_A=97 KEY_W=119 KEY_D=100 KEY_ESC=65307
	SPEED = C_SPEED=1000 E_SPEED=500 P_SPEED=200 END_SPEED=5000
endif
DEFINE = $(addprefix -D, $(KEYS) $(SPEED))

SRCDIR = src/
OBJDIR = obj/

SRCFILES = main.c check_map.c utils.c utils2.c mlx_use.c \
		   load_assets.c hook_handlers.c animations.c
OBJFILES = $(SRCFILES:.c=.o)

SRC = $(addprefix $(SRCDIR), $(SRCFILES))
SRCOBJ = $(addprefix $(OBJDIR), $(OBJFILES))

LIBFTLIB = -Llibft -lft

all: $(NAME)

$(NAME): $(SRCOBJ)
	$(MAKE) bonus -C libft
	$(MAKE) clean -C libft
ifeq ($(UNAME), Darwin)
	$(MAKE) -C minilibx
endif
	gcc -o so_long $^ $(LIBFTLIB) $(MLXFLAGS) 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p obj
	gcc -g -c $(CFLAGS) $(DEFINE) $< -o $@ 

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) clean -C minilibx
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
