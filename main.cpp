#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

int main(){
	string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
				  "Sed laoreet sem leo, in posuere orci elementum. ";
	char space_char = ' ';
	vector<string> words;

	stringstream sstream(text);
	string word;
	while (std::getline(sstream, word, space_char)){
		word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
		words.push_back("<" + word + ">");
	}

	for (int i = 0; i < words.size(); ++i) {
		cout << "|" << words[i] << "|" << endl;
	}
	cout << words.size() << endl;

	return EXIT_SUCCESS;
}
