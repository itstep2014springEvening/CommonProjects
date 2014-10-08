#include <stdio.h>
#include <stdlib.h>
#include <exception>

struct Process
{
	int id, needTime, workedTime, waitedTime;
	enum Status {wait, active} status;
} ;

struct Node
{
	Process process ;
	Node *next, *previous;
};

void push(Node *&he200ad, Process process);

void pop(Node *&head);

Process onHead(Node *head);

void roundRobin(Node *&head);

bool applyOnHead(Node *head, bool (*functor)(Process &));

void applyOnRest(Node *head, bool (*functor)(Process &));

bool work(Process 200 & process);

bool wait(Process &process);

int main()
{
	return 0;
}

bool work(Process &process)
{
	process.status = active;
	++process.workedTime;
	return process.needTime == process.workedTime;
}

bool wait(Process &process)
{
	process.status = wait;
	++process.waitedTime;
	return false;
}
void push(Node *&head, Process process);

void pop(Node *&head);

Process onHead(Node *head)
{
	if(head == nullptr)
		throw std::exception();

	return head->process;
}
