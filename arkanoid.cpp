#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cstdlib>
#include<graphics.h>
#define ESC 27
#define ENTER 13
#define line_length 12
#define line_rows 5
#define interval 3
#define half_width 320
#define frame_width_interval 20
#define frame_height_interval 50
#define margin 4
#define pauz 112


struct kl{
        int x;
        int y;
        int color;
    };

struct kl level_1[56]={
{11,55,GREEN},{67,55,RED},{123,55,GREEN},{179,55,RED},{235,55,YELLOW},{291,55,BLUE},{347,55,MAGENTA},{403,55,MAGENTA},{459,55,BLUE},{515,55,YELLOW},{571,55,RED},{627,55,GREEN},{683,55,RED},{739,55,GREEN},
{11,90,RED},{67,90,GREEN},{123,90,RED},{179,90,YELLOW},{235,90,BLUE},{291,90,MAGENTA},{347,90,GREEN},{403,90,GREEN},{459,90,MAGENTA},{515,90,BLUE},{571,90,YELLOW},{627,90,RED},{683,90,GREEN},{739,90,RED},
{11,125,GREEN},{67,125,RED},{123,125,YELLOW},{179,125,BLUE},{235,125,MAGENTA},{291,125,GREEN},{347,125,RED},{403,125,RED},{459,125,GREEN},{515,125,MAGENTA},{571,125,BLUE},{627,125,YELLOW},{683,125,RED},{739,125,GREEN},
{11,160,RED},{67,160,YELLOW},{123,160,BLUE},{179,160,MAGENTA},{235,160,GREEN},{291,160,RED},{347,160,GREEN},{403,160,GREEN},{459,160,RED},{515,160,GREEN},{571,160,MAGENTA},{627,160,BLUE},{683,160,YELLOW},{739,160,RED},
}, level_2[30]={
{67,55,MAGENTA},{179,55,RED},{291,55,BLUE},{459,55,BLUE},{571,55,RED},{683,55,MAGENTA},
{67,90,GREEN},{179,90,YELLOW},{291,90,MAGENTA},{459,90,MAGENTA},{571,90,YELLOW},{683,90,GREEN},
{67,125,YELLOW},{179,125,MAGENTA},{291,125,RED},{459,125,RED},{571,125,MAGENTA},{683,125,YELLOW},
{67,160,BLUE},{179,160,GREEN},{291,160,YELLOW},{459,160,YELLOW},{571,160,GREEN},{683,160,BLUE},
{67,195,RED},{179,195,BLUE},{291,195,GREEN},{459,195,GREEN},{571,195,BLUE},{683,195,RED},
}, level_3[42]={
{11,90,GREEN},{67,90,RED},{123,90,YELLOW},{179,90,BLUE},{235,90,MAGENTA},{291,90,GREEN},{347,90,RED},{403,90,RED},{459,90,GREEN},{515,90,MAGENTA},{571,90,BLUE},{627,90,YELLOW},{683,90,RED},{739,90,GREEN},
{11,160,RED},{67,160,YELLOW},{123,160,BLUE},{179,160,MAGENTA},{235,160,GREEN},{291,160,RED},{347,160,GREEN},{403,160,GREEN},{459,160,RED},{515,160,GREEN},{571,160,MAGENTA},{627,160,BLUE},{683,160,YELLOW},{739,160,RED},
{11,230,YELLOW},{67,230,BLUE},{123,230,MAGENTA},{179,230,GREEN},{235,230,RED},{291,230,GREEN},{347,230,YELLOW},{403,230,YELLOW},{459,230,GREEN},{515,230,RED},{571,230,GREEN},{627,230,MAGENTA},{683,230,BLUE},{739,230,YELLOW},
};



void open_graphics()
{
    initwindow(800,600); //otworzenie okna głównego

}

void frame1(){
     setcolor(WHITE) ;
        rectangle(0,0,800,600) ;
        rectangle(20,20,800-20,600-20) ;
        setfillstyle(SOLID_FILL,MAGENTA) ;
        floodfill(1,1,WHITE) ;
}

