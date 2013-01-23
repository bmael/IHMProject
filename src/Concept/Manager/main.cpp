#include <iostream>

#include "task.h"
#include "tasklist.h"

using namespace std;

int main()
{
    TaskList * mainList = new TaskList("Go to sleep");
        Task * t1 = new Task("take a tea");
        Task * t2 = new Task("go to the bed");
        TaskList * dreamList = new TaskList("Dreaming");
            Task * t1bis = new Task("sleep");

    dreamList->add(t1bis);
    mainList->add(t1);
    mainList->add(t2);
    mainList->add(dreamList);

    mainList->print();

    delete mainList;
    delete t1;
    delete t2;
    delete dreamList;
    delete t1bis;

    return 0;
}

