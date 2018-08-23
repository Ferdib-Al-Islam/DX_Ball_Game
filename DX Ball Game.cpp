#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#define l_len 200

int l_left,l_right,by,ax,b_cx,b_cy,b_r=10,score=0,acc=3,s=0,tm=0;

void sco()
{
    setcolor(WHITE);
    settextstyle(1,4,1);
    char m[30];
    sprintf(m,"Score : %d    Life : %d",++score,acc);
    outtextxy(ax/2,by+7,m);
    tm=0;
}


int drow_l() /// for paddle drawing
{
    setcolor(RED);
    rectangle(l_left,by-10,l_right,by-70);
    setfillstyle(SOLID_FILL,RED);
    floodfill(l_left+1,by-11,RED);
}

int drow_l_clr() /// for paddle drawing
{
    setcolor(BLACK);
    rectangle(l_left,by-10,l_right,by-70);
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(l_left+1,by-11,BLACK);
}

int drawbrick(int lx, int ly)
{
    rectangle(lx,ly,lx+31,ly+9) ;
    rectangle(lx+2,ly-2,lx+31-2,ly+9-2);
}
int bricks()
{
    int i, j, lx=0, ly=0;

    for(i=0; i<5; i++)
    {
        for(j=0; j<20; j++)
        {
            drawbrick(lx, ly) ;
            lx=lx+32;
        }
        lx=0;
        ly=ly+10;
    }
}

int check_accd(int x,int y)
{
    if(y > by-70) if (x+10<l_left || x-10 >l_right)
        {
            acc--;
            s=1;
        }
    if(!acc) exit(0);
}
int drow_crl(int x,int y)
{

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(x, y, 10);
    floodfill(x, y, RED);
}
int cclear(int x, int y) /// for clearing circle
{
    setcolor(BLACK);
    circle(x, y, 10);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(x, y, BLACK);
    return 0;
}
int key() /// for paddle controlling
{
    char ch=getch();
    switch(ch)
    {
    case 27:
        exit(0);
        break;
    case 77:
        if(l_right+l_len>=ax) break;
        l_left+=l_len;
        l_right+=l_len;
        break;
    case 75:
        if(l_left-l_len<=0)
        {
            l_left=0;
            l_right=l_len;
        }
        else
        {
            l_left-=l_len;
            l_right-=l_len;
        }
        break;
    }
}
int main()
{
    int gd=DETECT, gm=DETECT;
    int x, y=0, j, t=400, c=1, i,aa,bb;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bricks();
    ax=getmaxx();
    by=getmaxy();
    aa=ax/2;
    bb=by/2;

level:
    l_left=0;
    l_right=l_len;
    for(x=60; x < 602; x++)   //cleardevice();
    {
        drow_crl(x,y);
        drow_l();
        delay(40);
        tm++;
        cclear(x,y);
        drow_l_clr();
        if(y >= 400)
        {
            c=0;
            t -= 1;
        }
        if(y<=(400-t)) c=1;
        y=y+(c?15 : -15);
        {

            if(kbhit()) key();
            check_accd(x,y);
            if(tm==25) sco();
            if(s)
            {
                s=0;
                getch();
                goto level;
            }
        }
    }
        getch();
}

