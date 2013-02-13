#include <iostream>

#include "parser.h"
#include "sorting.h"

using namespace std;

int main()
{
    TaskList * list = parse("../../../sample/tasklist.xml");
    list->print();
    //    cout << "<<<<<<<<<<<<<< SORTING >>>>>>>>>>>>>>>" << endl;

    //    // Sort the list
    //    sorting(list);

    return 0;
}

