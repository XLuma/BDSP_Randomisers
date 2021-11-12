#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "../42-libft/libft.h"

int main(int argc, char **argv)
{
	char const *filename = argv[1];
	char const *newfile = ft_strjoin(argv[1], "_convert.txt");
	char const *move_file = argv[2];
	FILE *move;
	FILE *old;
	FILE *new;
	char *buffer;
	char *buffer2;
	char **move_array;
	char **old_array;
	char *line;
	long lSize;
	long lSize2;
	int i;
	int j;

	old = fopen(filename, "rb");
	new = fopen(newfile, "w");
	move = fopen(move_file, "rb");
	fseek(old, 0L, SEEK_END);
	lSize = ftell(old);
	rewind(old);

	fseek(move, 0L, SEEK_END);
	lSize2 = ftell(move);
	rewind(move);


	if (new == NULL)
		return 1;
	printf("Allocating mem\n");
	buffer = calloc(1, lSize+1);
	buffer2 = calloc(1, lSize2+1);

	if( !buffer ) fclose(old),fputs("memory alloc fails",stderr),exit(1);
	if( !buffer2 ) fclose(move),fputs("memory alloc fails2",stderr),exit(1);

	/* copy the file into the buffer */
	printf("Reading file into mem\n");
	if( 1!=fread( buffer , lSize, 1 , old) )
  		fclose(old),free(buffer),fputs("entire read fails",stderr),exit(1);

	if( 1!=fread( buffer2 , lSize2, 1 , move) )
  		fclose(move),free(buffer2),fputs("entire read fails2",stderr),exit(1);
	
	old_array = ft_split(buffer, '\n');
	move_array = ft_split(buffer2, '\n');
	free(buffer2);
	free(buffer);
	printf("We're in boys\n");

	i = 0;
	j = 0;
	//old array is move list in string, move_array is index
	while (old_array[i])
	{
		while (move_array[j])
		{
			int num = atoi(move_array[i]);
			//convert index array to int, compare with I, if both mtch we know the move is part of used index
		}
		printf("%s\n", line);
		fputs(line, new);
		fputs("\n", new);
		i++;
	}
	free(move_array);
	free(old_array);
	fclose(move);
	fclose(new);
	fclose(old);
	return 0;