#include <iostream>
using namespace std;
void RotateMatrix(int (&arr)[100][100], const int& M , const int& N, const int& K);

int main() {
	//code
    int n; 
    cin >> n; 
    
    int inputs[3], arr[100][100]; 
    while(n > 0)
    {
        cin >> inputs[0]; 
        cin >> inputs[1]; 
        cin >> inputs[2]; 
        
        for(int i =0 ; i < inputs[0]; i++)
        {
            for(int j =0 ; j < inputs[1]; j++)
                cin >> arr[i][j]; 
        }
        
        n--; 
    }
    int k = inputs[2];
    while (k > 0)
    {
        RotateMatrix(arr, inputs[0] , inputs[1], inputs[2]); 
        k = k-1;
    }
    
    for(int i =0 ; i < inputs[0]; i++)
    {
        for(int j =0 ; j < inputs[1]; j++)
            cout << arr[i][j] << " "; 
    }
    
	return 0;
}

void RotateMatrix(int (&arr)[100][100], const int& M , const int& N, const int& K)
{
    
    
    for(int i = 0 ; i < M; i++)
    {
        int first_ele = arr[i][0]; 
        for(int j = 1 ; j < N ; j++)
            arr[i][j -1] = arr[i][j]; 
        arr[i][N-1] = first_ele;    
    }
    
   
}