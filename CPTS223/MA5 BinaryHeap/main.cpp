/*
    NAME: Killian Griffin
    DATE: 10/23/20
    ASSIGNMENT: MA3
    DESCRIPTION: We are designing functions for an implementation of a binary heap.
*/
#include "Heap.h"
#include <time.h>

int printElementK(int k, Heap<int> h);

int main()
{
    Heap<int> h;
    srand(time(NULL));

    for(int i = 0; i < 1000; ++i)
    {
        h.push(rand() % 1000000);
    }

    h.print_array();

    std::cout << std::endl;
    std::cout << "30th smallest element: " << printElementK(30, h) << std::endl;

    return 0;
}

int printElementK(int k, Heap<int> h)
{
    if(k <= 0 || k > h.get_contents().size())
    {
        throw std::out_of_range("printElementK: k is greater than size of array");
    }
    Heap<int> copy = h;
    for(int i = 1; i < k; ++i)
    {
        copy.pop();
    }
    return copy.top();
}
