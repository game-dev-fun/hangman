#include<iostream>
#include<cctype>


void gameInit();
char* getUserPhrase();
char* createSecretPhrase(char* phrase);
char getUserGuess();
bool checkGuess(char* secretPhrase, char* phrase, char guess, bool& winner);
bool replay();
void printHangman(int tries);
int main()
{
	do
	{
		gameInit();
	} while (replay());
	return 0;
}

void printHangman(int tries)
{
	std::cout << " +---+\n"
		<< " |   |\n"
		<< " |   " << ((tries > 0) ? "o\n" : "\n")
		<< " |  " << ((tries > 1) ? "/" : "") << ((tries > 2) ? "|" : "") << ((tries > 3) ? "\\\n" : "\n")
		<< " |  " << ((tries > 4) ? "/ " : " ") << ((tries > 5) ? "\\\n" : "\n")
		<< "-+-\n";
}

bool replay()
{
	bool cinFail{};
	bool yOrN{ false };
	char userInput{};
	constexpr int MAX_CHARS{ 256 };
	do
	{
		std::cout << "Do you want to replay? (y/n): ";
		std::cin >> userInput;

		cinFail = std::cin.fail();
		if (cinFail)
		{
			std::cin.clear();
			std::cin.ignore(MAX_CHARS);
			std::cout << "Please enter y or n.\n";
		}
		else
		{
			if (userInput == 'y' || userInput == 'n')
			{
				yOrN = true;
			}
			else
			{
				std::cout << "Please enter y or n.\n";
				yOrN = false;
			}
		}

	} while (cinFail || !yOrN);
	return userInput == 'y';
}

void gameInit()
{

	char* userPhrase{ getUserPhrase() };
	system("cls");
	char* secretPhrase{ createSecretPhrase(userPhrase) };
	constexpr int TOTAL_TRIES{ 5 };
	int tries{ 5 };
	char userGuess{};
	bool winner{ false };
	bool guess{ false };
	while (tries >= 0 && !winner)
	{
		std::cout << "Secret Phrase: " << secretPhrase << '\n';
		printHangman(TOTAL_TRIES - tries);
		userGuess = getUserGuess();
		guess = checkGuess(secretPhrase, userPhrase, userGuess, winner);
		if(!guess)
		{
			--tries;
		}
		//std::cout << "Tries: " << tries << '\n';
	}
	if (!winner)
	{
		printHangman(TOTAL_TRIES - tries);
		std::cout << "Game over. Secret phrase: " << userPhrase << '\n';
	}
	else
	{
		std::cout << "You guessed the secret phrase!\n";
	}

	delete[] userPhrase;
	userPhrase = nullptr;
	delete[] secretPhrase;
	secretPhrase = nullptr;
}

char getUserGuess()
{
	constexpr int MAX_CHARS{ 256 };
	char userInput;
	bool cinFail{ false };
	bool onlyAlphabet{ true };
	do
	{
		onlyAlphabet = true;
		std::cout << "Enter a guess(character): ";
		std::cin >> userInput;
		cinFail = std::cin.fail();
		if (cinFail)
		{
			std::cin.clear();
			std::cin.ignore(MAX_CHARS);
			std::cout << "Please enter only characters.\n";
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(MAX_CHARS, '\n');
			if (!std::isalpha(userInput))
			{
				onlyAlphabet = false;
				std::cout << "Please enter alphabets only.\n";
			}
		}
	} while (cinFail || !onlyAlphabet);
	return std::tolower(userInput);
}

char* getUserPhrase()
{
	constexpr int MAX_CHARS{ 256 };
	char* userInput{ new char[MAX_CHARS] };
	bool cinFail{ false };
	bool onlyAlphabet{ true };
	do
	{
		onlyAlphabet = true;
		std::cout << "Please enter the secret phrase: ";
		std::cin >> std::ws;
		std::cin.getline(userInput, MAX_CHARS);
		cinFail = std::cin.fail();
		if (cinFail)
		{
			std::cin.clear();
			std::cin.ignore(MAX_CHARS);
			std::cout << "Please enter only characters.\n";
		}
		else
		{
			char c{};
			for (int i{ 0 }; i < std::strlen(userInput); ++i)
			{
				c = userInput[i];
				c = std::tolower(c);
				if (!std::isalpha(c) && c != ' ')
				{

					onlyAlphabet = false;
					std::cout << "Please enter only alphabets.\n";
					break;
				}
				userInput[i] = c;
			}

		}
	} while (cinFail || !onlyAlphabet);
	return userInput;
}


char* createSecretPhrase(char* phrase)
{
	const int length{ static_cast<int>(std::strlen(phrase)) };
	char* secretPhrase{ new char[length + 1] };
	for (int i{ 0 }; i < length; ++i)
	{
		if (phrase[i] == ' ')
		{
			secretPhrase[i] = ' ';
		}
		else
		{
			secretPhrase[i] = '_';
		}
	}
	secretPhrase[length] = '\0';
	return secretPhrase;
}



bool checkGuess(char* secretPhrase, char* phrase, char guess, bool& winner)
{
	winner = true;
	bool guessed{ false };
	for (int i{0}; i < std::strlen(phrase); ++i)
	{
		if (phrase[i] == guess)
		{
			guessed = true;
			secretPhrase[i] = guess;
		}
		if (phrase[i] != secretPhrase[i])
		{
			winner = false;
		}
	}
	return guessed;
}
