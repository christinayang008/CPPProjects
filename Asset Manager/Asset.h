// Asset.h
// Interface for the Asset class.
// This file is complete. You do not need to modify it, and there is no
// student work in Asset.cpp either. Asset itself does not use pointers
// internally, it is just a plain data object. All of the pointer work
// in this lab happens one level up, in AssetManager, which is the file
// you will actually be editing.
//
// Asset has three fields and a getter and setter for each.

#ifndef ASSET_H
#define ASSET_H

#include <string>
using namespace std;

class Asset {
public:
    // Static counter that tracks how many Asset objects currently exist
    // at any given moment. It is incremented in the constructor below
    // and decremented in the destructor below, both of which are
    // already implemented for you in Asset.cpp.
    //
    // The test harness in main.cpp reads this value after calling your
    // AssetManager functions. Since Asset's own constructor and
    // destructor are fixed and already correct, any unexpected value in
    // liveCount during testing is necessarily caused by how your
    // AssetManager code is calling new and delete, not by anything in
    // this class.
    static int liveCount;

    // Constructor. Already implemented in Asset.cpp.
    Asset(int id, string name, bool active);

    // Destructor. Already implemented in Asset.cpp.
    ~Asset();

    // Getters and setters. Already implemented in Asset.cpp.
    int getId() const;
    void setId(int newId);

    string getName() const;
    void setName(string newName);

    bool getActive() const;
    void setActive(bool newActive);

private:
    int id;
    string name;
    bool active;
};

#endif
