#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>

int maxx,maxy;

void win(int m[500],int n[500],int con,int number);
void mainMenu();
void border(int maxx,int maxy);
void end(int m[500],int n[500],int m1[500],int n1[500],int con,int con1,int num);

void main(void){

	//Initialization
	int m[500],n[500],m1[500],n1[500],con=3,con1=3;
	int x=13,y=14;
	int s,k,f,u;
	int ch,x1=13,y1=314,p,q,spd=100;
	
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	
	//Main Menu
	mainMenu();

	//Check for ESC
	ch=getch();
	if(ch==27) exit(0);
	cleardevice();
	maxx=getmaxx()-20;
	maxy=getmaxy()-20;

	randomize();		//This function initializes the start and stop

	//Randomizes the position of the fruit
	p=random(maxx-39);
	int temp=p%13;
	p=p-temp+13;
	q=random(maxy-42);
	temp=q%14;
	q=q-temp+14;

	int a=0,i=0,j;
	int a1=0;

	while(1){
		//Fruit
		 setcolor(WHITE);
		 setfillstyle(SOLID_FILL,con%4+con1%4);
		 circle(p,q,5);
		 floodfill(p,q,WHITE);

		 //Border
		 border(maxx,maxy);

		//Check for input
		if( kbhit() )
		{
			ch=getch();
			if(ch==72&& a!=2) a=1;
			if(ch==80&& a!=1) a=2;
			if(ch==75&& a!=4) a=3;
			if(ch==77&& a!=3) a=4;

			if(ch=='w'&& a1!=2) a1=1;
			if(ch=='s'&& a1!=1) a1=2;
			if(ch=='a'&& a1!=4) a1=3;
			if(ch=='d'&& a1!=3) a1=4;
		}
		else
		{
			if(ch==27) break;
		}

		//Logic part
		if(i<20){
			m[i]=x;
			n[i]=y;
			m1[i]=x1;
			n1[i]=y1;
			i++;
		}

		if(i>=20)
		{
			for(j=con;j>=0;j--){
				m[1+j]=m[j];
				n[1+j]=n[j];
			}
			m[0]=x;
			n[0]=y;
			for(s=con1;s>=0;s--){
				m1[1+s]=m1[s];
				n1[1+s]=n1[s];
			}
			m1[0]=x1;
			n1[0]=y1;

			//Head
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,con+6);
			circle(m[0],n[0],8);
			floodfill(m[0],n[0],WHITE);

			//Tail
			setcolor(WHITE);
			for(j=1;j<con;j++){
				setfillstyle(SOLID_FILL,con+23);
				circle(m[j],n[j],5);
				floodfill(m[j],n[j],WHITE);
			}

			//Head2
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,con1+15);
			circle(m1[0],n1[0],8);
			floodfill(m1[0],n1[0],WHITE);

			//Tail2
			setcolor(WHITE);
			for(k=1;k<con1;k++){
				setfillstyle(SOLID_FILL,con1+k%3);
				circle(m1[k],n1[k],5);
				floodfill(m1[k],n1[k],WHITE);
			}
			delay(spd);

			//Trailing part of the snake
			//Head Part
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			circle(m[0],n[0],8);
			floodfill(m[0],n[0],BLACK);

			//Tail part
			for(f=1;f<con;f++){
				setcolor(BLACK);
				setfillstyle(SOLID_FILL,BLACK);
				circle(m[f],n[f],5);
				floodfill(m[f],n[f],BLACK);
			}

			//Head Part2
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			circle(m1[0],n1[0],8);
			floodfill(m1[0],n1[0],BLACK);

			//Tail part2
			for(u=1;u<con1;u++){
				setcolor(BLACK);
				setfillstyle(SOLID_FILL,BLACK);
				circle(m1[u],n1[u],5);
				floodfill(m1[u],n1[u],BLACK);
			}
		}
			int check1;
			for(check1=1;check1<con;check1++){
					if(m[0]==m[check1] && n[0]==n[check1]) end(m,n,m1,n1,con,con1,1);
					else continue;
			}

			int check2;
			for(check2=1;check2<con1;check2++){
					if(m1[0]==m1[check2] && n1[0]==n1[check2]) end(m,n,m1,n1,con,con1,2);
					else continue;
			}

			//New Position of fruit
			if(x==p&&y==q){
				con=con+1;
				p=random(maxx-39); temp=p%13;  p=p-temp+39;
				q=random(maxy-42); temp=q%14;  q=q-temp+42;
			}
			if(con>16)
				win(m,n,con,1);

			if(x1==p&&y1==q){
				con1=con1+1;
				p=random(maxx-39); temp=p%13;  p=p-temp+39;
				q=random(maxy-42); temp=q%14;  q=q-temp+42;
			}
			if(con1>16)
				win(m1,n1,con1,2);

			//Border teleportation
			if(a==1)  y =  y-14; if(y<0) { temp=maxy%14;y=maxy-temp;}
			if(a==2)  y =  y+14; if(y>maxy) y=0;
			if(a==3)  x =  x-13; if(x<0) { temp=maxx%13;x=maxx-temp;}
			if(a==4)  x =  x+13; if(x>maxx) x=0;
			if(a==0){  y = y+14 ;  x=x+13; }

			if(a1==1)  y1 =  y1-14; if(y1<0) { temp=maxy%14;y1=maxy-temp;}
			if(a1==2)  y1 =  y1+14; if(y1>maxy) y1=0;
			if(a1==3)  x1 =  x1-13; if(x1<0) { temp=maxx%13;x1=maxx-temp;}
			if(a1==4)  x1 =  x1+13; if(x1>maxx) x1=0;
			if(a1==0){  y1 = y1+14 ;  x1=x1+13; }
		}

 }

