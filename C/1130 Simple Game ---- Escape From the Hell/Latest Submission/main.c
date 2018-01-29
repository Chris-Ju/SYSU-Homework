#include<stdio.h>
int game(char map[][16],int size,char move,int *x,int *y);
int whether(char map[][16],int x,int y);
void print(char map[][16],int size);
int last;
int main()
{
    int size;
    scanf("%d ",&size);
    char map[16][16];
    int i,j,x,y;
    for(i=0;i<size+2;i++)
        fgets(map[i],16,stdin);
    char move;
    for(i=0;i<size+2;i++)
    {
		for(j=0;j<size+2;j++)
        {
            if(map[i][j]=='A')
            {
                x=j;
                y=i;
                break;
            }
        }
        map[i][size+2]=0;
    }
    scanf(" %c",&move);
    while(game(map,size,move,&x,&y))
    {
        print(map,size); 
        if(scanf(" %c",&move)==EOF)
			break;
    }
    return 0;
}
int game(char map[][16],int size,char move,int *x,int *y)
{
    int value;
	if(last==-1)
    {
    	last=1;
    	return 1;    	
	}
    switch(move)
    {
        case 'a':
            value=whether(map,*x-1,*y);
            if(value!=0&&value!=3)
            {
                if(last!=1)
			        map[*y][*x]=' ';
                else
                	map[*y][*x]='@';
				*x-=1;
            }
           	if(last==1&&value!=0&&value==3)
            	map[*y][*x]='@';
            break;
        case 'd':
            value=whether(map,*x+1,*y);
            if(value!=0&&value!=3)
            {
                if(last!=1)
					map[*y][*x]=' ';
                else
                    map[*y][*x]='@';
                *x+=1;
            }
            if(last==1&&value!=0&&value==3)
            	map[*y][*x]='@';
            break;
        case 'w':
            value=whether(map,*x,*y-1);
            if(value!=0&&value!=3)
            {
                if(last!=1)
					map[*y][*x]=' ';
                else
                	map[*y][*x]='@';
                *y-=1;
            }
            if(last==1&&value!=0&&value==3)
            	map[*y][*x]='@';
            break;
        case 's':
            value=whether(map,*x,*y+1);
            if(value!=0&&value!=3)
            {
                if(last!=1)
			        map[*y][*x]=' ';
				else
					map[*y][*x]='@'; 
                *y+=1;
            }
            if(last==1&&value!=0&&value==3)
            	map[*y][*x]='@';
            break;
    }
	if(value==-1)
	{
		printf("Game Over!\n");
		return 0;	
	}
    else if(value==2)
        map[*y][*x]='A';
    else if(value==1)
    {
        map[*y][*x]='A';
        last=-1;
    }
    else if(value==3)
    {
    	if(last!=1)
			map[*y][*x]=' ';
		switch(move)
    	{
    		case 'a':
    			*x=size;
    			break;
    		case 'd':
    			*x=1;
    			break;
    		case 'w':
    			*y=size;
    			break;
    		case 's':
    			*y=1;
    			break;
		}
		value=whether(map,*x,*y);
		if(value==-1)
		{
			printf("Game Over!\n");
			return 0;	
		}
    	else if(value==2)
        	map[*y][*x]='A';
    	else if(value==1)
    	{
        	map[*y][*x]='A';
        	last=-1;
    	}
		else if(value==0)
		{
			switch(move)
    		{
    			case 'a':
    				*x=1;
    				break;
    			case 'd':
    				*x=size;
    				break;
    			case 'w':
    				*y=1;
    				break;
    			case 's':
    				*y=size;
    				break;
			}
            map[*y][*x]='A';
		}
	}
    else if(value==0)
        map[*y][*x]='A';
    if(value!=1)
        last=0;
}
int whether(char map[][16],int x,int y)
{
    if(map[y][x]=='$')
        return -1;
    else if(map[y][x]=='#')
        return 0;
    else if(map[y][x]=='@')
        return 1;
    else if(map[y][x]=='*')
        return 3;
    else
    	return 2;
}
void print(char map[][16],int size)
{
    int i;
    for(i=0;i<size+2;i++)
        printf("%s\n",map[i]);
}