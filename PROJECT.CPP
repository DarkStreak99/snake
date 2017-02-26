 // HEADER FILES
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include <string.h>
#include <time.h>

 // USER DEFINED CONSTANTS
#define maxx 500
#define maxy 400
#define MAX_BODYSIZE 200
#define BODY_SECTION_SIZE 5
#define BODY_WIDTH_SIZE 5
#define STEP_SIZE 5
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


int tx=98, ty=100, x, y, score=0, i, bodyLength=4;
int body[MAX_BODYSIZE][2] = {{40,10},{30,10},{20,10},{10,10}};
int direction = RIGHT , poly[6];
char sc[3], ch;

 // FUNCTION TO DRAW TARGET
void drawTarget()
{
   int nx, ny;
   x=body[0][0];
   y=body[0][1];
   randomize();

   if(body[0][0] == body[1][0])
    {
	// VERTICAL MOVEMENT

	if(((tx-3 <= x-BODY_WIDTH_SIZE/2 && tx+3 >= x-BODY_WIDTH_SIZE/2) ||
	   (tx-3 <= x+BODY_WIDTH_SIZE/2 && tx+3 >= x+BODY_WIDTH_SIZE/2))
	    && (y>ty-3 && y< ty+3) )
	{

	  sound(200);
	  delay(40);
	  nosound();
	  cleardevice();
	  tx = 5 + random(maxx-5);
	  randomize();
	  ty = 5 + random(maxy-5);
	  score = score + 10;
	  if(bodyLength != MAX_BODYSIZE)
	      bodyLength++;

	}
    }

    else
    {
	// HORIZONTAL MOVEMENT

	if(((ty-3 <= y-BODY_WIDTH_SIZE/2 && ty+3 >= y-BODY_WIDTH_SIZE/2) ||
	   (ty-3 <= y+BODY_WIDTH_SIZE/2 && ty+3 >= y+BODY_WIDTH_SIZE/2))
	    && (x-3<=tx && x+3>=tx))
	{

	   sound(200);
	   delay(40);
	   nosound();
	   cleardevice();
	   tx = 5 + random(maxx-5);
	   randomize();
	   ty = 5 + random(maxy-5);
	   score = score + 10;
	   if(bodyLength != MAX_BODYSIZE)
		bodyLength++;
	}

    }

   setcolor(RED);
   outtextxy(tx, ty, "*");

}

 // FUNCTION TO DRAW BORDER
void drawBorder()

{

   setfillstyle (INTERLEAVE_FILL , BLUE);
   bar(0,0,maxx+5,5);
   bar(0,0,5,maxy+5);
   bar(0,maxy+5,maxx+5,maxy+10);
   bar(maxx+5,0,maxx+10,maxy+10);

}

 // FUNCTION TO DISPLAY INSTRUCTIONS
void instructions()

{

   setcolor(CYAN);
   outtextxy(maxx+30,70,"INSTRUCTIONS:");
   outtextxy(maxx+25,100,"UP");
   outtextxy(maxx+70,100," ^ ");
   outtextxy(maxx+70,105," | ");
   outtextxy(maxx+25,120,"DOWN");
   outtextxy(maxx+70,120," | ");
   outtextxy(maxx+70,125," v ");
   outtextxy(maxx+25,140,"LEFT");
   outtextxy(maxx+70,140," <- ");
   outtextxy(maxx+25,160,"RIGHT");
   outtextxy(maxx+70,160," -> ");
   itoa(score,sc,10);
   outtextxy(maxx+25,250,"Score");
   outtextxy(maxx+70,250,sc);

}

 // FUNCTION TO DISPLAY THE MAINPAGE
void mainpage()

{

  drawBorder();
  setcolor(WHITE);
  settextstyle (GOTHIC_FONT, HORIZ_DIR, 5);
  outtextxy(120,130,"SNAKE GAME");
  settextstyle (DEFAULT_FONT, HORIZ_DIR, 0);
  setcolor(RED);
  line(115,185,410,185);
  setcolor(RED);
  line(115,125,410,125);

}

 // FUNCTION TO DRAW THE SNAKE