void win(int m[500],int n[500],int con,int number)
{
	int c,v;
	cleardevice();
	setcolor(WHITE);
	for(c=0;c<3;c++){
		for(v=0;v<=con;v++){
		   setfillstyle(SOLID_FILL,BLUE);
		   circle(m[v],n[v],5);
		   floodfill(m[v],n[v],WHITE);
		}
	delay(500);
	cleardevice();
	delay(500);
	}
	border(maxx,maxy);
	settextstyle(3,0,5);
	if(number==1)
		outtextxy(150,180," PLAYER 1 WINS ");
	if(number==2)
		outtextxy(150,180," PLAYER 2 WINS ");
	getch();
	getch();
	exit(0);
}

void mainMenu(){
	setcolor(GREEN);
	settextstyle(3,0,6);
	outtextxy(120,2," SNAKE BATTLE ");

	setcolor(YELLOW);
	settextstyle(6,0,2);
	outtextxy(20,80," Use Arrow Keys To Direct Snake1  ");
	outtextxy(20,120," Use w/a/s/d To Direct Snake2  ");
	outtextxy(20,160," Go For The Fruits Until One Player Wins The Game ");
	outtextxy(20,200," Press 'ESC' Anytime To Exit ");

	setcolor(WHITE);
	outtextxy(20,320," Press Any Key To Continue ");
}

void border(int maxx,int maxy){
	setcolor(GREEN);
	rectangle(0,0,maxx,maxy);
}

void end(int m[500],int n[500],int m1[500],int n1[500],int con,int con1,int num){
	int m0[500],n0[500],con0;
	int j,i,g,h;
	if(num==1){
		for(g=0;g<500;g++){
			m0[g]=m[g];
			n0[g]=n[g];
			con0=con;
		}
	}
	else{
		for(h=0;h<500;h++){
			m0[h]=m1[h];
			n0[h]=n1[h];
			con0=con1;
		}
	}
   setcolor(WHITE);
   for(i=0;i<3;i++){ 	//Blinking Effect
		delay(500);
		cleardevice();
		delay(500);
		for(j=0;j<=con0;j++){
		   setfillstyle(SOLID_FILL,RED);
		   circle(m0[j],n0[j],5);
		   floodfill(m0[j],n0[j],WHITE);
		}

		settextstyle(3,0,4);
		outtextxy(200,180," GAME OVER ");

	}
	cleardevice();

	if(num==1){
		win(m1,n1,con1,2);
	}
	else{
		win(m,n,con,1);
	}

}