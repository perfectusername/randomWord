#include "randomWord.h"

// Reference materials for pointer functions
// https://www.learncpp.com/cpp-tutorial/function-pointers/
// https://stackoverflow.com/questions/2898316/using-a-member-function-pointer-within-a-class
// https://stackoverflow.com/questions/28050325/illegal-operation-on-bound-member-function-expression

using namespace std;

RandomWord::RandomWord()
{
	_wordLength = 0;
	_lettersAdded = 0;
	_randomWord = nullptr;

	srand(time(NULL));
	initialize();
}

RandomWord::~RandomWord()
{
	deleteWord();
	deleteDonorList();
}



// Calls the functions to build the random word
// Returns 0 for failure, 1 for success
int RandomWord::initialize()
{
	int	successValue = 0;
	int	i;


	successValue = deleteWord();

	if (successValue != 0)
	{
		// Find the size of the incoming list and allocate _donorWordList's array to that size
		_listSize = allocateDonorList();

		// If the incoming list contains entries
		if (_listSize != 0)
		{
			// Then load the data into the previously allocated _donorWordList
			loadDB();

			// Generate a word length
			_wordLength = generateRandomNumber(SMALLEST_WORD, LARGEST_WORD);
			// Then allocate space for a new word of that length
			_randomWord = new char[_wordLength + 1];

			// Initialize the word to 0's
			for (i = 0; i < _wordLength; ++i)
			{
				_randomWord[i] = '0';
			}
			// Set the last spot to null
			_randomWord[_wordLength] = '\0';

			// Figure out the size of 1/3 of the word
			if (_wordLength >= 3)
			{
				_oneThird = _wordLength / 3;
			}

			// Now fill the empty spaces with letters
			successValue = generateLetters();
		}
		// Otherwise the file was opened, but had no entries
		else
		{
			cout << "Error! " << _fileName << "is empty!" << endl;
			successValue = -1;
		}
	}

	return successValue;
}

// Deallocates the dynamic memory in _randomWord
// returns 0 for failure, 1 for success
int RandomWord::deleteWord()
{
	int successValue = 0;


	// Deallocate memory if memory is not null
	if (_randomWord != nullptr)
	{
		delete[] _randomWord;
		_randomWord = nullptr;
	}

	// If null at this point return successful
	if (_randomWord == nullptr)
	{
		successValue = 1;
	}

	return successValue;
}

// Deallocates the dynamic memory in _donorWordList
// returns 0 for failure, 1 for success
int RandomWord::deleteDonorList()
{
	int successValue = 0;
	int i;


	if (_donorWordList != nullptr)
	{
		for (i = 0; i < _listSize; ++i)
		{
			delete[] _donorWordList[i];
			_donorWordList[i] = nullptr;
		}

		delete[] _donorWordList;
		successValue = 1;
	}

	return successValue;
}



// Scan the incoming .txt file for the number of entries and allocates _donorWordList with that number of elements
// Returns the size of the _donorWordList
int RandomWord::allocateDonorList()
{
	int		i;
	int		listSize = 0;
	ifstream	in;
	char            bufferWord[MAX_CHAR];


	// Open the file
	in.open(_fileName);
	if (!in)
	{
		cerr << "Cannot read from " << _fileName << endl;
		exit(1);
	}

	// First figure out how large the database needs to be
	while (!in.eof())
	{
		in.get(bufferWord, MAX_CHAR, '\n');
		in.get();

		++listSize;
	}
	in.close();

	// Then create the database at the correct size
	_donorWordList = new char* [listSize];

	// Initialize all array elements to nullptr
	for (i = 0; i < listSize; ++i)
	{
		_donorWordList[i] = nullptr;
	}

	return listSize;
}

// Loads the entries from the incoming .txt file into the previously allocated _donorWordList
// Returns 0 if the file can't open, -1 if the file is empty, and 1 for success
int RandomWord::loadDB()
{
	int		successValue = 0;	// Success or failure value
	ifstream	in;			// Name of the incoming file stream
	int             i = 0;			// Index for the _donorWordList
	char            bufferWord[MAX_CHAR];	// Buffer for next word to add to _donorWordList
	int             bufferWordLength;	// Length of the current buffer word
	char*		wordToAdd;		// Pointer to the new word to add to _donorWordList
	

	// Open the file
	in.open(_fileName);
	if (!in)
	{
		cerr << "Cannot read from " << _fileName << endl;
		exit(1);
	}
	else
	{
		successValue = 1;
	}

	// Now fill up the array
	while (!in.eof())
	{
		// Copies the information from the file into a word buffer
		in.get(bufferWord, MAX_CHAR, '\n');
		// gets rid of the newline
		in.get();

		// Get the length of the word in the buffer;
		bufferWordLength = strlen(bufferWord);


		// Create a cstring dynamically that is the right length for the new word
		wordToAdd = new char[bufferWordLength + 1];



		// Copy the buffer into the newly-created cstring
		strcpy_s(wordToAdd, (bufferWordLength + 1), bufferWord);

		// Add the newWord to the array
		_donorWordList[i] = wordToAdd;

		i++;
	}
	in.close();

	return successValue;
}



