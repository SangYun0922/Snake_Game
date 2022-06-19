
#include "SnakeGame.h"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <ctime> // for using rand() function
#include <queue> // for using queue
#include <unistd.h> // for using usleep
using namespace std;

SnakeGame::SnakeGame()
{
  StartWindow(); // initalize window
}

SnakeGame::~SnakeGame()
{
  getch();
  endwin(); // end game
}

void SnakeGame::StartWindow()
{
  initscr(); // start ncurses mode
  start_color();

  init_pair(0, COLOR_BLACK, COLOR_BLACK); // gate
  init_pair(1, COLOR_RED, COLOR_RED); //BlackMamba
  init_pair(2, COLOR_CYAN, COLOR_CYAN); //Trap
  init_pair(3, COLOR_GREEN, COLOR_GREEN); //snake
  init_pair(4, COLOR_BLACK, COLOR_WHITE);
  init_pair(5, COLOR_WHITE, COLOR_WHITE);
  init_pair(6, COLOR_BLUE, COLOR_WHITE);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);
  init_pair(8, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(9, COLOR_YELLOW, COLOR_YELLOW);

  nodelay(stdscr,TRUE);
  noecho(); // don't echo() while we do getch
  curs_set(0);
  cbreak(); // no buffer
  keypad(stdscr, TRUE); // initialize keypad
  getmaxyx(stdscr, vertical , horizontal); // get length of x,y of screen

  refresh(); // print on the screen
  return;
}


void SnakeGame::MakeMap1()
{
    height=21;
    width=42;
    start.y=start.x=0;

    for(int i=1;i<width-1;i++)
      {
          for(int j=1;j<height-1;j++)
          {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr,j,i,"A");
        attroff(COLOR_PAIR(5));
      }
    }
    attron(COLOR_PAIR(7));
    mvwprintw(stdscr,0, 0,"x");
    mvwprintw(stdscr,height-1,0 ,"x");
    mvwprintw(stdscr,0, width-1,"x");
    mvwprintw(stdscr,height-1, width-1,"x");

    for(int j=1;j<height-1;j++)
    {
      mvwprintw(stdscr,j,0,".");
      wall[j][0]= 1;
      wallCopy[j][0]= 1;
      mvwprintw(stdscr ,j,width-1,".");
      wall[j][width-1]=1;
      wallCopy[j][width-1]=1;
    }
    for(int i=1;i<width-1;i++)
    {
      mvwprintw(stdscr ,0,i,".");
      wall[0][i]=1;
      wallCopy[0][i]=1;
      mvwprintw(stdscr ,height-1,i,".");
      wall[height-1][i]=1;
      wallCopy[height-1][i]=1;
    }
    attroff(COLOR_PAIR(7));
}

void SnakeGame::MakeMap2()
{
    height=21;
    width=42;
    start.y=start.x=0;

    for(int i=1;i<width-1;i++)
      {
          for(int j=1;j<height-1;j++)
          {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr,j,i,"B");
        wall[j][i] = 0;
        wallCopy[j][i] = 0;
        attroff(COLOR_PAIR(5));
      }
    }
    attron(COLOR_PAIR(7));
    mvwprintw(stdscr,0, 0,"x");
    mvwprintw(stdscr,height-1,0 ,"x");
    mvwprintw(stdscr,0, width-1,"x");
    mvwprintw(stdscr,height-1, width-1,"x");

    for(int j=1;j<height-1;j++)
    {
      mvwprintw(stdscr,j,0,".");
      wall[j][0]= 1;
      wallCopy[j][0]= 1;
      mvwprintw(stdscr ,j,width-1,".");
      wall[j][width-1]=1;
      wallCopy[j][width-1]=1;
    }
    for(int i=1;i<width-1;i++)
    {
      mvwprintw(stdscr,10,i,".");
      wall[10][i]=1;
      wallCopy[10][i]=1;
    }
    for(int i=1;i<width-1;i++)
    {
      mvwprintw(stdscr ,0,i,".");
      wall[0][i]=1;
      wallCopy[0][i]=1;
      mvwprintw(stdscr ,height-1,i,".");
      wall[height-1][i]=1;
      wallCopy[height-1][i]=1;
    }
    mvwprintw(stdscr,10,0,"x");
    mvwprintw(stdscr,10,width-1,"x");
    attroff(COLOR_PAIR(7));
}

void SnakeGame::MakeMap3()
{
    height=21;
    width=42;
    start.y=start.x=0;

    for(int i=1;i<width-1;i++)
      {
          for(int j=1;j<height-1;j++)
          {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr,j,i,"C");
        wall[j][i] = 0;
        wallCopy[j][i] = 0;
        attroff(COLOR_PAIR(5));
      }
    }
    attron(COLOR_PAIR(7));
    mvwprintw(stdscr,0, 0,"x");
    mvwprintw(stdscr,height-1,0 ,"x");
    mvwprintw(stdscr,0, width-1,"x");
    mvwprintw(stdscr,height-1, width-1,"x");

    for(int j=1;j<height-1;j++)
    {
      mvwprintw(stdscr,j,0,".");
      wall[j][0]= 1;
      wallCopy[j][0]= 1;
      mvwprintw(stdscr ,j,width-1,".");
      wall[j][width-1]=1;
      wallCopy[j][width-1]=1;
    }
    for(int i=3;i<width-3;i++)
    {
      mvwprintw(stdscr,10,i,".");
      wall[10][i]=1;
      wallCopy[10][i]=1;
    }
    for(int j=2;j<height-2;j++)
    {
      mvwprintw(stdscr,j,21,".");
      wall[j][21]=1;
      wallCopy[j][21]=1;
    }
    for(int i=1;i<width-1;i++)
    {
      mvwprintw(stdscr ,0,i,".");
      wall[0][i]=1;
      wallCopy[0][i]=1;
      mvwprintw(stdscr ,height-1,i,".");
      wall[height-1][i]=1;
      wallCopy[height-1][i]=1;
    }
    attroff(COLOR_PAIR(7));
}

