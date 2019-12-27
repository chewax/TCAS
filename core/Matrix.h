#pragma once
#include "Vector3.h"

namespace core
{
  class Matrix
  {
  private:
    double m_mat[3][4];

    // function for elementary operation of swapping two rows
    void swap_row(double mat[3][4], int i, int j);

    // function to print matrix content at any stage
    void print(double mat[3][4]);

    // function to reduce matrix to r.e.f.
    int forwardElim(double mat[3][4]);

    // function to calculate the values of the unknowns
    void backSub(double mat[3][4], double (&solution)[3]);


  public:
    // function to get matrix content
    Vector3 gaussian_elimination();
    Matrix(double (&t_mat)[3][4]);
  };
} // namespace core