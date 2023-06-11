#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

// my classes
#include "libraries/Logger.h"

using namespace std;

Logger logger;
vector<string> paths(0);
vector<int> line_number(0);

void searchForString(const std::filesystem::path& filePath, const string& searchString) {
  logger.Info("Scaning file: " + (string) filePath);
  ifstream file(filePath);
  string line;
  int lineNumber = 0;

  while (getline(file, line)) {
    lineNumber++;
    if (line.find(searchString) != string::npos) {
      logger.Found("file: " + (string) filePath + ", line number: " + to_string(lineNumber));
      paths.push_back((string) filePath);
      line_number.push_back(lineNumber);
      return;
    }
  }
}

void processDirectory(const std::filesystem::path& directoryPath, const string& searchString) {
  for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
    const auto& path = entry.path();

    if (std::filesystem::is_regular_file(path)) {
      searchForString(path, searchString);
    }
  }
}

int main(int argc, char *args[]) {
  if (argc == 1) { cout << "This is a Password Checker. This Code will search the current directory you are in for all files where a specific key appears."; return 0; }

  string searchString = args[1];
  std::filesystem::path directoryPath = std::filesystem::current_path();

  logger.Info("Searching directory: " + directoryPath.string() + " for key: " + searchString);

  if (!std::filesystem::exists(directoryPath) || !std::filesystem::is_directory(directoryPath)) {
    cerr << "Invalid directory path." << endl;
    return 1;
  }

  processDirectory(directoryPath, searchString);

  cout << "----------------------------- RESULT ------------------------------" << endl;
  for (int i = 0; i < paths.size(); i++) {
    logger.Found("file: " + paths[i] + ", line number: " + to_string(line_number[i]));
  }
  cout << "----------------------------- DONE --------------------------------" << endl;

  return 0;
}