void SnakeGame::MakeMap4()
{
    height=21;
    width=42;
    start.y=start.x=0;

    for(int i=1;i<width-1;i++)
      {
          for(int j=1;j<height-1;j++)
          {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr,j,i,"D");
        attroff(COLOR_PAIR(5));
        wall[j][i] = 0;
        wallCopy[j][i] = 0;
      }
    }
    attron(COLOR_PAIR(7));
    mvwprintw(stdscr,0, 0,"x");
    mvwprintw(stdscr,height-1,0 ,"x");
    mvwprintw(stdscr,0, width-1,"x");
    mvwprintw(stdscr,height-1, width-1,"x");

    for(int j=1;j<height-1;j++)
    {
      mvwprintw(stdscr,j,0,".");
      wall[j][0]= 1;
      wallCopy[j][0]= 1;
      mvwprintw(stdscr ,j,width-1,".");
      wall[j][width-1]=1;
      wallCopy[j][width-1]=1;
    }

    for(int i=1;i<width-1;i++)
    {
      mvwprintw(stdscr ,0,i,".");
      wall[0][i]=1;
      wallCopy[0][i]=1;
      mvwprintw(stdscr ,height-1,i,".");
      wall[height-1][i]=1;
      wallCopy[height-1][i]=1;
    }

    for(int j=3;j<height-5;j++)
    {
      mvwprintw(stdscr,j,5,".");
      wall[j][5]= 1;
      wallCopy[j][5]= 1;
    }

    for(int i=5;i<width-5;i++)
    {
      mvwprintw(stdscr,3,i,".");
      wall[3][i]= 1;
      wallCopy[3][i]= 1;
    }

    for(int j=5;j<height-3;j++)
    {
      mvwprintw(stdscr,j,width-6,".");
      wall[j][width-6]= 1;
      wallCopy[j][width-6]= 1;
    }

    for(int i=5;i<width-5;i++)
    {
      mvwprintw(stdscr,height-4,i,".");
      wall[height-4][i]= 1;
      wallCopy[height-4][i]= 1;
    }

    for(int j=5;j<height-5;j++)
    {
      mvwprintw(stdscr,j,width-11,".");
      wall[j][width-11]= 1;
      wallCopy[j][width-11]= 1;
    }

    for(int j=5;j<height-5;j++)
    {
      mvwprintw(stdscr,j,10,".");
      wall[j][10]= 1;
      wallCopy[j][10]= 1;
    }

    for(int i=14;i<width-10;i++)
    {
      mvwprintw(stdscr,5,i,".");
      wall[5][i]= 1;
      wallCopy[5][i]= 1;
    }

    for(int i=11;i<width-13;i++)
    {
      mvwprintw(stdscr,height-6,i,".");
      wall[height-6][i]= 1;
      wallCopy[height-6][i]= 1;
    }
    attroff(COLOR_PAIR(7));
}

void SnakeGame::LocateSnake()
{
  if(stage == 1)
  {
    srand((unsigned int)time(0));
    Randwidth = rand() % (width-6)+3;
    Randheight = rand() % (height-6)+3;
    int c=rand()%4;

    direction=' ';

    if(c==0)
    {
      mvwprintw(stdscr,Randheight,Randwidth,"3");
      mvwprintw(stdscr,Randheight,Randwidth+1,"4");
      mvwprintw(stdscr,Randheight,Randwidth+2,"4");
      xy.push(make_pair(Randheight,Randwidth+2));
      xy.push(make_pair(Randheight,Randwidth+1));
      xy.push(make_pair(Randheight,Randwidth));
      direction='l'; // left
    }
    if(c==1)
    {
      mvwprintw(stdscr,Randheight,Randwidth,"3");
      mvwprintw(stdscr,Randheight,Randwidth-1,"4");
      mvwprintw(stdscr,Randheight,Randwidth-2,"4");
      xy.push(make_pair(Randheight,Randwidth-2));
      xy.push(make_pair(Randheight,Randwidth-1));
      xy.push(make_pair(Randheight,Randwidth));
      direction='r'; // right
    }
    if(c==2)
    {
      mvwprintw(stdscr,Randheight,Randwidth,"3");
      mvwprintw(stdscr,Randheight+1,Randwidth,"4");
      mvwprintw(stdscr,Randheight+2,Randwidth,"4");
      xy.push(make_pair(Randheight+2,Randwidth));
      xy.push(make_pair(Randheight+1,Randwidth));
      xy.push(make_pair(Randheight,Randwidth));
      direction='u'; // up
    }
    if(c==3)
    {
      mvwprintw(stdscr,Randheight,Randwidth,"3");
      mvwprintw(stdscr,Randheight-1,Randwidth,"4");
      mvwprintw(stdscr,Randheight-2,Randwidth,"4");
      xy.push(make_pair(Randheight-2,Randwidth));
      xy.push(make_pair(Randheight-1,Randwidth));
      xy.push(make_pair(Randheight,Randwidth));
      direction='d'; // down
    }
  }
  else if(stage == 2)
  {
    direction = 'r';
    mvwprintw(stdscr,5,24,"3");
    mvwprintw(stdscr,5,23,"4");
    mvwprintw(stdscr,5,22,"4");
    xy.push(make_pair(5,22));
    xy.push(make_pair(5,23));
    xy.push(make_pair(5,24));
  }
  else if(stage == 3)
  {
    direction = 'r';
    mvwprintw(stdscr,1,12,"3");
    mvwprintw(stdscr,1,11,"4");
    mvwprintw(stdscr,1,10,"4");
    xy.push(make_pair(1,10));
    xy.push(make_pair(1,11));
    xy.push(make_pair(1,12));
  }
  else if(stage == 4)
  {
    direction = 'r';
    mvwprintw(stdscr,1,12,"3");
    mvwprintw(stdscr,1,11,"4");
    mvwprintw(stdscr,1,10,"4");
    xy.push(make_pair(1,10));
    xy.push(make_pair(1,11));
    xy.push(make_pair(1,12));
  }
}

