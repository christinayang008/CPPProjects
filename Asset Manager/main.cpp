// main.cpp
// Test harness for the AssetManager lab.
// You should not need to modify this file.
//
// This program is organized into four sections, one per function you
// are asked to implement in AssetManager.cpp:
//   Section 1: addObject(index, id, name, active)   -- 25 points
//   Section 2: addObject(index, Asset*)              -- 25 points
//   Section 3: moveObject(fromIndex, toIndex)         -- 25 points
//   Section 4: removeObject(index)                    -- 25 points
//
// Each section is broken into several smaller checks that together add
// up to that section's 25 points. Each check tests one specific fact
// about your implementation, not just "did it work." When a check
// fails, it prints which fact failed and a hint about where to look,
// but never the exact fix. Your running score is printed after every
// single check, so you can watch it change as you write code and
// recompile.
//
// A note on how Sections 3 and 4 are set up: to test moveObject and
// removeObject in isolation from whatever bugs may or may not exist in
// your addObject implementations, this harness places Assets directly
// into the roster array itself for those two sections, rather than
// calling your addObject to do it. That means a broken addObject
// cannot cost you points in Sections 3 or 4, and a broken moveObject or
// removeObject cannot cost you points in Sections 1 or 2. Each
// section's score reflects only that section's own function.
//
// An unmodified copy of this lab (all four TODOs left as their
// starting stubs) compiles cleanly and scores exactly 0 out of 100.

#include <iostream>
#include "AssetManager.h"
using namespace std;

int pointsEarned = 0;
const int TOTAL_POINTS_POSSIBLE = 100;

// Prints a pass or fail line for one check, updates the running score,
// and prints that running score immediately.
void report(bool passed, int weight, string checkName, string failureExplanation) {
    if (passed) {
        pointsEarned += weight;
        cout << "[PASS] (" << weight << " pts) " << checkName << endl;
    } else {
        cout << "[FAIL] (0 / " << weight << " pts) " << checkName << endl;
        cout << "       Problem: " << failureExplanation << endl;
    }
    cout << "       Running score: " << pointsEarned << " / " << TOTAL_POINTS_POSSIBLE << endl;
}

// Returns true if every roster slot except the one or two given
// "except" indices still points to whatever it pointed to in the
// snapshot. Used to confirm a function only touched the slot(s) it was
// supposed to touch.
bool otherSlotsUnchanged(AssetManager& manager, Asset* snapshot[], int except1, int except2 = -1) {
    for (int i = 0; i < ROSTER_SIZE; i++) {
        if (i == except1 || i == except2) continue;
        if (manager.roster[i] != snapshot[i]) return false;
    }
    return true;
}

void takeSnapshot(AssetManager& manager, Asset* snapshot[]) {
    for (int i = 0; i < ROSTER_SIZE; i++) {
        snapshot[i] = manager.roster[i];
    }
}

