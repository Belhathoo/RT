
NAME = rt

SRCS = rt.c\
		rt_parse.c\
		rt_parse_utils.c\
		rt_draw.c\
		rt_events.c\
		rt_hit.c\
		rt_init.c\
		rt_lighting.c\
		rt_shading.c\
		rt_utils.c\
		rt_close.c\
		rt_hit_sphere.c\
		rt_hit_cylinder.c\
		rt_hit_cone.c\
		rt_hit_plan.c\
		rt_hit_torus.c\
		rt_solve_quartic.c\
		rt_solve_cubic.c\
		rt_solve_quadric.c\
		rt_hit_parabole.c\
		rt_textures.c\
		load_txt.c\
		rt_hit_cube.c\
		rt_cube_case.c\
#ft_parse0.c ft_parse.c\

SRC = $(add prefix srcs/, $(SRCS))
SRCS_NORM = $(SRCS)

OBJS_DIR = objs
OBJ = $(SRCS:%.c=$(OBJS_DIR)/%.o)

HEADERS = rt.h rt_struct.h rt_define.h
HEADER = headers
HEADERS_NORM = $(HEADERS)

LIBFT_NORM = $(shell find libs/libft/ | grep '\.c' | cut -c 8-)
LIBFT_NORM += libft.h

CLEAR_LINE=\033[2K
BEGIN_LINE=\033[A
_END_COL=\033[0m
_RED_COL=\033[1;31m
_GREEN_COL=\033[1;32m
_YELLOW_COL=\033[1;33m
_BLUE_COL=\033[1;34m
_VIOLET_COL=\033[1;35m
_CYAN_COL=\033[1;36m
_WHITE_COL=\033[1;37m

BUILD_PRINT = $(_GREEN_COL)rt successfully compiles$(_END_COL)
OK_STRING=$(_GREEN_COL)[OK]$(_END_COL)
KO_STRING=$(_RED_COL)[KO]$(_END_COL)

ifeq ($(shell uname), Darwin)
MLX_DIR = libs/minilibx_macos
else
MLX_DIR = libs/minilibx_linux
endif

ifeq ($(shell uname), Darwin)
$(info MacOs detected)
MLX = -I $(MLX_DIR) -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
$(info $(shell uname) detected)
MLX = -lm -I $(MLX_DIR) -L $(MLX_DIR) -lmlx -lXext -lX11
#MLX = -lm -I $(MLX_DIR) $(MLX_DIR)/libmlx.dylib -lXext -lX11
endif

#ifeq ($(shell uname), Darwin)
#SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
#SDL2_IMAGE = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
#SDL2_TTF = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
#SDL2_MIXER = ./frameworks/SDL2_mixer.framework/Versions/A/SDL2_mixer
#SDL_FLAGS = -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_MIXER 
#SDL_FLAGS = -I headers/SDL2 -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_MIXER 
#else
#SDL_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
#endif

CFLAGS = #-Wall -Wextra -Werror
LIBFT_DIR = libs/libft
XML_DIR = libs/libxml
VEC_DIR = libs/libvec
LIBS = $(MLX) -L $(LIBFT_DIR) -lft -L $(XML_DIR) -lxml -L $(VEC_DIR) -lvec -lpthread
INCS = -I $(LIBFT_DIR) -I $(XML_DIR) -I $(VEC_DIR) #-I headers/SDL2
#LIBS += $(SDL_FLAGS)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJ)
	@echo "$(CLEAR_LINE)$(_BLUE_COL)Compiling libraries$(_END_COL)"
	@make libmlx.a -C $(MLX_DIR) 2>/dev/null
	@make libft.a -C $(LIBFT_DIR)
	@make libxml.a -C $(XML_DIR)
	@make libvec.a -C $(VEC_DIR)
	@gcc $(CFLAGS) -o $(NAME) $(filter-out $<, $+) $(LIBS)
	@echo "$(BUILD_PRINT)"

#ifeq ($(shell uname), Darwin)
#	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
#	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_IMAGE) $(NAME)
#	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_TTF) $(NAME)
#	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_MIXER) $(NAME)
#endif

$(OBJS_DIR):
	@mkdir -p $@

COMPILE_OBJECT = gcc -I headers/SDL2 -I headers $(CFLAGS) $(INCS) -o $@ -c $< && echo "$(OK_STRING)" || echo "$(KO_STRING)"

objs/%.o: srcs/%.c headers/rt.h headers/rt_define.h headers/rt_struct.h
	@echo "$(CLEAR_LINE)$(_BLUE_COL)[$(NAME)]$(_CYAN_COL) Compiling [$(_END_COL)$(_YELLOW_COL)$<$(_END_COL)$(_CYAN_COL)] ==> [$(_YELLOW_COL)$@$(_END_COL)$(_CYAN_COL)] $(_END_COL)`$(COMPILE_OBJECT)`$(BEGIN_LINE)"

clean:
	@rm -rf $(OBJS_DIR) && echo "$(_YELLOW_COL)Deleting objects...$(_END_COL)"
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(XML_DIR)
	@make clean -C $(VEC_DIR)

fclean: clean
	@rm -rf $(NAME) && echo "$(_YELLOW_COL)Deleting $(NAME)...$(_END_COL)"
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(XML_DIR)
	@make fclean -C $(VEC_DIR)

re: fclean all

norm: $(SRCS_NORM) $(HEADERS_NORM) $(LIBFT_NORM)

NORM = norminette $< | awk 'BEGIN{i = 0}{if ($$1 != "Norme:") i++}END{if (i == 0) print "$(OK_STRING)"; else print "$(KO_STRING)"}'

$(SRCS_NORM) : % : srcs/%
	@echo "check norminette $< ==> `$(NORM)`"

$(HEADERS_NORM) : % : headers/%
	@echo "check norminette $< ==> `$(NORM)`"

$(LIBFT_NORM) : % : $(LIBFT_DIR)/%
	@echo "check norminette $< ==> `$(NORM)`"

.PHONY: all, clean, fclean, re, norm
