#include <iostream>
#include <random>
#include <chrono>

#include "Adapter.h"

using namespace std::chrono;

class Timer
{
    typedef high_resolution_clock Clock;
private:
    Clock::time_point start;
public:
    Timer()
        :start(Clock::now()) {}

    long long get_time_ms() const
    {
        return duration_cast<milliseconds>(Clock::now() - start).count();
    }
};

void bubble_sort(Adapter& adapter, uint64_t& nop) // F(n) = 56n^3 + 18n^2
{
    nop += 1;
    for (int i = 0; i < adapter.size() - 1; i++) // n
    {
        nop += 1;
        nop += 2;
        for (int j = 0; j < adapter.size() - i - 1; j++) // n
        {
            nop += 4;
            if (adapter.peekElement(j) > adapter.peekElement(j + 1)) // 20n + 8
            {
                int tmp = adapter.peekElement(j + 1);
                adapter.setElement(j, tmp);
                adapter.getElement(j + 2);
            }
        }
    }
}


void work(int size)
{
    std::mt19937 rng{ std::random_device()() };
    std::uniform_int_distribution<int> dist{ -20, 20 };

    uint64_t nop = 0;
    Adapter a(nop, size + 10);

    for (int i = 0; i < size; i++)
    {
        a.push(dist(rng));
    }

    // std::cout << "Initial stack: ";
    // a.display();

    const Timer t;
    bubble_sort(a, nop);
    const auto time = t.get_time_ms();

    // a.display();
    // std::cout << "Sorted stack: ";
    
    std::cout << "N=" << size << "; Elapsed time: " << time << "ms = " << time / 1000.0f << "s; nop=" << nop <<"\n-------\n";

}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        work( (i+1) * 300);
    }

}