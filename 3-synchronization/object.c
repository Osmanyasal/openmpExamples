
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

static long long __hashCode(struct Object *obj)
{
    long long hashVal = 5;

    return hashVal;
}
static char *__toString(struct Object *obj)
{
    char *arr = malloc(sizeof(char) * 7);
    strcpy(arr,"Object");
    return arr;
}

Object *Object_init()
{
    Object *obj = malloc(sizeof(Object));
    obj->hashCode = __hashCode;
    obj->toString = __toString;
    return obj;
}
