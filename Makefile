#------------------------------------------------------------------------------#
#----------------------------------PROPERTIES----------------------------------#
#------------------------------------------------------------------------------#

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
DFLAGS	 	= -MD -MP
LDFLAGS    	= -lreadline
IFLAGS		= -I $(INCLUDES)
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= cub3d

SRCSDIR		= srcs
INCLUDES	= includes

SRCS		= \
			$(SRCSDIR)/main.c \
			$(SRCSDIR)/map_tools/map_parser.c \
			$(SRCSDIR)/map_tools/file_reader.c \
			$(SRCSDIR)/test_tools/print.c \
			$(SRCSDIR)/freeing/freeing.c \

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.d))

#------------------------------------------------------------------------------#
#------------------------------------LIBFT-------------------------------------#
#------------------------------------------------------------------------------#

LIBDIR		= ./libft
LIBFT		= ${LIBDIR}/libft.a

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME)

$(NAME)	: ${OBJS}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} ${DFLAGS} ${IFLAGS} -o $@ $^ ${LIBFT} ${LDFLAGS}


${OBJSDIR}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} ${DFLAGS} ${IFLAGS} -c $< -o $@

clean	:
		$(MAKE) -C ${LIBDIR} clean
		$(RM) $(OBJSDIR)

fclean	:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME)

re		:
		$(MAKE) -C ${LIBDIR} re
		$(RM) $(OBJSDIR) $(NAME)
		$(MAKE) all

-include $(DEPS)

.PHONY	: all clean fclean re
