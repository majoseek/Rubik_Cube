#include<stdio.h>
#ifndef N
#define N 5
#endif

void print_down_up_wall(int arr[6][N][N],int up_down) //funkcja wypisuje sciane gorna albo dolna
{
    for(int w=0;w<N;w++)
    {
        putchar('\n');
        for(int i=0;i<N+1;i++)
            putchar(' ');
        for(int k=0;k<N;k++)
            printf("%d",arr[up_down][w][k]);


    }
}
void print_side_walls(int arr[6][N][N]) //funkcja wypisujaca sciany boczne
{
    for(int w=0;w<N;w++)
    {
        putchar('\n');
        for(int s=1;s<5;s++)
        {
            for(int k=0;k<N;k++)
            {
                printf("%d",arr[s][w][k]);
            }
            if(s!=4)
                putchar('|');
        }
    }
}
int get_wall(int c) //funkcja otrzymuje litere sciany i zwraca jej numer
{
    switch (c)
    {
    case 'u':
        return 0;
        break;
    case 'l':
        return 1;
        break;
    case 'f':
        return 2;
        break;
    case 'r':
        return 3;
        break;
    case 'b':
        return 4;
        break;
    case 'd':
        return 5;
        break;
    
    default:
        return -1;
        break;
    }
}
void rotate_front(int s,int cube[6][N][N])
{
       int exit_array[N][N];
       for(int w=0;w<N;w++)
            for(int k=0;k<N;k++)
            {
                exit_array[w][k]=cube[s][N-1-k][w];
            }

        for(int w=0;w<N;w++)
            for(int k=0;k<N;k++)
                cube[s][w][k]=exit_array[w][k];
}
void rotate(int wall,int layer,int cube[6][N][N])  //funkcja obracajaca kostke cube wzgledem sciany wall o layer warstw
{
    if(layer==-1)
        layer=1;

    int array_up[N][N];     //tablice pomocnicze do 
    int array_left[N][N];
    int array_right[N][N];
    int array_back[N][N];
    int array_down[N][N];
    int array_front[N][N];

    if(wall==0) //sciana gorna
    {
        
            for(int w=0;w<layer;w++)
                for(int k=0;k<N;k++)
                {
                    array_right[w][k]=cube[4][w][k];
                    array_front[w][k]=cube[3][w][k];
                    array_left[w][k]=cube[2][w][k];
                    array_back[w][k]=cube[1][w][k];
                }

            for(int w=0;w<layer;w++)
                for(int k=0;k<N;k++)
                {
                    cube[3][w][k]=array_right[w][k];
                    cube[2][w][k]=array_front[w][k];
                    cube[1][w][k]=array_left[w][k];
                    cube[4][w][k]=array_back[w][k];
                }
        
    }
    else if(wall==1)    //lewa sciana
    {
       
            for(int w=0;w<N;w++)
                for(int k=0;k<layer;k++)
                {
                    array_up[w][k]=cube[4][w][N-1-k];
                    array_front[w][k]=cube[0][w][k];
                    array_down[w][k]=cube[2][w][k];
                    array_back[w][N-1-k]=cube[5][w][k];
                }
        

            for(int w=0;w<N;w++)
                for(int k=0;k<layer;k++)
                {
                    cube[0][w][k]=array_up[w][k];
                    cube[2][w][k]=array_front[w][k];
                    cube[5][w][k]=array_down[w][k];
                    cube[4][w][N-1-k]=array_back[w][N-1-k];
                }
        
    }
    else if(wall==2)   //przednia sciana
    {
        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                array_right[w][k]=cube[0][N-1-k][w];
                array_left[w][N-1-k]=cube[5][k][w];
            }
        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
            {
                array_up[N-1-w][k]=cube[1][k][N-1-w];
                array_down[w][k]=cube[3][k][w];
            }

        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                cube[3][w][k]=array_right[w][k];
                cube[1][w][N-1-k]=array_left[w][N-1-k];
            }

        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
                {
                cube[0][N-1-w][k]=array_up[N-1-w][k];
                cube[5][w][k]=array_down[w][k];
            }
        
    }
    else if(wall==3)    //prawa sciana
    {
        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                array_up[N-w-1][N-1-k]=cube[2][w][N-1-k];
                array_back[N-w-1][k]=cube[0][N-1-w][N-1-k];
                array_down[w][N-k-1]=cube[4][w][k];
                array_front[N-w-1][N-1-k]=cube[5][w][N-k-1];
            }

        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                cube[0][N-w-1][N-1-k]=array_up[N-w-1][N-1-k];
                cube[4][N-w-1][k]=array_back[N-w-1][k];
                cube[5][w][N-k-1]=array_down[w][N-k-1];
                cube[2][N-w-1][N-1-k]=array_front[N-w-1][N-1-k];
            }    
    }
    else if(wall==4)    //tylnia sciana
    {
        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
                {
                    array_up[w][k]=cube[3][k][N-1-w];
                    array_down[w][k]=cube[1][k][w];
                }
        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                array_right[w][N-1-k]=cube[5][k][w];
                array_left[w][k]=cube[0][k][w];
            }

        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
            {
                cube[0][w][k]=array_up[w][k];
                cube[5][w][k]=array_down[w][k];
            }
        for(int w=0;w<N;w++)
            for(int k=0;k<layer;k++)
            {
                cube[3][w][N-1-k]=array_right[w][N-1-k];
                cube[1][w][k]=array_left[w][k];
            }
    }
    else if(wall==5)    //dolna sciana
    {
        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
            {
                array_front[N-1-w][k]=cube[1][N-1-w][k];
                array_right[N-1-w][k]=cube[2][N-1-w][k];
                array_back[N-1-w][k]=cube[3][N-1-w][k];
                array_left[N-1-w][k]=cube[4][N-1-w][k];
            }

        for(int w=0;w<layer;w++)
            for(int k=0;k<N;k++)
            {
                cube[2][N-1-w][k]=array_front[N-1-w][k];
                cube[3][N-1-w][k]=array_right[N-1-w][k];
                cube[4][N-1-w][k]=array_back[N-1-w][k];
                cube[1][N-1-w][k]=array_left[N-1-w][k];
            }
        
    }
    rotate_front(wall,cube);
}
void setup_cube(int cube[6][N][N])  //funkcja ustawiajaca kostke na poczatku
{
    for(int wall=0;wall<6;wall++)
    {
        for(int w=0;w<N;w++)
        {
            for(int k=0;k<N;k++)
            {
                cube[wall][w][k]=wall;
            }
        }
    }
}
void print_cube(int cube[6][N][N])  //funkcja drukujaca kostke
{
    print_down_up_wall(cube,0);
    print_side_walls(cube);
    print_down_up_wall(cube,5);
    putchar('\n');
}
int main()
{
    int cube[6][N][N];    //[NR_SCIANY][NR_WIERSZA][NR_KOLUMNY]

    setup_cube(cube);

    int input=getchar();
    int wall_to_rotate=-1,layer=-1,angle=1;  //angle=1 90 stopni angle=2 180 stopni angle=3 270 stopni(-90)

    while(input!=EOF && input!='.')
    {
        if(input=='u' || input=='l' || input=='f' || input=='r' || input=='b' || input=='d')
        {
            if(wall_to_rotate!=-1)
            {
                for(int i=0;i<angle;i++)
                    rotate(wall_to_rotate,layer,cube);

                angle=1;
                layer=-1;
            }
            wall_to_rotate=get_wall(input);
        }
        else if(input==39)  //apostrof
            angle=3;
        
        else if(input=='"')
            angle=2;

        else if(input>='0' && input<='9')
        {
            if(layer==-1)
                layer=input-'0';
            else
            {
                layer*=10;
                layer+=input-'0';
            }
        }
        if(input=='\n')
        {
            if(wall_to_rotate!=-1)
            {
                for(int i=0;i<angle;i++)
                    rotate(wall_to_rotate,layer,cube);
            }
            wall_to_rotate=-1;
            layer=-1;
            angle=1;
            print_cube(cube);
        }
        input=getchar();
    }
    return 0;
}