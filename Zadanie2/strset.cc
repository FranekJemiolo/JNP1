#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include "strset.h"
#include "strsetconst.h"
using namespace std;
#define ul unsigned long
#define cc const char
#define ss set<string>
#define strpair pair<ul,ss>
#define strmap map<ul,ss>
#ifdef DEBUG
static const bool debug = true;
#else
static const bool debug = false;
#endif

//The id which will next set get.
static ul maxId = 0;

//The map that holds a number key and mapped set.
strmap& strsets()
{
    static strmap* setty = new strmap();
    return *setty;
}

strmap::iterator findSet(ul id)
//This function returns a iterator to given set;
{
    strmap::iterator it;
    //Searching for the iterator that points to wanted set.
    it = strsets().find(id);
    return it;
}

void debug1Arg(const char* func, ul arg)
//Debug function that prints some info about some set. 
{
    fprintf(stderr, "%s(%lu)\n", func, arg);
}

void debugNonExistentSet(const char* func, ul id)
//Debug function that tells us that wanted set does not exist. 
{
    fprintf(stderr, "%s: set %lu does not exist\n", func, id);
}

ul strset_new()
{
    ul i;
    //New set will always get a bigger number than previous sets.
    (!strsets().empty()) ? (i = (maxId)) : (i = 0);
    //Pushing back a new pair of id and empty string set to our map.
    if (i == 0) {
        set<string> setstr42;
        if (debug) {
            fprintf(stderr, "strsetconst init invoked\n");
            fprintf(stderr, "strset_new()\n");
        }
        setstr42.insert("42");
        strsets().insert(strpair (i, setstr42));
        if (debug) {
            fprintf(stderr, "strset_new: the Set 42 created\n");
            fprintf(stderr, "strsetconst init finished\n");
        }
    }
    else {
        strsets().insert(strpair (i, ss ()));
        if (debug) {
            fprintf(stderr, "strset_new()\n");
            fprintf(stderr, "strset_new: set %lu created\n", i);
        }
    }
    //Updating biggest id set.
    maxId++;
    return i;
}

void strset_delete(ul id)
{
    static const char* name = "strset_delete";
    if (debug)
        debug1Arg(name, id);
    if (id != strset42){
        strmap::iterator it = strsets().find(id);
        if (it != strsets().end()) {
            strsets().erase(it);
            if (debug)
                fprintf(stderr, "%s: set %lu deleted\n", name, id);
        }
        if (debug)
            debugNonExistentSet(name, id);
    } else if (debug)
        fprintf(stderr, "%s: attempt to remove the 42 Set\n", name);
}

size_t strset_size(ul id)
{
    static const char* name = "strset_size";
    if (debug)
        debug1Arg(name, id);
    strmap::iterator it = strsets().find(id);
    size_t ret = 0;
    //If we found wanted set then we are returning its size.
    if (it != strsets().end()) {
        ret = it->second.size();
        if (debug)
            fprintf(stderr, "%s: set %lu contains %zu element(s)\n", name,
                id, ret);
    } else if (debug)
        debugNonExistentSet(name, id);
    return ret;
}

void strset_insert(ul id, cc* value)
{
    static const char* name = "strset_insert";
    if (debug)
        fprintf(stderr, "%s(%lu, \"%s\")\n", name, id, value); 
    if (id != strset42){
        strmap::iterator it = strsets().find(id);
        const string txt = value;
        //If we found wanted set, we are inserting given text and we are also 
        //checking if this text was not already there.
        if (it != strsets().end()) {
            pair<ss::iterator, bool> ret = it->second.insert(txt);
            if (debug) {
                if (ret.second == false)
                    fprintf(stderr, 
                        "%s: set %lu, element \"%s\" was already present\n",
                        name, id, value);
                else
                    fprintf(stderr, "%s: set %lu, element \"%s\" inserted\n",
                        name, id, value);
            }
        } else if (debug)
            debugNonExistentSet(name, id);
    } else if (debug)
        fprintf(stderr, "%s: attempt to insert into the 42 Set\n", name);
}

