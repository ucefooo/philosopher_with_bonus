NAME = philosopher

NAME_BONUS = philo_b

src = philo/main.c philo/InitParam.c philo/utils.c

src_b = philo_bonus/life.c philo_bonus/main.c philo_bonus/process.c\
		philo_bonus/utils_bonus.c

obj = $(src:.c=.o)

obj_b = $(src_b:.c=.o)

hd = philo/philo.h

hd_b = philo_bonus/philo_bonus.h

flags = -Wall -Wextra -Werror

cc = cc

all: $(NAME)

$(NAME): $(src) $(obj) $(hd)
	$(cc) $(flags) $(src) -o $(NAME)

%.o : %.c
	$(cc) $(flags) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(hd_b) $(obj_b) $(src_b)
	$(cc) $(flags) $(src_b) -o $(NAME_BONUS)
clean:
	rm -rf $(obj) $(obj_b)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all