#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int flags_left;
int count_mine(int** minefield,int row,int column,int size)
{
   
}

int** gen_mines(int size, int level)
{
   
}

int** gen_minefield(int size, int level)
{
   
}
void top_border(int size)
{

}
void mid_border(int size)
{
	
}
void bottom_border(int size)
{

}
void display_minefield(int x, int y, int size, int** minefield, int ref_matrix[size][size])
{
   
}
void get_input(int size, int* x,int* y,char* choice, int** minefield, int ref_matrix[size][size])
{

}
void game_over(int size, int** minefield, int ref_matrix[size][size])
{

}
void open_cell(int* cell)
{
	*cell = 0;
}
void open(int x,int y, int size, int** minefield, int ref_matrix[size][size])
{
   
}
int check_mines(int size, int ref_matrix[size][size],int mines)
{

}

int main()
{
	int size, level, i, j, mines, x, y;
	char choice;
	printf("\n\n GRID Sizes\n 1 - 8 x 8 \n 2 - 12 x 12 \n 3 - 16 x 16 \n\nEnter Grid Size : ");
	scanf("%d",&size);
	system("cls");
	printf("\n\n DIFFICULTY\n 1 - Beginner \n 2 - Intermediate \n 3 - Expert \n\nEnter Difficulty : ");
	scanf("%d",&level);
	system("cls");
	size = ((size+1)*4)+2, mines = (size-5)*level, x = size-2, y = size-2, flags_left = mines * 2;
	int **minefield = gen_minefield(size,level);
	int ref_matrix[size][size];
	for(i=0;i<size;i++)
    {
		for(j=0;j<size;j++)
		{
			if(i == 0 || j == 0 || i == size-1 || j == size-1)
			{
				ref_matrix[i][j] = -2;
			}
			else
			{
            	ref_matrix[i][j] = 1;
			}
		}
		printf("\n");
	}
	system("cls");
	while(1)
    {
        get_input(size, &x, &y, &choice, minefield, ref_matrix);
        if(choice == 'f')
        {
        	if(ref_matrix[x][y] == 1)
        	{
        		if(flags_left == 0)
        		{
        			printf("\a");
        			continue;
				}
        		ref_matrix[x][y] =  -1;
        		flags_left--;
			}
			else if(ref_matrix[x][y] == -1)
			{
				ref_matrix[x][y] =  1;
				flags_left++;
			}
			else
			{
				goto z;
			}
        }
        else if(choice == 'o')
        {
			if(ref_matrix[x][y] == 0 || ref_matrix[x][y] == -1)
        	{
            	goto z;
        	}
        	else if(minefield[x][y] == -1)
        	{
        		system("cls");
        		game_over(size, minefield, ref_matrix);
        		break;
			}
			else 
        	{
        		open(x, y, size, minefield, ref_matrix);
        		if(check_mines(size, ref_matrix, mines))
        		{
        			system("cls");
        			x = 0, y = 0;
        			display_minefield(x, y, size, minefield , ref_matrix);
        			printf("\n\n\t\t\t\t\t\tYOU WON\n\n");
        			getch();
        			break;
				}
			}
        }
        else
        {
        	z:
        		printf("\a");
		}  
	}
	return 0;
}
