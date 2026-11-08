// Asset.cpp
// Complete implementation of the Asset class.
// There is no student work in this file.
//
// Notice that the constructor increases Asset::liveCount and the
// destructor decreases it. This is the mechanism the test harness in
// main.cpp uses to detect whether AssetManager is creating and
// destroying objects correctly. Since this file is fixed and correct,
// any incorrect liveCount value seen during testing means the bug is in
// AssetManager.cpp, not here.

#include "Asset.h"
#include <iostream>
using namespace std;

// Definition of the static member declared in Asset.h.
// This line is required exactly once in a .cpp file for any static
// member variable. It starts the count at zero before any Asset has
// been created.
int Asset::liveCount = 0;

Asset::Asset(int id, string name, bool active) {
    this->id = id;
    this->name = name;
    this->active = active;
    liveCount++;
}

Asset::~Asset() {
    liveCount--;
}

int Asset::getId() const {
    return id;
}

void Asset::setId(int newId) {
    id = newId;
}

string Asset::getName() const {
    return name;
}

void Asset::setName(string newName) {
    name = newName;
}

bool Asset::getActive() const {
    return active;
}

void Asset::setActive(bool newActive) {
    active = newActive;
}
