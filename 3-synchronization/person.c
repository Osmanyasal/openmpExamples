#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *__Person_toString(struct Object *obj)
{
    Person *person = (Person *)obj;
    char *str = malloc(sizeof(char) * 500);
    strcpy(str, "Person(name=");
    strcat(str, Person_getName(person));
    strcat(str, ",age=");
    int age = Person_getAge(person);
    char agear[20];
    sprintf(agear, "%d", age);
    strcat(str, agear);
    strcat(str, ");");
    return str;
}

static long long __Person_hashcode(struct Object *obj)
{
    return 8765432l;
}

Person *Person_init(char *name, int age)
{
    Person *person = malloc(sizeof(Person));
    person->obj = Object_init();
    person->obj->hashCode = __Person_hashcode;
    person->obj->toString = __Person_toString;

    person->age = age;
    person->name = name;
    return person;
}

void Person_setName(Person *person, char *name)
{
    person->name = name;
}

void Person_setAge(Person *person, int age)
{
    person->age = age;
}
char *Person_getName(Person *person)
{
    return person->name;
}
int Person_getAge(Person *person)
{
    return person->age;
}