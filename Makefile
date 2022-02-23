# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 03:21:02 by ksuomala          #+#    #+#              #
#    Updated: 2021/05/26 15:20:23 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer

SRCS = visualizer.c \
save_graph.c \
backround.c \
ants.c \
animation.c \
visualize_algorithm.c \
free_all.c \
scale_map.c \
init_edges.c \
queue.c \
bfs_location.c \
ant_movement.c \
draw_graph.c \
colors.c \
events.c \
test_print.c \
realloc.c \
get_rekt.c

H_FILES = includes/lemin_visual.h

LIBSDL2 = lib/libSDL2/lib/libSDL2.a

LIBSDL_MAKE = SDL2/libSDL2/Makefile

LIBSDL2_TTF = $(LIB_DIR)lib/libSDL2_ttf.a

SDL2_CONFIG = $(abspath $(LIB_DIR)libSDL2/bin/sdl2-config)

FT2_CONFIG = $(abspath $(FREETYPE_BUILD)builds/unix/freetype-config)

LIB_FT2 = $(LIB_DIR)libft2/lib/libfreetype.a
#FT2 freetype-config is searched for in system.

FREETYPE_BUILD = SDL2/SDL2_ttf/external/freetype-2.9.1/

LIBFT = ../libft/libft.a

BUILD_DIR = SDL2/

LIB_DIR = lib/

OBJ_DIR = obj/
SRCS_DIR = src/

SDL_ARCHIVE = SDL2-2.0.14

TTF_ARCHIVE = SDL2_ttf-2.0.15

UNZIP_SDL = $(BUILD_DIR)libSDL2

UNZIP_TTF = $(BUILD_DIR)SDL2_ttf

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CC = gcc

C_FLAGS = -g -Wall -Wextra -Werror `$(LIB_DIR)libSDL2/bin/sdl2-config --cflags`

LINKS = -L ../libft -lft -L lib/lib -lSDL2_ttf -L lib/libSDL2/lib `$(LIB_DIR)libSDL2/bin/sdl2-config --libs` -L $(LIB_DIR)libft2/lib -lfreetype

INCL = -I ../includes -I includes -I ../libft -I lib/libSDL2/include -I lib/include/SDL2 -I lib/libft2/libft2/lib -I lib/libft2/include/freetype2/

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LINKS)
	@echo "executable compiled!"

$(OBJS):  $(addprefix $(SRCS_DIR), $(SRCS)) $(LIBSDL2) $(H_FILES) | $(OBJ_DIR) $(lib_dir) $(LIBSDL2_TTF)
	@echo "Compiling..."
	$(CC) $(C_FLAGS) $(INCL) -c $(addprefix $(SRCS_DIR), $(SRCS))
	@echo "*object files created"
	mv $(SRCS:.c=.o) $(OBJ_DIR)

$(LIBSDL2_TTF): | $(UNZIP_TTF) $(LIB_FT2)
	@echo "Configuring SDL2_ttf..."
	cd SDL2/SDL2_ttf && ./configure --prefix=$(abspath $(LIB_DIR)) SDL2_CONFIG=$(SDL2_CONFIG) FT2_CONFIG=$(FT2_CONFIG)
	@echo "SDL2_ttf configured!"
	@echo "bulding SDL2_ttf"
	$(MAKE) SDL2_CONFIG=$(SDL2_CONFIG) FT2_CONFIG=$(FT2_CONFIG) --directory=SDL2/SDL2_ttf
	$(MAKE) SDL2_CONFIG=$(SDL2_CONFIG) FT2_CONFIG=$(FT2_CONFIG) --directory=SDL2/SDL2_ttf install
	@echo "SDL2_ttf BUILT!"

$(LIB_FT2): | $(UNZIP_TTF)
	@echo "Configuring Freetype library..."
	cd $(FREETYPE_BUILD) && ./configure --prefix=$(abspath $(LIB_DIR)/libft2)
	@echo "Freetype2 library configured!"
	@echo "Building FT2 library"
	$(MAKE) --directory=$(FREETYPE_BUILD)
	$(MAKE) --directory=$(FREETYPE_BUILD) install
	@echo "LFT2 BUILT!"


$(LIBSDL2): $(LIB_DIR) | $(UNZIP_SDL)
	@echo "Configuring SDL2..."
	cd SDL2/libSDL2 && ./configure --prefix=$(abspath $(LIB_DIR)libSDL2) --disable-shared --disable-video-wayland
	@echo "SDL2 configured"
	@echo "Building SDL2..."
	$(MAKE) --directory=SDL2/libSDL2
	$(MAKE) --directory=SDL2/libSDL2 install
	@echo "SDL2 BUILT!"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "*.o removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 clean; fi
	@echo "*LIBSDL2 cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "Targets removed!"
	if test -f $(LIBSDL_MAKE); then $(MAKE) AUTOMAKE=: --directory=SDL2/libSDL2 distclean; fi
	rm -rf $(LIB_DIR) $(BUILD_DIR)
	@echo "*LIBSDL2 removed!"

$(LIBFT):
	make -C ../libft

$(LIB_DIR):
	mkdir $(@)

$(SRCS_DIR):
	mkdir $(@)

$(OBJ_DIR):
	mkdir $(@)

$(BUILD_DIR):
	mkdir $(@)

$(UNZIP_SDL): | $(BUILD_DIR)
	unzip $(SDL_ARCHIVE).zip
	mv $(SDL_ARCHIVE) $(UNZIP_SDL)

$(UNZIP_TTF): | $(BUILD_DIR)
	unzip $(TTF_ARCHIVE).zip
	mv $(TTF_ARCHIVE) $(UNZIP_TTF)

re: fclean all
