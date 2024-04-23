#include <fstream>
#include <iostream>
#include <stack>

bool isOpeningBracket(char bracket);
bool isClosingBracket(char bracket);
bool isBracketMatch(char openingBr, char closingBr);
void detectNonMatchingBracket(const std::string &filePath);

int main(int argc, char *argv[]){
  if (argc != 2) {
    std::cerr << "Usage: ./bracketScanner <file_path>" << std::endl;
    return 1;
  }

  std::string filePath = argv[1];

  // Open and check for errors
  detectNonMatchingBracket(filePath);

  return 0;
}

bool isOpeningBracket(char bracket) {
  if (bracket == '[' || bracket == '(' || bracket == '{') {
    return true;
  }
  return false;
}

bool isClosingBracket(char bracket) {
  if (bracket == ']' || bracket == ')' || bracket == '}') {
    return true;
  }
  return false;
}

bool isBracketMatch(char openingBr, char closingBr) {
  if (
  openingBr == '[' && closingBr == ']'||
  openingBr == '(' && closingBr == ')'||
  openingBr == '{' && closingBr == '}') {
    return true;
  }
  return false;
}

void detectNonMatchingBracket(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "File cannot be opened" << std::endl;
    return;
  }

  std::string line;
  int lineNumber = 1;
  while (std::getline(file, line)) {
    std::stack<std::pair<char, int>> bracketStack;
    for (size_t i = 0; i < line.size(); i++) {
      char currentChar = line[i];

      if (isOpeningBracket(currentChar)) {
        bracketStack.push(std::make_pair(currentChar, i + 1));

      } else if (isClosingBracket(currentChar)) {

        if (bracketStack.empty()) {
          std::cerr << "Invalid Bracket" << currentChar << " found at " << filePath << ":" << lineNumber << ":" 
          << i + 1 << "." << std::endl;
          return;

        } else {
          char top = bracketStack.top().first;

          if(!isBracketMatch(top, currentChar)) {
            std::cerr << "Invalid Bracket" << currentChar << " found at " << filePath << ":" << lineNumber << ":" 
          << i + 1 << "." << std::endl;
          return;
          }
          bracketStack.pop();
        }
      }
    }
    while (!bracketStack.empty()) {
      char remainingBracket = bracketStack.top().first;
      int columnNumber = bracketStack.top().second;
      std::cerr << "Invalid Bracket" << remainingBracket << " found at " << filePath << ":" << lineNumber << ":" 
          << columnNumber << "." << std::endl;

    }
    lineNumber++;
  }
  file.close();
}

