#include "Solver.hpp"

Solver::Solver(int *tab)
{
  convert(tab);
  sudoku_solver(_grille);
}

void Solver::convert(int *tab)
{
  int i = 0;
  int j = 0;
  int u = 0;

  while (i != 9)
  {
    j = 0;
    while (j != 9)
    {
      _grille[i][j] = u;
      u++;
      j++;
    }
    i++;
  }
}

void Solver::printLine()
{
  int i = 0;

  while (i < 13)
  {
    std::cout << '-';
    i++;
  }
  std::cout << std::endl;
}

void Solver::print()
{
  int i = 0;
  int j = 0;

  printLine();
  while (i != 9)
  {
    j = 0;
    std::cout << "|";
    while (j != 9)
    {
      std::cout << _grille[i][j];
      if ((j + 1) % 3 == 0)
        std::cout << '|';
      j++;
    }
    i++;
    std::cout << std::endl;
    if ((i) % 3 == 0)
      printLine();
  }
}
