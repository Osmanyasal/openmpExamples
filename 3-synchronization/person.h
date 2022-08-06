#ifndef PERSON_H
#define PERSON_H

#include "object.h"

typedef struct Person
{
    char *name;
    int age;
    Object *obj;
} Person;

Person *Person_init(char *name, int age);

void Person_setName(Person *person, char *name);
void Person_setAge(Person *person, int age);

char *Person_getName(Person *person);
int Person_getAge(Person *person);

#endif