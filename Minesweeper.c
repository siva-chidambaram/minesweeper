#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int flags_left;
int count_mine(int** minefield,int row,int column,int size)
{
    int i, j, count = 0, row_start = row-1, column_start = column-1, row_end = row+2, column_end = column+2;
    for(i=row_start;i<row_end;i++)
    {
        for(j=column_start;j<column_end;j++)
        {
            if(minefield[i][j]==-1)
            {
                count++;
            }
        }
    }
    return count;
}
int** gen_mines(int size, int level)
{
    int **mine,num_mines = (size-5)*level ,i,j,size1=(size-2)*(size-2);
    mine=(int**)malloc(size*sizeof(int*));
    for(i=0;i<size;i++){
        mine[i]=(int*)malloc(size*sizeof(int));
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            mine[i][j]=0;
        }
    }
    int ref[size1];
    for(i=0;i<size1;i++)
    {
        ref[i]=0;
    }
    int rand_num;
    srand(time(0));
    for(i=0;i<num_mines;)
    {
        rand_num = rand()%size1;
        if(ref[rand_num]==0)
        {
            mine[(rand_num/(size-2))+1][(rand_num%(size-2))+1]=-1;
            i++;
            ref[rand_num]=1;
        }
    }
    return mine;
}
int** gen_minefield(int size, int level)
{
    int i,j;
    int **minefield = gen_mines(size, level);
    for(i=1;i<size-1;i++)
    {
        for(j=1;j<size-1;j++)
        {
            if(minefield[i][j]==0)
            {
                minefield[i][j]=count_mine(minefield,i,j,size);
            }
        }
    }
    return minefield;
}
void top_border(int size)
{
	int i;
	printf("\t\t\t\t");
	printf("%c",218);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0)
		{
			printf("%c",194);
		}
	}
	printf("%c%c\n",196,191);
}
void mid_border(int size)
{
	int i;
	printf("\n\t\t\t\t%c",195);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0)
		{
			printf("%c",197);
		}
	}
	printf("%c%c",196,180);
}
void bottom_border(int size)
{
	int i;
	printf("\t\t\t\t");
	printf("%c",192);
	for(i=1;i<(size-2)*3;i++)
	{
		printf("%c",196);
		if(i%3==0){
			printf("%c",193);
		}
	}
	printf("%c%c",196,217);
}
void display_minefield(int x, int y, int size, int** minefield, int ref_matrix[size][size])
{
    int i,j;
    printf("\n");
    top_border(size);
    for(i=1;i<size-1;i++)
    {
        printf("\t\t\t\t");
        printf("%c",179);
        for(j=1;j<size-1;j++)
        {
        	if(i == x && j == y)
        	{
        		printf(" + ");
			}
			else if(ref_matrix[i][j]==-1)
       	    {
       	    	printf(" F ");
			}
			else if(ref_matrix[i][j]==0)
       	    {
				if(minefield[i][j]==0)
				{
       	 	printf("   ");
				}
				else
				{
       	    		printf(" %d ", minefield[i][j]);
				}
			}
			else
			{
				printf(" %c ",254);
			}
			printf("%c",179);	    
        }
        if(i<size-2)
        {
        	mid_border(size);
        }
        printf("\n");
    }
    bottom_border(size);
}
void get_input(int size, int* x,int* y,char* choice, int** minefield, int ref_matrix[size][size])
{
	int key,key1;
	char cell_status[][20] = {"FLAGGED", "OPEN", "CLOSED"};
	while(1)
	{
		z1:
		system("cls");
		display_minefield(*x, *y, size, minefield , ref_matrix);
		printf("\n\n\t\t\t\t\tThe Cell you are at is %s", cell_status[ref_matrix[*x][*y]+1]);
		printf("\n\n\t\t\t\t\tYou have %d flags remaining", flags_left);
		printf("\n\n\t\t\t\t\t    Use arrow keys to move\n\n\t\t\t\tUse 'f' to flag or unflag cells and 'o' to open cells");
		key=getch();
		if(key == 111 || key == 102)
		{
			*choice = (char)key;
			break;
		}
		else if(key != 224)
		{
			printf("\a");
			goto z1;
		}
		key1=0;
		key1=getch();
		switch(key1)
		{
			case 72:
			{
				if(*x>1)
				{
					*x-=1;
				}
				else
				{
            	    goto z;
				}
				break;
			}
			case 80:
			{
				if(*x<size-2)
				{
					*x+=1;
				}
				else
				{
            	    goto z;
				}
				break;
			}
			case 75:
			{
				if(*y>1)
				{
					*y-=1;
				}
				else
				{
                	goto z;
				}
				break;
			}
			case 77:
			{
				if(*y<size-2)
				{
					*y+=1;
				}
				else
				{
        	        goto z;
				}
				break;
			}
			default :
			{
				z:
					printf("\a\n");
				break;
			}
		}
	}
}
void game_over(int size, int** minefield, int ref_matrix[size][size])
{
	int i,j;
	printf("\n");
	top_border(size);
	for(i=1;i<size-1;i++)
	{
		printf("\t\t\t\t");
		printf("%c",179);
		for(j=1;j<size-1;j++)
		{
			if(ref_matrix[i][j] == 0)
			{
				if(minefield[i][j]==0)
				{
					printf("   ");
				}
				else
				{
					printf(" %d ",minefield[i][j]);
				}
			}
			else if(minefield[i][j] == -1)
			{
				printf(" B ");
			}
			else if(ref_matrix[i][j] == -1 && minefield[i][j] != -1)
			{
				printf(" X ");
			}
			else
			{
				printf(" %c ", 254);
			}
			printf("%c", 179);
		}
		if(i<size-2)
		{
			mid_border(size);
		}
		printf("\n");
	}
	bottom_border(size);
	printf("\n\n\t\t\t\t\t\tGAME OVER\n\n");
}
void open_cell(int* cell)
{
	*cell = 0;
}
void open(int x,int y, int size, int** minefield, int ref_matrix[size][size])
{
    if(ref_matrix[x][y]!=0 && ref_matrix[x][y] != -2 && minefield[x][y] != -1)
    {
    	if(ref_matrix[x][y] == -1)
    	{
    		flags_left++;
		}
        if(minefield[x][y] != 0)
        {
        	open_cell(&ref_matrix[x][y]);
		}
		else
		{
			open_cell(&ref_matrix[x][y]);
			int x1=x-1,x2=x+2,y1=y-1,y2=y+2,i,j;
	        for(i=x1;i<x2;i++)
    	    {
        	    for(j=y1;j<y2;j++)
            	{
                    open(i,j,size,minefield,ref_matrix);
            	}
        	}
    	}
	}
}
int check_mines(int size, int ref_matrix[size][size],int mines)
{
	int count=0,i,j;
	for(i=1;i<size-1;i++)
	{
		for(j=1;j<size-1;j++)
		{
			if(ref_matrix[i][j] == 1 || ref_matrix[i][j] == -1)
			{
				count++;
			}
		}
	}
	if(count == mines)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int size, level, i, j, mines, x, y;
	char choice;
	printf("GRID Sizes\n 1 - 8 x 8 \n 2 - 12 x 12 \n 3 - 16 x 16 \n\nEnter Grid Size : ");
	scanf("%d",&size);
	system("cls");
	printf("DIFFICULTY\n 1 - Beginner \n 2 - Intermediate \n 3 - Expert \n\nEnter Difficulty : ");
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
