#pragma once

namespace core::matrix
{
  // Solves a set of linear equations using Gaussian elimination
  double* solve(double* matrix, int rows, int cols)
  {
    for (int i = 0; i < cols - 1; i++)
      for (int j = i; j < rows; j++)
        if (matrix[i + j * cols] != 0)
        {
          if (i != j)
            for (int k = i; k < cols; k++)
            {
              double temp = matrix[k + j * cols];
              matrix[k + j * cols] = matrix[k + i * cols];
              matrix[k + i * cols] = temp;
            }

          j = i;

          for (int v = 0; v < rows; v++)
            if (v == j)
              continue;
            else
            {
              double factor = matrix[i + v * cols] / matrix[i + j * cols];
              matrix[i + v * cols] = 0;

              for (int u = i + 1; u < cols; u++)
              {
                matrix[u + v * cols] -= factor * matrix[u + j * cols];
                matrix[u + j * cols] /= matrix[i + j * cols];
              }
              matrix[i + j * cols] = 1;
            }
          break;
        }

    return matrix;
  }
} // namespace core