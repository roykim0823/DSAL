#include <iostream>
#include <iomanip>
using namespace std;

int v[6] = {3, 5, 6, 7, 20, 9};
int M[6][6];
char Pick[6][6];

int calculateM(int i, int j, int vi, int vj)
{
	cout << i << " " << j << " " << vi << " " << vj << endl;
	if(vi<0 || vj<0 || vi>5 || vj>5)
		return 0;
	if(vi>vj)
		return 0;
	return M[vi][vj];
}

void printM()
{
	for (int i=0; i<6; i++) {
		for (int j=0; j<6; j++) {
			cout <<setw(4) << M[i][j] << " ";
		}
		cout << endl;
	}
}

void printPick()
{
	for (int i=0; i<6; i++) {
		for (int j=0; j<6; j++) {
			cout <<setw(4) << Pick[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	///*
	for (int i=0; i<6; i++) 
		for (int j=0; j<6; j++) 
		{
			M[i][j]=0;
			Pick[i][j]='X';
		}
    //printM();
	//*/

	for (int i=0; i<6; i++) {
		for (int j=0; j<6-i; j++) {
				// i=j, j=j+i
				// pick i, then Opp pick j or i
				cout << "v[" << j << "][" << j+i << "]" << endl;
				int ij = calculateM(j, j+i, j+1, j+i-1);   // i+1, j-1
				int ii = calculateM(j, j+i, j+2, j+i);     // i+2, j
				cout << "ij=" << ij << " ii=" << ii << " v[i]=" << v[j] << endl;
				int min1=ij;
				if (ij>ii) 
					min1=ii;
				min1+=v[j];
				// pick j, then Opp pick j or i
				int jj = calculateM(j, j+i, j, j+i-2); 		// i, j-2
				int ji = calculateM(j, j+i, j+1, j+i-1);    // i+1, j-1
				cout << "jj=" << jj << " ji=" << ji << " v[j]=" << v[j+i] << endl;
				int min2=jj;
				if (jj>ji) 
					min2=ji;
				min2+=v[j+i];

				if(min1>=min2) 
				{
					M[j][j+i]=min1; 
					Pick[j][j+i]='i';
				}
				else
				{
					M[j][j+i]=min2;
					Pick[j][j+i]='j';
				}
				cout << "M[" << j << "][" << j+i << "]=" << M[j][j+i] << endl;
				cout<< endl;
				
		}
	}
	printM();
	cout << endl;
	printPick();
}

				

