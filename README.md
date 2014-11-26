214-pa2
=======

Assignment 2: Sorted List

###Version
1.0

###Introduction
In this assignment, you will practice with more complex data structures, as well as practice using
function pointers (along with using data pointers as in the last assignment).

Your task is to write a set of types and functions that implement a sorted list. The sorted list will
contain opaque objects. That is, the objects will be given to you as void* pointers. When a sorted
list is first created, the caller will provide you with a pointer to a comparator function and a destruct
function. This comparator function will understand the actual type of the objects to be stored in
the sorted list, and given two objects, will return an ordering of the two objects. Subsequently,
when new objects are inserted into the list, you will use the given comparator function to insert the
new objects such that the list will remain sorted in descending order; that is, objects are ordered
from largest (front of the list) to smallest (end of the list). The destruct function will deallocate
the object.

You will also implement an iterator to help users walk through lists. This iterator, together with
returning pointers to your sorted list objects as void*, will help you practice information hiding.
That is, your implementation is similar to a Java class, where the users do not know about the
implementation and so cannot access parts of the objects directly. (In C, there are obviously ways
to get around your hiding; nevertheless, it is good programming practice because it requires effort
to violate the hiding.)

###Invocation
    - make
    - ./sl <#>  where # corresponds to a testcase implemented in test_main.c
