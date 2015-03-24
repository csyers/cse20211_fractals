#include <stdio.h>
#include "gfx3.h"
#include <math.h>
#include <time.h>

static int xsize = 800;
static int ysize = 800;

void snowflake(int, int, int, int, float, int, int, int, int);

int main()
{
 srand ( time(NULL) );
 int i;
 char action;					// variable for storing gfx_wait() reception
 int color[48];					// the following 6 lines create variables for the properties of the 16 fractals.
 int num_arms[16];				// color contains 48 spots because each factal needs 3 colors (red, green, blue)
 int phase[16];					
 int size[16];	
 int complex[16];				
 int xpos[16] = {100, 300, 500, 700, 100, 300, 500, 700, 100, 300, 500, 700, 100, 300, 500, 700};		// xpos for each fractal. Paired with ypos,
 int ypos[16] = {100, 100, 100, 100, 300, 300, 300, 300, 500, 500, 500, 500, 700, 700, 700, 700};		// these create the center points for 16 evenly spaced
 gfx_open(xsize,ysize,"Snowflake Gallery");									// fractals
 while(1){
   if((action=gfx_wait())=='q') break;				// quit if the user presses 'q'
   else{							// do this if the user presses anything else
     for(i=0;i<48;i++) color[i]=rand()%256;			// populates color[] with 48 random color scale values between 0 and 255
     for(i=0;i<16;i++)						// loop to populate phase with 16 random integers up to 3000 (phase is the angle in radians from vertical)
     {								// gives num arms a value between 4 and 7.
       phase[i]=rand()%3000;					// populates 16 sizes with an integer between 35 and 75 pixels
       num_arms[i]=4+rand()%4;					// populates complex with a 1 or 0 to randomize if the snowflake is complex or not
       size[i]=35+rand()%41;
       complex[i]=rand()%2;
     }
     gfx_clear();						// clears the graphics window
     for(i=0;i<16;i++)						// loop to create the 16 fractals. Each one uses the random properties generated above
     {
     snowflake(color[i],color[i+16],color[i+32],num_arms[i],phase[i],xpos[i],ypos[i],size[i],complex[i]);
     }
   }
 }

}

void snowflake(int r, int g, int b, int num_arms, float phase, int x, int y, int l, int complex)	
{
  if (l<4) return;			// base case. stops when the branch gets to under 4 pixels
  int i;
  gfx_color(r,g,b);			// sets the color to the color passed into it (from the first three parameters)
  for(i=0;i<num_arms;i++)		// loop to draw each branch and recursively call function
  {
    gfx_line(x,y,x+l*sin(i*2*M_PI/num_arms+phase),y-l*cos(i*2*M_PI/num_arms+phase));			// draw the branch from the start point to the new point that is l pixels away and at angle related to num_arms
    snowflake(r,g,b,num_arms,phase,x+l*sin(i*2*M_PI/num_arms+phase),y-l*cos(i*2*M_PI/num_arms+phase),l/3,complex);	// recursively calls a new snowflake at the end of each branch
    if (complex)  snowflake(r,g,b,num_arms,phase,x+.5*l*sin(i*2*M_PI/num_arms+phase),y-.5*l*cos(i*2*M_PI/num_arms+phase),l/3,complex);	// if it is a complex snowflake, draw another snowflake at the midpoint of each branch
  }
}
