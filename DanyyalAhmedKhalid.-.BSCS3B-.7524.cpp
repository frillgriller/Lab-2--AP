#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>


int rows = 4, columns = 4;

using namespace std;

int max = 100;
int min = 1;

int RandGenerator() {
	srand(time(NULL));

	int RandGenerator = (rand() % ((MAX - MIN) + 1)) + MIN;

	return RandGenerator;
}

vector<vector<int>> iterative(vector<vector<int>> A, vector<vector<int>> B)
{
	int rows = A.size();
	int columns = A[0].size();
	int dimensionsZ = B[0].size();

	vector<vector<int>> answer;
	answer.resize(rows, vector<int>(dimensionsZ, 0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < dimensionsZ; j++) {
			int addition = 0;
			for (int k = 0; k < columns; k++)
				addition = addition + (A[i][k] * B[k][j]);
			answer[i][j] = addition;
		}
	return answer;
}

void display(vector<vector<int>> answer)
{
	int rows = answer.size();
	int columns = answer[0].size();
	cout << "\n \t";
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < columns; j++) {
			if (j == columns - 1)
				cout << answer[i][j];
			else
				cout << answer[i][j] << " ";
		}
		cout << "]\n \t";
	}
	cout << "\n \t";
}

vector<vector<int>> addition(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return result;
}

vector<vector<int>> subtraction(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] - B[i][j];
		}
	}
	return result;
}

vector<vector<int>> Strassen_Resursive(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();

	vector<vector<int>> answer;
	answer.resize(n, vector<int>(n, 0));

	if (n == 1) {
		answer[0][0] = A[0][0] * B[0][0];
		return answer;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n/2, vector<int>(n/2, 0));
		a12.resize(n/2, vector<int>(n/2, 0));
		a21.resize(n/2, vector<int>(n/2, 0));
		a22.resize(n/2, vector<int>(n/2, 0));

		b11.resize(n/2, vector<int>(n/2, 0));
		b12.resize(n/2, vector<int>(n/2, 0));
		b21.resize(n/2, vector<int>(n/2, 0));
		b22.resize(n/2, vector<int>(n/2, 0));

		c11.resize(n/2, vector<int>(n/2, 0));
		c12.resize(n/2, vector<int>(n/2, 0));
		c21.resize(n/2, vector<int>(n/2, 0));
		c22.resize(n/2, vector<int>(n/2, 0));

		p1.resize(n/2, vector<int>(n/2, 0));
		p2.resize(n/2, vector<int>(n/2, 0));
		p3.resize(n/2, vector<int>(n/2, 0));
		p4.resize(n/2, vector<int>(n/2, 0));
		p5.resize(n/2, vector<int>(n/2, 0));
		p6.resize(n/2, vector<int>(n/2, 0));
		p7.resize(n/2, vector<int>(n/2, 0));

		vector<vector<int>> aResult;
		vector<vector<int>> bResult;
		aResult.resize(n/2, vector<int>(n/2, 0));
		bResult.resize(n/2, vector<int>(n/2, 0));


		int i, j;

	
		for (i = 0; i < n/2; i++) {
			for (j = 0; j < n/2; j++) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + n/2];
				a21[i][j] = A[i + n/2][j];
				a22[i][j] = A[i + n/2][j + n/2];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + n/2];
				b21[i][j] = B[i + n/2][j];
				b22[i][j] = B[i + n/2][j + n/2];
			}
		}

		aResult = addition(a11, a22); 
		bResult = addition(b11, b22); 
		p1 = Strassen_Resursive(aResult, bResult); 

		aResult = addition(a21, a22); 
		p2 = Strassen_Resursive(aResult, b11); 

		bResult = subtraction(b12, b22); 
		p3 = Strassen_Resursive(a11, bResult); 

		bResult = subtraction(b21, b11); 
		p4 = Strassen_Resursive(a22, bResult); 

		aResult = addition(a11, a12); 
		p5 = Strassen_Resursive(aResult, b22); 	

		aResult = subtraction(a21, a11); 
		bResult = addition(b11, b12); 
		p6 = Strassen_Resursive(aResult, bResult); 

		aResult = subtraction(a12, a22); 
		bResult = addition(b21, b22);
		p7 = Strassen_Resursive(aResult, bResult); 

										

		c12 = addition(p3, p5); 
		c21 = addition(p2, p4); 

		aResult = addition(p1, p4); 
		bResult = addition(aResult, p7); 
		c11 = subtraction(bResult, p5); 

		aResult = addition(p1, p3); 
		bResult = addition(aResult, p6); 
		c22 = subtraction(bResult, p2); 

									
		for (i = 0; i < n/2; i++) {
			for (j = 0; j < n/2; j++) {
				answer[i][j] = c11[i][j];
				answer[i][j + n/2] = c12[i][j];
				answer[i + n/2][j] = c21[i][j];
				answer[i + n/2][j + n/2] = c22[i][j];
			}
		}
	}
	return answer;
}

int main()
{
	vector<vector<int>> A;
	vector<vector<int>> B;

	A.resize(rows, vector<int>(columns, 0));
	B.resize(rows, vector<int>(columns, 0));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			A[i][j] = RandGenerator();
			B[i][j] = RandGenerator();
		}
	}

	display(iterative(A, B));
	display(Strassen_Resursive(A, B));


	cout << "Test results \n \t" << ;

	if (iterative(A, B) == Strassen_Recursive(A, B))

	{

		cout << "TEST CLEARD" << ;	
	}

	else, , cout << "TEST FAILED" << ;

}