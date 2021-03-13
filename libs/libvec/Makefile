
NAME = libvec.a

SRCS = vec.c vec_op.c vec_op_ad.c

OBJS = $(SRCS:.c=.o)

CLEAR_LINE=\033[2K
BEGIN_LINE=\033[A
OK_COLOR=\x1b[102;01m
GREEN_COLOR=\x1b[32;01m
NO_COLOR=\x1b[0m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
BUILD_PRINT = $(GREEN_COLOR)libvec.a successfully compiles$(NO_COLOR)
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
KO_STRING=$(ERROR_COLOR)[KO]$(NO_COLOR)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CLEAR_LINE)"
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "$(BUILD_PRINT)"

COMPILE_OBJECT = gcc $(CFLAGS) -o $@ -c $< -I ../libft -I . 2>/dev/null && echo "$(OK_STRING)" || echo "$(KO_STRING)" 

$(OBJS): %.o : %.c
	@echo "$(CLEAR_LINE)Compiling $< ==> $@ `$(COMPILE_OBJECT)`$(BEGIN_LINE)"
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re