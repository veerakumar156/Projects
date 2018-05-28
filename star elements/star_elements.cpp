#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void StarElements(std::vector<int>& inputs, std::vector<int>& stars); 
void SuperStarElements(std::vector<int>& inputs, const int& large_right, std::vector<int>& superstars); 

int main() 
{
	int n, temp; 
    cin >> n; 
    
    int arrSize; 
    std::vector<int> inputs;
    while(n > 0)
    {
        cin >> arrSize; 
        inputs.clear();
        for(int i = 0 ; i < arrSize; i++)
        {
            cin >> temp;
            inputs.push_back(temp);
        }
        std::vector<int> stars, superstars;
        StarElements(inputs, stars); 
        for (auto i: stars)
            cout << i << " "; 
        cout << endl;
        int large_right = -1;
        if (stars.size() > 0)
            large_right = stars[0]; 
        SuperStarElements(inputs, large_right, superstars);
        for (auto i: superstars)
            cout << i << " "; 
        cout << endl;
        n--; 
    }

	return 0;
}

void StarElements(std::vector<int>& inputs, std::vector<int>& stars) 
{
    std::vector<int>::reverse_iterator it;
    int last_max = -1;
    for (it = inputs.rbegin() ; it != inputs.rend(); ++it)
    {
       if (*it > last_max)
       {
          stars.push_back(*it); 
          last_max = *it; 
       }
    }
    std::reverse(stars.begin(),stars.end());
}

void SuperStarElements(std::vector<int>& inputs, const int& large_right, std::vector<int>& superstars) 
{
    std::vector<int>::iterator it;
    int last_max = -1;
    superstars.push_back(large_right);
    for (it = inputs.begin() ; it != inputs.end(); ++it)
    {
       if ((*it > last_max) && (*it > large_right))
       {
          superstars.push_back(*it); 
          last_max = *it; 
       }
    }
    
}