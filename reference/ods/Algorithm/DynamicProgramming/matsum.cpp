#include <iostream>

using namespace std;

#define N 6 // 8x8 matrix

/* problem description:
   Given a matrix of NxN, all elements in the matrix are integers -- positive and negative
   Find a submatrix so that the sum is the largest
*/

/* 
  Algorithm:
    Add rows (i, j) to form a new array, find the largest sum subarray
    then if we do that for all the rows in the matrix pairwise, the largest of the largest sum subarray would be the largest submatrix 
    for example, if we add row r1 to row r2 to get one subarray, the largest sum subarray of it is between position c1 and c2, 
    then the largest sub matrix would be between (r1, c1) and (r2, c2) ==> the up-left point and bottom-right point

    Refer to http://www.cppblog.com/superKiki/archive/2010/05/27/116465.html
*/

// find a max sum subarray
int FindMaxSumArray(int arr[N])
{
    int maxsum = 0;

    int curmax = 0; 
    int start = 0;

    for (int i=0; i<N; i++)
    {
        curmax += arr[i];
        if (curmax > maxsum)
            maxsum = curmax;

        if (curmax < 0)
        {
            start = i+1;
            curmax = 0;
        }
    }

    return maxsum;
}

// find the largest sum submatrix
int FindMaxSumMatrix(int mat[N][N])
{
    int sumarray[N] = {0};
    int maxsum = 0;

    for (int rowstart = 0; rowstart < N; rowstart++)
    {
        for (int i=0; i<N; i++)
            sumarray[i] = 0;

        for (int rowend = rowstart; rowend < N; rowend++)
        {
            for (int k=0; k<N; k++)
            {
                sumarray[k] += mat[rowend][k];
            }

            int arraymax = FindMaxSumArray(sumarray);
            if (maxsum < arraymax)
                maxsum = arraymax;
        }
    }

    return maxsum;
}

int main()
{
    int arr[] = { 6, 2, -9, 2, -6, 8, 9, -4, 8};

    int maxSubArray = FindMaxSumArray(arr);

    cout << "The largest sum sub array is: " << maxSubArray << endl;

    int mat[N][N] = { {6, 3, -2, -5, 1, 10}, {-2, 8, 3, 5, 10, -6}, {-6, 4, 2, 8, 9, -4},
                      {10, -2, 6, 8, 4, -5}, {-6, 8, 0, 9, -2, 1},  {10, 5, -2, 9, 2, 1}};

    int maxSubMatrix = FindMaxSumMatrix(mat);

    cout << "The largest sum sub matrix is: " << maxSubMatrix << endl;

}
