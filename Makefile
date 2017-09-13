NAME	= ft_select
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), ft_select.h)
TERMCAP	= -ltermcap

SOURCES	:= $(shell find src | grep "\.c" | grep -v "\.c.")
NB		:= $(shell find src | grep "\.c" | grep -v "\.c." | wc -l\
			| rev | cut -f 1 -d ' ' | rev)

OBJECTS	= $(SOURCES:src/%.c=obj/%.o)

RED		= \033[31m
GREEN	= \033[32m
BLUE	= \033[34m
WHITE	= \033[37m
EOC		= \033[0m

.PHONY: all clean nclean fclean re

all: $(NAME)

$(NAME): obj $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(TERMCAP)
	@ echo "$(GREEN)[$@]: binary successfully created !$(EOC)"

obj/%.o: src/%.c $(HEADERS)
	$(eval FILE=$(shell echo $$(($(FILE) + 1))))
	$(eval PERCENT=$(shell echo $$(($(FILE) * 100 / $(NB)))))
	@ echo "[$(NAME)]: $(PERCENT)% ($(FILE)/$(NB))\r\c"
	$(CC) $(FLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	mkdir -p ./obj
	@ echo "$(BLUE)[$(NAME)]: objects directory created$(EOC)"

clean:
	rm -rf obj
	@ echo "$(RED)[$(NAME)]: objects directory deleted$(EOC)"

fclean: clean
	rm -rf $(NAME)

re: fclean all
