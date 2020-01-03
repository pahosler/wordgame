#include<iostream> //for input and output streams.
#include<fstream> //for file
#include<vector>
#include<time.h>
#include<string.h>
#include<locale>
#include<ncurses.h>
#include<algorithm>
using namespace std;

class Words {
  private:
    vector<string> words;
    string word;
    string board;

    void setWord()
    {
      srand(time(nullptr)); // use current time as seed for random generator
      int random_variable = rand();
      word = words.at(rand()/((RAND_MAX + 1u)/words.size()));
      int lc = word.length();
      char _word[lc + 1];
      strcpy(_word, word.c_str());
      newBoard(_word);
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

    void newBoard(string b)
    {
      int lc = b.length(); // letter count
      char _board[lc + 1];
      strcpy(_board, b.c_str());
      for (int i = 0; i < sizeof(_board)-1; i++)
      {
        board += "*";
      }
    }

    string getBoard()
    {
      return board;
    }

    string getWord()
    {
      return word;
    }

    void newWord()
    {
      word = "";
      board = "";
      setWord();
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

string replaceStrChar(string str, string b, char ch)
{
  // thanks to psyperl!
  transform(str.begin(), str.end(), b.begin(), b.begin(), [ch](char w, char b){
    return w == ch ? w : b;
  });

  return b;
}

int main() {
// Init Wordgame
  char l;
  char replay = 'y';
  int guess = 5;
  Words game("werds.txt");
  Words *wordgame;
  wordgame = &game;
  wordgame->newWord();
  string board = wordgame->getBoard();
  string word = wordgame->getWord();
  size_t found;

// GAME LOOP!
   while (l != '0' && replay == 'y') 
  {
    if (replay != 'y')
    {
      cout << '\n' << "Goodbye" << endl;
      return 1;
    }
    cout << board << '\n';
    l = wordgame->handleInput("Enter a letter (0 to quit): ");

    if (l == '0')
    {
      cout << '\n' << "Goodbye" << endl;
    }
    else
    {
      board = replaceStrChar(word, board, l);
      found = board.find(l);
      if (found == string::npos) // check correct guess
      {
        --guess; // lose a chance if incorrect
      }
      else 
      {
        wordgame->newBoard(board); // update board if correct
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
        replay = wordgame->handleInput("Try again? (y/n) ");
      }
      guess = 5;
      wordgame->newWord();
      word = wordgame->getWord();
      board = wordgame->getBoard();
      system("clear");
    }
    else if (board == word)
    {
      replay = ' ';
      cout << '\n' << word << '\n' << "Winner Winner Chicken Dinner!" << endl;
      while (replay != 'y' && replay != 'n')
      {
        replay = wordgame->handleInput("Try again? (y/n) ");
      }
      guess = 5;
      wordgame->newWord();
      word = wordgame->getWord();
      board = wordgame->getBoard();
      system("clear");
    }
  }
} 
