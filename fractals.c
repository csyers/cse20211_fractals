// Christopher Syers	cse20211	Lab 10
// factals.c		December 4, 2014

#include <stdio.h>
#include <math.h>
#include "gfx3.h"
static int xsize = 800;					// width of window
static int ysize = 800;					// height of window

// functions for each recursive shape
void sierpinski(int, int, int, int, int, int);	
void shrinksquares(int, int, int);
void spiralsquares(float, float, float);
void circlelace(int, int, int);
void snowflake(int, int, int);
void tree(int, int, float, float);
void fern(int, int, int, float);
void spiral(float, float, float, float, int);

int main()
{
 int margin = 20;				// distance from border for sierpinski triangle
 char choice;				
 gfx_open(xsize,ysize,"Fractals");
 while(1){
   if((choice=gfx_wait())=='q') break;		// quits when 'q' is pressed
   else{
     switch(choice){
       case '1':								// if the user pressed '1', draw sierpinski triangles
	 gfx_clear();
         sierpinski(margin,margin,xsize-margin,margin,xsize/2,ysize-margin);		
	 break;
       case '2':								
	 gfx_clear();
         shrinksquares(xsize/2,ysize/2,xsize/2);				// '2' draws shrinking squares starting in the middle of screen
 	 break;
       case '3':
	 gfx_clear();						
	 spiralsquares(1,0,5);							// '3' draws spiral squares with start size 1, start angle 0 radians, and start radius 5
	 break;
       case '4':
	 gfx_clear();
	 circlelace(xsize/2,ysize/2,xsize/3);					// '4' draws circles on circles fractal starting in the middle of screen
	 break;
       case '5':
	 gfx_clear();
	 snowflake(xsize/2,ysize/2,xsize/3);					// '5' draws snowflakes starting in the middle
         break;	
       case '6':
	 gfx_clear();
	 tree(xsize/2,ysize,ysize*.30,0);					// '6' draws a tree starting at the middle of the bottom of screen, height 30% of ysize
         break;
       case '7':
	 gfx_clear();
	 fern(xsize/2,ysize,ysize*(65./100),0);					// '7' draws a fern starting from the middle of the bottom of the screen
	 break;
       case '8':
	 gfx_clear();
	 spiral(xsize/2,ysize/2,2,xsize,0);						// draws a spiral of spirals
	 break;
     }
   }
 }
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
   // Base case. 
   if( abs(x2-x1) < 2 ) return;

   // Draw the triangle
   gfx_triangle(x1,y1,x2,y2,x3,y3);

   // Recursive calls
   sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
   sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
   sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void shrinksquares(int x, int y, int l)
{
  if (l<8) return;			// base case (stops when the square length gets below 8 pixels
  
  gfx_line(x-l/2,y-l/2,x+l/2,y-l/2);	// draw the square. 4 lines connecting 4 corners
  gfx_line(x+l/2,y-l/2,x+l/2,y+l/2);
  gfx_line(x+l/2,y+l/2,x-l/2,y+l/2);
  gfx_line(x-l/2,y+l/2,x-l/2,y-l/2);

  shrinksquares(x-l/2,y-l/2,l/2);	// recursive calls recall function using the 4 corners as the center point for the next square, which has
  shrinksquares(x+l/2,y-l/2,l/2);	// a length of 1/2 the previous length
  shrinksquares(x+l/2,y+l/2,l/2);
  shrinksquares(x-l/2,y+l/2,l/2);
}

void spiralsquares(float s, float theta, float r)
{
  if (r>xsize) return;			// base case. stops when the radius from center point gets larger than half of the screen size 

  gfx_rectangle(xsize/2+r*cos(theta),ysize/2-r*sin(theta),s,s);			// draws a rectangle that is r pixels away from the middle at angle theta with size s
  
  spiralsquares(1.05*s,theta+.4,1.05*r);					// recursive calls with s and r increased by 5%, and theta increased by .4 radians
}

void circlelace(int x, int y, int r)
{
 int i;
 if (r<1) return;		// base case. stops when radius gets below 1

 gfx_circle(x,y,r);		// draws circle

 for(i=0;i<=5;i++)		// recursive calls. 5 iterations to draw 5 new circles around the circumference of the previously drawn circle
 {
   circlelace(x+r*sin(i*M_PI/3),y-r*cos(i*M_PI/3),r/3);		// start position adjusted and radius divided by 3 each time
 }
}

void snowflake(int x, int y, int l)
{
 int i;
 if (l<1) return;			// base case. Stops when the length of the brach gets below 1.

 for(i=0;i<5;i++)			// 1 call for each arm on tyhe snowflake
 {
   gfx_line(x,y,x+l*sin(i*2*M_PI/5),y-l*cos(i*2*M_PI/5));	// draw the branch at angle related to i
   snowflake(x+l*sin(i*2*M_PI/5),y-l*cos(i*2*M_PI/5),l/3);	// recursive call with center position at the end of each branch, and the branch length divided by 3
 }

}

void tree(int x, int y, float l, float theta)
{
 if(l<3) return;			// base case. stops when the length of a branch is lower than 3

 gfx_line(x,y,x+l*sin(theta),y-l*cos(theta));		// draws a line at angle theta and with length l from the original point
 
 tree(x+l*sin(theta),y-l*cos(theta),l*.68,theta+0.628318531);		// recursive call for the next branch with theta adjusted by 36 degrees
 tree(x+l*sin(theta),y-l*cos(theta),l*.68,theta-0.628318531);		// recursive call for the next branch with theta adjusted by 36 degrees the other way
}

void fern(int x, int y, int l, float theta)
{
 int i;
 if (l<3) return;							// base case. stops when the length of the branch is less than 3 pixels

 gfx_line(x,y,x+l*sin(theta),y-l*cos(theta));				// draws line for stem starting at x,y and going to a point l pixels away at theta degrees

 for(i=1;i<=4;i++)							// 4 times through these 2 recurisve calls gets 8 branches
 {
   fern(x+(i/4.)*l*sin(theta),y-(i/4.)*l*cos(theta),l*(3./10),theta+0.628318531);		// recursive call with the start position at an increment related to i
   fern(x+(i/4.)*l*sin(theta),y-(i/4.)*l*cos(theta),l*(3./10),theta-0.628318531);		// along the stem, and angle adjusted by +- 36 degrees
 }
}

void spiral(float x, float y, float r, float rmax, int step)
{
  float x1,y1;
  if (r>rmax) return;
  x1 = x+r*cos(M_PI*step/10);
  y1 = y-r*sin(M_PI*step/10);
  step++;
  gfx_point(x1,y1);
  float rincrease = r*1.05;
  float rdecrease = r/4;
  spiral(x1,y1,2,rdecrease,step);
  spiral(x,y,rincrease,rmax,step);

}
