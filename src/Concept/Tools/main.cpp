#include <iostream>

#include "parser.h"
#include "sorting.h"

using namespace std;

int main(int argc, char *argv[])
{
    TaskList * list = parse(argv[1]);

//    TaskList * list = parse("../../../sample/tasklist.xml");
    list->print();
    //    cout << "<<<<<<<<<<<<<< SORTING >>>>>>>>>>>>>>>" << endl;

//    TaskList * list2 = parse("../../../template/course.xml");
//    list2->print();
    //    // Sort the list
    //    sorting(list);

    return 0;
}

