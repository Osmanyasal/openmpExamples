#ifndef OBJECT_H
#define OBJECT_H

typedef struct Object
{
    long long (*hashCode)(struct Object *obj);
    char *(*toString)(struct Object *obj);
} Object;

Object *Object_init();

#endif