void drawSnake()

{
      // HEAD

   setcolor(GREEN);

   switch(direction)

   {
       case RIGHT: poly[0] = body[0][0] + 5;
		   poly[1] = body[0][1];

		   break;

       case UP   : poly[0] = body[0][0];
		   poly[1] = body[0][1] - 5;

		   break;

       case DOWN : poly[0] = body[0][0];
		   poly[1] = body[0][1] + 5;

		   break;

       case LEFT : poly[0] = body[0][0] - 5;
		   poly[1] = body[0][1];

		   break;

   }

    poly[2] = body[0][0] - BODY_WIDTH_SIZE/2;
    poly[3] = body[0][1] - BODY_WIDTH_SIZE/2;

    poly[4] = body[0][0] + BODY_WIDTH_SIZE/2;
    poly[5] = body[0][1] + BODY_WIDTH_SIZE/2;

    setfillstyle (SOLID_FILL, GREEN);
    fillpoly(3, poly);

     // REMAINING BODY

   for(int i=0;i<bodyLength-1;i++)
   {
       if(body[i][0] == body[i+1][0])
	  bar(body[i][0]-BODY_WIDTH_SIZE/2,body[i][1],body[i+1][0]+BODY_WIDTH_SIZE/2, body[i+1][1]);

       else
	  bar(body[i][0],body[i][1]-BODY_WIDTH_SIZE/2,body[i+1][0], body[i+1][1]+BODY_WIDTH_SIZE/2);

   }

}

 // FUNCTION TO END GAME
void game_over()

{
   settextstyle (GOTHIC_FONT, HORIZ_DIR, 4);
   outtextxy(120,120,"GAME OVER");
   cout<<"\a";
   itoa(score,sc,10);
   outtextxy(130,200,"Score");
   outtextxy(250,200,sc);
   getch();
   exit(0);

}

 // MAIN FUNCTION
void main()

{
   clrscr();
   int gd = DETECT, gm;

   initgraph(&gd,&gm,"C:\\tc\\BGI");
   if(graphresult()!=0)

   {
       gotoxy(10,10);
       cout<<"Graphics error\n"<<grapherrormsg(graphresult());
       gotoxy(20,10);
       cout<<"Press any key to halt\n";
       getch();
       exit(1);

   }

   cleardevice();

    // MAIN PAGE
   mainpage();
   getch();
   cleardevice();

   while(1)

   {
      if(kbhit())

      {

	 // UPDATE DIRECTION

	 ch = getch();
	 switch(ch)

	{

		case 72: if(direction!=DOWN)
			    direction=UP;
			  break;

		case 80: if(direction!=UP)
			    direction=DOWN;
			  break;

		case 75: if(direction!=RIGHT)
			    direction=LEFT;
			  break;

		case 77: if(direction!=LEFT)
			    direction=RIGHT;
			  break;

		case 'e': case 'E' : exit(0);

	}

     }

    for(i=bodyLength-1; i>0; i--)
     {
	body[i][0] = body[i-1][0];
	body[i][1] = body[i-1][1];
     }

      // UPDATE SNAKE HEAD

     switch(direction)

     {

	case UP  : body[0][1] = body[0][1] - STEP_SIZE;
		   if(body[0][1]==0)
		     game_over();
		   break;

	case DOWN: body[0][1] = body[0][1] + STEP_SIZE;
		   if(body[0][1]==maxy)
		      game_over();
		   break;

	case LEFT: body[0][0] = body[0][0] - STEP_SIZE;
		   if(body[0][0]==0)
		      game_over();
		   break;

	case RIGHT: body[0][0] = body[0][0] + STEP_SIZE;
		    if(body[0][0]==maxx)
		       game_over();
		    break;

     }

     cleardevice();

     drawBorder();

     instructions();

     drawSnake();

     drawTarget();

     if(ch == ‘f’ || ch == ‘F’)
        delay(50);
     
     else
        delay(150);


   }

}
