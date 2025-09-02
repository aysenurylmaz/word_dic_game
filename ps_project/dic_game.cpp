//****************************************************************************************
//**********       STUDENT NAME : AYÞENUR YILMAZ  ****************************************
//**********     STUDENT NUMBER : B231202019      ****************************************
//**********            -HONOR CODE-               ***************************************
//****************************************************************************************





#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For Turkish character


using namespace std;

struct Word {
    string english;
    string turkish;
};

// Define the maximum number of words in the dictionary
const int MAX_WORDS = 1000;

// Loads the dictionary from a file
int loadDictionary(const string& filename, Word dictionary[], int maxSize) {
    ifstream file(filename);
    string line;
    unsigned int count = 0;

    // Read each line from the file
    while (getline(file, line) && count < maxSize) {
        unsigned int delimiterPos = -1;
        for (unsigned int i = 0; i < line.length(); ++i) {
            if (line[i] == ':') { // If we find the ':' character
                delimiterPos = i; // Store its position
                break; // Stop cehcking further once we find it
            }
        }

        // If the ':' character was found
        if (delimiterPos != -1) {
            // Get the English word: everything before the ':' character
            string englishWord = "";
            for (unsigned int i = 0; i < delimiterPos; ++i) {
                englishWord += line[i]; // Build the English word
            }

            // Get the Turkish word: everything after the ':' character
            string turkishWord = "";
            for (unsigned int i = delimiterPos + 1; i < line.length(); ++i) {
                turkishWord += line[i]; // Build the Turkish word
            }

            // Add the word pair to the dictionary
            dictionary[count].english = englishWord;
            dictionary[count].turkish = turkishWord;
            count++;
        }
    }

    file.close();
    return count;
}

// Randomly shuffles an array
void shuffleArray(int array[], unsigned int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(array[i], array[j]);
    }
}

// Randomly generate options for either English-to-Turkish or Turkish-to-English translation questions
void generateOptions(const Word dictionary[], int count, int correctIndex, string options[], int& correctOption,bool isEnglishToTurkish) {
    int indices[4];
    indices[0] = correctIndex;
    unsigned int filled = 1;

   //Ensure no duplicate options
    while (filled < 4) {
        int randIndex = rand() % count;
        bool alreadyChosen = false;

        //Check if the index is already chosen
        for (unsigned int i = 0; i < filled; i++) {
            if (indices[i] == randIndex) {
                alreadyChosen = true;
                break;
            }
        }

        if (!alreadyChosen) {
            indices[filled] = randIndex;
            filled++;
        }
    }

    //Shuffle the indices to randomize the order of options
    shuffleArray(indices, 4);

    //Assign the options based on whether it's an English-to-Turkish or Turkish-to-English question
    for (unsigned int i = 0; i < 4; i++) {
        if (isEnglishToTurkish) {
            options[i] = dictionary[indices[i]].turkish;
        }
        else {
            options[i] = dictionary[indices[i]].english;
        }
        if (indices[i] == correctIndex) {
            correctOption = i + 1; // 1-based index for user choice
        }
    }
}

// Plays the word translation game
void playGame(const Word dictionary[], unsigned int count) {
    if (count == 0) {
        cout << "The dictionary is empty. Add some words first!" << endl;
        return;
    }

    srand(time(0));
    int score = 0; //Initialize score
    unsigned int wrongAnswers = 0;
    unsigned int questionCount = 0;

    int indices[MAX_WORDS];
    for (unsigned int i = 0; i < count; i++) {
        indices[i] = i;
    }

    //Shuffle the word indices to randomize the order of questions
    shuffleArray(indices, count);

    for (unsigned int i = 0; i < count; i++) {
        if (wrongAnswers >= 3 || questionCount >= 10) {
            break;
        }

        int currentIndex = indices[i]; //Current word index
        string options[4]; //Array to hold options
        int correctOption; //Correct option index
        bool isEnglishToTurkish = rand() % 2; //Randomly decide whether it's English to Turkish or Turkish to English

        //Generate the options for the question
        generateOptions(dictionary, count, currentIndex, options, correctOption, isEnglishToTurkish);

        // Display the question based on the selected language
        if (isEnglishToTurkish) {
            cout << "\nTranslate to Turkish: " << dictionary[currentIndex].english << endl;
        }
        else {
            cout << "\nTranslate to English: " << dictionary[currentIndex].turkish << endl;
        }
        
        //Display the possible answer options
        for (unsigned int j = 0; j < 4; j++) {
            cout << (j + 1) << ") " << options[j] << endl;
        }
        string input; // To hold user input
        unsigned int userChoice;

        while (true) { // Loop until valid input is received
            cout << "Your choice (or 5 to end the game): ";
            cin >> input;

            // Validate the input
            if (input.size() == 1 && isdigit(input[0])) { // Check if input is a single digit
                userChoice = input[0] - '0'; // Convert char to int
                if (userChoice >= 1 && userChoice <= 5) {
                    break; // Valid input; exit loop
                }
                else {
                    cout << "\nInvalid choice. Please enter a number between 1 and 5." << endl;
                }
            }
            else {
                cout << "\nInvalid input. Please enter a valid number." << endl;
            }
        }

        // Allow the user to end the game early
        if (userChoice == 5) {
            cout << "\nGame ended early!" << endl;
            break;
        }

        // Check if the user's answer is correct
        if (userChoice == correctOption) {
            cout << "\nCorrect!(+3p) " << endl;
            score += 3; //Increase score by 3

        }
        else {
            cout << "\nWrong!(-1p)  The correct answer is: " << options[correctOption - 1] << endl;
            score -= 1;//Decrease score by 1
            wrongAnswers++;

        }

        questionCount++;
    }

    cout << "\nGame over! Your score: " << score << " points out of " << questionCount * 3 <<" possible." << endl;

    // Game end menu
    int choice;
    string input;
    do {
        cout << "\nWhat would you like to do next?" << endl;
        cout << "1) Replay the Game" << endl;
        cout << "2) Previous Menu" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter your choice: ";
        cin >> input;

        // Validate the menu input
        if (input.size() == 1 && isdigit(input[0])) {
            choice = input[0] - '0'; // Convert char to int
            if (choice >= 1 && choice <= 3) {
                switch (choice) {
                case 1:
                    playGame(dictionary, count); // Replay the game
                    return;
                case 2:
                    return; // Return to the main menu
                case 3:
                    cout << "\nExiting the program. Goodbye!" << endl;
                    exit(0);
                }
            }
            else {
                cout << "\nInvalid choice. Please enter a number between 1 and 3." << endl;
            }
        }
        else {
            cout << "\nInvalid input. Please enter a valid number." << endl;
        }
    } while (true);

}

