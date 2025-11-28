#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Stack
{
private:
    T *elements;
    int n;
    int maxDim;

public:
    Stack(int maxDim) : maxDim(maxDim), n(0)
    {
        elements = new T[maxDim];
    }

    void push(T value)
    {
        if (n == maxDim)
        {
            cout << "MaxDim reached\n";
            return;
        }
        elements[n++] = value;
    }

    T pop()
    {
        if (n == 0)
        {
            throw runtime_error("Stack empty");
        }
        return elements[--n];
    }

    T peek() const
    {
        if (n == 0)
        {
            throw runtime_error("Stack empty");
        }
        return elements[n - 1];
    }

    ~Stack()
    {
        delete[] elements;
    }
};

template <typename T>
class Queue {
private:
    T* elements;
    int maxDim;
    int frontIndex;   // indexul primului element
    int rearIndex;    // indexul de inserare
    int n;            // numărul de elemente

public:
    Queue(int maxDim) : maxDim(maxDim), frontIndex(0), rearIndex(0), n(0) {
        elements = new T[maxDim];
    }

    void enqueue(T value) {
        if (n == maxDim) {
            std::cout << "Queue is full\n";
            return;
        }
        elements[rearIndex] = value;
        rearIndex = (rearIndex + 1) % maxDim;
        n++;
    }

    T dequeue() {
        if (n == 0) {
            throw std::runtime_error("Queue is empty");
        }
        T value = elements[frontIndex];
        frontIndex = (frontIndex + 1) % maxDim;
        n--;
        return value;
    }

    T peek() const {
        if (n == 0) {
            throw std::runtime_error("Queue is empty");
        }
        return elements[frontIndex];
    }

    int size() const {
        return n;
    }

    bool isEmpty() const {
        return n == 0;
    }

    bool isFull() const {
        return n == maxDim;
    }

    ~Queue() {
        delete[] elements;
    }
};

int main()
{
    Stack<int> stackInt(5);

    stackInt.push(1);   cout << stackInt.peek() << endl;
    stackInt.push(2);   cout << stackInt.peek() << endl;
    stackInt.push(3);   cout << stackInt.peek() << endl;
    stackInt.push(4);   cout << stackInt.peek() << endl;
    stackInt.push(5);   cout << stackInt.peek() << endl;
    cout << stackInt.pop() << endl;
    cout << stackInt.pop() << endl;
    cout << stackInt.pop() << endl;
    cout << stackInt.pop() << endl;
    cout << stackInt.pop() << endl;

    Stack<char> stackChar(2);

    stackChar.push('a');    cout << stackChar.peek() << endl;
    stackChar.push('b');    cout << stackChar.peek() << endl;

    cout<<stackChar.pop()<<endl;
    cout<<stackChar.pop()<<endl;

    //================ QUEUE
    Queue<int> q(4);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << q.dequeue() <<endl;
    cout << q.peek() <<endl;

    q.enqueue(40);
    q.enqueue(50); 

    cout<<q.peek()<<endl;
    cout<<q.peek()<<endl;
}
