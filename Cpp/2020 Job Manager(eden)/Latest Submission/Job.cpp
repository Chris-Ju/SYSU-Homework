#include <sstream>
#include "Job.h"

using namespace std;

int Job::number = 0;

Job::Job(int priority)
{
    this->priority = priority;
    nextJob = NULL;
    id = number;
    number++;
}

void Job::setId(int id)
{
    this->id = id;
}
int Job::getId() const
{
    return id;
}

void Job::setPriority(int priority)
{
    this->priority = priority;
}

int Job::getPriority() const
{
    return priority;
}

void Job::setNext(Job *job)
{
    nextJob = job;
}

Job* Job::getNext() const
{
    return nextJob;
}

string Job::toString()
{
    string goal = "[";
    string tmp;
    stringstream bri1;
    stringstream bri2;
    bri1 << id;
    bri2 << priority;
    bri1 >> tmp;
    goal = goal + tmp + ":";
    bri2 >> tmp;
    goal = goal + tmp + "]";
    return goal;
}