void arkanoid_intro() // intro na otwarcie gry
{
    int n=0;

    while(!kbhit())
    {
        frame1();
        setcolor(BLACK);
        settextstyle(0,0,1);
        for(int i=0; i<=5; i++)
            outtextxy(259+textwidth("Nacisnij ENTER aby kontynuowac: ")+i+textwidth(".")*(i+1)+2,230,".");
        settextstyle(1,0,7);
        setcolor(YELLOW);
        outtextxy(110,100,"ARKANOID");
        settextstyle(0,0,1);
        setcolor(LIGHTGREEN);
        settextstyle(0,0,1);
        outtextxy(250,230,"Nacisnij ENTER aby kontynuowac: ");
        for(int i=0; i<n; i++)
            outtextxy(250+textwidth("Nacisnij ENTER aby kontynowac: ")+i+textwidth(".")*(i+1)+2,230,"."); // kropkowanie w ramach czekania na wcisniecie enter
        n++;
        if(n>=5)
            n=0;
        delay(150);
    }

    cleardevice();
    settextstyle(0,0,1);
    setcolor(WHITE);
}

void menu(){
settextstyle(1,0,7);
setcolor(YELLOW);
outtextxy(110,100,"ARKANOID");
setcolor(YELLOW);
settextstyle(6,0,2);
outtextxy(300,200,"[N]owa gra");
outtextxy(300,250,"[Z]apisana gra");
outtextxy(300,300,"[R]ekordy");
outtextxy(300,350,"[F1] Pomoc");
outtextxy(300,400,"Wyjscie [ESC]");

}


void next_new_game(){
    frame1();
    settextstyle(1,0,7);
    setcolor(YELLOW);
    outtextxy(110,100,"ARKANOID");
    setcolor(YELLOW);
    settextstyle(6,0,2);
    outtextxy(225,200,"Wybierz poziom trudnosci");
    outtextxy(310,250,"[1] Latwy");
    outtextxy(310,300,"[2] Sredni");
    outtextxy(310,350,"[3] Trudny");
}

void records(){
struct{
    int liczba;
    char nazwa[20];
    } dane, dane_ranks[10];
FILE *ranks;
ranks = fopen("records.dat", "rb");
for(int i=0;i<10;i++){
    fread(&dane_ranks[i], sizeof(dane),1,ranks);
}
fclose(ranks);
cleardevice();
outtextxy(250,100,"Ranking");
char tekst[150];
tekst[150]=' ';
for(int i=0;i<10;i++){
    sprintf(tekst,"%d. %s\t%5d",i+1,dane_ranks[i].nazwa,dane_ranks[i].liczba);
    outtextxy(225,150+30*i,tekst);
}
outtextxy(150,450,"Wcisnij dowolny klawisz aby powrocic do menu");
getch();
cleardevice();
}

void instruction(int main_window) //instrukcja
{
    int help_window;
    initwindow(640,240);
    help_window = getcurrentwindow();
    setcolor(YELLOW);
    outtextxy(5,0,"Witamy w grze arkanoid");
    outtextxy(5,20,"INSTRUKCJA");
    outtextxy(5,40,"1. Celem gry jest niedopuszczenie do wydostania sie pileczki poza prostokat oraz odbijanie jej w taki");
    outtextxy(5,60,"sposob, aby zbic jak najwiecej klocków rozmieszczonych wewnatrz prostokata.");
    outtextxy(5,80,"2. Nacisnij Esc aby wyjsc z gry.");
    outtextxy(5,100,"3. Klawisze ktorymi poruszamy w grze to strzalka lewa,strzalka prawa.");
    outtextxy(5,120,"4. Gra posiada trzy poziomy.");
    outtextxy(5,140,"5.W lewym gornym rogu ukazany jest poziom oraz liczba zdobytych punktow");
    outtextxy(5,160,"Aby zamknac wcisnij dowolny klawisz");
    getch();

    closegraph(help_window);
    setcurrentwindow(main_window);
}


