encounter_src = Randomizers/encounters.c
trainers_src = Randomizers/trainers.c

LIBFT = 42-libft/libft.a

CC = gcc

all: $(encounters) $(trainers)

encounters:
	$(MAKE) -C ./42-libft
	gcc $(encounter_src) $(LIBFT) -o Randomizers/encounters

trainers:
	$(MAKE) -C ./42-libft
	gcc $(trainers_src) $(LIBFT) -o Randomizers/trainers

clean:
	$(MAKE) clean -C ./42-libft

fclean: clean
	rm -f ./Randomizers/encounters
	rm -f ./Randomizers/trainers

re: fclean all