void SnakeGame::WrongDirection()
{
    clear();
    WINDOW * win = newwin(height, width, start.y, start.x);
    refresh();
    mvwprintw(win, 10, 5,"Game Over!!!\tWrong Direction!!!");
    wrefresh(win);
    beep();
    usleep(1000000);
    death = true;
}

int SnakeGame::ControlSnake()
{

  if(ch = getch())
  {
    switch(ch)
    {
      case KEY_LEFT:
        if(direction!='r')
        {
          direction='l';
        }
        else
        {
          WrongDirection();
        }
        break;

      case KEY_RIGHT:
        if(direction!='l')
        {
          direction='r';
        }
        else
        {
          WrongDirection();
        }
        break;

      case KEY_UP:
        if(direction!='d')
        {
          direction='u';
        }
        else
        {
          WrongDirection();
        }
        break;

      case KEY_DOWN:
        if(direction!='u')
        {
          direction='d';
        }
        else
        {
          WrongDirection();
        }
        break;
      }
    }

    if(direction == 'l')
    {
      tail.y = xy.front().first;
      tail.x = xy.front().second;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr, xy.front().first, xy.front().second,"E");
      attroff(COLOR_PAIR(5));
      xy.pop();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr, xy.back().first, xy.back().second,"4");
      attroff(COLOR_PAIR(3));
      if(IsBody(xy.back().first, xy.back().second-1)==TRUE)
      {
        BumpedintoBody();
        death =TRUE;
      }

      xy.push(make_pair(xy.back().first, xy.back().second-1));
      ControlGate();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr, xy.back().first, xy.back().second,"3");
      attroff(COLOR_PAIR(3));
        
      if(EatGrowthItem()==true)
      {
        xy.push(make_pair(tail.y, tail.x));
        for(int i = 0; i < xy.size()-1;i++)
        {
          tail.y = xy.front().first;
          tail.x = xy.front().second;
          xy.pop();
          xy.push(make_pair(tail.y, tail.x));
        }
        num_growth++;
        length++;
        ScoreBoard();
      }
      if(IsBlackMamba()==true)
      {
        BumpedintoBlackMamba();
        death =TRUE;

      }
      if(IsTrap()==true)
      {
        BumpedintoTrap();
        death =TRUE;
      }

      if(EatPoisonItem()==TRUE)
      {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr, xy.front().first, xy.front().second,"F");
        attroff(COLOR_PAIR(5));
        xy.pop();
        num_poison++;
        length-=1;
        ScoreBoard();
      }
      refresh();
    }

    else if(direction == 'r')
    {
      tail.y=xy.front().first;
      tail.x=xy.front().second;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,xy.front().first,xy.front().second,"H");
      attroff(COLOR_PAIR(5));
      xy.pop();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr, xy.back().first, xy.back().second,"4");
      attroff(COLOR_PAIR(3));
      if(IsBody(xy.back().first, xy.back().second+1)==TRUE)
      {
        BumpedintoBody();
        death =TRUE;
      }
      xy.push(make_pair(xy.back().first, xy.back().second+1));
      ControlGate();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr,xy.back().first, xy.back().second,"3");
      attroff(COLOR_PAIR(3));
      if(EatGrowthItem()==true)
      {
        xy.push(make_pair(tail.y, tail.x));
        for(int i = 0; i < xy.size()-1;i++)
        {
          tail.y = xy.front().first;
          tail.x = xy.front().second;
          xy.pop();
          xy.push(make_pair(tail.y, tail.x));
        }
        num_growth++;
        length++;
        ScoreBoard();
      }
      if(IsBlackMamba()==true)
      {
        BumpedintoBlackMamba();
        death =TRUE;
      }
      if(IsTrap()==true)
      {
        BumpedintoTrap();
        death =TRUE;
      }

      if(EatPoisonItem()==TRUE)
      {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr, xy.front().first, xy.front().second,"V");
        attroff(COLOR_PAIR(5));
        xy.pop();
        num_poison++;
        length-=1;
        ScoreBoard();
      }
      refresh();
    }

    else if(direction == 'u')
    {
      tail.y=xy.front().first;
      tail.x=xy.front().second;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,xy.front().first,xy.front().second,"I");
      attroff(COLOR_PAIR(5));
      xy.pop();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr, xy.back().first, xy.back().second,"4");
      attroff(COLOR_PAIR(3));
      if(IsBody(xy.back().first-1, xy.back().second)==TRUE)
      {
        BumpedintoBody();
        death =TRUE;
      }
      xy.push(make_pair(xy.back().first-1, xy.back().second));
      ControlGate();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr,xy.back().first, xy.back().second,"3");
      attroff(COLOR_PAIR(3));
      if(EatGrowthItem()==true)
      {

        xy.push(make_pair(tail.y, tail.x));
        for(int i = 0; i < xy.size()-1;i++)
        {
          tail.y = xy.front().first;
          tail.x = xy.front().second;
          xy.pop();
          xy.push(make_pair(tail.y, tail.x));
        }
        num_growth++;
        length++;
        ScoreBoard();
      }
      if(IsBlackMamba()==true)
      {
        BumpedintoBlackMamba();
        death =TRUE;
      }
      if(IsTrap()==true)
      {
        BumpedintoTrap();
        death =TRUE;
      }

      if(EatPoisonItem()==TRUE)
      {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr, xy.front().first, xy.front().second,"J");
        attroff(COLOR_PAIR(5));
        xy.pop();
        num_poison++;
        length-=1;
        ScoreBoard();
      }
      refresh();
    }

    else if(direction == 'd')
    {
      tail.y=xy.front().first;
      tail.x=xy.front().second;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,xy.front().first,xy.front().second,"K");
      attroff(COLOR_PAIR(5));
      xy.pop();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr, xy.back().first, xy.back().second,"4");
      attroff(COLOR_PAIR(3));
      if(IsBody(xy.back().first+1, xy.back().second)==TRUE)
      {
        BumpedintoBody();
        death =TRUE;
      }
      xy.push(make_pair(xy.back().first+1, xy.back().second));
      ControlGate();
      attron(COLOR_PAIR(3));
      mvwprintw(stdscr,xy.back().first, xy.back().second,"3");
      attroff(COLOR_PAIR(3));
      if(EatGrowthItem()==true)
      {
        xy.push(make_pair(tail.y, tail.x));
        for(int i = 0; i < xy.size()-1;i++)
        {
          tail.y = xy.front().first;
          tail.x = xy.front().second;
          xy.pop();
          xy.push(make_pair(tail.y, tail.x));
        }
        num_growth++;
        length++;
        ScoreBoard();
      }
      if(IsBlackMamba()==true)
      {
        BumpedintoBlackMamba();
        death =TRUE;
      }
      if(IsTrap()==true)
      {
        BumpedintoTrap();
        death =TRUE;
      }

      if(EatPoisonItem()==TRUE)
      {
        attron(COLOR_PAIR(5));
        mvwprintw(stdscr, xy.front().first, xy.front().second,"L");
        attroff(COLOR_PAIR(5));
        xy.pop();
        num_poison++;
        length-=1;
        ScoreBoard();
      }
      refresh();
    }
  return 0;
}

