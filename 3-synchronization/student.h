#ifndef STUDENT_H
#define STUDENT_H
#include "person.h"

typedef struct Student
{
    int id;
    Person *person;
    Object *obj;

} Student;


Student *Student_init(int id, char *name, int age);

void Student_setId(Student *student, int id);
int Student_getId(Student *student);

char *Student_getName(Student *student);
int Student_getAge(Student *student);

#endif