void strset_remove(ul id, cc* value)
{
    static const char* name = "strset_remove";
    if (debug)
        fprintf(stderr, "%s(%lu, \"%s\")\n", name, id, value);
    if (id != strset42){
        strmap::iterator it = strsets().find(id);
        const string txt = value;
        //If we found wanted set, we are checking if this text is there and
        //then we are removing it.
        if (it != strsets().end()) {
            if ((it->second.find(txt)) != (it->second.end())) {
                it->second.erase(txt);
                if (debug)
                    fprintf(stderr, "%s: set %lu, element \"%s\" removed\n",
                        name, id, value);
            } else if (debug)
                fprintf(stderr, "%s: set %lu does not contain element \"%s\"\n",
                    name, id, value);
        } else if (debug)
            debugNonExistentSet(name, id);
    } else if (debug)
        fprintf(stderr, "%s: attempt to remove from the 42 Set\n", name);
}

int strset_test(ul id, cc* value)
{
    static const char* name = "strset_test";
    if (debug)
        fprintf(stderr, "%s(%lu, \"%s\")\n", name, id, value);
    strmap::iterator it = strsets().find(id);
    const string txt = value;
    int ret = 0;
    //If we found wanted set and the text is in the set, we are returning 1
    //otherwise 0.
    if (it != strsets().end()) {
        (it->second.find(txt) != it->second.end()) ? (ret = 1) : (ret = 0);
        if (debug) {
            if (ret == 1)
                fprintf(stderr, "%s: set %lu contains the element \"%s\"\n",
                    name, id, value);
            else
                fprintf(stderr,
                    "%s: set %lu does not contain the element \"%s\"\n",
                    name, id, value);
        }
    } else if (debug)
        debugNonExistentSet(name, id);
    return ret;
}


void strset_clear(ul id)
{
    static const char* name = "strset_clear";
    if (debug)
        debug1Arg(name, id);   
    if (id != strset42){
        strmap::iterator it = strsets().find(id);
        //If we found wanted set, we are removing every element of it.
        if (it != strsets().end()) {
            ss::iterator sit;
            for (sit = it->second.begin(); sit != it->second.end(); ++sit)
            {
                it->second.erase(sit);
            }
            if (debug)
                fprintf(stderr, "%s: set %lu cleared\n", name, id);
        } else if (debug)
            debugNonExistentSet(name, id);
    } else if (debug)
        fprintf(stderr, "%s: attempt to clear the 42 Set\n", name);
}

int strset_comp(ul id1, ul id2)
{
    static const char* name = "strset_comp";
    if (debug)
        fprintf(stderr, "%s(%lu, %lu)\n", name, id1, id2);
    strmap::iterator it1 = strsets().find(id1), it2 = strsets().find(id2);
    int ret = 0;
    //If we found wanted sets, we are comparing their sizes and then element by
    //element we will be checking if one or the other is bigger.
    if ((it1 != strsets().end()) && (it2 != strsets().end())) {
        ss::iterator sit1, sit2, endsit1, endsit2;
        sit1 = it1->second.begin();
        sit2 = it2->second.begin();
        endsit1 = it1->second.end();
        endsit2 = it2->second.end();
        bool stop = false;
        while ((sit1 != endsit1) && (sit2 != endsit2) && (!stop))
        {
            if (sit1->compare(*sit2) == 0) {
                ++sit1;
                ++sit2;
            }
            else if (sit1->compare(*sit2) < 0) {
                ret = -1;
                stop = true;
            }
            else if (sit1->compare(*sit2) > 0) {
                ret = 1;
                stop = true;
            }
        }
        if (!stop) {
            if (sit1 != it1->second.end()) {
                ret = 1;
            }
            else if (sit2 != it2->second.end()) {
                ret = -1;
            }
        }

    }
    else if (it1 != strsets().end()) {
        if (it1->second.empty()) {
            ret = 0;
        }
        else {
            ret = 1;  
        }
        if (debug)
            debugNonExistentSet(name, id2);

    }
    else if (it2 != strsets().end()) {
        if (it2->second.empty()) {
            ret = 0;
        }
        else {
            ret = -1;  
        }
        if (debug)
            debugNonExistentSet(name, id1);
    }
    else if (debug) {
        debugNonExistentSet(name, id1);
        debugNonExistentSet(name, id2);
    }    
    if (debug)
        fprintf(stderr, "%s: result of comparing set %lu to set %lu is %d\n",
            name, id1, id2, ret);
    return ret;
}