void escape_window(int main_window, unsigned char *key, int level, float x_ball, float y_ball, float move_x_ball, float move_y_ball, float x_pad, int points, int lives, int many_blocks, float move_k, float k){
int number_escape_window;
initwindow(350,100);
number_escape_window = getcurrentwindow();
outtextxy(5,5,"Czy chcesz zamknac gre?");
outtextxy(5,20,"[T]ak lub Nie[Y]"); // zapytanie o zamkniecie gry
if(level!=0)
    outtextxy(5,35,"Aby zapisac gre wcisnij Z"); // zapytanie czy chcesz zapisac
do{
    (*key)=getch();
if ((*key)=='t'||(*key)=='T')
    exit(0);

if(level!=0){
if((*key)=='z'||(*key)=='Z'){ //zapisanie gry do pliku
    FILE *zapisz;
    struct{
    int x;
    int y;
    int color;
    } dane;
    zapisz = fopen("zapis.dat", "w+b");
    setcurrentwindow(main_window);
    for(int i=0;i<5;i++){
        for(int j=0;j<14;j++){
                dane.x=11+56*j;
                dane.y=55+35*i;
                dane.color=getpixel(dane.x+25,dane.y+15);
                if(dane.color==WHITE)
                    dane.color=BLACK;
                fwrite(&dane, sizeof(dane),1,zapisz);
        }
    }
    setcurrentwindow(number_escape_window);
    fwrite(&x_ball,sizeof(float),1,zapisz);
    fwrite(&y_ball,sizeof(float),1,zapisz);
    fwrite(&move_x_ball,sizeof(float),1,zapisz);
    fwrite(&move_y_ball,sizeof(float),1,zapisz);
    fwrite(&x_pad,sizeof(float),1,zapisz);
    fwrite(&level,sizeof(int),1,zapisz);
    fwrite(&points,sizeof(int),1,zapisz);
    fwrite(&lives,sizeof(int),1,zapisz);
    fwrite(&many_blocks,sizeof(int),1,zapisz);
    fwrite(&move_k,sizeof(float),1,zapisz);
    fwrite(&k,sizeof(float),1,zapisz);
    fclose(zapisz);
    outtextxy(5,50,"Gra zapisana");
}
}
if((*key)=='y' || (*key)=='Y') {
    closegraph(number_escape_window);
    setcurrentwindow(main_window);
    }
}while((*key)!='y'&&(*key)!='Y');
}



void ksztalt(){
int tablica[20][20]={
{0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,2,2,3,3,2,2,1,1,0,0,0,0,0},
{0,0,0,0,1,2,2,2,3,4,4,3,2,2,2,1,0,0,0,0},
{0,0,0,1,2,2,2,3,4,4,4,4,3,2,2,2,1,0,0,0},
{0,0,1,2,2,2,3,4,4,4,4,4,4,3,2,2,2,1,0,0},
{0,1,2,2,2,3,4,4,4,4,4,4,4,4,3,2,2,2,1,0},
{0,1,2,2,3,4,5,5,5,5,5,5,5,5,4,3,2,2,1,0},
{1,2,2,3,4,4,5,6,7,7,7,7,6,5,4,4,3,2,2,1},
{1,2,3,4,4,4,5,7,6,7,7,6,7,5,4,4,4,3,2,1},
{1,3,4,4,4,4,5,7,7,6,6,7,7,5,4,4,4,4,3,1},
{1,3,4,4,4,4,5,7,7,6,6,7,7,5,4,4,4,4,3,1},
{1,2,3,4,4,4,5,7,6,7,7,6,7,5,4,4,4,3,2,1},
{1,2,2,3,4,4,5,6,7,7,7,7,6,5,4,4,3,2,2,1},
{0,1,2,2,3,4,5,5,5,5,5,5,5,5,4,3,2,2,1,0},
{0,1,2,2,2,3,4,4,4,4,4,4,4,4,3,2,2,2,1,0},
{0,0,1,2,2,2,3,4,4,4,4,4,4,3,2,2,2,1,0,0},
{0,0,0,1,2,2,2,3,4,4,4,4,3,2,2,2,1,0,0,0},
{0,0,0,0,1,2,2,2,3,4,4,3,2,2,2,1,0,0,0,0},
{0,0,0,0,0,1,1,2,2,3,3,2,2,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0}
};
for(int i=0;i<20;i++){
    for(int j=0;j<20;j++){
        if(tablica[i][j]==0)
            putpixel(300+i,450+j,BLACK);
        if(tablica[i][j]==1)
            putpixel(300+i,450+j,GREEN);
        if(tablica[i][j]==2)
            putpixel(300+i,450+j,WHITE);
        if(tablica[i][j]==3)
            putpixel(300+i,450+j,MAGENTA);
        if(tablica[i][j]==4)
            putpixel(300+i,450+j,YELLOW);
        if(tablica[i][j]==5)
            putpixel(300+i,450+j,CYAN);
        if(tablica[i][j]==6)
            putpixel(300+i,450+j,BROWN);
        if(tablica[i][j]==7)
            putpixel(300+i,450+j,RED);
    }
}

}


