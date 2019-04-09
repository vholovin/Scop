
NAME		=	scop

COM			=	gcc
FLAGS		=	-Wall -Wextra -Werror -Wno-deprecated-declarations
OPTIMA		=	-O3

SRC_DIR		=	./srcs/
INC_DIR		=	./includes/
OBJ_DIR		=	./objs/

SRC_FILES	= 	main.c						\
				tutorial.c					\
				core_lst.c					\
				core_face.c					\
				core_time.c					\
				core_keyboard.c				\
				core_keyboard_transform.c	\
				core_render.c				\
				core_vertex.c 				\
				scop_init.c					\
				scop_shader_upload.c		\
				scop_shader_linking.c 		\
				scop_upload_texture.c		\
				scop_upload_obj.c			\
				scop_centered_obj.c			\
				scop_create_array.c			\
				scop_set_array.c			\
				scop_set_transform.c		\
				scop_set_matrix.c			\
				scop_calculate_mvp.c		\
				scop_loop.c					\
				scop_free.c					\
				scop_error.c				\
				sdl_init.c					\
				sdl_exit.c					\
				sdl_error.c					\
				gl_init_buffer.c 			\
				gl_init_viewport.c			\
				vector/vec3_1.c				\
				vector/vec3_2.c

INC_FILES 	= 	scop.h	\
				vec3.h

OBJ_FILES 	=	$(SRC_FILES:.c=.o)

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2 -framework OpenGL

LIBFT_DIR	=	./libft
LIBFT_LIB	= 	$(LIBFT_DIR)/libft.a
LIBFT_INC	=	$(LIBFT_DIR)/includes

STB_DIR		=	./stb
STB_INC		=	$(STB_DIR)

PWD			= 	$(shell pwd)
LIB_FLAG	=	-rpath $(PWD)/$(SDL_DIR)

SRCS 		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
HDRS 		=	$(addprefix $(INC_DIR), $(INC_FILES))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

GREEN		=	\033[32m
RESET		=	\033[39m
YELLOW		=	\033[33m
RED 		=	\033[31m

all: obj libft sdl2 stb $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/vector
	@mkdir -p $(OBJ_DIR)/stb

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(COM) $(FLAGS) $(OPTIMA) $(SDL_FRM) -c $< -o $@ -I $(INC_DIR) -I$(LIBFT_INC) -I$(STB_INC)

$(NAME): $(OBJS) $(HDRS)
	@make -C $(LIBFT_DIR)
	@$(COM) $(FLAGS) $(OPTIMA) $(LIBFT_LIB) $(SDL_FRM) $(SDL_LINK) $(LIB_FLAG) $(OBJS) -o $(NAME)
	@ echo "$(GREEN)Attention: $(YELLOW)$(NAME)$(RESET) installed"

libft:
	@ mkdir -p $(LIBFT_DIR)
	@ test -f $(LIBFT_DIR)/Makefile && echo "$(YELLOW)File Libft already exist$(RESET)" || make libft-install

libft-install:
	@ echo "$(GREEN)LIBFT: install LIBFT$(RESET)"
	@ git clone https://github.com/vholovin/Libft.git $(LIBFT_DIR)

libft-delete:
	@ rm -rf $(LIBFT_DIR)
	@ echo "$(RED)Attention: $(YELLOW)LIBFT$(RESET) removed"

sdl2:
	@ mkdir -p $(SDL_DIR)
	@ test -f $(SDL_DIR)/SDL2.framework/SDL2 && echo "$(YELLOW)File SDL2 already exist$(RESET)" || make sdl2-install

sdl2-install:
	@ echo "$(GREEN)SDL: install SDL2.framework$(RESET)"
	@ curl -o sdl2.dmg https://www.libsdl.org/release/SDL2-2.0.8.dmg
	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; hdiutil eject ../../../Volumes/SDL2;
	@ rm -rf sdl2.dmg

sdl2-delete:
	@ rm -rf $(SDL_DIR)
	@ echo "$(RED)Attention: $(YELLOW)SDL2$(RESET) removed"

stb:
	@ mkdir -p $(STB_DIR)
	@ test -f $(STB_DIR)/stb_image.h && echo "$(YELLOW)File STB already exist$(RESET)" || make stb-install

stb-install:
	@ echo "$(GREEN)STB: install STB$(RESET)"
	@ git clone https://github.com/nothings/stb.git $(STB_DIR)

stb-delete:
	@ rm -rf $(STB_DIR)
	@ echo "$(RED)Attention: $(YELLOW)STB$(RESET) removed"

clean:
	@ make -C $(LIBFT_DIR) clean
	@ rm -rf $(OBJ_FILES)
	@ rm -rf $(OBJ_DIR)
	@ echo "$(RED)Attention: $(YELLOW)$(NAME)$(RESET) object removed"

fclean: clean
	@ make -C $(LIBFT_DIR) fclean
	@ rm -rf $(NAME)
	@ echo "$(RED)Attention: $(YELLOW)$(NAME)$(RESET) removed"

lclean: fclean libft-delete sdl2-delete stb-delete
	@ echo "$(RED)Attention: $(YELLOW)all libs$(RESET) removed"	

re:	fclean all

.PHONY: all libft sdl2 stb clean fclean re
