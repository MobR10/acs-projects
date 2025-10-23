#include <iostream>
#include <random> // Required for modern random number generation
#include <ctime>  // Required for time() and localtime()

using namespace std;

const int MIN_VAL = 0;
const int MAX_VAL = 5000;

class Exchange
{
    static int numberOfExchange;
    int money;

public:
    Exchange()
    {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distrib(MIN_VAL, MAX_VAL);

        this->money = distrib(gen);

        numberOfExchange++;
    }

    int getMoney() const
    {
        return this->money;
    }

    // Static function to access the counter
    static int getNumberOfExchange()
    {
        return numberOfExchange;
    }
};

int Exchange::numberOfExchange = 0;

int getCurrentDayOfMonth_Ctime()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    if (now != nullptr)
    {
        return now->tm_mday;
    }

    return -1;
}

int main()
{

    int numberOfObjects = getCurrentDayOfMonth_Ctime();
    int counter = 0;
    for (int i = 0; i < numberOfObjects; i++)
    {
        Exchange exchange;
        if (exchange.getMoney() > 3000)
            counter++;
    }
    cout << "Numarul de obiecte cu money > 3000 este " << counter;
    return 0;
}