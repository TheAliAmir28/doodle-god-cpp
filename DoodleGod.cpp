#include "DoodleGod.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Default Constructor
DoodleGod::DoodleGod() {
    //Initialize default values for the default member variables
    m_myName = "";
    m_attempts = 0;
    m_repeats = 0;
    m_numElements = 0;
}

//Overloaded Constructor
DoodleGod::DoodleGod(string name) {
    //Assign name given by user to m_myName member variable and set other variables to default
    m_myName = name;
    m_attempts = 0;
    m_repeats = 0;
    m_numElements = 0;
}

// Name: GetName()
// Desc - Getter for DoodleGod name
// Preconditions - DoodleGod exists
// Postconditions - Returns the name of the DoodleGod
string DoodleGod::GetName() {
    return m_myName;
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the DoodleGod
// Preconditions - DoodleGod exists
// Postconditions - Sets name of DoodleGod
void DoodleGod::SetName(string name) {
    m_myName = name;
}

// Name: DisplayElements()
// Desc - Displays a numbered list of all elements known by the DoodleGod
// Preconditions - DoodleGod exist
// Postconditions - Displays numbered list of all known elements
void DoodleGod::DisplayElements() {
    for (int i = 0; i < m_numElements; i++) {
        //If an element resides at the index, then display it.
        if (m_myElements[i]->m_name != "") {
            cout << i+1 << ". " << m_myElements[i]->m_name << endl;
        }
    }
}

// Name: GetNumElements()
// Desc - Returns number of elements known by the DoodleGod
// Preconditions - DoodleGod exists
// Postconditions - Returns the integer value of all known elements
int DoodleGod::GetNumElements() {
    return m_numElements;
}

// Name: CheckElement(Element)
// Desc - Checks to see if the DoodleGod had identified an element
// Preconditions - DoodleGod already has elements
// Postconditions - Returns true if DoodleGod has element else false
bool DoodleGod::CheckElement(Element anElement) {
    for (int i = 0; i < m_numElements; i++) {
        if (m_myElements[i] != nullptr) {
            if (m_myElements[i]->m_name == anElement.m_name) {
                return true;
            }
        }
    }
    return false;
}

// Name: AddElement(Element)
// Desc - Adds element to m_myElements if not known and increases numElements
// Preconditions - DoodleGod exists and new element not already known
// Postconditions - Adds element to m_myElements
void DoodleGod::AddElement(Element* anElement) {
    bool elementsExists = CheckElement(*anElement);
    if (elementsExists == false) {
        m_myElements[m_numElements] = anElement;
        m_numElements++;
    } else {
        //if the element already exists, print a message saying so.
        cout << "Element already exists in the list." << endl;
    }
}

// Name: GetElement(int)
// Desc - Checks to see if the DoodleGod has an element
// Preconditions - DoodleGod already has elements
// Postconditions - Returns element at index
Element* DoodleGod::GetElement(int place) {
    if (place >= 0 && place <= m_numElements) {
        return m_myElements[place-1];
    } else {
        //if the index is out of range, print a message saying so.
        cout << "Out of range." << endl;
        return nullptr;
    }
}

// Name: AddAttempt
// Desc - Increments attempts
// Preconditions - DoodleGod attempts a merge
// Postconditions - Increments every time a merge is attempted
void DoodleGod::AddAttempt() {
    m_attempts++;
}

// Name: GetAttempts()
// Desc - Returns number of attempts for that DoodleGod
// Preconditions - DoodleGod exists
// Postconditions - Returns total number of attempts
int DoodleGod::GetAttempts() {
    return m_attempts;
}

// Name: AddRepeat()
// Desc - Increments repeats for every time an element has already been found
// Preconditions - DoodleGod attempts a merge
// Postconditions - Increments every time a merge yields an element already found
void DoodleGod::AddRepeat() {
    m_repeats++;
}

// Name: GetRepeats()
// Desc - Returns number of repeats for that DoodleGod
// Preconditions - DoodleGod exists
// Postconditions - Returns total number of repeats
int DoodleGod::GetRepeats() {
    return m_repeats;
}
