#include <stdio.h>
#include <stdlib.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square 
{
	int size;
	int **array;
} Square;

int get_square_size();
Square * generate_magic(int size);
void write_to_file(Square * square, char *filename);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
	if(argc != 2)
	{
		printf("Usage: %s <filename>",argv[0]);
	}
	// Get size from user
	int size = get_square_size();
;
	if(!size)
	{
		return 0;
	}
	// Generate the magic square
	Square *square = generate_magic(size);
	// Write the square to the output file
	write_to_file(square,argv[1]);
	
	return 0;
}

// get_square_size prompts the user for the magic square size
// checks if it is an odd number >= 3 and returns the number
int get_square_size()
{
	int size;
	// Prompt user for size of square
	printf("Enter size of magic square, must be odd\n");
	// Retireve user input
	scanf("%d",&size);
	// Check user input to see if it is even or odd
	if(size < 3 || (size % 2 == 0))	
	{
		printf("Size must be an odd number >= 3.\n");
		return 0;
	}
	return size;
}

// generate_magic constructs a magic square of size n
// using the Siamese algorithm and returns the Square struct
Square * generate_magic(int n)
{
	int max_value = n * n;
	int r = 0;
	int c = n/2;
	// Alloc memory for struct ptr
	Square *square = malloc(sizeof(*square));
	// Check to see if memory was allocated correctly
	if(square == NULL)
	{
		printf("Could not allocate memory");
		exit(0);
	}

	square->size = n;
	// Allocate mmemory for rows and handle any errors that arise
	if(NULL == (square->array =  malloc(n * sizeof(int*))))
	{
		printf("Could not allocate memory");
		exit(0);
	}
	for(int i = 0; i < n; i++)
	{
		// Allocate memory for columns and handle errors
		if(NULL == (*(square->array + i) = malloc(n * sizeof(int))))
		{
			printf("Could not allocate memory");
			exit(0);
		}
			
		
	} 
	// Run throgh siamese method to generate and assign values to square slots
	// Each iteration, i will be placed in the square that is 1 above and 1 tothe right of prior slot
	for(int i = 1; i <= max_value; i++)
	{
		*(*(square->array + r) + c) = i;
		// Move up one row
		r--;
		// Move to right one column
		c++;
		// For every value that is a multiple of the square size, it will be placed one square below instead
		if(i % n == 0)
		{
			r += 2;
			c--;
		}
		else
		{
			// Wrap around vertically
			if(c == n)
			{
				c -=n;
			}
			// Wrap around horizontally
			else if(r < 0)
			{
				r += n;
			}
		}
	}
	
	return square;
}

// write_to_file opens up a new file(or overwrites the existing file)
// and writes out the square in the format expected by verify_magic.c
void write_to_file(Square * square, char *filename)
{
	int n = square->size;	
	// Open file to write
	FILE *f = fopen(filename, "w");
	// Write first char to file
	fprintf(f,"%d\n",n);
	// Go through square array and write each row to the txt file, with commas separating the numbers
	for(int r = 0; r < n; r++)
	{
		for(int c = 0; c < n; c++)
		{
			fprintf(f,"%d",*(*(square->array + r) + c));
			if(c + 1 != n)
			{
				fprintf(f,",");
			}
			else
			{
				// Place a newline char at end of each row
				fprintf(f,"\n");
			}
		}
	}	

	fclose(f);
}
