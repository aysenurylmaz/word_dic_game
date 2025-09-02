# Word Dictionary Game

A C++ console-based word translation game that helps users learn English and Turkish words through an interactive quiz.

## 📖 Description

This program is a vocabulary learning tool that quizzes users on word translations between English and Turkish. It loads words from a dictionary file, allows users to add new words, and provides a multiple-choice quiz format to test translation skills.

## ✨ Features

- **Interactive Quiz**: Multiple-choice questions for English-to-Turkish and Turkish-to-English translations
- **Scoring System**: +3 points for correct answers, -1 point for incorrect answers
- **Word Management**: Add new words to the dictionary and view all words
- **Turkish Character Support**: Proper handling of Turkish characters
- **Game Menu**: Options to replay, return to main menu, or exit

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (Visual Studio recommended)
- Windows OS (for Turkish character support)

### Installation

1. Clone the repository or download the source code
2. Create a `dictionary.txt` file with word pairs in the format: `english:turkish`
3. Compile the program using your C++ compiler

### Usage

1. Run the executable
2. Use the menu to:
   - Start playing the translation game
   - List all words in the dictionary
   - Add new words to the dictionary
   - Exit the program

## 🎮 How to Play

1. Select option 1 from the main menu to start the game
2. You'll be presented with words to translate either from English to Turkish or Turkish to English
3. Choose the correct translation from the multiple-choice options (1-4)
4. Enter 5 to end the game early
5. After the game ends, choose to replay, return to the main menu, or exit

## 📁 File Format

The dictionary file (`dictionary.txt`) should contain word pairs in the format:

english_word1:turkish_translation1
english_word2:turkish_translation2


## 🛠️ Technical Details

- Built with C++
- Uses file I/O for dictionary persistence
- Implements bubble sort for alphabetizing words
- Includes input validation for user choices
- Supports Turkish characters through Windows.h functions

## 👥 Contributing

1. Fork the project
2. Create a feature branch: `git checkout -b new-feature`
3. Commit changes: `git commit -am 'Add new feature'`
4. Push to branch: `git push origin new-feature`
5. Submit a pull request

## 📜 License

This project is available for educational purposes.

## 👤 Author

**Ayşenur Yılmaz**  
Student Number: B231202019

---

*Note: This program requires a dictionary.txt file with word pairs to function properly.*
