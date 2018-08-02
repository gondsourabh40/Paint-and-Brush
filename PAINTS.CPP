#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
union REGS in,out;
void mousepos(int *,int *,int*);
void save(int);
void main();
void mhide();
void detect();
void show();
void restrict(int,int,int,int);
void logo();
void select(int);
void fwindow(int,int,int,int);
void dwindow(int,int,int,int,int,int);
int mfigure(int);
void open(int);
char s[16][20]= {"Black       ","Blue        ","Green       ","Cyan        ","Red         ","Magenta     ","Brown       ","LightGray   ","DarkGray    ","LightBlue   ","LightGreen  ","LightCyan   ","LightRed    ","LightMagenta","Yellow      ","White       "};
int buffer[2000];
void get(char *s,int left)
{
	int x,y,i=0,color=getcolor();
	char ch[2]=" ";
	setcolor(WHITE);
		while((*ch=getch())!=13)
		{
		x=getx();
		y=gety();
		if(*ch==8)
		{
			if(x>left&&i>0)
			{
			mhide();
			setfillstyle(SOLID_FILL,getpixel(x,y));
			bar(x-9,y-5,x-2,y+15);
			show();
			moveto(x-8,y);
			i--;
			}
		}
		else if(*ch==27)
		{
		*ch='\0';
		return;
		}
		else if(x<554&&i<11)
		{
			mhide();
			outtext(ch);
			s[i++]=*ch;
			show();
		}
		}
		s[i]=0;
		setcolor(color);
}
void about()
{
	int color=getcolor();
	save(0);
	dwindow(120,50,507,250,BLUE,RED);
	setcolor(BLACK);
	settextstyle(0,HORIZ_DIR,0);
	outtextxy(290,55,"ABOUT");
	outtextxy(200,100,"Project: Paint");
	outtextxy(200,130,"Created by: Sourabh gond");
	outtextxy(200,160,"Completed Date: 29/03/2017");
	getch();
	rectangle(35,15,600,330);
	setcolor(color);
	open(0);
}
void open(int n)
{
	int i,j;
	FILE *fp;
	char ch[20];
	if(n)
	{
	int color=getcolor();
	settextstyle(0,HORIZ_DIR,1);
	dwindow(207,100,407,200,BLUE,RED);
	setcolor(BLACK);
	outtextxy(290,105,"Open");
	setcolor(WHITE);
	outtextxy(250,130,"<<Enter Name>>");
	outtextxy(250,150,"->");
	setcolor(color);
	moveto(270,150);
	get(ch,250);
	fp=fopen(ch,"r");
	if(fp==NULL)
	{
		outtextxy(235,165,"File does not find");
		delay(400);
		main();
	}
	}
	else
	fp=fopen("cpaint.txt","r");
	fwindow(35,14,600,330);
	outtextxy(639/2-30,1,"Paint");
	logo();
	for(i=30;i<300;i++)
	{
		for(j=75;j<560;j++)
	       putpixel(j,i,fgetc(fp));
	}
	fclose(fp);
}
void save(int n)
{
	int i,j;
	char ch[20],c;
	FILE *fp1,*fp2;
	fp1=fopen("cpaint.txt","w+");
	for(i=30;i<300;i++)
	{
		for(j=75;j<560;j++)
		fputc(getpixel(j,i),fp1);
	}
	if(n)
	{
	int color=getcolor();
	fseek(fp1,0,0);
	settextstyle(0,HORIZ_DIR,1);
	dwindow(207,100,407,200,BLUE,RED);
	setcolor(BLACK);
	outtextxy(290,105,"Save");
	setcolor(WHITE);
	outtextxy(250,130,"<<Enter Name>>");
	outtextxy(250,150,"->");
	setcolor(color);
	moveto(270,150);
	get(ch,250);
	fp2=fopen(ch,"w");
	if(fp2==NULL)
	{
		outtextxy(235,165,"File doesn't save");
		delay(400);
		main();

	}
	while((c=fgetc(fp1))!=EOF)
	fputc(c,fp2);
	fclose(fp2);
	}
	fclose(fp1);
	open(0);
}
void xy(int x,int y)
{
    if(x>75&&x<560&&y>30&&y<300)
    {
	gotoxy(52,23);
	printf("%d  ",x-76);
	gotoxy(59,23);
	printf("%d",y-31);
    }
    else
    {
	gotoxy(52,23);
	printf("-  ");
	gotoxy(59,23);
	printf("-  ");
    }
}
void getlinebk(int x1,int y1,int x2,int y2)
{
	FILE *fp=fopen("rect.txt","w");
	float x,y,dx,dy,pixel;
	int i,t,j=0;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>=dy)
	pixel=dx;
	else
	pixel=dy;
	dx/=pixel;
	dy/=pixel;
	if(x1<=x2&&y1<=y2)
	{
	x=x1;
	y=y1;
	}
	else if(x1>=x2&&y1>=y2)
	{
	x=x2;
	y=y2;
	}
	else if(x1>x2&&y1<=y2)
	{
	x=x2;
	y=y2;
	dy=dy*-1;
	}
	else
	{
	x=x1;
	y=y1;
	dy=dy*-1;
	}
	i=1;
	while(i<=pixel)
	{
		buffer[j++]=getpixel(x,y);
		x=x+dx;
		y=y+dy;
		i++;
	}
	fclose(fp);
}
void putlinebk(int x1,int y1,int x2,int y2)
{
	float x,y,dx,dy,pixel;
	int i,t,j=0;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>=dy)
	pixel=dx;
	else
	pixel=dy;
	dx/=pixel;
	dy/=pixel;
	if(x1<=x2&&y1<=y2)
	{
	x=x1;
	y=y1;
	}
	else if(x1>=x2&&y1>=y2)
	{
	x=x2;
	y=y2;
	}
	else if(x1>x2&&y1<=y2)
	{
	x=x2;
	y=y2;
	dy=dy*-1;
	}
	else
	{
	x=x1;
	y=y1;
	dy=dy*-1;
	}
	i=1;
	while(i<=pixel)
	{
		putpixel(x,y,buffer[j++]);
		x=x+dx;
		y=y+dy;
		i++;
	}
}
void drawline(int x1,int y1,int x2,int y2)
{
	float x,y,dx,dy,pixel;
	int i,t;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>=dy)
	pixel=dx;
	else
	pixel=dy;
	dx/=pixel;
	dy/=pixel;
	if(x1<=x2&&y1<=y2)
	{
	x=x1;
	y=y1;
	}
	else if(x1>=x2&&y1>=y2)
	{
	x=x2;
	y=y2;
	}
	else if(x1>x2&&y1<=y2)
	{
	x=x2;
	y=y2;
	dy=dy*-1;
	}
	else
	{
	x=x1;
	y=y1;
	dy=dy*-1;
	}
	i=1;
	while(i<=pixel)
	{
		putpixel(x,y,getcolor());
		x=x+dx;
		y=y+dy;
		i++;
	}
}

