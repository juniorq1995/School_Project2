#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square 
{
	int size;
	int **array;
} Square;

Square * construct_square(char *filename);
int verify_magic(Square * square);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
	if(argc != 2 || argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
	}
	else
	{
		// Construct square
		Square *sqrPtr = construct_square(argv[1]);
		// Verify if it's a magic square and print true or false
		if(verify_magic(sqrPtr))
		{
			printf("true\n");
		}
		else
		{
			printf("false\n");
		}
	}
	return 0;
}

// construct_square reads the input file to initialize a square struct
// from the contents of the file and returns the square.
// The format of the file is defined in the assignment specifications
Square * construct_square(char *filename)
{ 	
	// Allocate memory for struct and handle errors
	Square *square = malloc(sizeof(*square));
	if(square == NULL)
	{
		printf("Could not allocate memory");
		exit(0);
	}
	// This will hold the size
	char x;
	// Open and read the file
	FILE *f = fopen(filename, "r");
	// Handle errors
	if(f == 0)
	{
		printf("Cannot open file for reading\n");
		return NULL;
	}
 	// Read the first line to get the square size
	x = getc(f);
	int size = x - '0';
 	// Initialize a new Square struct of that size
    	square->size = size;
	if(NULL == (square->array = malloc(size * sizeof(int *))))
	{
		printf("Could not allocate memory");
		exit(0);
	}

	for(int i = 0; i < size; i++)
	{
		if(NULL == (*(square->array + i) = malloc(size * sizeof(int))))
		{
			printf("Could not allocate memory");
			exit(0);
		}
	}
	int y;
	// Read the rest of the file to fill up the square	
	// Rows
	for(int i = 0; i < size; i++)
	{	//columns
		for(int j = 0; j < size; j++)
		{
			while(fscanf(f,"%d,",&y) != EOF)
			{
				// Assign number to square slot
				*(*(square->array + i) + j) =  y;
				break;
			}
		}	
	}
	fclose(f);
 	return square;
}

// verify_magic verifies if the square is a magic square
// returns 1(true) or 0(false)
int verify_magic(Square * square)
{
	int compare = 0;
	int temp = 0;
	int size = square->size;
	// Add up the slots for one section to use as a base to compare against
	for(int c = 0; c < size; c++)
	{
		compare += *(*(square->array)+c);
	}	
	// Check all rows sum to same number
	for(int r = 0; r < size; r++)
	{
		for(int c = 0; c < size; c ++)
		{
			temp += (*(*(square->array + r) + c));
		}
		if(temp != compare) 
		{
			return 0;
		}
		temp = 0;
	}
	// Check all cols sum to same number
	temp = 0;
	for(int c = 0; c < size; c++)
	{
		for(int r = 0; r < size; r++)
		{
			temp += (*(*(square->array + r) + c));	
		}
	
		if(temp != compare) 
		{
			return 0;
		}
		temp = 0;
	}
	// Check main diagonal
	temp = 0;
	for(int i = 0; i < size; i ++)
	{
		temp += (*(*(square->array + i) + i));	
	}
	
	if(temp != compare)
	{
		return 0;
	}
	// Check secondary diagonal
	temp = 0;
	for(int count = size-1; count >= 0; count--)
	{
		temp += (*(*(square->array + count) + count));
	}
	if(temp != compare)
	{
	 	return 0;
	}
	return 1;
}
