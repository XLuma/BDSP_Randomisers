encounter_src = Randomizers/encounters.c
trainers_src = Randomizers/trainers.c
abilities_src = Randomizers/abilities.c
tm_src = Randomizers/tm.c

LIBFT = 42-libft/libft.a

CC = gcc

all: $(encounters) $(trainers)

encounters:
	$(MAKE) -C ./42-libft
	gcc $(encounter_src) $(LIBFT) -o Randomizers/encounters

trainers:
	$(MAKE) -C ./42-libft
	gcc $(trainers_src) $(LIBFT) -o Randomizers/trainers

abilities:
	$(MAKE) -C ./42-libft
	gcc $(abilities_src) $(LIBFT) -o Randomizers/abilities

tm:
	$(MAKE) -C ./42-libft
	gcc $(tm_src) $(LIBFT) -o Randomizers/tm

clean:
	$(MAKE) clean -C ./42-libft

fclean: clean
	rm -f ./Randomizers/encounters
	rm -f ./Randomizers/trainers

re: fclean all