int Line()
{
int x,y,button;
	do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		    int left=x;
		    int top=y;
		    delay(200);
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x<561&&y>30&&y<300)
			    {
				int x1,y1;
				mhide();
				x1=x;
				y1=y;
				getlinebk(left,top,x1,y1);
				drawline(left,top,x1,y1);
				delay(100);
				mousepos(&x,&y,&button);
				if(button==1)
				putlinebk(left,top,x1,y1);
				show();
			    }
			}
		    }
		    while(button==1 );
		}
		return 3;
	    }
	}
	while(!kbhit());
	return 3;
}
int mrectangle()
{
	int x,y,button=1;
	gotoxy(1,1);
	do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	  if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		    int left=x,top=y,l=x,t=y;
		    delay(200);
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x<560&&y>30&&y<300)
			    {
				int i,temp,x1,y1,j=0;
				if(x<l&&y>t)
				{
				left=x;
				top=t;
				x1=l;
				y1=y;
				}
				else if(x<l&&y<t)
				{
				left=x;
				top=y;
				x1=l;
				y1=t;
				}
				else if(x>l&&y>t)
				{
				left=l;
				top=t;
				x1=x;
				y1=y;
				}
				else if(x>l&&y<t)
				{
				left=l;
				top=y;
				x1=x;
				y1=t;
				}
				mhide();
				for(i=left;i<=x1;i++)
				buffer[j++]=getpixel(i,top);
				for(i=left;i<=x1;i++)
				buffer[j++]=getpixel(i,y1);
				for(i=top;i<=y1;i++)
				buffer[j++]=getpixel(left,i);
				for(i=top;i<=y1;i++)
				buffer[j++]=getpixel(x1,i);
				rectangle(l,t,x,y);
				delay(100);
				mousepos(&x,&y,&button);
				if(button==1)
				{
				j=0;
				for(i=left;i<=x1;i++)
				putpixel(i,top,buffer[j++]);
				for(i=left;i<=x1;i++)
				putpixel(i,y1,buffer[j++]);
				for(i=top;i<=y1;i++)
				putpixel(left,i,buffer[j++]);
				for(i=top;i<=y1;i++)
				putpixel(x1,i,buffer[j++]);
				}
				show();
			    }
			}
		    }
		    while(button==1);
		}
		else
		return 1;
	    }
	}
	while(!kbhit());

	return 1;
}
int Poly()
{
	int x,y,button;
	do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		    int left=x;
		    int top=y;
		    delay(200);
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x<560&&y>30&&y<300)
			    {
				int x1,y1;
				mhide();
				x1=x;
				y1=y;
				getlinebk(left,top,x1,y1);
				drawline(left,top,x1,y1);
				delay(100);
				mousepos(&x,&y,&button);
				if(button==1)
				putlinebk(left,top,x1,y1);
				else
				{
				left=x1;
				top=y1;
				}
				show();
			    }
			    else
			    return 4;
			}
		    }
		    while(button!=2);
		}
		return 4;
	    }
	}
	while(!kbhit());
	return 4;
}

