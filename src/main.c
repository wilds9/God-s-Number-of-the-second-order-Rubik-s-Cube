#include <stdio.h>
#include <stdlib.h>

// Loop variable:
// i: for database[5040][][]
// j: for database[][2187][]
// k: for database[][][MAX_STEP]
// k: for rotation_sequence[MAX_STEP]
// m: for cube[16]
// q: for (*rotate[])

// Axis:
// x-axis points backward
// y-axis points rightward
// z-axis points downward

#define MAX_STEP 11

int rotation_sequence[MAX_STEP];

// The state of the second-order Rubik's Cube
int cube[16];
int cube_pre[16];
int cube_restored[16]={0,1,2,3,4,5,6,7,3,3,3,3,3,3,3,3};

int database[5040][2187][MAX_STEP];
int database_length[5040][2187];

void copy_cube(int source_in[16],int destination_in[16])
{
  // copy the state of the Rubik's Cube
  int m;
  for(m=0;m<16;m++)
    {
      destination_in[m] = source_in[m];
    }
}

void copy_rotation_sequence(int source_in[MAX_STEP],int destination_in[MAX_STEP])
{
  int k;
  for(k=MAX_STEP-1;k>=0;k--)
    {
      if(source_in[k]==0)
	{
	  break;
	}
      else
	{
	  destination_in[k] = source_in[k];
	}
    }
}

int direction_change_x(int direction_in)
{
  // Rotate along the x axis (only used by rotate_back_*())
  if(direction_in==1)      return 1;
  else if(direction_in==2) return 3;
  else return 2;
}

int direction_change_y(int direction_in)
{
  // Rotate along the y axis (only used by rotate_right_*())
  if(direction_in==1)      return 3;
  else if(direction_in==2) return 2;
  else return 1;
}

int direction_change_z(int direction_in)
{
  // Rotate along the z axis (only used by rotate_down_*())
  if(direction_in==1)      return 2;
  else if(direction_in==2) return 1;
  else return 3;
}

void rotate_back_90()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]  = cube[6];
  cube[10] = direction_change_x(cube[14]);
  cube[6]  = cube[5];
  cube[14] = direction_change_x(cube[13]);
  cube[5]  = cube[1];
  cube[13] = direction_change_x(cube[9]);
  cube[1]  = position;
  cube[9]  = direction_change_x(direction);
}

void rotate_back_180()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]   = cube[5];
  cube[10]  = cube[13];
  cube[5]   = position;
  cube[13]  = direction;
  position  = cube[1];
  direction = cube[9];
  cube[1]   = cube[6];
  cube[9]   = cube[14];
  cube[6]   = position;
  cube[14]  = direction;
}

void rotate_back_270()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]  = cube[1];
  cube[10] = direction_change_x(cube[9]);
  cube[1]  = cube[5];
  cube[9]  = direction_change_x(cube[13]);
  cube[5]  = cube[6];
  cube[13] = direction_change_x(cube[14]);
  cube[6]  = position;
  cube[14] = direction_change_x(direction);
}

void rotate_down_90()
{
  int position  = cube[7];
  int direction = cube[15];
  cube[7]  = cube[4];
  cube[15] = direction_change_z(cube[12]);
  cube[4]  = cube[5];
  cube[12] = direction_change_z(cube[13]);
  cube[5]  = cube[6];
  cube[13] = direction_change_z(cube[14]);
  cube[6]  = position;
  cube[14] = direction_change_z(direction);
}

void rotate_down_180()
{
  int position = cube[7];
  int direction = cube[15];
  cube[7]   = cube[5];
  cube[15]  = cube[13];
  cube[5]   = position;
  cube[13]  = direction;
  position  = cube[4];
  direction = cube[12];
  cube[4]   = cube[6];
  cube[12]  = cube[14];
  cube[6]   = position;
  cube[14]  = direction;
}

void rotate_down_270()
{
  int position  = cube[7];
  int direction = cube[15];
  cube[7]  = cube[6];
  cube[15] = direction_change_z(cube[14]);
  cube[6]  = cube[5];
  cube[14] = direction_change_z(cube[13]);
  cube[5]  = cube[4];
  cube[13] = direction_change_z(cube[12]);
  cube[4]  = position;
  cube[12] = direction_change_z(direction);
}

void rotate_right_90()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]  = cube[3];
  cube[10] = direction_change_y(cube[11]);
  cube[3]  = cube[7];
  cube[11] = direction_change_y(cube[15]);
  cube[7]  = cube[6];
  cube[15] = direction_change_y(cube[14]);
  cube[6]  = position;
  cube[14] = direction_change_y(direction);
}

