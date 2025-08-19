#include "Game.h"
#include <string>
#include <iostream>

using namespace std;


//Default Constructor
Game::Game() {}

// Name: LoadRecipes
// Desc - A recipe is what elements are required to merge in order to create a new element
//        For example, if you merge Fire and Earth, you get Lava.
//        Loads each recipe from provided file (Must use getline)
// Preconditions - Requires file with valid element/recipe data
// Postconditions - m_elements is populated with valid recipe data
void Game::LoadRecipes() {
    ifstream inputstream;
    inputstream.open(PROJ2_RECIPES);

    string elementName, elementReq1, elementReq2;
    string line;
    
    int i = 0;
    //Use multiple getlines with delimiters to extract information.
    while (getline(inputstream, elementName, ',') && getline(inputstream, elementReq1, ',') && getline(inputstream, elementReq2, '\n')) {
        if (elementReq1 != "") {
            //Create Element object with extracted information.
            Element anElement(elementName, elementReq1, elementReq2);
            //Add the element to m_elements array which holds all elements to discover.
            m_elements[i] = anElement;
            i++;  
        }       
    }
    inputstream.close();
    cout << "139 elements loaded." << endl;
}

// Name: StartGame()
// Desc: 1. Loads all recipes into m_elements (by making elements)
//       2. Asks user for their DoodleGod's name
//          (store in m_myDoodleGod as m_myName)
//       3. Adds Fire, Water, Air, and Earth to Doodle God's known element list
//          (in m_myDoodleGod)
//       4. Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - None
// Postconditions - Continually checks to see if player has quit
void Game::StartGame() {
    GameTitle();
    LoadRecipes();
    string doodleGodName;
    cout << "What is the name of the Doodle God?" << endl;
    getline(cin, doodleGodName);
    m_myDoodleGod.SetName(doodleGodName);
    //Create starter elements
    Element Fire("Fire", "", "");
    Element Air("Air", "", "");
    Element Water("Water", "", "");
    Element Earth("Earth", "", "");
    //Add starter elements to Doodle God's collection
    m_myDoodleGod.AddElement(&Air);
    m_myDoodleGod.AddElement(&Earth);
    m_myDoodleGod.AddElement(&Fire);
    m_myDoodleGod.AddElement(&Water);
    //Initiate menu
    int userMenuChoice = 0;
    while (userMenuChoice != 4) {
        userMenuChoice = MainMenu();
        if (userMenuChoice == 1) {
            DisplayElements();
        } else if (userMenuChoice == 2) {
            CombineElements();
        } else if (userMenuChoice == 3) {
            CalcScore();
            //Validate input
        } else if (userMenuChoice != 4) {
            cout << "Invalid choice. Please try again!" << endl;
        }
    }
    //End message
    cout << "Thanks for playing the Doodle God!" << endl;
}

