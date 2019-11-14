#include<stdio.h>

#ifndef N
#define N 5
#endif
#define UP 0
#define LEFT 1
#define FRONT 2
#define RIGHT 3
#define BACK 4
#define DOWN 5
#define NONE -1
#define ANGLE_90 1
#define ANGLE_180 2
#define ANGLE_270 3


void print_down_up_wall(int cube[6][N][N],int up_down) //Funkcja drukujaca sciane gorna lub dolna
{
    for(int w=0;w<N;w++)
    {
        putchar('\n');
        for(int i=0;i<N+1;i++)
            putchar(' ');
        for(int k=0;k<N;k++)
            printf("%d",cube[up_down][w][k]);
    }
}
void print_side_walls(int cube[6][N][N]) //Funkcja drukujaca sciany boczne
{
    for(int w=0;w<N;w++)
    {
        putchar('\n');
        for(int s=LEFT;s<DOWN;s++)
        {
            for(int k=0;k<N;k++)
            {
                printf("%d",cube[s][w][k]);
            }
            if(s!=BACK)
                putchar('|');
        }
    }
}
int get_wall(int c) //Fukcja ktora dla zadanej litery sciany zwraca jej numer
{
    switch (c)
    {
    case 'u':
        return UP;
        break;
    case 'l':
        return LEFT;
        break;
    case 'f':
        return FRONT;
        break;
    case 'r':
        return RIGHT;
        break;
    case 'b':
        return BACK;
        break;
    case 'd':
        return DOWN;
        break;
    
    default:
        return NONE;
        break;
    }
}
void turn_front(int wall,int cube[6][N][N])
{
    /*
    Funkcja obraca kolory na scianie na ktora patrzymy
    W pomocniczej tablicy (exit_array) przypisywane jest wyjsciowe ustawienie sciany po obrocie,
    po czym sciana kostki na ktora aktualnie patrzymy zostaje nadpisana ta tablica
    */

   int exit_array[N][N];

   for(int w=0;w<N;w++)
        for(int k=0;k<N;k++)
            exit_array[w][k]=cube[wall][N-1-k][w];

    for(int w=0;w<N;w++)
        for(int k=0;k<N;k++)
            cube[wall][w][k]=exit_array[w][k];

}
void rotate_up(int cube[6][N][N],int layer,int wall_right[N][N],int wall_front[N][N],int wall_left[N][N],int wall_back[N][N])
{
    /*
    Funkcja ktora obraca sciane gorna o 90 stopni i layer warstw.
    */

    for(int w=0;w<layer;w++)
        for(int k=0;k<N;k++)
        {
            wall_right[w][k]=cube[BACK][w][k];
            wall_front[w][k]=cube[RIGHT][w][k];
            wall_left[w][k]=cube[FRONT][w][k];
            wall_back[w][k]=cube[LEFT][w][k];
        }

    for(int w=0;w<layer;w++)
        for(int k=0;k<N;k++)
        {
            cube[RIGHT][w][k]=wall_right[w][k];
            cube[FRONT][w][k]=wall_front[w][k];
            cube[LEFT][w][k]=wall_left[w][k];
            cube[BACK][w][k]=wall_back[w][k];
        }
}
void rotate_left(int cube[6][N][N],int layer,int wall_up[N][N],int wall_front[N][N],int wall_down[N][N],int wall_back[N][N])
{
    /*
    Funkcja ktora obraca sciane lewa o 90 stopni i layer warstw
    */

    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            wall_up[w][k]=cube[BACK][N-w-1][N-1-k];
            wall_front[w][k]=cube[UP][w][k];
            wall_down[w][k]=cube[FRONT][w][k];
            wall_back[w][N-1-k]=cube[DOWN][N-w-1][k];
        }
        
    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            cube[UP][w][k]=wall_up[w][k];
            cube[FRONT][w][k]=wall_front[w][k];
            cube[DOWN][w][k]=wall_down[w][k];
            cube[BACK][w][N-k-1]=wall_back[w][N-k-1];
        }
}
void rotate_front(int cube[6][N][N],int layer,int wall_up[N][N],int wall_right[N][N],int wall_down[N][N],int wall_left[N][N])
{
    /*
    Funkcja ktora obraca sciane przednia o 90 stopni i layer warstw
    */

    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            wall_up[N-k-1][w]=cube[LEFT][N-w-1][N-k-1];
            wall_right[w][k]=cube[UP][N-k-1][w];
            wall_down[k][w]=cube[RIGHT][N-w-1][k];
            wall_left[w][N-k-1]=cube[DOWN][k][w];
        }
        
    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            cube[UP][N-k-1][w]=wall_up[N-k-1][w];
            cube[RIGHT][w][k]=wall_right[w][k];
            cube[DOWN][k][w]=wall_down[k][w];
            cube[LEFT][w][N-k-1]=wall_left[w][N-k-1];
        }
}
void rotate_right(int cube[6][N][N],int layer,int wall_up[N][N],int wall_back[N][N],int wall_down[N][N],int wall_front[N][N])
{
    /*
    Funkcja ktora obraca sciane prawa o 90 stopni i layer warstw
    */

    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            wall_up[w][N-1-k]=cube[FRONT][w][N-1-k];
            wall_back[N-w-1][k]=cube[UP][w][N-1-k];
            wall_down[N-w-1][N-k-1]=cube[BACK][w][k];
            wall_front[w][N-1-k]=cube[DOWN][w][N-k-1];
        }

    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            cube[UP][w][N-1-k]=wall_up[w][N-1-k];
            cube[BACK][N-w-1][k]=wall_back[N-w-1][k];
            cube[DOWN][N-w-1][N-k-1]=wall_down[N-w-1][N-k-1];
            cube[FRONT][w][N-1-k]=wall_front[w][N-1-k];
        }
}
void rotate_back(int cube[6][N][N],int layer,int wall_up[N][N],int wall_right[N][N],int wall_down[N][N],int wall_left[N][N])
{
    /*
    Funkcja ktora obraca tylnia gorna o 90 stopni i layer warstw
    */

    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            wall_up[k][w]=cube[RIGHT][w][N-k-1];
            wall_right[w][N-k-1]=cube[DOWN][N-k-1][N-w-1];
            wall_down[N-k-1][N-w-1]=cube[LEFT][N-w-1][k];
            wall_left[w][k]=cube[UP][k][N-w-1];
        }
            
    for(int w=0;w<N;w++)
        for(int k=0;k<layer;k++)
        {
            cube[UP][k][w]=wall_up[k][w];
            cube[RIGHT][w][N-k-1]=wall_right[w][N-k-1];
            cube[DOWN][N-k-1][N-w-1]=wall_down[N-k-1][N-w-1];
            cube[LEFT][w][k]=wall_left[w][k];
        }
}
void rotate_down(int cube[6][N][N],int layer,int wall_left[N][N],int wall_back[N][N],int wall_right[N][N],int wall_front[N][N])
{
    /*
    Funkcja ktora obraca sciane dolna o 90 stopni i layer warstw
    */

    for(int w=0;w<layer;w++)
        for(int k=0;k<N;k++)
        {
            wall_front[N-1-w][k]=cube[LEFT][N-1-w][k];
            wall_right[N-1-w][k]=cube[FRONT][N-1-w][k];
            wall_back[N-1-w][k]=cube[RIGHT][N-1-w][k];
            wall_left[N-1-w][k]=cube[BACK][N-1-w][k];
        }

    for(int w=0;w<layer;w++)
        for(int k=0;k<N;k++)
        {
            cube[FRONT][N-1-w][k]=wall_front[N-1-w][k];
            cube[RIGHT][N-1-w][k]=wall_right[N-1-w][k];
            cube[BACK][N-1-w][k]=wall_back[N-1-w][k];
            cube[LEFT][N-1-w][k]=wall_left[N-1-w][k];
        }
}
void rotate_wall(int wall,int layer,int cube[6][N][N])
{
    /*
    Funkcja obracajaca kostka wzgledem danej sciany wall o layer warstw o 90 stopni
    W tablicach pomocniczych wall_up, wall_left, wall_right, wall_back, wall_down oraz wall_front
    sa ustawiane nowe wartosci sciany po obrocie
    Po obrocie danej sciany program przepisuje wartosci do kostki wyjsciowej (cube)
    Na koniec funkcja obraca rowniez sciane wzgledem ktorej wykonywalismy obrot (wall)
    */

    if(layer==-1)   //Jesli warstwa nie jest ustawiona funkcja obraca sciane o 1 warstwe
        layer=1;

    int wall_up[N][N];
    int wall_left[N][N];
    int wall_right[N][N];
    int wall_back[N][N];
    int wall_down[N][N];
    int wall_front[N][N];

    if(wall==UP)
        rotate_up(cube,layer,wall_right,wall_front,wall_left,wall_back);
    else if(wall==LEFT)
        rotate_left(cube,layer,wall_up,wall_front,wall_down,wall_back);
    else if(wall==FRONT)
        rotate_front(cube,layer,wall_up,wall_right,wall_down,wall_left);
    else if(wall==RIGHT)
        rotate_right(cube,layer,wall_up,wall_back,wall_down,wall_front);
    else if(wall==BACK)
        rotate_back(cube,layer,wall_up,wall_right,wall_down,wall_left);
    else if(wall==DOWN)
        rotate_down(cube,layer,wall_left,wall_back,wall_right,wall_front);


    turn_front(wall,cube);
}
void setup_cube(int cube[6][N][N])  //Funkcja ustawiajaca kostke na poczatku
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
void print_cube(int cube[6][N][N])  //Funkcja drukujaca kostke
{
    print_down_up_wall(cube,UP);
    print_side_walls(cube);
    print_down_up_wall(cube,DOWN);
    putchar('\n');
}
void manage_input(int input, int *wall_to_rotate, int *angle, int *layer, int cube[6][N][N])
{
    /*
    Funkcja zarzadzajaca wejsciem dla danego inputu, sciany, kata oraz ilosci warstw.
    Gdy uzytkownik wczyta litere sciany, to jeśli sciana do obrotu jest juz ustawiona, to funkcja wykonuje obrot
    oraz pobiera nowy numer sciany.
    Po kazdym obrocie sciany lub wydruku kostki wszystkie wyzej wspomniane parametry przyjmuja wartosci startowe.
    Gdy uzytkownik wczyta apostrof lub cudzyslow funkcja ustawia nowy kat obrotu sciany.
    Gdy uzytkownik wczyta cyfre, to jeśli ilosc warstw jest juz ustawiona to zwieksza jej rzad wielkosci i dodaje do niej
    nowo wczytana cyfre, w przeciwnym wypadku ustawia ilosc warstw na nowo wczytana cyfre.
    Gdy uzytkownik wczyta znak nowej linii funkcja sprawdza, czy kostki nie nalezy obrocic (jesli tak, to ja obraca),
    po czym ustawia wszystkie parametry na startowe i drukuje kostke.
    */

    if(input=='u' || input=='l' || input=='f' || input=='r' || input=='b' || input=='d')
        {
            if(*wall_to_rotate!=NONE)
            {
                for(int i=0;i<*angle;i++)
                    rotate_wall(*wall_to_rotate,*layer,cube);

                *angle=ANGLE_90;
                *layer=NONE;
            }
            *wall_to_rotate=get_wall(input);
        }
        else if(input=='\'')
            *angle=ANGLE_270;
        
        else if(input=='"')
            *angle=ANGLE_180;

        else if(input>='0' && input<='9')
        {
            if(*layer==NONE)
                *layer=input-'0';
            else
            {
                *layer*=10;
                *layer+=input-'0';
            }
        }
        if(input=='\n')
        {
            if(*wall_to_rotate!=NONE)
            {
                for(int i=0;i<*angle;i++)
                    rotate_wall(*wall_to_rotate,*layer,cube);
            }
            *wall_to_rotate=NONE;
            *layer=NONE;
            *angle=ANGLE_90;
            print_cube(cube);
        }
}
int main()
{

    int cube[6][N][N];    //Tablica 3-wymiarowa przechowujaca kostke. [NR_SCIANY][NR_WIERSZA][NR_KOLUMNY]
    setup_cube(cube);

    int wall_to_rotate=NONE;
    int layer=NONE;
    int angle=ANGLE_90;

    /*
    wall_to_rotate to sciana, wzgledem ktorej kostka ma byc obrocona (domyslnie nie wskazuje na zadna sciane)
    layer to ilosc warstw, ktore beda przekrecone przy obrocie sciany kostki
    angle to kat o jaki dana sciana ma byc obrocona
    */

    int input=getchar();
    while(input!=EOF && input!='.')
    {
        manage_input(input,&wall_to_rotate,&angle,&layer,cube);
        input=getchar();
    }
    return 0;
}