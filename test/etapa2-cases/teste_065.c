//ERROR: As construções iterativas são separadas com : e não aceitam atribuicoes repetidas
int f()
{
  int x;
  int i;
  int j;
  for(i <= 0, j <= 0 : i : i <= 2, j <= 3) {
  };
}
