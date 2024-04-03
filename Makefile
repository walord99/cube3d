FILES			= 	game/main.c

SRC_DIR			= 	src
OBJ_DIR			= 	obj
SRC				= 	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ 			= 	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CC				= 	gcc

NAME			= 	cube3d
HEADER_DIR		= 	include
LIB_DIR  		=	libs
LIBFT_DIR 		= 	$(LIB_DIR)/libft
MLX_DIR			=	$(LIB_DIR)/MLX42
MLX_BUILD_DIR	=	$(MLX_DIR)/build

MLX				= 	$(MLX_BUILD_DIR)/libmlx42.a
LIBFT			= 	$(LIBFT_DIR)/libft.a

INCLUDES		= 	-I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include


UNAME 			= 	$(shell uname -s)
ifeq ($(UNAME), Linux)
  LIB_FLAGS		= 	-L$(MLX_BUILD_DIR) -lmlx42 -lglfw -lm -ldl -pthread -L$(LIBFT_DIR) -lft
endif
ifeq ($(UNAME), Darwin)
  LIB_FLAGS		= 	-framework Cocoa -framework OpenGL -framework IOKit -L"/Users/$(shell whoami)/.brew/Cellar/glfw/3.3.9/lib/" -lglfw -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx42
endif

ERROR_FLAGS 	= 	#-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
   		mkdir -p $(dir $@); \
	fi
	$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ -g

$(LIBFT): $(LIBFT_DIR)/Makefile
	make -C $(LIBFT_DIR)

$(LIBFT_DIR)/Makefile:
	@git submodule init
	@git submodule update $(LIBFT_DIR)

$(MLX): $(MLX_DIR)/CMakeLists.txt
	cmake $(MLX_DIR) -B $(MLX_BUILD_DIR)
	make -C $(MLX_BUILD_DIR)

$(MLX_DIR)/CMakeLists.txt:
	@git submodule init
	@git submodule update $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re