int main() {
    cout << "Running AssetManager test harness." << endl;
    cout << "----------------------------------------" << endl;

    AssetManager manager;
    Asset* snapshot[ROSTER_SIZE];

    // ============================================================
    // Section 1: addObject(index, id, name, active)      25 points
    // ============================================================
    cout << endl << "Section 1: addObject(index, id, name, active)" << endl;

    takeSnapshot(manager, snapshot);
    Asset* a0 = manager.addObject(0, 100, "Laptop", true);

    report(
        manager.roster[0] != nullptr,
        6,
        "addObject(value) stores a pointer in the target slot",
        "roster[0] is still nullptr after calling addObject. The new "
        "Asset was either never created with new, or its pointer was "
        "never stored in the array."
    );

    report(
        a0 != nullptr && a0->getId() == 100 && a0->getName() == "Laptop" && a0->getActive() == true,
        6,
        "addObject(value) correctly sets fields from its parameters",
        "The returned pointer's fields do not match the values passed "
        "into addObject. Check that id, name, and active are being "
        "passed into the Asset constructor in the right order."
    );

    report(
        Asset::liveCount == 1,
        5,
        "addObject(value) increases Asset::liveCount",
        "Asset::liveCount is not 1 after creating a single Asset. "
        "addObject may not be using new to construct the Asset."
    );

    report(
        manager.roster[0] != nullptr && otherSlotsUnchanged(manager, snapshot, 0),
        4,
        "addObject(value) does not affect unrelated roster slots",
        "Either the target slot was not updated, or a slot other than "
        "the one you were told to use changed value. Double check you "
        "are indexing the roster array with the index parameter, not a "
        "hardcoded number or a different variable."
    );

    // Overwrite the same slot to test the orphan/leak case.
    int liveBeforeOverwrite = Asset::liveCount;
    manager.addObject(0, 999, "Docking Station", false);

    report(
        Asset::liveCount == liveBeforeOverwrite
            && manager.roster[0] != nullptr
            && manager.roster[0]->getId() == 999,
        4,
        "addObject(value) deletes the previous occupant before overwriting an already-occupied slot",
        "Asset::liveCount grew when you called addObject a second time "
        "on a slot that already held an Asset. That means the first "
        "Asset was orphaned instead of deleted before the new one was "
        "stored. Check whether roster[index] is already non null before "
        "you overwrite it."
    );

    // ============================================================
    // Section 2: addObject(index, Asset*)                 25 points
    // ============================================================
    cout << endl << "Section 2: addObject(index, Asset*)" << endl;

    takeSnapshot(manager, snapshot);
    int liveBeforeExternal = Asset::liveCount;
    Asset* externalAsset = new Asset(200, "Monitor", false); // liveCount++ happens here, not inside addObject
    Asset* returnedExternal = manager.addObject(1, externalAsset);

    report(
        manager.roster[1] == externalAsset,
        6,
        "addObject(pointer) stores the exact pointer it was given",
        "roster[1] does not hold the same address as externalAsset. "
        "This overload should not call new. It should store the pointer "
        "it was handed, not build a new Asset from it."
    );

    report(
        manager.roster[1] == externalAsset && Asset::liveCount == liveBeforeExternal + 1,
        6,
        "addObject(pointer) does not construct an additional Asset",
        "Asset::liveCount changed by more than the single increment "
        "caused by the new Asset(...) call in this test file. If your "
        "addObject(index, Asset*) is calling new itself, remove that; "
        "this overload only stores a pointer it is already given."
    );

    report(
        manager.roster[1] != nullptr && otherSlotsUnchanged(manager, snapshot, 1),
        5,
        "addObject(pointer) does not affect unrelated roster slots",
        "Either the target slot was not updated, or a slot other than "
        "the one you were told to use changed value. Double check you "
        "are indexing the roster array with the index parameter."
    );

    int liveBeforeExternalOverwrite = Asset::liveCount;
    Asset* externalReplacement = new Asset(201, "Keyboard", true); // liveCount++ here
    manager.addObject(1, externalReplacement);

    report(
        Asset::liveCount == liveBeforeExternalOverwrite,
        4,
        "addObject(pointer) deletes the previous occupant before overwriting an already-occupied slot",
        "Asset::liveCount grew by more than the one increment caused by "
        "creating externalReplacement in this test file. That means the "
        "Asset previously in roster[1] was orphaned instead of deleted "
        "before you stored the new pointer there."
    );

    report(
        returnedExternal == externalAsset,
        4,
        "addObject(pointer) returns the same pointer it was given",
        "The value returned by addObject(index, Asset*) does not match "
        "the pointer that was passed in as an argument."
    );

    // ============================================================
    // Section 3: moveObject(fromIndex, toIndex)           25 points
    // ============================================================
    cout << endl << "Section 3: moveObject(fromIndex, toIndex)" << endl;

    // This Asset is placed directly into the roster by the test itself,
    // not through your addObject, so this section's score reflects
    // moveObject alone.
    manager.roster[2] = new Asset(300, "Router", true);

    takeSnapshot(manager, snapshot);
    int liveBeforeMove = Asset::liveCount;
    Asset* movedPointer = manager.moveObject(2, 6);

    report(
        manager.roster[6] != nullptr && manager.roster[6] == movedPointer,
        6,
        "moveObject places the pointer in the destination slot",
        "roster[6] does not hold the pointer that moveObject returned. "
        "The Asset may not have actually been moved to the destination "
        "index."
    );

    report(
        manager.roster[2] == nullptr,
        6,
        "moveObject clears the source slot after moving",
        "roster[2] still holds a pointer after moving its Asset to "
        "another slot. roster[2] and roster[6] are now both pointing "
        "at the same Asset. Set roster[fromIndex] back to nullptr after "
        "copying the pointer to roster[toIndex]."
    );

    report(
        manager.roster[6] != nullptr
            && manager.roster[6]->getId() == 300
            && manager.roster[6]->getName() == "Router"
            && manager.roster[6]->getActive() == true,
        5,
        "moveObject preserves the moved object's data",
        "The Asset at the destination slot does not have the data of "
        "the Asset that was originally at the source slot. moveObject "
        "should move the existing pointer, not build a new Asset."
    );

    report(
        manager.roster[6] != nullptr && manager.roster[2] == nullptr
            && otherSlotsUnchanged(manager, snapshot, 2, 6),
        4,
        "moveObject does not affect unrelated roster slots",
        "Either the move did not actually happen, or a slot other than "
        "the source and destination changed value. Double check you are "
        "only touching roster[fromIndex] and roster[toIndex]."
    );

    report(
        manager.roster[6] != nullptr && manager.roster[2] == nullptr
            && Asset::liveCount == liveBeforeMove,
        4,
        "moveObject does not create or destroy any Assets",
        "Either the move did not actually happen, or Asset::liveCount "
        "changed during the move. Moving a pointer between array slots "
        "should never call new or delete; it should only copy an "
        "existing address and clear the old slot."
    );

    // ============================================================
    // Section 4: removeObject(index)                       25 points
    // ============================================================
    cout << endl << "Section 4: removeObject(index)" << endl;

    // Again placed directly into the roster so this section's score
    // reflects removeObject alone.
    manager.roster[3] = new Asset(400, "Switch", true);

    takeSnapshot(manager, snapshot);
    Asset* addressBeforeRemove = manager.roster[3];
    int liveBeforeRemove = Asset::liveCount;
    Asset* returnedFromRemove = manager.removeObject(3);

    report(
        manager.roster[3] == nullptr,
        6,
        "removeObject clears the slot after deleting",
        "roster[3] still holds a non null pointer after removeObject "
        "was called on it. The Asset may have been deleted without "
        "clearing the array slot, which would leave a dangling pointer "
        "in the array."
    );

    report(
        Asset::liveCount == liveBeforeRemove - 1,
        6,
        "removeObject decreases Asset::liveCount",
        "Asset::liveCount did not decrease by exactly one after "
        "removeObject was called. removeObject may not be calling "
        "delete on the Asset at this index."
    );

    report(
        returnedFromRemove == addressBeforeRemove,
        5,
        "removeObject returns the address that was removed",
        "The pointer returned by removeObject does not match the "
        "address that was stored in the slot before the call. Capture "
        "the pointer before you delete it, and return that saved value, "
        "not roster[index] after it has already been cleared."
    );

    report(
        manager.roster[3] == nullptr && otherSlotsUnchanged(manager, snapshot, 3),
        4,
        "removeObject does not affect unrelated roster slots",
        "Either the target slot was not cleared, or a slot other than "
        "the one you were told to remove changed value. Double check "
        "you are only touching roster[index]."
    );

    cout << "Calling removeObject a second time on the same slot." << endl;
    cout << "If your program crashes here, that is a double free." << endl;
    int liveBeforeSecondRemove = Asset::liveCount;
    Asset* returnedFromSecondRemove = manager.removeObject(3);

    report(
        manager.roster[3] == nullptr
            && Asset::liveCount == liveBeforeSecondRemove
            && returnedFromSecondRemove == nullptr,
        4,
        "removeObject is safe to call twice on the same slot",
        "Calling removeObject twice on the same already empty slot "
        "either changed Asset::liveCount again or returned a non null "
        "pointer. Your function likely does not check whether the slot "
        "is already nullptr before deleting it."
    );

    // ============================================================
    cout << endl << "----------------------------------------" << endl;
    cout << "Final score: " << pointsEarned << " / " << TOTAL_POINTS_POSSIBLE << endl;

    return 0;
}
