// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Teyo Turrubiates
// ttt2443
// Slip days used: 0
// Summer 2022
// Copy and paste this file at the top of all your submitted source code files.
// Do not turn this in by itself.

#include <assert.h>     //to provide assert()
#include <stdbool.h>    //to provide "bool" datatype (true or false)
#include <stdlib.h>     //dynamic allocation functions
#include <stdint.h>     //integer datatype with precise explicit width
#include <string.h>     //utility functions for string management
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    int length = strlen(src);
    UTString* Copy;
    Copy = (UTString*)malloc(sizeof(UTString));
    Copy->length = length;
    Copy->capacity = length;
    Copy->string = (char*)malloc(length + 1 + sizeof(SIGNATURE));
    strcpy(Copy->string, src);
    CHECK(Copy) = SIGNATURE;
    /Users/teyoturrubiates/CLionProjects/Project3/Project3.cpp


    return Copy;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    return(s->length);
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    /*
    if((s->length + strlen(suffix)) < s->capacity){

        strcat(s->string, suffix);
        s->length = s->length + strlen(suffix);
        CHECK(s) = SIGNATURE;
    }
    else {
        while(s->length < s->capacity && *suffix != '\0'){
            s->string[s->length] = *suffix;
            suffix++;
            s->length++;
        }
        s->string[s->length] = '\0';
        CHECK(s) = SIGNATURE;
    }
    */
    while(s->length < s->capacity && *suffix != '\0'){
        s->string[s->length] = *suffix;
        suffix++;
        s->length++;
    }
    s->string[s->length] = '\0';
    CHECK(s) = SIGNATURE;


    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) { //CHECK
    assert(isOurs(dst));
    if(strlen(src) < dst->capacity){
        strcpy(dst->string, src);
        dst->length = strlen(src);
        CHECK(dst) = SIGNATURE;
        return dst;
    }
    else {
        dst->length = 0;
        while(dst->length < dst->capacity && *src != '\0'){
            dst->string[dst->length] = *src;
            src++;
            dst->length++;
        }
        dst->string[dst->length] = '\0';
        CHECK(dst) = SIGNATURE;
        return dst;
    }
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);

}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(s->capacity >= new_capacity){
        return s;
    }
    else {
        char holdStr[100];
        strcpy(holdStr, s->string);
        free(s->string);
        s->string = (char*)malloc(new_capacity + 1 + sizeof(SIGNATURE));
        strcpy(s->string, holdStr);
        s->capacity = new_capacity;
        CHECK(s) = SIGNATURE;
        return s;

    }
}
