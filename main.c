#include <stdio.h>
#include <stdlib.h>

/* Screen size */
#define MAXX 40
#define MAXY 23

/* Probablity (x/256) for certain magic. See generate_maze(). */
#define PROB 138


/* Characters */

#define WALL '#'
#define FLOOR ' '
#define UNOPENED '/'
#define TRAVERSED '.'
#define PATH '~'

/* maze */

char maze[MAXX][MAXY];

/* stack */

#define SMAX 768
int stack[SMAX];
int sptr = 0;
int maxsptr = 0;

/* pseudo-random number generator */

unsigned short randseed = 69;

/* General location information */

int x, y;
int starty, endy;

/* Set designations */

char *sets = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int setptr = 0;

/* Debugging & monitoring =========================================== */

/* Prints out the maze. */
void print_maze(void) {
  int x, y;

  for(y=0; y<MAXY; y++) {
    for(x=0; x<MAXX; x++) {
      putchar(maze[x][y]);
    }
    putchar('\n');
  }
}

/* Pseudorandom number generator ==================================== */

/* We could use BASIC ROM's rnd function, but personally, I have no
   clue whatsoever on how to use that. Well, we only need random
   numbers between 0..10; This should do the trick. We can use RDTIM
   to get an appropriate seed.
*/

/* Random number generator initialization */
void randgen_init(void)
{
  randseed = time(NULL) % 256;
}

/* Generate pseudorandom number */
unsigned short rnd(void)
{
  randseed += 42; /* Magic number??? */
  randseed %= 256; /* ADC + CLC will do the trick here... */
  return(randseed);
}

/* Stack implementation ============================================= */

/* The stack needs to be implemented in the actual assembler program
   as well - looks like that in order to find the solution using
   normal depth-first search, approximately more than 256 bytes of
   stack space is required. Subroutine calls would also mangle the
   stack quite nastily, so I'll implement my own stack, thank you very
   much.
*/


/* Push number to stack */
void push(int n)
{
  if(sptr++ > SMAX) {
    printf(" *** Pretty tough maze: Stack overflow!\n");
    exit(1);
  } else {
    stack[sptr] = n;
  }
  /* Keep track of maximum stack use */
  if(sptr > maxsptr)
    maxsptr = sptr;
}

int pop(void)
{
  if(--sptr < 0) {
    printf(" *** *Really* fatal error: Stack underflow!\n");
    exit(1);
  } else {
    return(stack[sptr+1]);
  }
  return 0; /* to keep compiler happy */
}

/* Maze stuff ======================================================= */

/* generates maze grid. */
void make_grid(void)
{
  /* Clean the whole maze */
  for(y=0; y<MAXY; y++) {
    for(x=0; x<MAXX; x++) {
      /* printf("x,y=%d,%d\n",x,y); */
      maze[x][y]=FLOOR;
    }
  }

  /* Fill the borders. First l/r sides  */
  for(y=0; y<MAXY; y++) {
    maze[0][y] = WALL;
    maze[MAXX-1][y] = WALL;
  }

  /* Then the top/bottom sides */
  for(x=0; x<MAXX; x++) {
    maze[x][0] = WALL;
    maze[x][MAXY-1] = WALL;
  }

  /* Generate a grid, y'know... */

  for(y=0; y<MAXY; y += 2) {
    for(x=0; x<MAXX; x++) {
      maze[x][y] = WALL;
    }
  }
  /* Clean the other side */
  for(y=0; y<MAXY; y++) {
    maze[MAXX][y] = FLOOR;
  }
  for(x=0; x<MAXX; x += 2) {
    for(y=0; y<MAXY; y++) {
      maze[x][y] = WALL;
    }
  }

  /* Start and end points */


}

int main()
{
    randgen_init();

  make_grid();
  print_maze();
  printf("Starting situation:\n");
    return 0;
}