// Returns a random number between the bounds (inclusive)
int RandomWord::generateRandomNumber(const int& lowerBound, const int& upperBound) const
{
	int	randomNumber;
	int	range = (upperBound - lowerBound);

	// An amount to add onto the lower range
	randomNumber = rand() % (range + 1);

	// Now add the lower range to get the length of the word
	randomNumber += lowerBound;

	return randomNumber;
}

// Returns a random lowercase letter
char RandomWord::generateRandomLetter()
{
	return generateRandomNumber(97, 122);
}

// Returns a random lowercase vowel
char RandomWord::generateRandomVowel()
{
	int	vowelNumber = generateRandomNumber(1, 5);
	char	returnChar;

	switch (vowelNumber) {
	case 1:
		returnChar = 'a';
		break;
	case 2:
		returnChar = 'e';
		break;
	case 3:
		returnChar = 'i';
		break;
	case 4:
		returnChar = 'o';
		break;
	case 5:
		returnChar = 'u';
		break;
	default:
		returnChar = 1;
	}

	return returnChar;
}



// Calls fillSection() with appropriate arguments
// Returns 0 for failure, 1 for success
int RandomWord::generateLetters()
{
	int successValue = 0;
	int lettersGenerated = 0;

	// Special case: Only 2 letters
	if (_oneThird == 0)
	{
		lettersGenerated = generateTwoLetterWord();
		if (lettersGenerated == 2)
		{
			successValue = 1;
		}
	}
	else
	{
		int test;

		// Add the first letter randomly
		if (_lettersAdded == 0)
		{
			_randomWord[_lettersAdded] = generateRandomLetter();
			successValue = 1;
			++_lettersAdded;
		}
		
		// Function pointer reference material
		// https://www.learncpp.com/cpp-tutorial/function-pointers/
		// https://stackoverflow.com/questions/2898316/using-a-member-function-pointer-within-a-class
		// https://stackoverflow.com/questions/28050325/illegal-operation-on-bound-member-function-expression
		
		// Don't run the first section if your word is 5 or less because it will already
		// have been added because the first 1/3 rounded down is only 1 letter
		if (_wordLength > 5)
		{
			successValue = (this->fillSection)(&RandomWord::firstThird, &RandomWord::firstDonor);
		}
		if (successValue != 0)
		{
			successValue = (this->fillSection)(&RandomWord::middleThird, &RandomWord::middleDonor);
			if (successValue != 0)
			{
				(this->fillSection)(&RandomWord::lastThird, &RandomWord::lastDonor);
			}
		}
	}
	
	return successValue;
}

// Generates a random two-letter word containing 1 lowercase vowel and 1 lowercase consonant in random order
// Returns 0 for failure, 1 for success
int RandomWord::generateTwoLetterWord()
{
	int	successValue = 0;
	int	lettersGenerated = 0;
	char	charBuffer;

	// Generate a random first letter
	charBuffer = generateRandomLetter();
	_randomWord[0] = charBuffer;
	++lettersGenerated;

	// If the first generated letter was a vowel, do not generate another vowel
	if ((charBuffer == 'a') || (charBuffer == 'e') || (charBuffer == 'i') || (charBuffer == 'o') || (charBuffer == 'u'))
	{
		// Generate a random letter
		charBuffer = generateRandomLetter();

		// If that letter is a vowel, keep generating letters until a non-vowel is generated
		while ((charBuffer == 'a') || (charBuffer == 'e') || (charBuffer == 'i') || (charBuffer == 'o') || (charBuffer == 'u'))
		{
			charBuffer = generateRandomLetter();
		}
		_randomWord[1] = charBuffer;

		++lettersGenerated;
		successValue = 1;
	}
	// Otherwise, generate a random vowel to follow the first letter
	else
	{
		charBuffer = generateRandomVowel();
		_randomWord[1] = charBuffer;

		++lettersGenerated;
		successValue = 1;
	}

	return lettersGenerated;
}

