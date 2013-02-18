#include <iostream>

#include "parser.h"
#include "sorting.h"

using namespace std;

int main(int argc, char *argv[])
{
    TaskList * list = parse(argv[1]);
    list->print();

    save(list, "../../../sample/testSaving.xml");
    TaskList * list2 = parse("../../../sample/testSaving.xml");
    list2->print();

    delete list;
    delete list2;

    return 0;
}

