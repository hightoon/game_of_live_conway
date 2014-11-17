#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 5
#define N 5
int life[M][N];
int life_snapshot[M][N];

int isAlive(int numOfLiveNb, int selfState)
{
  return numOfLiveNb == 3 || (numOfLiveNb == 2 && selfState);
}

int get_nb_live_num(int x, int y)
{
  int n = 0;
  for(int i=x-1; i<=x+1; i++)
    for(int j=y-1; j<=y+1; j++)
      n += life[i][j];
  return n - life[x][y];
}

void get_every_next_state()
{
  for(int i=0; i<M; i++)
    for(int j=0; j<N; j++)
      life_snapshot[i][j] = isAlive(get_nb_live_num(i,j), life[i][j]);
}

void get_next_gen()
{
  memcpy(life_snapshot, life, sizeof(life));
  get_every_next_state();
  memcpy(life, life_snapshot, sizeof(life));
}

/* UT cases */
int test_isAlive_dead_no_live_nb()
{
  int expected = 0;
  return expected == isAlive(0, 0);
}

int test_isAlive_dead_less_two_nb()
{
  int expected = 0;
  return expected == isAlive(1, 1);
}

int test_isAlive_live_with_two_nb()
{
  int expected = 1;
  return expected == isAlive(2, 1);
}

int test_isAlive_live_with_three_nb_self_live()
{
  int expected = 1;
  return expected == isAlive(3,1);
}

int test_isAlive_live_with_three_nb_self_die()
{
  int expected = 1;
  return expected == isAlive(3,0);
}

int test_isAlive_die_with_four_nb_self_die()
{
  int expected = 0;
  return  expected == isAlive(4,0);
}
int test_isAlive_die_wiht_fouw_nb_self_live()
{
  int expected = 0;
  return expected == isAlive(4,1);
}

int test_nb_num()
{
  life[1][1] = 1;
  life[1][2] = 1;
  life[2][1] = 1;
  int nCount = get_nb_live_num(2,2);
  if(nCount == 3) return 1;
  else return 0;
}

int test_nb_num_2_live_nb()
{
  life[1][1] = 1;
  life[1][2] = 0;
  life[2][1] = 1;
  return 2 == get_nb_live_num(2,2);
}

int test_still()
{
  (void)memset(life, 0, sizeof(life));
  life[1][1]=life[1][2]=life[2][1]=1;
  get_next_gen();
  return life[1][1]==1 && life[1][2]==1 && life[2][1]==1 && life[2][2]==1;
}

void screen_print()
{
  int i, j;
  char symbols[2] = {'-', '@'};
  for (i=0; i<M; i++) {
    for (j=0; j<N; j++)
      printf ("%c", symbols[life[i][j]]);
    printf("\n");
  }
}

int main()
{

#ifdef UT
  int res = 0;
  res = test_isAlive_dead_no_live_nb();
  if (!res) printf("failed\n");
  else printf("passed\n");
  res = test_isAlive_dead_less_two_nb();
  if(res) printf("passed\n");
  else printf("failed\n");
  res = test_nb_num();
  if(res)printf("passed\n");
  else printf("failed\n");
  res = test_nb_num_2_live_nb();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_isAlive_live_with_two_nb();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_isAlive_live_with_three_nb_self_live();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_isAlive_live_with_three_nb_self_die();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_isAlive_die_with_four_nb_self_die();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_isAlive_die_wiht_fouw_nb_self_live();
  if (res) printf("passed\n");
  else printf("failed\n");
  res = test_still();
  if (res) printf("passed\n");
  else printf("failed\n");
#else
  int num_of_gens = 200;
  (void)memset(life, 0, sizeof(life));
  (void)memset(life, 0, sizeof(life));
  life[2][1]=life[2][2]=life[2][3]=life[3][1] = 1;
  while (num_of_gens--) {
    system("clear");
    get_next_gen();
    screen_print();
    sleep(1);
  }
#endif
  return 0;
}
