#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

int main() {
  string key = "word";
  string def_1 = "a unit of language, consisting of one or more spoken sounds "
                 "or their written representation, that functions as a "
                 "principal carrier of meaning";
  string def_2 = "speech or talk: to express one's emotion in words";
  string def_3 =
      "a short talk or conversation: 'Marston, I'd like a word with you.'";
  string def_4 = "an expression or utterance: a word of warning";
  unordered_map<string, vector<string>> my_dictionary;

  if (my_dictionary.find(key) == my_dictionary.end()) {
    cout << "The key 'word' is not in the dictionary." << "\n";
    cout << "Inserting a key-value pair into the dictionary." << "\n\n";
    my_dictionary[key] = vector<string>{def_1, def_2, def_3, def_4};
  }

  cout << key << ": \n";
  auto definitions = my_dictionary[key];
  for (string definition : definitions) {
    cout << definition << "\n";
  }
}
