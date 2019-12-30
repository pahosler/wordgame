#include<iostream> //for input and output streams.
#include<fstream> //for file
#include<vector>
#include<time.h>
#include<string.h>
#include<locale>
#include<ncurses.h>
#include<stdio.h>
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
      setLetters();
    }

    void setWords(vector<string> w)
    {
      words = w;
    }

     void setBoard(string b)
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

    void setLetters()
    {
      vector<string> _letters;
      srand(time(nullptr)); // use current time as seed for random generator
      int random_variable = rand();
      word = words.at(rand()/((RAND_MAX + 1u)/words.size()));
      int lc = word.length();
      char letters[lc + 1];
      strcpy(letters, word.c_str());
      setBoard(letters);
    }

    private:
    vector<string> words;
    string word;
    string board;
};
int main() {
  char l;
  locale loc;
  Words wordgame("werds.txt");
  cout << wordgame.getWord() << '\n'; 
  cout << wordgame.getBoard() << '\n';
  cout << "Enter a letter: ";
  system("stty raw");
   l = getchar();
   system("stty cooked");
  cout << '\n' << "You entered " << tolower(l, loc) << '\n';
}