// Name: DisplayMyElements()
// Desc - Displays the current elements
// Preconditions - Player has elements
// Postconditions - Displays a numbered list of elements
void Game::DisplayElements() {
    m_myDoodleGod.DisplayElements();
}
// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Player has an DoodleGod
// Postconditions - Returns number including exit
int Game::MainMenu() {
    int menuChoice;
    //Display menu choices
    cout << "\nWhat would you like to do?" << endl;
    cout << "1. Display the Doodle God's Elements" << endl;
    cout << "2. Attempt to Combine Elements" << endl;
    cout << "3. See Score" << endl;
    cout << "4. Quit" << endl;
    //Get input
    cin >> menuChoice;
    //Validate input
    while (menuChoice < 1|| menuChoice > 4) {
        cout << "Invalid choice please try again." << endl;
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Display the Doodle God's Elements" << endl;
        cout << "2. Attempt to Combine Elements" << endl;
        cout << "3. See Score" << endl;
        cout << "4. Quit" << endl;
        cin >> menuChoice;
    }
    return menuChoice;
}
// Name: CombineElements()
// Desc - Attempts to combine known elements
// Preconditions - DoodleGod is populated with elements
// Postconditions - May add element to DoodleGod's list of elements
void Game::CombineElements() {
    m_myDoodleGod.AddAttempt();
    int userElement1 = 0, userElement2 = 0;
    //Get 2 elements from the user.
    RequestElement(userElement1);
    RequestElement(userElement2);
    //Associate the index of the element to the element name using GetElement.
    Element* element1 = m_myDoodleGod.GetElement(userElement1);
    Element* element2 = m_myDoodleGod.GetElement(userElement2);
    //Validate the recipe
    int recipeFound = SearchRecipes(element1->m_name, element2->m_name);
    //if the recipe is valid...
    if (recipeFound != -1) {
        //Check if the element already exists in Doodle God's collection
        bool elementExists = m_myDoodleGod.CheckElement(m_elements[recipeFound]);
        //If the element already exists, let the Doodle God know.
        if (elementExists == true) {
            cout << '\n' <<  element1->m_name << " combined with " << element2->m_name << " makes Dust!";
            cout << " But you already know " << m_elements[recipeFound].m_name << "!" << endl;
            m_myDoodleGod.AddRepeat();
            return;
            //If it's a newly discovered element, add it to Doodle God's collection and print message.
        } else {
            m_myDoodleGod.AddElement(&m_elements[recipeFound]);
            cout << element1->m_name << " combined with " << element2->m_name << " to make " << m_elements[recipeFound].m_name << "!" << endl;
            cout << "The Doodle God now knows " << m_elements[recipeFound].m_name << "." << endl;
        }
        //If the recipe doesn't exist, print a appropriate message.
    } else {
        cout << "Nothing happened when you tried to combine " << element1->m_name << " and " << element2->m_name << endl;
    }
}
// Name: RequestElement()
// Desc - Asks user to chose an element to try and merge.
//        Checks to make sure value in range
// Preconditions - DoodleGod has elements to try and merge
// Postconditions - Updates choice (pass by reference)
void Game::RequestElement(int &choice) {
    int elementNum = 0;
    int allElements = m_myDoodleGod.GetNumElements();
    cout << "Which element would you like to merge?" << endl;
    cout << "To list known elements, enter -1" << endl;
    cin >> elementNum;
    //Display the list of discovered elements by Doodle God
    if (elementNum == -1) {
        m_myDoodleGod.DisplayElements();
    }
    //Validate element
    while ((elementNum <= 0 || elementNum > allElements) || elementNum == -1) {
        cout << "Which element would you like to merge?" << endl;
        cout << "To list known elements, enter -1" << endl;
        cin >> elementNum;
        //Display the list of discovered elements by Doodle God
        if (elementNum == -1) {
            m_myDoodleGod.DisplayElements();
        }
    }
    //Directly modify 'choice' to the element index.
    choice = elementNum;
}
// Name: SearchRecipes()
// Desc - Searches recipes for two strings passed
// Preconditions - m_elements is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string element1, string element2) {
    for (int i = 0; i < PROJ2_SIZE; i++) {
        //Validate recipe both ways. The recipe can be "Fire" and "Earth" or "Earth" and "Fire" which is the same.
        if (m_elements[i].m_element1 == element1 && m_elements[i].m_element2 == element2) {
            return i;
        } else if (m_elements[i].m_element2 == element1 && m_elements[i].m_element1 == element2) {
            return i;
        }
    }
    //If no recipe is found, return -1 to indicate so.
    return -1;
}

// Name: CalcScore()
// Desc - Displays current score for Doodle God
// Preconditions - Doodle God is populated with elements
// Postconditions - None
void Game::CalcScore() {
    //Display name, attempts, repeats, total elements found and total completion.
    cout << "***The Doodle God***" << endl;
    cout << "The Great Doodle God " << m_myDoodleGod.GetName() << endl;
    cout << "The Doodle God has tried to combine " << m_myDoodleGod.GetAttempts() << " elements." << endl;
    cout << "The Doodle God has repeated attempts " << m_myDoodleGod.GetRepeats() << " times." << endl;
    cout << "The Doodle God found " << m_myDoodleGod.GetNumElements() << " out of " << PROJ2_SIZE << " elements." << endl;
    cout.precision(2);
    double completion = (double(m_myDoodleGod.GetNumElements())/PROJ2_SIZE)*100;
    cout << fixed << "You have completed " << completion << "% of the elements." << endl; 
}