void SnakeGame::BumpedintoWall()
{
  head.x=xy.back().second;
  head.y=xy.back().first;

  if(wall[head.y][head.x]==1)
  {
    clear();
    WINDOW * win = newwin(height, width, start.y,start.x);
    refresh();
    mvwprintw(win, 10, 5,"Game Over!!!\tBumped into Wall!!");
    wrefresh(win);
      beep();
      usleep(1000000);
      death = TRUE;
  }
}

void SnakeGame::RandGate()
{
  if(count3%40==0 && count3!=0)
  {
    if(wallCopy[gate1.y][gate1.x] == 1){
      wall[gate1.y][gate1.x]=1;
      attron(COLOR_PAIR(7));
      mvwprintw(stdscr,gate1.y,gate1.x,".");
      attroff(COLOR_PAIR(7));
    }
    else{
      wall[gate1.y][gate1.x]=0;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,gate1.y,gate1.x,"M");
      attroff(COLOR_PAIR(5));
    }

    if(wallCopy[gate2.y][gate2.x] == 1){
      wall[gate2.y][gate2.x]=1;
      attron(COLOR_PAIR(7));
      mvwprintw(stdscr,gate2.y,gate2.x,".");
      attroff(COLOR_PAIR(7));
    }
    else{
      wall[gate1.y][gate1.x]=0;
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,gate2.y,gate2.x,"N");
      attroff(COLOR_PAIR(5));
    }

    while(1)
    {
      gate1.x=rand()%42;
      gate1.y=rand()%21;
      gate2.x=rand()%42;
      gate2.y=rand()%21;
      if(((gate1.x!=gate2.x)||(gate1.y!=gate2.y))
      && !IsBody(gate1.y, gate1.x) && !IsBody(gate2.y, gate2.x)
      && gate1.x != 0 && gate1.y != 0 && gate2.x != 0 && gate2.y != 0)
      {
        break;
      }
    }
  }
  if(count3 == 0)
  {
    while(1)
    {
      gate1.x=rand()%42;
      gate1.y=rand()%21;
      gate2.x=rand()%42;
      gate2.y=rand()%21;
      if(((gate1.x!=gate2.x)||(gate1.y!=gate2.y))
       && !IsBody(gate1.y, gate1.x) && !IsBody(gate2.y, gate2.x)
       && gate1.x != 0 && gate1.y != 0 && gate2.x != 0 && gate2.y != 0)// && wall[gate1.y][gate1.x]==1 && wall[gate2.y][gate2.x]==1)
      {
        break;
      }
    }
  }
  wall[gate1.y][gate1.x]=2;
  wall[gate2.y][gate2.x]=2;
  attron(COLOR_PAIR(0));
  mvwprintw(stdscr,gate1.y,gate1.x,"G");
  mvwprintw(stdscr,gate2.y,gate2.x,"G");
  attroff(COLOR_PAIR(0));
  count3++;
}

