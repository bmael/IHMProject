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
            t1bis->setPriority(40);
            TaskList * plopList = new TaskList("plop list");
                Task * t1bibis = new Task("t1bibis");

    plopList->add(t1bibis);
    dreamList->add(t1bis);
    dreamList->add(plopList);
    mainList->add(t1);
    mainList->add(t2);
    mainList->add(dreamList);

    cout << "pouzt" << endl;

    mainList->print();



    return 0;
}

