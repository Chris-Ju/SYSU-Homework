#include "JobManager.h"
#include <iostream>

using namespace std;

JobManager* JobManager::instance = NULL;

JobManager::JobManager()
{
    /*if(instance == NULL)
    {
        instance = new JobManager;
    }
    instance->jobFrontPointer = NULL;
    */
}

JobManager::~JobManager()
{
    /*clear();
    if(instance != NULL)
        delete instance;
    instance = NULL;*/
}

JobManager* JobManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new JobManager;
        instance->jobFrontPointer = NULL;
    }
    return instance;
}

bool JobManager::deleteInstance()
{
    if(instance == NULL)
        return false;
    else
    {
        instance->clear();
        delete instance;
        instance = NULL;
        return true;
    }
}

void JobManager::addJob(int priority)
{
    if(jobFrontPointer == NULL)
        jobFrontPointer = new Job(priority);
    else
    {
        Job* current = jobFrontPointer;
        while(current->getNext())
        {
            current = current->getNext();
        }
        current->setNext(new Job(priority));
    }
}


void JobManager::finishOneJob()
{
    if(jobFrontPointer == NULL)
        return;
    Job* current = jobFrontPointer;
    jobFrontPointer = jobFrontPointer->getNext();
    delete current;
}


void JobManager::sortJob()
{
    int num = getNumOfJob();
    Job* current;
    Job* next;
    int tmp;
    for(int i = 0; i < num; i++)
    {
        current = jobFrontPointer;
        next = current->getNext();
        for(int j = 0; j < num - 1; j++)
        {
            if(current->getPriority() < next->getPriority())
            {
                tmp = current->getPriority();
                current->setPriority(next->getPriority());
                next->setPriority(tmp);
                tmp = current->getId();
                current->setId(next->getId());
                next->setId(tmp);
            }
                current = next;
                next = next->getNext();

        }

    }
}

void JobManager::printJob()
{
    if(jobFrontPointer == NULL)
    {
        cout << "empty!" << endl;
        return;
    }
    Job* current = jobFrontPointer;
    cout << current->toString();
    while(current->getNext())
    {
        current = current->getNext();
        cout << "->" << current->toString();
    }
    cout << endl;
}


int JobManager::getNumOfJob()
{
    int num = 0;
    Job* current = jobFrontPointer;
    while(current)
    {
        num++;
        current = current->getNext();
    }
    return num;
}
    
void JobManager::clear()
{
    Job* current = jobFrontPointer;
    Job* next;
    while(current)
    {
        next = current->getNext();
        delete current;
        current = next;
    }
    jobFrontPointer = NULL;
}

