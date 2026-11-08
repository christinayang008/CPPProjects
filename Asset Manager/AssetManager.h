// AssetManager.h
// Interface for the AssetManager class.
// This file is complete. You should not need to modify it.
//
// AssetManager owns a fixed size array of Asset pointers. Asset itself
// is already fully implemented and given to you, since it does not use
// pointers internally. All of the pointer manipulation in this lab
// happens in AssetManager.cpp, where you will implement four
// functions that add, move, and remove Assets from this array using
// new and delete. Read each function's comments in AssetManager.cpp
// before writing any code, since each one tests a specific and
// different way pointer mistakes happen.

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Asset.h"
using namespace std;

// Fixed capacity of the roster array. Not a variable, this is a constant
// used to size the array and to bounds check index arguments.
const int ROSTER_SIZE = 10;

class AssetManager {
public:
    // The roster is public so the test harness in main.cpp can directly
    // inspect each slot after calling your functions, and in some cases
    // set up a slot directly itself before calling one of your
    // functions. In a larger or more formal codebase you would likely
    // keep this private and provide read only access through a getter,
    // but for this lab direct access makes it much easier to verify
    // your work slot by slot.
    Asset* roster[ROSTER_SIZE];

    // Constructor. Already implemented. Initializes every slot to
    // nullptr so the array does not start out holding garbage addresses.
    AssetManager();

    // Destructor. Already implemented. Deletes any Assets still present
    // in the roster when an AssetManager is destroyed, so the test
    // program itself does not leak memory after it finishes its checks.
    ~AssetManager();

    // TODO (you implement this): Creates a new Asset on the heap using
    // the three values given, stores its pointer in the roster slot at
    // the given index, and returns the pointer.
    Asset* addObject(int index, int id, string name, bool active);

    // TODO (you implement this): Stores an already-constructed Asset
    // pointer directly into the roster slot at the given index, and
    // returns the pointer. Unlike the overload above, this version does
    // not call new itself. The object already exists somewhere else in
    // the program before this function is ever called.
    Asset* addObject(int index, Asset* existingAsset);

    // TODO (you implement this): Moves the Asset pointer currently at
    // fromIndex into toIndex.
    Asset* moveObject(int fromIndex, int toIndex);

    // TODO (you implement this): Deletes the Asset at the given index,
    // clears that slot, and returns the address the slot held
    // immediately before it was deleted.
    Asset* removeObject(int index);
};

#endif