// Fills letters into _randomWord based on the given functions which will provide the needed index bounds
// Returns 0 for failure, 1 for success
int RandomWord::fillSection(void (RandomWord::* boundaryFunction)(int& upperBoundary), void (RandomWord::* donorBoundary)(int& donorLength, int& donorLower, int& donorUpper))
{
	int	successValue = 0;	// Success or failure of function
	int	numberOfTries = 0;	// Number of times the function has picked a random word from the _donorWordList database and failed to find a match
	int	lastLetterIndex;	// Index of the last letter added to _randomWord
	int	nextLetterIndex;	// Index of the next letter that will be added to _randomWord
	int	donorWordIndex;		// Index of the current donorWord in the _donorWordList database
	int	i;			// Index of the current position within the donorWord

	int	_upperBoundary;		// The index position of _randomWord which this function will stop before reaching
	int	_donorLength;		// The length of the current donor word
	int	_donorLower;		// Index of the lower bound of the donor word
	int	_donorUpper;		// Index of the upper bound of the donor word


	// Set the value of _upperBoundary
	(this->*boundaryFunction)(_upperBoundary);

	// Here we generate the letters in the needed range of _randomWord
	while (_lettersAdded < _upperBoundary)
	{
		// Index of the last letter added to _randomWord
		lastLetterIndex = _lettersAdded - 1;
		nextLetterIndex = _lettersAdded;

		// Get a random Index from our database which will be our donor word
		donorWordIndex = generateRandomNumber(0, (_listSize - 1));
		_donorLength = strlen(_donorWordList[donorWordIndex]);

		(this->*donorBoundary)(_donorLength, _donorLower, _donorUpper);

		// i is the position within the donor word
		i = _donorLower;
		// While we are within the correct range for this portion of our word
		// AND we haven't already found a match to pull the next letter from
		while ((i < _donorUpper) && (_lettersAdded == nextLetterIndex))
		{
			// If the current i position isn't the last in the donor word
			// AND the letter at the index matches the letter that was last added
			if ((i < strlen(_donorWordList[donorWordIndex])) &&
				(tolower(_donorWordList[donorWordIndex][i]) == tolower(_randomWord[lastLetterIndex])))
			{
				// Only add the letter if it's an alpha letter
				if (checkChar(_donorWordList[donorWordIndex][i + 1]))
				{
					// Then add the next letter in the donor word to the current word.
					_randomWord[nextLetterIndex] = _donorWordList[donorWordIndex][i + 1];
					++_lettersAdded;

					successValue = 1;
				}
			}
			++i;
		}
		++numberOfTries;

		// Stop trying if you haven't found a match in a large number of tries (equal to _listSize)
		// then just fill in the next space with a vowel
		if (numberOfTries >= _listSize)
		{
			_randomWord[nextLetterIndex] = generateRandomVowel();
			++_lettersAdded;

			successValue = 1;
		}
	}

	return successValue;
}

// Check if argument character is an alpha
// Returns true if it is an alpha, or false if it is anything else
bool RandomWord::checkChar(char& aChar)
{
	bool returnValue = false;

	if ((tolower(aChar) >= 97) && (tolower(aChar) <= 122))
	{
		returnValue = true;
	}

	return returnValue;
}

// Gives index bounds for the first 1/3 of _randomWord (rounded down)
void RandomWord::firstThird(int& upperBound)
{
	upperBound = _oneThird;
}

// Gives index bounds for the middle 1/3 of _randomWord
void RandomWord::middleThird(int& upperBound)
{
	upperBound = _wordLength - _oneThird;
}

// Gives index bounds for the last 1/3 of _randomWord (rounded down)
void RandomWord::lastThird(int& upperBound)
{
	upperBound = _wordLength;
}

// Gives index bounds for the first 1/3 of a donorIndex (rounded down)
void RandomWord::firstDonor(int& donorWordLength , int& donorLower, int& donorUpper)
{
	donorLower = 0;
	donorUpper = donorWordLength / 3;
}

// Gives index bounds for the middle 1/3 of a donor word
void RandomWord::middleDonor(int& donorWordLength, int& donorLower, int& donorUpper)
{
	int donorThird = donorWordLength / 3;

	donorLower = donorThird;
	donorUpper = donorWordLength - donorThird;
}

// Gives index bounds for the last 1/3 of a donor word (rounded down)
void RandomWord::lastDonor(int& donorWordLength, int& donorLower, int& donorUpper)
{
	donorLower = donorWordLength - (donorWordLength / 3);
	donorUpper = donorWordLength;
}



// Displays the random word
int RandomWord::display() const
{
	int successValue = 0;

	if (_randomWord != nullptr)
	{
		cout << _randomWord;
		successValue = 1;
	}

	return successValue;
}