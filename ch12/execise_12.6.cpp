#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

// excecise 12.6
vector<int> *NewVector(initializer_list<int> li)
{
    vector<int> *pVector = new vector<int>(li);
    return pVector ? pVector : nullptr;
}

void Read(vector<int> *pVector)
{
    if(pVector)
    {
        int tmp;
        while(cin >> tmp)
            pVector->push_back(tmp);
    }
}

void Write(vector<int> *pVector)
{
    for_each(pVector->begin(), pVector->end(), [](int &tmp) { cout << tmp << endl; });
}
// excecise 12.6 end

// excecise 12.7
shared_ptr<vector<int>> NewSharedVector(initializer_list<int> li)
{
    shared_ptr<vector<int>> pVector = make_shared<vector<int>>(li);
    return pVector;
}

void Read(shared_ptr<vector<int>> pVector)
{
    if(pVector)
    {
        int tmp;
        while (cin >> tmp)
            pVector->push_back(tmp);
    }
}

void Write(shared_ptr<vector<int>> pVector)
{
    for_each(pVector->begin(), pVector->end(), [](int &tmp) { cout << tmp << endl; });
}
// excecise 12.7 end

int main()
{
    vector<int> *pVector = NewVector({1, 2, 3});
    Read(pVector);
    Write(pVector);
    delete pVector;

    shared_ptr<vector<int>> ptrVector = NewSharedVector({7, 8, 9});
    Read(ptrVector);
    Write(ptrVector);
}
