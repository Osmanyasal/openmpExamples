#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
//#include <omp.h>
#include "student.h"

void yaz()
{
}
int main(int argc, char **argv)
{
       printf("%p\n", &yaz);

       printf("%ld\n", __STDC_VERSION__);
       Student *osman = Student_init(2035, "osman yasal", 26);
       printf("%s\n", osman->obj->toString((Object *)osman));

       return 0; // Noncompliant, file f has not been closed
}