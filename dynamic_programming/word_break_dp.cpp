#include <iostream>
#include <vector>
using namespace std;

class Dictionary{
  public:
    Dictionary();
    Dictionary(vector<string> new_dictionary);
    void clear();
    bool contains(string &word);
  protected:
    vector<string> dictionary;
};

Dictionary::Dictionary(vector<string> new_dictionary){
  vector<string> *dictionary_reference = &dictionary;
  *dictionary_reference = new_dictionary;
}

void Dictionary::clear(){
  vector<string> *dictionary_reference = &dictionary;
  dictionary_reference->clear();
}

bool Dictionary::contains(string &word)
{
    for (auto const &dict_word : dictionary)
        if (dict_word.compare(word) == 0)
            return true;
    return false;
}


void wordBreakUtil(string query, int string_length, string result, Dictionary dictionary)
{
    for (int split_position=1; split_position<=string_length; split_position++)
    {
        string prefix = query.substr(0, split_position);

        if (dictionary.contains(prefix))
        {
            if (split_position == string_length)
            {
                result += prefix;
                cout << result << endl;
                return;
            }
            wordBreakUtil(query.substr(
                split_position,
                string_length-split_position
              ),
              string_length-split_position,
              result + prefix + " ",
              dictionary
            );
        }
    }
}


void wordBreak(string query, Dictionary dictionary)
{
    wordBreakUtil(query, query.size(), "", dictionary);
}

int main()
{
  vector<string> words = {"mobile","samsung","sam","sung",
                          "man","mango", "icecream","and",
                          "go","i","love","ice","cream"};

  Dictionary dictionary(words);

  cout << "First Test:\n";
  wordBreak("iloveicecreamandmango", dictionary);

  cout << "\nSecond Test:\n";
  wordBreak("ilovesamsungmobile", dictionary);

  dictionary.clear();

  return 0;
}
