NAME			=	cub3D
FILES			=	parsing/map.c  parsing/file.c  parsing/floodfill.c\
					parsing/map_utils.c  parsing/error_handler.c parsing/parser.c\
					parsing/color_parse.c  parsing/grid.c  parsing/parsing_utils.c  parsing/texture_parse.c main.c \
					game/game.c rendering/rendering.c utils/vector.c utils/more_math.c \
					utils/map_accessor.c raycasting/raycasting.c game/game_init.c

SRC_DIR			=	src
OBJ_DIR			=	obj
SRC				=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ				=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CC				=	gcc

HEADER_DIR		=	includes
LIB_DIR			=	libs
LIBFT_DIR		=	$(LIB_DIR)/libft
MLX_DIR			=	$(LIB_DIR)/MLX42
MLX_BUILD_DIR	=	$(MLX_DIR)/build

MLX				=	$(MLX_BUILD_DIR)/libmlx42.a
LIBFT			=	$(LIBFT_DIR)/libft.a

INCLUDES		=	-I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include

UNAME 			= 	$(shell uname -s)
ifeq ($(UNAME), Linux)
	LIB_FLAGS	=	-L$(MLX_BUILD_DIR) -lmlx42 -lglfw -lm -ldl -pthread -L$(LIBFT_DIR) -lft
endif
ifeq ($(UNAME), Darwin)
	LIB_FLAGS	=	-framework Cocoa -framework OpenGL -framework IOKit -L"$(shell brew info glfw | grep files | cut -d " " -f1)/lib/" -lglfw -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx42
endif

GMON			= 	#-pg
ERROR_FLAGS 	= 	#-Wall -Werror -Wextra
CASAN			= 	#-fsanitize=address
LASAN			= 	#-fsanitize=address -static-libasan


all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME) $(LASAN) $(GMON)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
   		mkdir -p $(dir $@); \
	fi
	$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ $(CASAN) $(GMON) -g

$(LIBFT): | $(LIBFT_DIR)/Makefile
	make -C $(LIBFT_DIR)

$(LIBFT_DIR)/Makefile:
	@git submodule init
	@git submodule update $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)/CMakeLists.txt
	cmake $(MLX_DIR) -B $(MLX_BUILD_DIR)
	make -C $(MLX_BUILD_DIR)

$(MLX_DIR)/CMakeLists.txt:
	@git submodule init
	@git submodule update $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

leaks:
	make && valgrind --leak-check=full ./$(NAME) map.cub

.PHONY: all clean fclean re