void belt(){
setcolor(MAGENTA);
setfillstyle(SOLID_FILL,MAGENTA);
int punkty[8]={0,0,800,0,800,45,0,45};
fillpoly(4, punkty);
} // pasek na informacje o stanie żyć oraz zdobytych punktów


void point(int points, char liczba_punktow[]){
sprintf(liczba_punktow,"%3d  ",points);
setcolor(YELLOW);

outtextxy(370,5,liczba_punktow);
setbkcolor(BLACK);
}


void frame(){
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
int points[16]={0,45,800,45,800,600,795,600,795,50,5,50,5,600,0,600};
fillpoly(8,points);
}

void lower_belt(){
setcolor(MAGENTA);
setfillstyle(SOLID_FILL,MAGENTA);
int points1[16]={5,582,795,582,800,600,5,600};
fillpoly(8,points1);
}





void draw_pad(float x_pad,int color)
{

    setcolor(color);
    setfillstyle(SOLID_FILL,color);
    rectangle(x_pad,560,x_pad+100,580);
    floodfill(x_pad+1,561,color);
}

void draw_ball(float x, float y, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    circle(x,y,4);
    floodfill(x,y,color);
    setcolor(BLACK);
    circle(x,y,5);
}

void draw_lives(int i){
int lives;
for(lives=0;lives<3;lives++){
    setfillstyle(SOLID_FILL,MAGENTA);
    floodfill(20+20*lives,20,MAGENTA);
}
for(lives=0;lives<i;lives++){
    draw_ball(20+20*lives,20,YELLOW);
}
}

void block(int x, int y, int color){
setcolor(color);
setfillstyle(SOLID_FILL, color);
rectangle(x, y, x+51, y+30);
floodfill(x+1, y+1, color);
}



void draw_blocks (struct kl b[], int N){
int i;
for(i=0;i<N;i++){
block(b[i].x, b[i].y, b[i].color);
}
}


