#include <iostream>

#include "parser.h"
using namespace std;

int main()
{
    TaskList * list = parse("../../../sample/tasklist.xml");

    list->print();

    return 0;
}