//Adds a new word to the dictionary
void addWord(const string& filename, Word dictionary[], unsigned int& count, unsigned int maxSize) {
    if (count >= maxSize) {
        cout << "Dictionary is full!" << endl;
        return;
    }

    string english, turkish;
    cout << "\nEnter the English word: ";
    cin.ignore(); //Clears the cin buffer
    getline(cin, english);

    cout << "Enter the Turkish translation: ";
    getline(cin, turkish);

    // Add the new word to the dictionary
    dictionary[count].english = english;
    dictionary[count].turkish = turkish;
    count++;

    // Bubble Sort: Sort the dictionary alphabetically by the English word
    for (unsigned int i = 0; i < count - 1; ++i) {
        for (unsigned int j = 0; j < count - i - 1; ++j) {
            if (dictionary[j].english > dictionary[j + 1].english) {
                // Swap the elements
                Word temp = dictionary[j];
                dictionary[j] = dictionary[j + 1];
                dictionary[j + 1] = temp;
            }
        }
    }


    // Save the updated dictionary to the file
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << english << ":" << turkish << endl;
        cout << "\nWord added successfully!\n" << endl;
    }
    else {
        cout << "Failed to open the dictionary file!" << endl;
    }
    file.close();
}

//Lists all words in the dictionary
void listWords(const Word dictionary[], unsigned int count) {
    if (count == 0) {
        cout << "No words in the dictionary!" << endl;
        return;
    }

    cout << "\nWord List:" << endl;
    for (unsigned int i = 0; i < count; ++i) {
        cout << dictionary[i].english << " - " << dictionary[i].turkish << endl;
    }
}

//Main function
int main() {
    SetConsoleOutputCP(CP_UTF8);  //For Turkish character support
    SetConsoleCP(CP_UTF8);   // For Turkish character support

    cout << "+--------------------------+" << endl;
    cout << "|                          |" << endl;
    cout << "|  WELCOME!                |" << endl;
    cout << "|  The Game is Starting... |" << endl;
    cout << "|                          |" << endl;
    cout << "+--------------------------+" << endl;
   
    const string filename = "dictionary.txt";
    Word dictionary[MAX_WORDS];

    unsigned int wordCount = loadDictionary(filename, dictionary, MAX_WORDS);

    int choice;
    string input;
   
    while (true) {
        // Display the menu
        cout << "\nWord Dictionary Game" << endl;
        cout << " 1) Start Playing" << endl;
        cout << " 2) List Words" << endl;
        cout << " 3) Add New Word" << endl;
        cout << " 4) Exit" << endl;
        cout << "Select an option: ";
        cin >> input;

        // Check if the input is valid and within range
        if (input.size() == 1 && isdigit(input[0])) {
            choice = input[0] - '0'; // Convert the character to an integer



            // Process valid choices
            if (choice >= 1 && choice <= 4) {
                switch (choice) {
                case 1:
                    playGame(dictionary, wordCount);//Start the game
                    break;
                case 2:
                    listWords(dictionary, wordCount);//List words
                    break;
                case 3:
                    addWord(filename, dictionary, wordCount, MAX_WORDS);//Add a new word
                    break;
                case 4:
                    cout << "\nExiting the game. Goodbye!" << endl;
                    return 0; // Exit the program
                }
            }
            else {
                cout << "\nInvalid option. Please enter a number between 1 and 4." << endl;
            }
        }
        else {
            cout << "\nInvalid input. Please enter a number between 1 and 4." << endl;
        }
    }
    return 0;
}