void drawEllipse(float xc,float yc,float x,float y)
{
	int color=getcolor();
	putpixel(xc+x,yc+y,color);
	putpixel(xc-x,yc+y,color);
	putpixel(xc+x,yc-y,color);
	putpixel(xc-x,yc-y,color);
}
void ellipseMidpoint(float xc,float yc,float rx,float ry,int check)
{
	float rxsq=rx*rx,rysq=ry*ry,x=0,y=ry,p,px=0,py=2*rxsq*y;
	int i=0;
	if(check==1)
		{
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc+y);
		buffer[i++]= getpixel(xc+x,yc-y);
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc-y);
		}
		else if(check==2)
		{
		drawEllipse(xc,yc,x,y);
		}
		else if(check==3)
		{
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc+y,buffer[i++]);
		putpixel(xc+x,yc-y,buffer[i++]);
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc-y,buffer[i++]);
		}
	p=rysq-(rxsq*ry)+(0.25*rxsq);
	while(px<py)
	{
		x++;
		px=px+2*rysq;
		if(p<0)
		p=p+rysq+px;
		else
		{
			y--;
			py=py-2*rxsq;
			p=p+rysq+px-py;
		}
		if(check==1)
		{
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc+y);
		buffer[i++]= getpixel(xc+x,yc-y);
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc-y);
		}
		else if(check==2)
		{
		drawEllipse(xc,yc,x,y);
		}
		else if(check==3)
		{
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc+y,buffer[i++]);
		putpixel(xc+x,yc-y,buffer[i++]);
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc-y,buffer[i++]);
		}
	}
	p=rysq*(x+0.5)*(x+0.5)+rxsq*(y-1)*(y-1)-rxsq*rysq;
	while(y>0)
	{
		y--;
		py=py-2*rxsq;
		if(p>0)
		p=p+rxsq-py;
		else
		{
			x++;
			px=px+2*rysq;
			p=p+rxsq-py+px;
		}
		if(check==1)
		{
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc+y);
		buffer[i++]= getpixel(xc+x,yc-y);
		buffer[i++]= getpixel(xc+x,yc+y);
		buffer[i++]= getpixel(xc-x,yc-y);
		}
		else if(check==2)
		drawEllipse(xc,yc,x,y);
		else if(check==3)
		{
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc+y,buffer[i++]);
		putpixel(xc+x,yc-y,buffer[i++]);
		putpixel(xc+x,yc+y,buffer[i++]);
		putpixel(xc-x,yc-y,buffer[i++]);
		}
	}
}
int Ellipse()
{
	int x,y,button;
	do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		    int cx=x,cy=y;
		    button=0;
		    delay(200);
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x<560)
			    {
				float radiusx=sqrt(pow(cx-x,2));
				button=0;
				if(cx-radiusx>74&&cx+radiusx<561)
				{
					mousepos(&x,&y,&button);
					xy(x,y);
					if(button==1)
					{
					    if(y>30&&y<300)
					    {
						float radiusy=sqrt(pow(cy-y,2));
						mhide();
						if(cy-radiusy>29&&cy+radiusy<301)
						{
						ellipseMidpoint(cx,cy,radiusx,radiusy,1);
						ellipseMidpoint(cx,cy,radiusx,radiusy,2);
						delay(100);
						mousepos(&x,&y,&button);
						if(button==1)
						ellipseMidpoint(cx,cy,radiusx,radiusy,3);
						}
					    }
					}
				}
			    }
			    else
				return 2;
			}
			show();
		    }
		    while(button==1);
		}
		else
		return 2;
	    }
	}
	while(!kbhit());
