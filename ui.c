#include<stdio.h>
int n;
void printMatrix(char outbox[n][n])
{
    int i,k,j;
	
	for(i=0;i<n;i++)
	{
		
	}
    printf("%c",201);
    for(i=0;i<n;i++)
    	{
		printf("%c%c%c%c",205,205,205,203);
		}
	printf("\b%c\n",187);
    
    
	for (i = 0; i < n; i++)
    {
    	if (i>0)
		{
        	printf("%c",204);
    		for(k=0;k<n;k++)
    		{
				printf("%c%c%c%c",205,205,205,206);
			}
			printf("\b%c\n",185);
		}
        for (j = 0; j < n; j++)
        {
            printf("%c %c ",186,outbox[i][j]);
        }
        printf("%c\n",186);
    }
    
	//LAST LINE
    printf("%c",200);
    for(i=0;i<n;i++)
    	{
		printf("%c%c%c%c",205,205,205,202);
		}
	printf("\b%c\n",188);
}

void main()
{
	printf("n = ");
	scanf("%d",&n);
	char outbox[n][n];
	int x,y;
	for(x=0;x<n;x++)
	{
		for(y=0;y<n;y++)
		{
			outbox[x][y]=254;
		}
	}
	printMatrix(outbox);
}