void SnakeGame::RandGrowthItem()
{
  if((DestroyedbyBlackMamba(growth.y,growth.x)==TRUE)||(EatGrowthItem()==TRUE)||(count1%30==0 && count1!=0)){
    if(wallCopy[growth.y][growth.x]!=1){
    attron(COLOR_PAIR(5));
    mvwprintw(stdscr,growth.y,growth.x,"O");
    attroff(COLOR_PAIR(5));
    }
    while(1)
    {
      growth.x=rand()%(width-2)+1;
      growth.y=rand()%(height-2)+1;
      if(IsBody(growth.y,growth.x)==false && wallCopy[growth.y][growth.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(9));
    mvwprintw(stdscr,growth.y,growth.x,"5");
    attroff(COLOR_PAIR(9));
  }
  if(count1 == 0)
  {
    while(1)
    {
      growth.x=rand()%(width-2)+1;
      growth.y=rand()%(height-2)+1;
      if(IsBody(growth.y,growth.x)==false && wallCopy[growth.y][growth.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(9));
    mvwprintw(stdscr,growth.y,growth.x,"5");
    attroff(COLOR_PAIR(9));
  }
  count1++;
}

void SnakeGame::RandPoisonItem()
{
  if((DestroyedbyBlackMamba(poison.y,poison.x)==TRUE)||(EatPoisonItem()==TRUE)||(count2%30==0 && count2!=0)){
    if(wallCopy[poison.y][poison.x]!=1){
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,poison.y,poison.x,"P");
      attroff(COLOR_PAIR(5));
    }
    while(1)
    {
      poison.x=rand()%(width-2)+1;
      poison.y=rand()%(height-2)+1;
      if(IsBody(poison.y, poison.x)==false && wallCopy[poison.y][poison.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(8));
    mvwprintw(stdscr,poison.y,poison.x,"6");
    attroff(COLOR_PAIR(8));
  }
  if(count2 == 0)
  {
    while(1)
    {
      poison.x=rand()%(width-2)+1;
      poison.y=rand()%(height-2)+1;
      if(IsBody(poison.y, poison.x)==false && wallCopy[poison.y][poison.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(8));
    mvwprintw(stdscr,poison.y,poison.x,"6");
    attroff(COLOR_PAIR(8));
  }
  count2++;
}

bool SnakeGame::EatGrowthItem()
{
  if((growth.x==xy.back().second) && (growth.y==xy.back().first))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

bool SnakeGame::EatPoisonItem()
{
  if((poison.x==xy.back().second) && (poison.y==xy.back().first))
  {
    if(xy.size()<3)
    {
      SizeofSnake();
    }
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

bool SnakeGame::IsBody(int rand1, int rand2)
{
  for(int i=0;i<xy.size();i++)
  {
    body.x = xy.front().second;
    body.y = xy.front().first;

    if(body.x==rand2 && body.y==rand1)
    {
      return TRUE;
    }
    else
    {
      xy.pop();
    }
    xy.push(make_pair(body.y,body.x));
  }
  return FALSE;
}

void SnakeGame::SizeofSnake()
{
  clear();
  WINDOW * win = newwin(height, width, start.y, start.x);
  refresh();
  mvwprintw(win, 10, 5,"Game Over!!!\tToo Short!!!");
  wrefresh(win);
      beep();
      usleep(1000000);
      death = TRUE;
}

bool SnakeGame::IsGate()
{
  if(xy.back().second==gate1.x && xy.back().first==gate1.y)
  {
    in.x=gate1.x;
    in.y=gate1.y;
    out.x=gate2.x;
    out.y=gate2.y;
    num_gate++;
    ScoreBoard();
    return true;
  }
  else if(xy.back().second==gate2.x && xy.back().first==gate2.y)
  {
    in.x=gate2.x;
    in.y=gate2.y;
    out.x=gate1.x;
    out.y=gate1.y;
    num_gate++;
    ScoreBoard();
    return true;
  }
  else
  {
    return false;
  }
}

bool SnakeGame::DestroyedbyBlackMamba(int itemy,int itemx)
{
  for(int i=0;i<BlackMamba.size();i++)
  {
    int second = BlackMamba.front().second;
    int first = BlackMamba.front().first;
    if(BlackMamba.front().second==itemx && BlackMamba.front().first==itemy)
    {
      return TRUE;
    }
    else
    {
      BlackMamba.pop();
    }
    BlackMamba.push(make_pair(first, second));
  }
  return FALSE;
}

void SnakeGame::ControlGate()
{
  if(IsGate()==true)
  {
    for(int i=0;i<xy.size()-1;i++)
    {
      body.x = xy.front().second;
      body.y = xy.front().first;
      xy.pop();
      xy.push(make_pair(body.y,body.x));
    }
    xy.pop();
    attron(COLOR_PAIR(0));
    mvwprintw(stdscr, in.y, in.x, "G");
    attroff(COLOR_PAIR(0));
    if(IsEdgeGate()==true)
    {
      switch(direction){
        case 'r':
            xy.push(make_pair(out.y,out.x+1));
            break;
        case 'l':
            xy.push(make_pair(out.y,out.x-1));
            break;
        case 'u':
            xy.push(make_pair(out.y-1,out.x));
            break;
        case 'd':
            xy.push(make_pair(out.y+1,out.x));
            break;
      }
    }
  else if(IsEdgeGate()!=true)
  {
    switch(direction){
      case 'r':
          if(wall[out.y][out.x+1] == 0)
          {
            xy.push(make_pair(out.y,out.x+1));
            direction='r';
          }
          else if(wall[out.y+1][out.x] == 0)
          {
            xy.push(make_pair(out.y+1,out.x));
            direction='d';
          }
          else if(wall[out.y-1][out.x] == 0)
          {
            xy.push(make_pair(out.y-1,out.x));
            direction='u';
          }
          else
          {
            xy.push(make_pair(out.y,out.x-1));
            direction='l';
          }
          break;
      case 'l':
          if(wall[out.y][out.x-1] == 0)
          {
            xy.push(make_pair(out.y,out.x-1));
            direction='l';
          }
          else if(wall[out.y-1][out.x] == 0)
          {
            xy.push(make_pair(out.y-1,out.x));
            direction='u';
          }
          else if(wall[out.y+1][out.x] == 0)
          {
            xy.push(make_pair(out.y+1,out.x));
            direction='d';
          }
          else
          {
            xy.push(make_pair(out.y,out.x+1));
            direction='r';
          }
          break;
      case 'u':
          if(wall[out.y-1][out.x] == 0)
          {
            xy.push(make_pair(out.y-1,out.x));
            direction='u';
          }
          else if(wall[out.y][out.x+1] == 0)
          {
            xy.push(make_pair(out.y,out.x+1));
            direction='r';
          }
          else if(wall[out.y][out.x-1] == 0)
          {
            xy.push(make_pair(out.y,out.x-1));
            direction='l';
          }
          else
          {
            xy.push(make_pair(out.y+1,out.x));
            direction='d';
          }
          break;
      case 'd':
            if(wall[out.y+1][out.x] == 0)
            {
              xy.push(make_pair(out.y+1,out.x));
              direction='d';
            }
            else if(wall[out.y][out.x-1] == 0)
            {
              xy.push(make_pair(out.y,out.x-1));
              direction='l';
            }
            else if(wall[out.y][out.x+1] == 0)
            {
              xy.push(make_pair(out.y,out.x+1));
              direction='r';
            }
            else
            {
              xy.push(make_pair(out.y-1,out.x));
              direction='u';
            }
            break;
          }
      }
   }
}

bool SnakeGame::IsEdgeGate()
{
  if(out.y==0)
  {
    direction = 'd';
    return true;
  }
  else if(out.y==20)
  {
    direction = 'u';
    return true;
  }
  else if(out.x==0)
  {
    direction = 'r';
    return true;
  }
  else if(out.x==41)
  {
    direction = 'l';
    return true;
  }
  else
  {
    return false;
  }
}

void SnakeGame::BumpedintoBody()
{
  clear();
  WINDOW * win = newwin(height, width, start.y,start.x);
  refresh();
  mvwprintw(win, 10, 5,"Game Over!!!\tBumped into Body!!!");
  wrefresh(win);
      beep();
      usleep(1000000);
      death = TRUE;

  }

void SnakeGame::ScoreBoard()
{
  mvwprintw(stdscr,2,45,"<Score Board>");
  mvwprintw(stdscr,3,45,"B :                   ");
  mvwprintw(stdscr,4,45,"+ :                   ");
  mvwprintw(stdscr,5,45,"- :                   ");
  mvwprintw(stdscr,6,45,"G :                   ");
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr,7,45,"-");
  attroff(COLOR_PAIR(3));
  mvwprintw(stdscr,7,46,": snake");
  attron(COLOR_PAIR(0));
  mvwprintw(stdscr,8,45,"G");
  attroff(COLOR_PAIR(0));
  mvwprintw(stdscr,8,46,": gate");
  attron(COLOR_PAIR(7));
  mvwprintw(stdscr,9,45,"-");
  attroff(COLOR_PAIR(7));
  mvwprintw(stdscr,9,46,": wall");
  attron(COLOR_PAIR(8));
  mvwprintw(stdscr,10,45,"-");
  attroff(COLOR_PAIR(8));
  mvwprintw(stdscr,10,46,": poison");
  attron(COLOR_PAIR(9));
  mvwprintw(stdscr,11,45,"-");
  attroff(COLOR_PAIR(9));
  mvwprintw(stdscr,11,46,": growth");
  attron(COLOR_PAIR(2));
  mvwprintw(stdscr,12,45,"-");
  attroff(COLOR_PAIR(2));
  mvwprintw(stdscr,12,46,": Trap");
  attron(COLOR_PAIR(1));
  mvwprintw(stdscr,13,45,"-");
  attroff(COLOR_PAIR(1));
  mvwprintw(stdscr,13,46,": BlackMamba");

  char len1[100];
  char len2[100];
  char len3[100];
  char len4[100];
  char len[100];
  char growth[100];
  char poison[100];
  char gate[100];
  if(max_length < length)
  {
    max_length = length;
  }
  if(max_length>=mission_length)
  {
    mvwprintw(stdscr,3,49,"Mission Clear");
  }
  else
  {
    string itos1= to_string(max_length);
    strcpy(len1,itos1.c_str());
    mvwprintw(stdscr,3,49,len1);
    itos1= to_string(mission_length);
    strcpy(len,itos1.c_str());
    mvwprintw(stdscr,3,51,"/");
    mvwprintw(stdscr,3,52,len);
  }

  if(num_growth>=mission_growth)
  {
    mvwprintw(stdscr,4,49,"Mission Clear");
  }
  else
  {
    string itos2=to_string(num_growth);
    strcpy(len2,itos2.c_str());
    mvwprintw(stdscr,4,49,len2);
    itos2= to_string(mission_growth);
    strcpy(growth,itos2.c_str());
    mvwprintw(stdscr,4,51,"/");
    mvwprintw(stdscr,4,52,growth);
  }

  if(num_poison>=mission_poison)
  {
    mvwprintw(stdscr,5,49,"Mission Clear");
  }
  else
  {
    string itos3=to_string(num_poison);
    strcpy(len3,itos3.c_str());
    mvwprintw(stdscr,5,49,len3);
    itos3= to_string(mission_poison);
    strcpy(poison,itos3.c_str());
    mvwprintw(stdscr,5,51,"/");
    mvwprintw(stdscr,5,52,poison);
  }

  if(num_gate>=mission_gate)
  {
    mvwprintw(stdscr,6,49,"Mission Clear");
  }
  else
  {
    string itos4=to_string(num_gate);
    strcpy(len4,itos4.c_str());
    mvwprintw(stdscr,6,49,len4);
    itos4= to_string(mission_gate);
    strcpy(gate,itos4.c_str());
    mvwprintw(stdscr,6,51,"/");
    mvwprintw(stdscr,6,52,gate);
  }
}

bool SnakeGame::CheckMission()
{
  if(stage==1)
  {
    if(max_length>=5 && num_growth>=2 && num_poison>=2 && num_gate>=1)
    {
      stage++;
      countBlackMamba = 0;
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else if(stage==2)
  {
    if(max_length>=6 && num_growth>=3 && num_poison>=3 && num_gate>=2)
    {
      stage++;
      countBlackMamba = 0;
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else if(stage==3)
  {
    if(max_length>=7 && num_growth>=5 && num_poison>=3 && num_gate>=3)
    {
      stage++;
      countBlackMamba = -2;
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else if(stage==4)
  {
    if(max_length>=6 && num_growth>=3 && num_poison>=3 && num_gate>=3)
    {
      stage++;
      countBlackMamba = 0;
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

void SnakeGame::RandTrap()
{
  if((DestroyedbyBlackMamba(Trap.y,Trap.x)==TRUE)||(IsTrap()==TRUE)||(count4%30==0 && count4!=0)){
    if(wallCopy[Trap.y][Trap.x]!=1){
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,Trap.y,Trap.x,"Q");
      attroff(COLOR_PAIR(5));
    }
    while(1)
    {
      Trap.x=rand()%(width-2)+1;
      Trap.y=rand()%(height-2)+1;
      if(IsBody(Trap.y, Trap.x)==false && wallCopy[Trap.y][Trap.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr,Trap.y,Trap.x,"@");
    attroff(COLOR_PAIR(2));
  }
  if(count4 == 0)
  {
    while(1)
    {
      Trap.x=rand()%(width-2)+1;
      Trap.y=rand()%(height-2)+1;
      if(IsBody(Trap.y, Trap.x)==false && wallCopy[Trap.y][Trap.x]!=1)
      {
        break;
      }
    }
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr,Trap.y,Trap.x,"@");
    attroff(COLOR_PAIR(2));
  }
  count4++;
}

void SnakeGame::BumpedintoTrap()
{
  clear();
  WINDOW * win = newwin(height, width, start.y,start.x);
  refresh();
  mvwprintw(win, 10, 5,"Game Over!!!\tFall into a Trap!!");
  wrefresh(win);
      beep();
      usleep(1000000);
      death = TRUE;
}

bool SnakeGame::IsTrap()
{
  if((Trap.x==xy.back().second) && (Trap.y==xy.back().first))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void SnakeGame::LocateBlackMamba()
{
    attron(COLOR_PAIR(1));
  switch(stage){
    case 1:
          BlackMamba.push(make_pair(5,10));
          BlackMamba.push(make_pair(5,11));
          BlackMamba.push(make_pair(5,12));
          BlackMamba.push(make_pair(5,13));
          BlackMamba.push(make_pair(5,14));
          mvwprintw(stdscr,5,10,"O");
          mvwprintw(stdscr,5,11,"O");
          mvwprintw(stdscr,5,12,"O");
          mvwprintw(stdscr,5,13,"O");
          mvwprintw(stdscr,5,14,"C");
          break;
    case 2:
      while(!BlackMamba.empty())
      {
        BlackMamba.pop();
      }
          BlackMamba.push(make_pair(4,6));
          BlackMamba.push(make_pair(4,7));
          BlackMamba.push(make_pair(4,8));
          BlackMamba.push(make_pair(4,9));
          BlackMamba.push(make_pair(4,10));
          mvwprintw(stdscr,4,6,"O");
          mvwprintw(stdscr,4,7,"O");
          mvwprintw(stdscr,4,8,"O");
          mvwprintw(stdscr,4,9,"O");
          mvwprintw(stdscr,4,10,"C");
          break;
    case 3:
      while(!BlackMamba.empty())
      {
        BlackMamba.pop();
      }
      BlackMamba.push(make_pair(4, 6));
      BlackMamba.push(make_pair(4,7));
      BlackMamba.push(make_pair(4,8));
      BlackMamba.push(make_pair(4,9));
      BlackMamba.push(make_pair(4,10));
      mvwprintw(stdscr,4,6,"O");
      mvwprintw(stdscr,4,7,"O");
      mvwprintw(stdscr,4,8,"O");
      mvwprintw(stdscr,4,9,"O");
      mvwprintw(stdscr,4,10,"C");
      break;
    case 4:
      while(!BlackMamba.empty())
      {
        BlackMamba.pop();
      }
          BlackMamba.push(make_pair(8, 14));
          BlackMamba.push(make_pair(8,15));
          BlackMamba.push(make_pair(8,16));
          BlackMamba.push(make_pair(8,17));
          BlackMamba.push(make_pair(8,18));
          mvwprintw(stdscr,8,14,"O");
          mvwprintw(stdscr,8,15,"O");
          mvwprintw(stdscr,8,16,"O");
          mvwprintw(stdscr,8,17,"O");
          mvwprintw(stdscr,8,18,"C");
          break;
    }
    attroff(COLOR_PAIR(1));
}

void SnakeGame::DangerousBlackMamba()
{
  switch(stage){
    case 1:
          row=15;
          col=10;
      break;
    case 2:
        row=23;
        col=3;
        break;
    case 3:
      row=5;
      col=3;
      break;
    case 4:
      row=9;
      col=3;
      break;
  }

  if(countBlackMamba<=row)
  {
    cdirection = 'r';
  }
  else if((row+col>=countBlackMamba)&&(countBlackMamba > row))
  {
    cdirection = 'd';
  }
  else if((  4+row+row+col>=countBlackMamba) && (countBlackMamba > row+col))
  {
    cdirection = 'l';
  }
  else if(( 4+row+row+col+col>countBlackMamba) && (countBlackMamba > 4+row+row+col))
  {
    cdirection = 'u';
  }
  else if(countBlackMamba % (4+row+row+col+col) ==0){
    countBlackMamba = -4;
  }

  switch (cdirection){
    case 'r':
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,BlackMamba.front().first,BlackMamba.front().second,"R");
      attroff(COLOR_PAIR(5));
      BlackMamba.pop();
        attron(COLOR_PAIR(1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"O");
      BlackMamba.push(make_pair(BlackMamba.back().first, BlackMamba.back().second+1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"C");
        attroff(COLOR_PAIR(1));
        break;
    case 'l':
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,BlackMamba.front().first,BlackMamba.front().second,"S");
      attroff(COLOR_PAIR(5));
      BlackMamba.pop();
        attron(COLOR_PAIR(1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"O");
      BlackMamba.push(make_pair(BlackMamba.back().first, BlackMamba.back().second-1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"C");
        attroff(COLOR_PAIR(1));
        break;
    case 'u':
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,BlackMamba.front().first,BlackMamba.front().second,"T");
      attroff(COLOR_PAIR(5));
      BlackMamba.pop();
        attron(COLOR_PAIR(1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"O");
      BlackMamba.push(make_pair(BlackMamba.back().first-1, BlackMamba.back().second));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"C");
        attroff(COLOR_PAIR(1));
        break;
    case 'd':
      attron(COLOR_PAIR(5));
      mvwprintw(stdscr,BlackMamba.front().first,BlackMamba.front().second,"U");
      attroff(COLOR_PAIR(5));
      BlackMamba.pop();
        attron(COLOR_PAIR(1));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"O");
      BlackMamba.push(make_pair(BlackMamba.back().first+1, BlackMamba.back().second));
      mvwprintw(stdscr,BlackMamba.back().first,BlackMamba.back().second,"C");
        attroff(COLOR_PAIR(1));
        break;
      }
  countBlackMamba++;
}

void SnakeGame::BumpedintoBlackMamba()
{
  clear();
  WINDOW * win = newwin(height, width, start.y,start.x);
  refresh();
  mvwprintw(win, 10, 5,"Game Over!!!\n\tBumped into BlackMamba!!");
  wrefresh(win);
      beep();
      usleep(1000000);
      death = TRUE;
}

bool SnakeGame::IsBlackMamba()
{
  for(int j = 0; j < BlackMamba.size();j++)
  {
     cbody.x = BlackMamba.front().second;
     cbody.y = BlackMamba.front().first;
     BlackMamba.pop();

    for(int i=0;i<xy.size();i++)
    {
      body.x = xy.front().second;
      body.y = xy.front().first;

      if(body.x==cbody.x && body.y==cbody.y)
      {
      return TRUE;
      }
      else
      {
      xy.pop();
      }
      xy.push(make_pair(body.y,body.x));
    }
    BlackMamba.push(make_pair(cbody.y, cbody.x));
  }
  return FALSE;
}

void SnakeGame::Start(int stage)
{
  this->stage = stage;
  StartWindow();
  length=3;
  num_growth=0;
  num_poison=0;
  num_gate=0;

  if(stage==1)
  {
    mission_length=5;
    mission_growth=2;
    mission_poison=2;
    mission_gate=1;
    attron(COLOR_PAIR(4));
    mvwprintw(stdscr,0,45,"[ Stage 1 ]");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    MakeMap1();
    attroff(COLOR_PAIR(6));
  }
  else if(stage==2)
  {
    mission_length=6;
    mission_growth=3;
    mission_poison=3;
    mission_gate=2;

    attron(COLOR_PAIR(4));
    mvwprintw(stdscr,0,45,"[ Stage 2 ]");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    MakeMap2();
    attroff(COLOR_PAIR(6));
  }

  else if(stage==3)
  {
    mission_length=7;
    mission_growth=5;
    mission_poison=3;
    mission_gate=3;
    attron(COLOR_PAIR(4));
    mvwprintw(stdscr,0,45,"[ Stage 3 ]");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    MakeMap3();
    attroff(COLOR_PAIR(6));
  }
  else if(stage==4)
  {
    mission_length=6;
    mission_growth=3;
    mission_poison=3;
    mission_gate=3;
    attron(COLOR_PAIR(4));
    mvwprintw(stdscr,0,45,"[ Stage 4 ]");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    MakeMap4();
    attroff(COLOR_PAIR(6));
  }
  max_length=length;
  while(!xy.empty())
  {
    xy.pop();
  }
    LocateSnake();
  LocateBlackMamba();
  ScoreBoard();
  while(1)
  {
    DangerousBlackMamba();
    ControlSnake();
    RandGate();
    BumpedintoWall();
    RandGrowthItem();
    RandPoisonItem();
    RandTrap();
    if(death==TRUE )
    {
        break;
    }
    if(CheckMission()==TRUE)
    {
      break;
    }
    usleep(150000); // 0.2 seconds
  }
}
