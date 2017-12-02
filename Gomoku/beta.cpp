#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<math.h>
#pragma comment(lib,"Winmm.lib")
int comp_board[23][23] = {0};

void music1()
{
  PlaySound(TEXT("music1.wav"),NULL,SND_ASYNC | SND_NODEFAULT);
}

void music2()
{
  PlaySound(TEXT("music2.wav"),NULL,SND_ASYNC | SND_NODEFAULT);
}

void draw_chessboard()
{
 initgraph(1200,750);
 setfillcolor(BROWN);
 fillrectangle(0,0,750,750);
 for(int i=20;i<=720;i+=50)
 {
   setlinecolor(BLACK);
   line(20,i,720,i);
 }
   for(int i=20;i<=720;i+=50)
 {
   setlinecolor(BLACK);
   line(i,20,i,720);
 }
   setfillcolor(BLACK);
   fillcircle(170,170,5);
   fillcircle(170,570,5);
   fillcircle(570,170,5);
   fillcircle(570,570,5);
   fillcircle(370,370,5);
}

void draw_white_piece(int x, int y)
{ 
  setlinecolor(WHITE);
  setfillcolor(WHITE);
  fillcircle(x,y,20);
}

void draw_black_piece(int x, int y)
{ 
  setlinecolor(BLACK);
  setfillcolor(BLACK);
  fillcircle(x,y,20);
}

bool judge_dot(int x, int y)
{
 int i = abs(x - 20);
 int j = abs(y - 20);
 int a = i % 50 < 50- i % 50 ? i % 50: 50 - i % 50;
 int b = j % 50 < 50- j % 50 ? j % 50: 50 - j % 50;
 int c = a * a + b * b;
 if (c <= 100)
 {
  int dot_x = i % 50 < 50- i % 50 ? (x - 20) / 50 + 4 :(x - 20) / 50 + 5;
  int dot_y = j % 50 < 50- j % 50 ? (y - 20) / 50 + 4 :(y - 20) / 50 + 5;
  if (comp_board[dot_x][dot_y] == 0)
	  return true;
 }
 return false;
}

bool check(int x,int y,int color)
{
  int i;
  int count = 0;
  for (i = -4;i <= 4;i ++ )
  {
    if (comp_board[x+i][y+i] == color)
		count ++;
	else
		count = 0;
	if (count == 5)
		return true;
   }
  count = 0;

  for (i= -4;i <= 4; i++ )
  {
    if (comp_board[x+i][y-i] == color)
		count ++;
	else
		count = 0;
	if (count == 5)
		return true;
  }
  count = 0;

  for (i= -4;i <= 4; i++)
  {
    if (comp_board[x][y+i] == color)
		count ++;
	else
		count = 0;
	if (count == 5)
		return true;
  }
  count = 0;
  
  for (i= -4;i <= 4; i++)
  {
    if (comp_board[x+i][y] == color)
		count ++;
	else
		count = 0;
	if (count == 5)
		return true;
  }
  count = 0;
  return false;
}
 

bool put_piece(int x, int y,int color)
{
  int x1 = abs(x - 20);
  int y1 = abs(y - 20);
  int piece_x = x1 % 50 < 50- x1 % 50 ? (x - 20) / 50 * 50 + 20:(x - 20) / 50 * 50 + 70;
  int piece_y = y1 % 50 < 50- y1 % 50 ? (y - 20) / 50 * 50 + 20:(y - 20) / 50 * 50 + 70;
  int dot_x = x1 % 50 < 50- x1 % 50 ? (x - 20) / 50 + 4:(x - 20) / 50 + 5;
  int dot_y = y1 % 50 < 50- y1 % 50 ? (y - 20) / 50 + 4:(y - 20) / 50 + 5;
  if (color == 1)
  {
	draw_black_piece(piece_x,piece_y);
	music1();
    comp_board[dot_x][dot_y] = 1;
	if (check(dot_x,dot_y,1))
		return true;
  }
  else
  {
    draw_white_piece(piece_x,piece_y);
	music2();
	comp_board[dot_x][dot_y] = 2;
	if (check(dot_x,dot_y,2))
		return true;
  }	 
  return false;
}

void clear_words()
{
  setfillcolor(BLACK);
  setlinecolor(BLACK);
  fillrectangle(790,140,1200,200);
}

void main()
{
  draw_chessboard();
  for(int k1 = 19; k1 <= 22; k1++)
	for(int k2 = 0; k2 <= 22; k2++)
		comp_board[k1][k2] = -1;

  MOUSEMSG m;
  settextstyle(50,0,_T("¿¬Ìå"));
  outtextxy(800,150,_T("ÏÈÊÖÖ´ºÚÆå"));
  int ok_black = 0;
  while (true)
  {
      	m = GetMouseMsg();
		if (m.mkLButton && judge_dot(m.x,m.y))
		   {
			if (ok_black == 0)
			{
			  if (put_piece(m.x,m.y,1))
			   {
			    settextstyle(50,0,_T("¿¬Ìå"));
				outtextxy(260,150,_T("ºÚÆå»ñÊ¤"));
				break;
			   }
			  clear_words();
			  settextstyle(50,0,_T("¿¬Ìå"));
			  outtextxy(800,150,_T("Ö´°×Æå"));
			  ok_black = 1;
			}
			else
			{
			  if (put_piece(m.x,m.y,2))
			   {
				settextstyle(50,0,_T("¿¬Ìå"));
				outtextxy(260,150,_T("°×Æå»ñÊ¤"));
				break;
			   }
			  clear_words();
			  settextstyle(50,0,_T("¿¬Ìå"));
			  outtextxy(800,150,_T("Ö´ºÚÆå"));
			  ok_black = 0;
			}
		   }

  }
  PlaySound(TEXT("clap.wav"),NULL,SND_ASYNC | SND_NODEFAULT);
  char end = _getch();
}