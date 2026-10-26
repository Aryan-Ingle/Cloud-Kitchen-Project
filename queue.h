#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    int data[100];
    int front, rear;

public:
    Queue()
    {
        front = 0;
        rear = -1;
    }

    bool isEmpty()
    {
        return front > rear;
    }

    void enqueue(int id)
    {
        if(rear < 99)
            data[++rear] = id;
    }

    int getAt(int i)
    {
        if(i < front || i > rear)
            return -1;

        return data[i];
    }

    int getFrontIndex() { return front; }
    int getRearIndex() { return rear; }
};

class PriorityQueue
{
    int data[100], priority[100];
    int count;

public:
    PriorityQueue()
    {
        count = 0;
    }

    void enqueue(int id, int p)
    {
        if(count == 100)
            return;

        int i = count - 1;

        while(i >= 0 && priority[i] < p)
        {
            data[i + 1] = data[i];
            priority[i + 1] = priority[i];
            i--;
        }

        data[i + 1] = id;
        priority[i + 1] = p;
        count++;
    }

    int getAt(int i)
    {
        if(i < 0 || i >= count)
            return -1;

        return data[i];
    }

    int getCount() { return count; }
};

#endif