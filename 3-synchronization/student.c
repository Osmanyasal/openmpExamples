#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


static char *__Student_toString(struct Object *obj)
{
    Student *student = (Student *)obj;
    char *res = malloc(sizeof(char) * 500);

    strcpy(res, "Person(");
    strcat(res, "id=");

    char arr[20];
    sprintf(arr, "%d,", student->id);
    strcat(res, arr);

    strcat(res, student->person->obj->toString((Object *)student->person));
    strcat(res, "\b");

    strcat(res, ");");

    return res;
}

Student *Student_init(int id, char *name, int age)
{
    Student *student = malloc(sizeof(Student));
    student->person = Person_init(name, age);
    student->obj = Object_init();

    student->obj->toString = __Student_toString;
    student->id = id;
    return student;
}

void Student_setId(Student *student, int id)
{
    student->id = id;
}
int Student_getId(Student *student)
{
    return student->id;
}

char *Student_getName(Student *student)
{
    return Person_getName(student->person);
}

int Student_getAge(Student *student)
{
    return Person_getAge(student->person);
}