void rotate_right_180()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]  = cube[7];
  cube[10] = cube[15];
  cube[7]  = position;
  cube[15] = direction;
  position = cube[6];
  direction= cube[14];
  cube[6]  = cube[3];
  cube[14] = cube[11];
  cube[3]  = position;
  cube[11] = direction;
}

void rotate_right_270()
{
  int position  = cube[2];
  int direction = cube[10];
  cube[2]  = cube[6];
  cube[10] = direction_change_y(cube[14]);
  cube[6]  = cube[7];
  cube[14] = direction_change_y(cube[15]);
  cube[7]  = cube[3];
  cube[15] = direction_change_y(cube[11]);
  cube[3]  = position;
  cube[11] = direction_change_y(direction);
}

void (*rotate[])(void)={
  rotate_down_90, rotate_down_180, rotate_down_270,
  rotate_back_90, rotate_back_180, rotate_back_270,
  rotate_right_90, rotate_right_180, rotate_right_270};

int factorial(int n_in)
{
  // In order to reduce the amount of calculation, the factorial result is directly given
  switch(n_in)
    {
    case 0: return 1; break;
    case 1: return 1; break;
    case 2: return 2; break;
    case 3: return 6; break;
    case 4: return 24; break;
    case 5: return 120; break;
    case 6: return 720; break;
    case 7: return 5040; break;
    default:printf("Error: in factorial, n_in = %d\n",n_in); exit(-1); break;
    }
}

int get_position_unique_value()
{
  int cube_temp[16];
  int m,p;
  int position_unique_value = 0;

  copy_cube(cube,cube_temp);
  position_unique_value += (cube_temp[1]-1) * factorial(6);
  for(p=2;p<=6;p++)
    {
      for(m=p;m<8;m++)
	{
	  if(cube_temp[m]>cube_temp[p-1]) cube_temp[m]--;
	}
      position_unique_value += (cube_temp[p]-1) * factorial(7-p);
    }
  return position_unique_value;
}

int get_direction_unique_value()
{
  int m;
  int direction_unique_value = 0;
  for(m=9;m<16;m++)
    {
      direction_unique_value = 3*direction_unique_value + cube[m] - 1;
    }
  return direction_unique_value;
}

void initialize()
{
  int i,j,k;
  for(i=0;i<5040;i++)
    {
      for(j=0;j<2187;j++)
        {
	  for(k=0;k<MAX_STEP;k++)
	    {
	      database[i][j][k] = 0;
	    }
	  database_length[i][j] = -1;
        }
    }
  database_length[0][2186] = 0;
}

int count()
{
  // Count how many states have been found.
  int i,j;
  int counter = 0;
  for(i=0;i<5040;i++)
    {
      for(j=0;j<2187;j++)
	{
	  if(database_length[i][j]>-1) counter++;
	}
    }
  return counter;
}

void run(int n_in)
{
  int i;
  int j;
  int k;
  int q;
  int pos_uv;
  int dir_uv;
  for(i=0;i<5040;i++)
    {
      for(j=0;j<2187;j++)
	{
	  if( database_length[i][j]!=(n_in-1) ) continue;

	  // I have found the "plan a" is wrong, but I don't understand.
	  // plan a
	  /* copy_rotation_sequence(database[i][j],rotation_sequence); */

	  // plan b
	  for(k=0;k<MAX_STEP;k++) rotation_sequence[k] = database[i][j][k];

	  copy_cube(cube_restored,cube);
	  for(k=MAX_STEP-1;k>=0;k--)
	    {
	      if(rotation_sequence[k]>0) rotate[rotation_sequence[k]-1]();
	      else break;
	    }
	  copy_cube(cube,cube_pre);

	  for(q=1;q<=9;q++)
	    {
	      rotation_sequence[MAX_STEP-n_in] = q;

	      if( (rotation_sequence[MAX_STEP-n_in]+2)/3 == (rotation_sequence[MAX_STEP-n_in+1]+2)/3 ) continue;

	      copy_cube(cube_pre,cube);
	      rotate[q-1]();
	      pos_uv = get_position_unique_value();
	      dir_uv = get_direction_unique_value();
	      if(database_length[pos_uv][dir_uv]==-1)
		{
		  copy_rotation_sequence(rotation_sequence,database[pos_uv][dir_uv]);
		  database_length[pos_uv][dir_uv] = n_in;
		}
	    }
	}
    }
}

void main()
{
  initialize();
  for(int i=1;i<=11;i++)
    {
      run(i);
      printf("%d: %d\n",i,count());
    }
}
