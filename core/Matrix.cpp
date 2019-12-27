#include "Matrix.h"
#include <iostream>
#include <math.h>
#include <memory>

using namespace core;

Matrix::Matrix(double (&t_mat)[3][4])
{
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 4; j++)
      m_mat[i][j] = t_mat[i][j];
}

// function for elementary operation of swapping two rows
void Matrix::swap_row(double mat[3][4], int i, int j)
{
  // printf("Swapped rows %d and %d\n", i, j);

  for (int k = 0; k <= 3; k++)
  {
    double temp = mat[i][k];
    mat[i][k] = mat[j][k];
    mat[j][k] = temp;
  }
}

// function to print matrix content at any stage
void Matrix::print(double mat[3][4])
{
  for (int i = 0; i < 3; i++, printf("\n"))
    for (int j = 0; j <= 3; j++)
      printf("%lf ", mat[i][j]);

  printf("\n");
}

// function to reduce matrix to r.e.f.
int Matrix::forwardElim(double mat[3][4])
{
  for (int k = 0; k < 3; k++)
  {
    // Initialize maximum value and index for pivot
    int i_max = k;
    int v_max = mat[i_max][k];

    /* find greater amplitude for pivot if any */
    for (int i = k + 1; i < 3; i++)
      if (abs(mat[i][k]) > v_max)
        v_max = mat[i][k], i_max = i;

    /* if a prinicipal diagonal element  is zero,
     * it denotes that matrix is singular, and
     * will lead to a division-by-zero later. */
    if (!mat[k][i_max])
      return k; // Matrix is singular

    /* Swap the greatest value row with current row */
    if (i_max != k)
      swap_row(mat, k, i_max);


    for (int i = k + 1; i < 3; i++)
    {
      /* factor f to set current row kth element to 0,
       * and subsequently remaining kth column to 0 */
      double f = mat[i][k] / mat[k][k];

      /* subtract fth multiple of corresponding kth
         row element*/
      for (int j = k + 1; j <= 3; j++)
        mat[i][j] -= mat[k][j] * f;

      /* filling lower triangular matrix with zeros*/
      mat[i][k] = 0;
    }

    // print(mat);        //for matrix state
  }
  // print(mat);            //for matrix state
  return -1;
}

// function to calculate the values of the unknowns
void Matrix::backSub(double mat[3][4], double (&solution)[3])
{
  /* Start calculating from last equation up to the
     first */
  for (int i = 3 - 1; i >= 0; i--)
  {
    /* start with the RHS of the equation */
    solution[i] = mat[i][3];

    /* Initialize j to i+1 since matrix is upper
       triangular*/
    for (int j = i + 1; j < 3; j++)
    {
      /* subtract all the lhs values
       * except the coefficient of the variable
       * whose value is being calculated */
      solution[i] -= mat[i][j] * solution[j];
    }

    /* divide the RHS by the coefficient of the
       unknown being calculated */
    solution[i] = solution[i] / mat[i][i];
  }
}

// function to get matrix content
Vector3 Matrix::gaussian_elimination()
{
  /* reduction into r.e.f. */
  int singular_flag = forwardElim(m_mat);

  /* if matrix is singular */
  if (singular_flag != -1)
  {
    printf("Singular Matrix.\n");

    /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
    if (m_mat[singular_flag][3])
      printf("Inconsistent System.");
    else
      printf(
        "May have infinitely many "
        "solutions.");
    return Vector3::zero();
  }

  double solution[3];
  backSub(m_mat, solution);

  return Vector3(solution);
}
