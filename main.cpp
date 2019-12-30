#include<iostream> //for input and output streams.
#include<fstream> //for file
#include<vector>
#include<time.h>
#include<string.h>
#include<locale>
#include<ncurses.h>
using namespace std;

class Words {
  public:
    Words(string wordfile){
      vector<string> _words;
      string line;
      ifstream file(wordfile);

      while (getline(file,line))
      {
        _words.push_back(line);
      }
      
      file.close();
      setWords(_words);
      setWord();
    }

    void setWords(vector<string> w)
    {
      words = w;
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
      return tolower(c, loc);
    }

    private:
    vector<string> words;
    string word;
    string board;
};
int main() {
  char l;
  char replay = 'y';
  int guess = 5;
  Words wordgame("werds.txt");
  
   while (l != '0' && replay == 'y') 
  {
    if (replay != 'y')
    {
      cout << '\n' << "Goodbye" << endl;
      return 1;
    }
    cout << '\n' << wordgame.getWord() << '\n'; 
    cout << wordgame.getBoard() << '\n';
    l = wordgame.handleInput("Enter a letter (0 to quit): ");
    if (l == '0')
    {
      cout << '\n' << "Goodbye" << endl;
    }
    else
    {
      cout << '\n' << "You entered " << l << '\n';
      --guess;
      cout << '\n' << "You have " << guess << " guesses remaining." << endl;
    }
    if(guess == 0) // and !winner
    {
      replay = ' ';
      while (replay != 'y' && replay != 'n')
      {
        cout << '\n' << "Sorry, you lost this round" << endl;
        replay = wordgame.handleInput("Try again? (y/n) ");
      }
      guess = 5;
      wordgame.newWord();
    }
  }
}
