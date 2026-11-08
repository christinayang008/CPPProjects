// AssetManager.cpp
// Implementation of the AssetManager class.
//
// The constructor and destructor below are already implemented for you.
// Read them anyway. They show you the pattern you will need to reuse
// inside the four functions you are about to write.
//
// You will implement: addObject (two overloads), moveObject, and
// removeObject. Each one is doing real pointer manipulation with new
// and delete. Each one also has a specific way to get it subtly wrong
// that will either crash the program, leak memory, or corrupt the
// array. The comments above each function tell you what to watch for.
// They do not give you the code itself.
//
// This file currently compiles as-is and will score 0 out of 100 when
// run against main.cpp, since none of the four functions do anything
// yet. Compile and run it once before you write any code, just to see
// that starting point and confirm your toolchain works.

#include "AssetManager.h"
#include <iostream>
using namespace std;

// Already implemented.
// Every slot starts as nullptr. This matters because an uninitialized
// pointer does not start out empty, it starts out holding whatever bits
// happened to already be in that memory location. Setting every slot to
// nullptr here guarantees that an "empty" slot can always be safely
// checked with a simple if (roster[i] == nullptr) test later.
AssetManager::AssetManager() {
	for (int i = 0; i < ROSTER_SIZE; i++) {
		roster[i] = nullptr;
	}
}

// Already implemented.
// When an AssetManager is destroyed, any Assets it still owns need to be
// cleaned up too, or they become leaks the moment this object goes away.
// This loop walks the roster and deletes anything still present. Notice
// this is the same delete and null pattern you will need to write
// yourself inside removeObject.
AssetManager::~AssetManager() {
	for (int i = 0; i < ROSTER_SIZE; i++) {
		if (roster[i] != nullptr) {
			delete roster[i];
			roster[i] = nullptr;
		}
	}
}

// TODO: Implement addObject (the value overload).
//
// Parameters: an index into the roster, and the three values needed to
// build a new Asset (id, name, active).
//
// Requirements:
//   1. Use new to create a single Asset on the heap, passing the three
//      values through to its constructor.
//   2. Store the resulting pointer in roster[index].
//   3. Return the pointer.
//
// Think about what should happen if roster[index] is not nullptr when
// this function is called, meaning a slot that is already occupied by a
// different Asset. Overwriting that slot's pointer without deleting the
// old Asset first would orphan it. It would still be sitting on the heap
// with no pointer left anywhere in the program pointing to it. That is a
// memory leak you would be causing directly, not one that happens later.
// Decide how you want to handle this case before you write the rest of
// the function.
Asset* AssetManager::addObject(int index, int id, string name, bool active)
{
	if (roster[index] != nullptr) delete roster[index];
	roster[index] = new Asset(id, name, active);
	return roster[index];
}

// TODO: Implement addObject (the pointer overload).
//
// Parameters: an index into the roster, and a pointer to an Asset that
// already exists somewhere else in the program.
//
// This is not the same job as the overload above. The overload above
// builds a brand new Asset with new. This overload does not call new at
// all. The Asset already exists before this function is ever called;
// your only job here is to store the pointer you are given into the
// correct roster slot and return it.
//
// Requirements:
//   1. Store existingAsset in roster[index]. Do not construct anything.
//   2. Return existingAsset.
//
// The same occupied slot problem from the overload above applies here
// too. If roster[index] already holds a different Asset when this
// function is called, you still need to delete that old Asset before
// you overwrite the slot with the new pointer, for exactly the same
// orphaning reason described above.
Asset* AssetManager::addObject(int index, Asset* existingAsset)
{
	if (roster[index] != nullptr) delete roster[index];
	roster[index] = existingAsset;
	return existingAsset;

}

// TODO: Implement moveObject.
//
// Parameters: the index to move an Asset pointer from, and the index to
// move it to.
//
// Requirements:
//   1. Take the pointer currently stored at roster[fromIndex].
//   2. Store that same pointer at roster[toIndex].
//   3. Clear roster[fromIndex] so it no longer also points at that
//      Asset.
//   4. Return the pointer that was moved.
//
// Read requirement 3 again. If you only complete steps 1 and 2, you have
// not actually moved anything, you have copied the address into a second
// slot. Both roster[fromIndex] and roster[toIndex] would now point to
// the exact same Asset on the heap. That is not a crash by itself, but
// it means your array no longer accurately reflects which slots are
// holding which objects. It will cause real problems the moment either
// slot is later deleted, because deleting one would leave the other
// slot holding a dangling pointer to memory that no longer belongs to
// your program.
Asset* AssetManager::moveObject(int fromIndex, int toIndex)
{
	if (roster[toIndex] != nullptr) delete roster[toIndex];
	roster[toIndex] = roster[fromIndex];
	roster[fromIndex] = nullptr;
	return roster[toIndex];
}

// TODO: Implement removeObject.
//
// Parameter: the index of the Asset to remove.
//
// Requirements:
//   1. Save the pointer currently stored at roster[index] before you do
//      anything else to it.
//   2. Delete the Asset pointed to by roster[index].
//   3. Set roster[index] to nullptr after deleting it.
//   4. Return the pointer you saved in step 1. This is the address that
//      was just deleted, not roster[index] itself, since roster[index]
//      is nullptr by the time you return.
//
// Read requirement 3 again, and think about why it has to happen right
// after requirement 2, not at some later point. Once you call delete on
// a pointer, that pointer still holds the same address, but the memory
// at that address no longer belongs to your program. The pointer is now
// dangling. If this function is ever called twice on the same index,
// and you have not set roster[index] back to nullptr after the first
// call, the second call will attempt to delete that same dangling
// pointer again. That is a double free, and it corrupts the heap rather
// than just failing safely. If roster[index] is already nullptr when
// this function is called, there is nothing to delete; do not call
// delete on a nullptr slot, and return nullptr instead.
Asset* AssetManager::removeObject(int index)
{
	Asset *k = roster[index];
	if (roster[index] != nullptr)
	{
		delete roster[index];
		roster[index] = nullptr;
	}
	return k;
}