void collision(float *x_ball, float *move_x_ball, float *y_ball, float *move_y_ball,int *points, int *number_blocks,float k, float x_pad, float move_k){
float alfa;
int kolor;

if((getpixel(((*x_ball)+6),(*y_ball))!=BLACK)&&(getpixel(((*x_ball)-6),(*y_ball))!=BLACK))
    (*move_y_ball)=-(*move_y_ball);
if((getpixel((*x_ball),((*y_ball)-6))!=BLACK)&&(getpixel((*x_ball),((*y_ball)+6))!=BLACK))
    (*move_x_ball)=-(*move_x_ball);
if(getpixel(((*x_ball)+6),(*y_ball))!=BLACK){
    kolor = getpixel((*x_ball+6), (*y_ball));
    if(kolor==GREEN){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)+6,(*y_ball),BLACK);
        (*points)=(*points)+5*k;
        (*number_blocks)--;
    }
    if(kolor==RED){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)+6,(*y_ball),BLACK);
        (*points)=(*points)+10*k;
        (*number_blocks)--;
    }
    if(kolor==YELLOW){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)+6,(*y_ball),BLACK);
        (*points)=(*points)+15*k;
        (*number_blocks)--;
    }
    if(kolor==BLUE){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball+6),(*y_ball),BLACK);
        (*points)=(*points)+20*k;
        (*number_blocks)--;
    }
    if(kolor==MAGENTA){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)+6,(*y_ball),BLACK);
        (*points)=(*points)+25*k;
        (*number_blocks)--;
    }

    if(kolor==WHITE){
        (*points)=(*points)-1;
    }

    (*x_ball)=(*x_ball)-(*move_x_ball);
    (*move_x_ball)=-(*move_x_ball);
}
if(getpixel(((*x_ball)-6),(*y_ball))!=BLACK){
    kolor=getpixel((*x_ball)-6, (*y_ball));
    if(kolor==GREEN){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)-6,(*y_ball),BLACK);
        (*points)=(*points)+5*k;
        (*number_blocks)--;
    }
    if(kolor==RED){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)-6,(*y_ball),BLACK);
        (*points)=(*points)+10*k;
        (*number_blocks)--;
    }
    if(kolor==YELLOW){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)-6,(*y_ball),BLACK);
        (*points)=(*points)+15*k;
        (*number_blocks)--;
    }
    if(kolor==BLUE){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)-6,(*y_ball),BLACK);
        (*points)=(*points)+20*k;
        (*number_blocks)--;
    }
    if(kolor==MAGENTA){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball)-6,(*y_ball),BLACK);
        (*points)=(*points)+25*k;
        (*number_blocks)--;
    }
    if(kolor==WHITE){
        (*points)=(*points)-1;
    }
    (*x_ball)=(*x_ball)-(*move_x_ball);
    (*move_x_ball)=-(*move_x_ball);
}
if(getpixel((*x_ball),((*y_ball)-6))!=BLACK){
    kolor=getpixel((*x_ball), (*y_ball)-6);
    if(kolor==GREEN){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)-6,BLACK);
        (*points)=(*points)+5*k;
        (*number_blocks)--;
    }
    if(kolor==RED){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)-6,BLACK);
        (*points)=(*points)+10*k;
        (*number_blocks)--;
    }
    if(kolor==YELLOW){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)-6,BLACK);
        (*points)=(*points)+15*k;
        (*number_blocks)--;
    }
    if(kolor==BLUE){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)-6,BLACK);
        (*points)=(*points)+20*k;
        (*number_blocks)--;
    }
    if(kolor==MAGENTA){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)-6,BLACK);
        (*points)=(*points)+25*k;
        (*number_blocks)--;
    }
    if(kolor==WHITE){
        (*points)=(*points)-1;
    }
    (*y_ball)=(*y_ball)-(*move_y_ball);
    (*move_y_ball)=-(*move_y_ball);
}
if(getpixel((*x_ball),((*y_ball)+6))!=BLACK){
    kolor=getpixel((*x_ball), (*y_ball)+6);
    if(kolor==GREEN){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)+6,BLACK);
        (*points)=(*points)+5*k;
        (*number_blocks)--;
    }
    if(kolor==RED){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)+6,BLACK);
        (*points)=(*points)+10*k;
        (*number_blocks)--;
    }
    if(kolor==YELLOW){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball+6),BLACK);
        (*points)=(*points)+15*k;
        (*number_blocks)--;
    }
    if(kolor==BLUE){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)+6,BLACK);
        (*points)=(*points)+20*k;
        (*number_blocks)--;
    }
    if(kolor==MAGENTA){
        setfillstyle(SOLID_FILL,BLACK);
        floodfill((*x_ball),(*y_ball)+6,BLACK);
        (*points)=(*points)+25*k;
        (*number_blocks)--;
    }
    if(kolor==WHITE){
        (*points)=(*points)-1;
    }
    (*y_ball)=(*y_ball)-(*move_y_ball);
    (*move_y_ball)=-(*move_y_ball);
    if(getpixel((*x_ball),((*y_ball)-(*move_y_ball)+6))==WHITE){
        alfa = -(((((*x_ball)-x_pad)/150.0)*160.0)+10);
        (*move_x_ball)=-(move_k)*cos(M_PI*(alfa/180.0));
        (*move_y_ball)=(move_k)*sin(M_PI*(alfa/180.0));
    }



}
}

