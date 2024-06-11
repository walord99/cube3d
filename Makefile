NAME            = cub3D
FILES           = parsing/map.c parsing/file.c parsing/floodfill.c parsing/element_utils.c parsing/elements_parser.c \
                  parsing/map_utils.c parsing/error_handler.c parsing/parser.c parsing/get_colors.c parsing/file_process.c \
                  parsing/color_parse.c parsing/grid.c parsing/parsing_utils.c parsing/texture_parse.c main.c \
                  game/game.c rendering/rendering.c utils/vector.c utils/more_math.c utils/free_game.c \
                  utils/map_accessor.c raycasting/raycasting.c game/game_init.c game/input_handling.c game/player_movement.c \
                  rendering/rendering_utils.c rendering/circle_fill.c raycasting/raycasting_utils.c rendering/background_renderer.c

SRC_DIR         = src
OBJ_DIR         = obj
SRC             = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ             = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CC              = gcc
HEADER_DIR      = includes
LIB_DIR         = libs
LIBFT_DIR       = $(LIB_DIR)/libft
MLX_DIR         = $(LIB_DIR)/MLX42
MLX_BUILD_DIR   = $(MLX_DIR)/build

MLX             = $(MLX_BUILD_DIR)/libmlx42.a
LIBFT           = $(LIBFT_DIR)/libft.a

INCLUDES        = -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include

UNAME           = $(shell uname -s)
ifeq ($(UNAME), Linux)
    LIB_FLAGS   = -L$(MLX_BUILD_DIR) -lmlx42 -lglfw -lm -ldl -pthread -L$(LIBFT_DIR) -lft
endif
ifeq ($(UNAME), Darwin)
    LIB_FLAGS   = -framework Cocoa -framework OpenGL -framework IOKit -L"$(shell brew info glfw | grep files | cut -d " " -f1)/lib/" -lglfw -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx42
endif

ERROR_FLAGS     = -Wall -Werror -Wextra

all: $(NAME)
$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
        mkdir -p $(dir $@); \
    fi
	$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ -g -O3

$(LIBFT): | $(LIBFT_DIR)/Makefile
	@make -C $(LIBFT_DIR)

$(LIBFT_DIR)/Makefile:
	@git submodule init
	@git submodule update $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)/CMakeLists.txt
	@cmake $(MLX_DIR) -B $(MLX_BUILD_DIR)
	@make -C $(MLX_BUILD_DIR)

$(MLX_DIR)/CMakeLists.txt:
	@git submodule init
	@git submodule update $(MLX_DIR)

clean:
	@echo "$(BOLD)$(PINK)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR) $(NAME).dSYM

fclean: clean
	@echo "$(BOLD)$(PINK)Cleaning executable...$(RESET)"
	@rm -f $(NAME) $(NAME).dSYM

norm :
	@echo "$(BOLD)$(PINK)🚀Launching norminette ...$(RESET)"
	@sleep 1
	@echo "$(BOLD)$(CYAN)checking libraries ...$(RESET)"
	@sleep 1
	@norminette $(LIBFT_DIR)
	@echo "$(BOLD)$(CYAN)checking headers ...$(RESET)"
	@sleep 1
	@norminette $(HEADER_DIR)
	@echo "$(BOLD)$(CYAN)checking sources ...$(RESET)"
	@sleep 1
	@norminette $(SRC)
	@echo "$(BOLD)$(GREEN)✔ All checks passed! Code is in perfect norm. ✔$(RESET)"

re: fclean all

test: $(NAME)
	@leaks --atExit -- ./$(NAME) maps/map.cub

test1: $(NAME)
	@leaks --atExit -- ./$(NAME) maps/empty_map.cub

test2: $(NAME)
	@leaks --atExit -- ./$(NAME) maps/incorrect_element.cub

leaks: $(NAME)
	@leaks --atExit -- ./$(NAME) maps/school_map.cub

.PHONY: all clean fclean re norm test test1 test2 leaks

##############COLORS################
MINT    = \033[38\;2\;189\;252\;201m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m
BOLD    = \033[1m
PINK    = \033[35m