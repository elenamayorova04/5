#ifndef __JOBSTREAM_H__
#define __JOBSTREAM_H__

#include <iostream>
#include <ctime>
#include "tqueue.h"

class TJobStream
{
private:
	TQueue<int> taskQueue;

	int curTaskID = 0;
	int newTaskID = 0;

	int fullCounter = 0;
	int cycleCounter = 0;
  int freeCounter = 0;

	bool taskActive = false;

public:
	TJobStream(int size) : taskQueue(size) { };

	int procIsBusy();
	int getNewTask();

	void runTask();
	void runNewTask();

	void runCycle();
	void run(int t);
};

#endif


int TJobStream::getNewTask()
{
	if((((double)rand() / RAND_MAX) * (100 - 0 + 1)) < 50)
		return true;
	else
		return false;
}

int TJobStream::procIsBusy()
{
	if ((((double)rand() / RAND_MAX) * (100 - 0 + 1)) < 50)
		return true;
	else
		return false;
}

void TJobStream::runTask()
{
	std::cout << "task " << curTaskID << ": running" << std::endl;
	if (procIsBusy())
		taskActive = true;
	else
	{
		std::cout << "task " << curTaskID << ": over" << std::endl;
		taskActive = false;
	}
}

void TJobStream::runNewTask()
{
	curTaskID++;
	std::cout << "task " << curTaskID << ": starting" << std::endl;
	taskQueue.pull();
	runTask();
}

void TJobStream::runCycle()
{
	std::cout << "cycle " << cycleCounter << std::endl;

	if (getNewTask())
	{
		newTaskID++;
		std::cout << "task " << newTaskID << ": new" << std::endl;
		if (!taskQueue.isFull())
			taskQueue.push(newTaskID);
		else
		{
			fullCounter++;
			std::cout << "task " << newTaskID << ": queue is full\nfull count is " << fullCounter << std::endl;
			newTaskID--;
		}
	}
	else
		std::cout << "no new tasks" << std::endl;

	if (taskActive == true)
		runTask();
	else 
	{
		if (!(taskQueue.isEmpty()))
			runNewTask();
		else
		{
			std::cout << "queue is empty" << std::endl;
			freeCounter++;
		}
	}

	cycleCounter++;
	std::cout << "==========" << std::endl;
}

void TJobStream::run(int t)
{
	std::srand(std::time(nullptr));

	while (cycleCounter < t)
		runCycle();

	std::cout << cycleCounter << " CYCLES" << std::endl;
	std::cout << curTaskID << " TASKS" << std::endl;
	std::cout << "QUEUE WAS FULL " << fullCounter << " TIMES" << std::endl;
  std::cout << "PROC WAS FREE " << freeCounter << " TIMES" << std::endl;
}