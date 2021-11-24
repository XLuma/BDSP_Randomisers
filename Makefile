encounter_src = Randomizers/encounters.c
trainers_src = Randomizers/trainers.c
abilities_src = Randomizers/abilities.c
tm_src = Randomizers/tm.c
tm_compat_src = Randomizers/tm_compat.c
fld_item_src = Randomizers/fld_items.c

encounters = encounters
trainers = trainers
abilities = abilities
tm = tm
tm_compat = tm_compat
fld_item = fld_item

LIBFT = 42-libft/libft.a

CC = gcc

all: $(encounters) $(trainers) $(abilities) $(tm) $(tm_compat) $(fld_item)	

$(encounters):
	$(MAKE) -C ./42-libft
	gcc $(encounter_src) $(LIBFT) -o Randomizers/encounters

$(trainers):
	$(MAKE) -C ./42-libft
	gcc $(trainers_src) $(LIBFT) -o Randomizers/trainers

$(abilities):
	$(MAKE) -C ./42-libft
	gcc $(abilities_src) $(LIBFT) -o Randomizers/abilities

$(tm):
	$(MAKE) -C ./42-libft
	gcc $(tm_src) $(LIBFT) -o Randomizers/tm

$(tm_compat):
	$(MAKE) -C ./42-libft
	gcc $(tm_compat_src) $(LIBFT) -o Randomizers/tm_compat

$(fld_item):
	$(MAKE) -C ./42-libft
	gcc $(fld_item_src) $(LIBFT) -o Randomizers/fld_item
clean:
	$(MAKE) clean -C ./42-libft

fclean: clean
	rm -f ./Randomizers/encounters
	rm -f ./Randomizers/trainers
	rm -f ./Randomizers/tm
	rm -f ./Randomizers/abilities

re: fclean all

.PHONY: trainers encounters abilities tm all