#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <stdio.h>
#include <iostream>
#include "Sudoku_solver.hpp"

class Solver {
  public:
    Solver(int *tab);
    void print(void);
  private:
    int _grille[9][9];
    void convert(int *tab);
    void printLine();
};

#endif /* SOLVER_HPP */
