#include <iostream>
#include <string.h>

using namespace std;

#define ROW_SIZE 15
#define COLUMN_SIZE 15
#define WORDS_SIZE 16

char puzzle[ROW_SIZE][COLUMN_SIZE] = {
    {'a', 'x', 'd', 'u', 'r', 'y', 'h', 'p', 's', 'p', 't', 't', 'i', 'd', 't'},
    {'v', 'n', 'x', 's', 'e', 'c', 'a', 'q', 'c', 'u', 'i', 'u', 'o', 'z', 'p'},
    {'m', 'e', 'r', 'g', 'f', 'w', 'o', 'z', 'i', 's', 'n', 'l', 'k', 'a', 'c'},
    {'v', 's', 'c', 'x', 's', 'e', 's', 'x', 'o', 'f', 'l', 'w', 'z', 'j', 'z'},
    {'v', 't', 'r', 'p', 'n', 'd', 'l', 'p', 'b', 'a', 'c', 'h', 'e', 'b', 'y'},
    {'p', 'r', 'e', 'k', 'a', 'w', 'e', 'c', 'r', 'c', 't', 'x', 'n', 's', 'b'},
    {'f', 'p', 'd', 'm', 'r', 'd', 'l', 'o', 's', 'p', 'e', 'j', 'a', 'q', 't'},
    {'w', 'h', 'i', 'n', 't', 'l', 'y', 'i', 'b', 't', 'c', 'a', 's', 'h', 'n'},
    {'l', 'a', 't', 'c', 'i', 'q', 'n', 'n', 'r', 'i', 'l', 'h', 't', 'y', 'j'},
    {'k', 'r', 'r', 'x', 'o', 'i', 'f', 'k', 'y', 'b', 'w', 'o', 'e', 'w', 'a'},
    {'v', 'c', 'p', 'd', 'u', 'y', 'z', 'k', 'l', 'e', 't', 'n', 'a', 'k', 'w'},
    {'i', 'u', 'e', 'o', 'h', 'k', 'n', 'a', 'b', 'd', 'o', 't', 'a', 'n', 'a'},
    {'f', 'a', 'q', 'h', 'y', 't', 'j', 'b', 'i', 'm', 'y', 'm', 'u', 'd', 's'},
    {'v', 'q', 'z', 'f', 'c', 'j', 'i', 'e', 'e', 'm', 'n', 'k', 'u', 'x', 'l'},
    {'b', 'a', 'l', 'a', 'n', 'c', 'e', 'w', 'e', 'c', 'n', 'u', 'o', 'p', 'b'}};

char *locations[WORDS_SIZE];

const char *words[WORDS_SIZE] = {
    "balance",
    "bank",
    "cash",
    "check",
    "coin",
    "credit",
    "debit",
    "deposit",
    "dollar",
    "loan",
    "money",
    "paws",
    "pounce",
    "sunwest",
    "transfer",
    "withdraw"};

// For searching in all 8 direction
int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};


bool searchIn2D(char *grid, int row, int col, string word)
{
    char *puz = NULL;
    int R = ROW_SIZE, C = COLUMN_SIZE;

    // Find alphabet word from puzzle.
    if (*(grid + row * C + col) != word[0])
        return false;

    // store first location of the word
    int puz_mem = 0;
    locations[puz_mem++] = grid + row * C + col;

    int len = word.length();

    // Search word in all 8 directions starting from (row, col)
    for (int dir = 0; dir < 8; dir++)
    {
        // Initialize starting point for current direction
        int k, rd = row + x[dir], cd = col + y[dir];

        // Find remaining remaining characters
        for (k = 1; k < len; k++)
        {
            // If out of bound break
            if (rd >= R || rd < 0 || cd >= C || cd < 0)
            {
                break;
            }

            puz = grid + rd * C + cd;
            // If not matched,  break
            if (*puz != word[k])
            {
                break;
            }

            // remember the location to capitalize
            locations[puz_mem++] = puz;

            // Moving in particular direction
            rd += x[dir], cd += y[dir];
        }

        // all character matched
        if (k == len)
        {
            // capatalize the alphabet from the list
            for (int i = 0; i < word.length(); i++)
            {
                locations[i][0] = toupper(locations[i][0]);
            }

            // cout << word << endl;
            return true;
        }
        // if not matched then find in other direction and reset location to 1
        puz_mem = 1;
    }
    return false;
}

// Searches given word in matrix
void searchPattern(char *grid, string word)
{
    // Start from begining and search again
    for (int row = 0; row < ROW_SIZE; row++)
    {
        for (int col = 0; col < COLUMN_SIZE; col++)
        {
            searchIn2D(grid, row, col, word);
        }
    }
}

int main()
{

    for (int i = 0; i < WORDS_SIZE; i++)
    {
        searchPattern((char *)puzzle, words[i]);
    }

    // printing puzzle output
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COLUMN_SIZE; j++)
            cout << puzzle[i][j] << " ";
        cout << endl;
    }

    return 0;
}