int main()
{
    unsigned char key;
    int level,errorcode;
    int points,number_blocks,many_blocks;
    float x_pad, move_x_pad, now_x_pad;
    float x_ball,y_ball,now_x_ball,now_y_ball,move_x_ball,move_y_ball;
    float k,move_k;
    int main_window;
    int lives = 3;
    open_graphics();
    main_window = getcurrentwindow();
    arkanoid_intro();
    number_blocks = 0;
    move_k = 5.0;
    k = 1;
    points = 1;
    move_x_pad = 7;
    move_x_ball = 0;
    move_y_ball = 0;
    x_pad = 325;
    x_ball = 405;
    y_ball = 555;
    key = 1;
    char tab_points[8];

    many_blocks = 0;
    errorcode = graphresult();

if (errorcode!=grOk)
{
    printf("Blad BGI: %s\n",grapherrormsg(errorcode));
    printf("Wcisnij dowolny klawisz, zeby zakonczyc:");
    getch();
}

else{
menu:
menu();
level=0;
frame1();
do{
    if(kbhit()){
        key=getch();
    }
    if(key==0||key==224){
        key=getch();
        if(key==59)
            instruction(main_window);
    }
    if(key=='R'||key=='r'){
        records();
        key=1;
        goto menu;
    }
    if(key==ESC)
        escape_window(main_window,&key,level,x_ball,y_ball,move_x_ball,move_y_ball,x_pad,points,lives,many_blocks,move_k,k);
    if(key=='Z'||key=='z')
        goto gra_zapis;
    if(key=='N'||key=='n')
        goto gra_nowa;

}while(1);
gra_nowa:
cleardevice();
next_new_game();

do{ //petla wyboru poziomu
    if(kbhit())
        key=getch();
    if(key==49){
        move_k=4.0;
        k=0.8;
    }
    if(key==50){
        move_k=5.0;
        k=1;
    }
    if(key==51){
        move_k=6.0;
        k=1.2;
    }
    if(key==ESC)
        escape_window(main_window,&key,level,x_ball,y_ball,move_x_ball,move_y_ball,x_pad,points,lives,many_blocks,move_k,k);
    if(key==0||key==224){
        key=getch();
        if(key==59)
            instruction(main_window);
    }
}while (key!=49&&key!=50&&key!=51);
cleardevice();
many_blocks = 0;
level=0;
if(0){ //wczytujemy zapis gry
        gra_zapis:
        cleardevice();
        FILE *plik;
        struct{
        int x;
        int y;
        int kolor;
        } dane;
        plik=fopen("zapis.dat", "rb");
        int l=0;
        for(l=0;l<70;l++){
            fread(&dane, sizeof(dane),1,plik);
            block(dane.x,dane.y,dane.kolor);
        }
        fread(&x_ball,sizeof(float),1,plik);
        fread(&y_ball,sizeof(float),1,plik);
        fread(&move_x_ball,sizeof(float),1,plik);
        fread(&move_y_ball,sizeof(float),1,plik);
        fread(&x_pad,sizeof(float),1,plik);
        fread(&level,sizeof(int),1,plik);
        fread(&points,sizeof(int),1,plik);
        fread(&lives,sizeof(int),1,plik);
        fread(&many_blocks,sizeof(int),1,plik);
        fread(&move_k,sizeof(float),1,plik);
        fread(&k,sizeof(float),1,plik);
        fclose(plik);
}
belt();
lower_belt();
draw_lives(lives);
setcolor(YELLOW);
setbkcolor(MAGENTA);
settextstyle(6,0,1);
outtextxy(250, 5, "PUNKTY");
setbkcolor(BLACK);

    do
    {
        draw_pad(x_pad,WHITE);
        now_x_pad = x_pad;
        draw_ball(x_ball,y_ball,WHITE);
        now_x_ball = x_ball;
        now_y_ball = y_ball;
        point(points, tab_points);
        frame();
        if(many_blocks==0){
    level++;
    y_ball = 555;
    x_ball= x_pad +80;
    draw_ball(now_x_ball,now_y_ball,BLACK);
    draw_ball(x_ball,y_ball,WHITE);
    now_x_ball = x_ball;
    now_y_ball = y_ball;


    if(level==1){
        draw_blocks(level_1,56);
        many_blocks = 56;

    }
    if(level==2){
        draw_blocks(level_2,30);
        many_blocks = 30;

    }
    if(level==3){
        draw_blocks(level_3, 42);
        many_blocks = 42;
    }

        }
        collision(&x_ball, &move_x_ball, &y_ball, &move_y_ball, &points, &number_blocks, k, x_pad, move_k);
        x_ball = x_ball + move_x_ball;
        y_ball = y_ball + move_y_ball;

        if(y_ball >= 570) {
            lives --;
            delay(500);
            y_ball = 555;
            x_ball = x_pad+80;
            draw_ball(now_x_ball,now_y_ball,BLACK);
            draw_ball(x_ball,y_ball,WHITE);
            draw_pad(now_x_pad,BLACK);
            draw_pad(x_pad,WHITE);
        }

        if(kbhit())
            key = getch();

        switch(key)
        {
        case 224:
        case 0:
        {
            key = getch();
            if (key == 77)
            {
                x_pad = x_pad + move_x_pad;

                if (x_pad >= 644)
                    x_pad = 644;


            }
            if (key == 75)
            {
                x_pad = x_pad - move_x_pad;

                if (x_pad <= 6)
                    x_pad = 6;

            }

            if (key ==59)
                instruction(main_window);


        }
        default:
            break;
        }

if (key == ESC )
        escape_window(main_window,&key,level,x_ball,y_ball,move_x_ball,move_y_ball,x_pad,points,lives,many_blocks,move_k,k);

        delay(20);
draw_ball(now_x_ball,now_y_ball,BLACK);
draw_pad(now_x_pad,BLACK);

    }
    while(1);
}
}
