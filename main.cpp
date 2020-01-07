/*
*
*  wordgame by P.A. Hosler
*
*  console hangman style game, guess a word by entering
*  letters. You get 5 chances!
*  0 - exit during gameplay
*  y/n - replay query, n ends game
*
* @params string wordfile, single line list of words in a txt file
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/


#include<iostream>   // for input and output streams.
#include<fstream>    // for file
#include<vector>     // for variable arrays
#include<time.h>     // for seeding rand
#include<string.h>   // for string methods
#include<locale>     // for system
#include<algorithm>  // for finding/replacing a char in a string
using namespace std;

class Words {
  private:
    vector<string> words;
    string word;
    string board;

    void _word()
    {
      word = "";
      srand(time(nullptr)); // use current time as seed for random generator
      int random_variable = rand();
      word = words.at(rand()/((RAND_MAX + 1u)/words.size()));
    }

    void _board()
    {
      board = "";
      for(int i = 0; i < word.length(); i++)
      {
        board += "*";
      }

    }

  public:
    Words(string wordfile="werds.txt")
    {
      string line;
      ifstream file(wordfile);

      while (getline(file,line))
      {
        words.push_back(line);
      }
      
      file.close();
    }

    string getBoard()
    {
      _board();
      return board;
    }

    string getWord()
    {
      _word();
      return word;
    }

    char handleInput(string msg)
    {
      locale loc;
      char c;
      cout << msg;
      system("stty raw");
      c = getchar();
      system("stty cooked");
      cout << endl;
      return tolower(c, loc);
    }

};

void replaceStrChar(string str, string *b, char ch)
{
  // thanks to psyperl!
  transform(str.begin(), str.end(), b->begin(), b->begin(), [ch](char w, char b){
    return w == ch ? w : b;
  });
}

int initGame(Words *wg, string *w, string *b, int g = 5)
{
  *w = wg->getWord();
  *b = wg->getBoard();
  return g;
}

int main() {
// Init Wordgame
  char l;
  char replay = 'y';
  int guess = 5;
  size_t found;
  Words wordgame("werds.txt");
  string board;
  string word;

  initGame(&wordgame, &word, &board);
  
// GAME LOOP!
   while (l != '0' && replay == 'y') 
  {
    if (replay != 'y')
    {
      cout << '\n' << "Goodbye" << endl;
      return 1;
    }
    cout << board << '\n';
    l = wordgame.handleInput("Enter a letter (0 to quit): ");

    if (l == '0')
    {
      cout << '\n' << "Goodbye" << endl;
    }
    else
    {
      replaceStrChar(word, &board, l);
      found = board.find(l);
      if (found == string::npos) // check correct guess
      {
        --guess; // lose a chance if incorrect
      }
      cout << '\n' << "You have " << guess << " guesses remaining." << endl;
    }

    if(guess == 0 && board != word) // check if out of guess and we didn't win
    {
      replay = ' ';
      cout << '\n' << "Sorry, you lost this round" << endl;
      cout << "The word was " << word << endl;
      while (replay != 'y' && replay != 'n')
      {
        replay = wordgame.handleInput("Try again? (y/n) ");
      }
      guess = initGame(&wordgame, &word, &board,7);
      system("clear");
    }
    else if (board == word)
    {
      replay = ' ';
      cout << '\n' << word << '\n' << "Winner Winner Chicken Dinner!" << endl;
      while (replay != 'y' && replay != 'n')
      {
        replay = wordgame.handleInput("Try again? (y/n) ");
      }
      guess = initGame(&wordgame, &word, &board);
      system("clear");
    }
  }
} 
