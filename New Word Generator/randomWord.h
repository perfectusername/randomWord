#include "utilities.h"


// WORD SIZE SETTINGS
// Range of word sizes that can be randomly generated
const int SMALLEST_WORD = 2;	// Smallest possible word generated (do not set below 2)
const int LARGEST_WORD = 12;	// Largest possible word generated (do not set above 255)


class RandomWord
{
public:
	// Constructor
	// All word generation occurs in the constructor
	RandomWord();
	//
	// Destructor
	~RandomWord();

	// Displays the random word
	int display() const;

private:
	int		_wordLength;			// Length of the random word
	int		_oneThird;			// 1/3 of the length of the random word (rounded down)
	int		_lettersAdded;			// Number of letters that have been generated in the random word
	char*		_randomWord;			// The pointer to the locaiton of the random word
	const string    _fileName = "words.txt";	// The file name of the .txt file containing the database of donor words for the _donorWordList
	int		_listSize;			// The number of lines in the incoming .txt file and size of the _donorWordList
	char**		_donorWordList;			// The pointer to the location of the database list of donor words pulled from the .txt file



	// CONSTRUCTOR & DESTRUCTOR SUPPORT
	//
	// Calls the functions to build the random word
	// returns 0 for failure, 1 for success
	int initialize();
	//
	// Deallocates the dynamic memory in _randomWord
	// returns 0 for failure, 1 for success
	int deleteWord();
	//
	// Deallocates the dynamic memory in _donorWordList
	// returns 0 for failure, 1 for success
	int deleteDonorList();



	// LOAD THE DATABASE
	//
	// Scan the incoming .txt file for the number of entries and allocates _donorWordList with that number of elements
	// Returns the size of the _donorWordList
	int allocateDonorList();
	//
	// Loads the entries from the incoming .txt file into the previously allocated _donorWordList
	// Returns 0 if the file can't open, -1 if the file is empty, and 1 for success
	int loadDB();



	// RANDOM CHARACTER RETURNS
	//
	// Returns a random number between the bounds (inclusive)
	int generateRandomNumber(const int& lowerBound, const int& upperBound) const;
	//
	// Returns a random lowercase letter
	char generateRandomLetter();
	//
	// Returns a random lowercase vowel
	char generateRandomVowel();



	// WORD GENERATION
	//
	// Calls fillSection() with appropriate arguments
	// Returns 0 for failure, 1 for success
	int generateLetters();
	//
	// Generates a random two-letter word containing 1 lowercase vowel and 1 lowercase consonant in random order
	// Returns 0 for failure, 1 for success
	int generateTwoLetterWord();
	//
	// Fills letters into _randomWord based on the given functions which will provide the needed index bounds
	// Returns 0 for failure, 1 for success
	int fillSection(void (RandomWord::*boundaryFunction)(int& upperBoundary), void (RandomWord::*donorBoundary)(int& donorLength, int& donorLower, int& donorUpper));
	//
	// Check if argument character is an alpha
	// Returns true if it is an alpha, or false if it is anything else
	bool checkChar(char& aChar);
	//
	//
	// Gives index bounds for the first 1/3 of _randomWord (rounded down)
	void firstThird(int& upperBound);
	//
	// Gives index bounds for the middle 1/3 of _randomWord
	void middleThird(int& upperBound);
	//
	// Gives index bounds for the last 1/3 of _randomWord (rounded down)
	void lastThird(int& upperBound);
	//
	//
	// Gives index bounds for the first 1/3 of a donorIndex (rounded down)
	void firstDonor(int& donorWordLength, int& donorLower, int& donorUpper);
	//
	// Gives index bounds for the middle 1/3 of a donor word
	void middleDonor(int& donorWordLength, int& donorLower, int& donorUpper);
	//
	// Gives index bounds for the last 1/3 of a donor word (rounded down)
	void lastDonor(int& donorWordLength, int& donorLower, int& donorUpper);
};