#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Data{
    int interesting;
    int utility;
    int level_of_hard;
    float deadline;

    bool operator<(const Data& temporary) const
    {
        if(level_of_hard != temporary.level_of_hard)
        {
            return level_of_hard < temporary.level_of_hard;
        }
        else if(interesting != temporary.interesting)
        {
            return interesting < temporary.interesting;
        }
        else if(utility != temporary.utility)
        {
            return utility < temporary.utility;
        }
        return  deadline<temporary.deadline;
    }
    bool operator==(const Data& temporary) const
    {
        if(level_of_hard == temporary.level_of_hard&&interesting == temporary.interesting
           &&utility == temporary.utility&&deadline == temporary.deadline)
        {
            return true;
        }
        return false;
    }

};

void swap1(Data* A, Data*B)
{
    Data* temp = A;
    *A = *B;
    *B = *temp;
}
struct PriorityQueue{
    vector<Data> H;
    int size1;
    int first_el;

    PriorityQueue()
    {
        size1 = 0;
        first_el = 0;
    }

    bool empty() const
    {
        return size1 == first_el;
    }

    int size() const
    {
        return size1;
    }

    static int getParent(int index)
    {
        return (index-1)/2;
    }

    static int getLeftChild(int index)
    {
        return 2*index+1;
    }

    static int getRightChild(int index)
    {
        return 2*index+2;
    }

    void siftDown(int index) const
    {
        while(getLeftChild(index)<H.size())
        {
            int left = getLeftChild(index);
            int right = getRightChild(index);
            int j = left;
            if(right<H.size()&&H.at(right)<H.at(left)) j = right;
            if(H.at(index).level_of_hard<=H.at(j).level_of_hard) break;

            swap(H.at(index),H.at(j));
            index = j;
        }
    }

    void siftUp(int index) const
    {
        int parent = getParent(index);

        while(H.at(index)<H.at(parent))
        {
            swap(&H.at(index),&H.at(parent));
            index = parent;
            parent = getParent(index);
        }
    }

    void push(Data element)
    {
        H.push_back(element);
        size1++;
        siftUp(H.size()-1);
    }

    Data pop()
    {
        Data elem = H.at(0);
        H.at(0) = H.at(H.size() - 1);
        H.pop_back();
        size1--;
        siftDown(0);
        return elem;
    }

    Data top() const
    {
        if(!empty()){
            return H.at(0);
        }
        else throw 1;
    }

    ~PriorityQueue()
    {
        H.clear();
    }
};


#include <queue>
#include <cstdlib>
using namespace std;
template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}
bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;

    priority_queue<Data> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime =
    testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}


int main() {
    srand(time(NULL));

    testPriorityQueue();
    return 0;
}
