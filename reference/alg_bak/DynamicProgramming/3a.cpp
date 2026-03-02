#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

const int N = 200;

void print_Matrix(int M[][N], int n)
{
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cout << setw(4) << M[i][j] << " ";
		}
		cout << endl;
	}
}

void positiveMatrix(int Ref[][N], int posMat[][N], int n)
{
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if(Ref[i][j]>0)
				posMat[i][j]=1;
			else
				posMat[i][j]=0;
		}
	}
}
				

void preComputeMatrix(int Ref[][N], int preMat[][N], int n)
{
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if(Ref[i][j]>0) {
			if(i==0 && j==0)
				preMat[i][j] = Ref[i][j];
			else if(i==0)
				preMat[i][j] = preMat[i][j-1] +Ref[i][j];
			else if(j==0)
				preMat[i][j] = preMat[i-1][j] +Ref[i][j];
			else {
				// Left and Up is zero
				if(preMat[i-1][j]+preMat[i][j-1]==0)
					preMat[i][j]=1;
				else if(preMat[i-1][j]==0)	// Left is Zero
					preMat[i][j]=preMat[i][j-1]+1;
				else if(preMat[i][j-1]==0) 	// Up is Zero
					preMat[i][j]=preMat[i-1][j]+1;
				else // Left and Up are not Zero
				{
					if(preMat[i-1][j-1]==0) // Diagonal is zero
					{
						if(preMat[i-1][j]>preMat[i][j-1])
							preMat[i][j]=preMat[i-1][j]+1;
						else
							preMat[i][j]=preMat[i][j-1]+1;
					} else // All is not zero
						preMat[i][j] = preMat[i-1][j] + preMat[i][j-1] - preMat[i-1][j-1] + Ref[i][j];
				}
			}

			} else
				preMat[i][j]=0;
		}
	}
}


int main(int argc, char *argv[])
{
	int matrix[N][N];
	int posMat[N][N];
	int preMat[N][N];
	int matSum[N][N];
	if(argc<2)
	{ 	cout << "Specify input file..." << endl;
		return 0;
	}
	// Read CSV file
	ifstream ifile(argv[1]);
	string line;
	int line_num=0;
	while(getline(ifile, line)) {
		vector<string> results;
		boost::split(results, line, boost::is_any_of(","));
		for(int i=0; i<200; i++)
			matrix[line_num][i] = boost::lexical_cast<int>(results[i+1]);
		line_num++;
	}
	print_Matrix(matrix, 20);
    cout << endl;
	positiveMatrix(matrix, posMat, 20);
	print_Matrix(posMat, 20);
    cout << endl;
	preComputeMatrix(posMat, preMat, 20);
	print_Matrix(preMat, 20);





	//Cal_matSum(&matrix[0][0], &matSum[0][0], 20);
	
}



				