return 2;
}
int mfigure(int opt)
{
    int x,y,button;
    switch(opt)
    {
    case 1:
    return (mrectangle());
    case 2:
    return (Ellipse());
 case 3:
 return (Line());
 case 4:
    return (Poly());
	case 5:
	  do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		char ch[2]="";
		int left=x,color=getcolor();
		moveto(x,y);
		settextstyle(SMALL_FONT,HORIZ_DIR,5);
		while((*ch=getch())!=13)
		{
		mousepos(&x,&y,&button);
		xy(x,y);
		x=getx();
		y=gety();
		if(*ch=='\b')
		{
			if(x>left)
			{
			mhide();
			setfillstyle(SOLID_FILL,getpixel(x-8,y-4));
			bar(x-9,y-5,x-2,y+15);
			show();
			moveto(x-8,y);
			}
		}
		else if(x<554)
		{
			mhide();
			outtext(ch);
			show();
		}
		}
		setfillstyle(SOLID_FILL,color);
		}
		else
		return 5;
		}
	}while(!kbhit());
	break;

   case 6:
	   do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		    int left=x,top=y;
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x<560&&y>30&&y<300)
			    {
				mhide();
				line(left,top,x,y);
				left=x;
				top=y;
				show();
			    }
			    else
				return 6;
			}
		    }
		    while(button!=0);
		}
		return 6;
	    }
	}
	while(!kbhit());
	break;
    case 7:
       do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
	    struct fillsettingstype fillinfo;
	    getfillsettings(&fillinfo);
		if(x>75&&x<560&&y>30&&y<300)
		{
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x>75&&x+10<560&&y>30&&y+10<300)
			    {
				mhide();
				setfillstyle(SOLID_FILL,BLACK);
				bar(x,y,x+10,y+10);
				x=x+10;
				y=y+10;
				show();
			    }
			    else
				return 7;
			}
		    }
		    while(button!=0);
		setfillstyle(SOLID_FILL,fillinfo.color);
		}
		return 7;
	    }
	}
	while(!kbhit());
	break;

     case 8:
       do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
	    struct fillsettingstype fillinfo;
	    getfillsettings(&fillinfo);
		if(x>75&&x<560&&y>30&&y<300)
		{
		    do
		    {
			mousepos(&x,&y,&button);
			xy(x,y);
			if(button==1)
			{
			    if(x-5>75&&x+5<560&&y-5>30&&y+5<300)
			    {
				int i;
				mhide();
				fillellipse(x,y,5,5);
				show();
			    }
			    else
				return 8;
			}
		    }
		    while(button!=0);
		setfillstyle(SOLID_FILL,fillinfo.color);
		}
		return 8;
	    }
	}
	while(!kbhit());
	break;

  case 9:
   do
     {
	mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
			int check,p,color;
			int left=x,top=y;
			mhide();
			check=getpixel(x,y);
			do
			{
				p=getpixel(++x,y);
			}while(check==p);
			color=getcolor();
			setcolor(p);
			rectangle(75,14+16,560,330-30);
			line(75,330-30,75,328);
			line(560,330-30,560,328);
			floodfill(left,top,p);
			setcolor(color);
			show();
		}
		else
		return 9;
	    }
     }while(!kbhit());
	break;
     case 10:
     do
	{
	    mousepos(&x,&y,&button);
	    xy(x,y);
	    if(button==1)
	    {
		if(x>75&&x<560&&y>30&&y<300)
		{
		int color;
		gotoxy(36,23);
		mhide();
		color=getpixel(x,y);
		show();
		setcolor(color);
		setfillstyle(SOLID_FILL,color);
		printf("%s",s[color]);
		}
		else
		return 10;
	    }
	}
	while(!kbhit());
	break;
    }
    return 0;
}
void select(int ans)
{
    int x,y,button,i,color;
    do
    {
	if(ans)
	    mfigure(ans);
	mousepos(&x,&y,&button);
	if(button==1)
	{
	    gotoxy(19,23);
	    if(x>42&&x<68&&y>39&&y<61)
	    {
		printf("Square ");
		ans=mfigure(1);
	    }
	    else if(x>42&&x<68&&y<94&&y>66)
	    {
		printf("Circle ");
		ans=mfigure(2);
	    }
	    else if(x<69&&x>41&&y<116&&y>98)
	    {
		printf("Line   ");
		ans=mfigure(3);
	    }
	    else if(44<x&&y>124&&x<68&&y<147)
	    {
		printf("Polygon");
		ans=mfigure(4);
	    }
	    else if(x>42&&y>142&&x<68&&y<176)
	    {
		printf("Text   ");
		ans=mfigure(5);
	    }
	    else if(42<x&&y>181&&x<68&&y<206)
	    {
		printf("Pencil ");
		ans=mfigure(6);
	    }
	    else if(42<x&&y>212&&x<68&&y<235)
	    {
		printf("Eraser ");
		ans=mfigure(7);
	    }
	    else if(x>42&&y>241&&x<68&&y<264)
	    {
		printf("Brush  ");
		ans=mfigure(8);
	    }
	    else if(x>42&&y>270&&x<68&&y<293)
	    {
		printf("Fill   ");
		ans=mfigure(9);
	    }
	    else if(x>42&&y>299&&x<68&&y<321)
	    {
		printf("Picker ");
		ans=mfigure(10);
	    }
	    else if(x>80&&x<135&&y>13&&y<28)
	    {
		mhide();
		rectangle(90,14,135,28);
		delay(200);
		main();
		show();
	    }
	    else if(x>135&&x<190&&y>13&&y<28)
	    {
		mhide();
		rectangle(135,14,190,28);
		open(1);
		show();
	    }
	    else if(x>190&&x<245&&y>13&&y<28)
	    {
		mhide();
		rectangle(190,14,245,28);
		save(1);
		show();
	    }
	    else if(x>245&&x<296&&y>13&&y<28)
	    {
		mhide();
		rectangle(245,14,296,28);
		about();
		show();
	    }
	    else if(x>296&&x<366&&y>13&&y<28)
	    {
		mhide();
		rectangle(296,14,366,28);
		exit(0);
	    }
	    else
	    {
		gotoxy(36,23);
		for(color=0,i=35; color<16; color++,i+=18)
		{
		    if(x>566&&y>i+1&&596>x&&y<i+13)
		    {
			printf("%s",s[color]);
			setcolor(color);
			rectangle(75,14+16,560,330-30);
			line(75,330-30,75,328);
			line(560,330-30,560,328);
			setfillstyle(SOLID_FILL,color);
		    }
		}
	    }
	  delay(200);
	}
	else
	    xy(x,y);
    }
    while(!kbhit());
}
void main()
{
    int gd=9,gm=1,x,y;
    initgraph(&gd,&gm,"..\\BGI");
    cleardevice();
    fwindow(35,14,600,330);
    outtextxy(639/2-30,1,"Paint");
    detect();
    show();
    logo();
    restrict(35,15,600,330);
    //gotoxy(19,23);
    //printf("Square");
    gotoxy(36,23);
    printf("White");
    select(0);
    getch();
    closegraph();
    exit(0);
}
void mousepos(int *x1,int *y1,int *button)
{
    in.x.ax=3;
    int86(0x33,&in,&out);
    *x1=out.x.cx;
    *y1=out.x.dx;
    *button=out.x.bx;
}
void mhide()
{
    in.x.ax=2;
    int86(0x33,&in,&out);
}
void detect()
{
    in.x.ax=0;
    int86(0x33,&in,&out);
}
void show()
{
    in.x.ax=1;
    int86(0x33,&in,&out);
}
void restrict(int x1,int y1,int x2,int y2)
{
    in.x.ax=7;
    in.x.cx=x1;
    in.x.dx=x2;
    int86(0x33,&in,&out);
    in.x.ax=8;
    in.x.cx=y1;
    in.x.dx=y2;
    int86(0x33,&in,&out);
}
void logo()
{
    int p[12]= {53,125,40,147,67,147,63,125,53,125};
    int i,color;
    setcolor(WHITE);
    rectangle(43,40,67,60);
    ellipse(55,80,0,360,12,12);
    line(45,102,64,115);
    drawpoly(5,p);
    rectangle(43,155,67,175);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
    outtextxy(50,153,"A");
     rectangle(43,183,67,205);
     line(48,200,60,188);
     line(48,195,57,186);
     line(53,200,63,190);
     line(57,186,63,190);
     line(48,200,48,195);
     line(53,200,48,200);
    setusercharsize(1, 3, 1, 2);
  //  outtextxy(41,227,"Pencil");
    rectangle(43,213,67,234);
    bar3d(45,223,55,230,8,10);
    rectangle(43,242,67,263);
    arc(46,258,3,85,10);
    line(47,250,47,258);
    line(47,258,57,258);
    line(47,250,52,245);
    line(57,258,63,252);
    setfillstyle(SOLID_FILL,BROWN);
    floodfill(50,254,WHITE);
    line(52,245,63,252);
    rectangle(43,271,67,292);
      line(47,275,63,275);
      line(63,275,63,287);
      line(63,287,50,287);
      line(50,287,50,280);
      line(50,280,47,275);
      setfillstyle(SOLID_FILL,CYAN);      //281
      bar(51,281,62,284);
      rectangle(43,300,67,320);
      rectangle(53,302,57,306);
      rectangle(47,306,63,312);
      setfillstyle(SOLID_FILL,RED);
      bar(52,312,58,318);
    for(color=0,i=35; color<16; color++)
    {
	setfillstyle(SOLID_FILL,color);
	setcolor(WHITE);
	rectangle(567,i,595,i+12);
	setfillstyle(SOLID_FILL,color);
	floodfill(572,i+3,WHITE);
	i+=18;
    }
}
void dwindow(int xt,int yt,int xb,int yb,int outclr,int inclr)
{
    int x=getcolor();
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,outclr);
    bar(xt,yt,xb,yb);
     setfillstyle(SOLID_FILL,inclr);
    bar(xt+15,yt+15,xb-15,yb-15);
    rectangle(xt+15,yt+15,xb-15,yb-15);
    setcolor(x);
}
void fwindow(int xt,int yt,int xb,int yb)
{
    int color=getcolor();
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    line(xt,yt+15,xt,yb);
    line(xb,yt+15,xb,yb);
    line(xt,yb,xb,yb);
    //rectangle(xt,yt+16,xb,yb);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    //setbkcolor(BLUE);
    setfillstyle(SOLID_FILL,CYAN);
    setcolor(BLACK);
    bar(xt,yt,xb,yt+14);
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(100,yt+4,"New");
    outtextxy(150,yt+4,"Open");
    outtextxy(200,yt+4,"Save");
    outtextxy(250,yt+4,"About");
    outtextxy(310,yt+4,"Exit");
    setcolor(15);
    setcolor(WHITE);
    rectangle(75,yt+16,560,yb-30);
    line(75,yb-30,75,yb-2);
    line(560,yb-30,560,yb-2);
    gotoxy(11,23);
    printf("Figure:");
    gotoxy(28,23);
    printf("Colour:");
    gotoxy(50,23);
    printf("X:   ");
    gotoxy(57,23);
    printf("Y:   ");
    setcolor(color);
    //gotoxy();
    /*printf("X:");
    gotoxy(16,23);
    printf("Y:"); */
}