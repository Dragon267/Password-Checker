#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

class Logger {
 public:
  const std::string RESET_COLOR = "\033[0m";
  const std::string RED_COLOR = "\033[31m";
  const std::string GREEN_COLOR = "\033[32m";
  const std::string YELLOW_COLOR = "\033[33m";
  const std::string BLUE_COLOR = "\033[34m";
  const std::string PURPLE_COLOR = "\033[1;35m";

  string DeleteNext(string s) {
    string r = "";
    for (int i = 0; i < s.size(); i++) {
      char c = s[i];
      if (c != '\n') {
        r += c;
      }
    }
    return r;
  }

  string CurrentTime() {
    time_t tt;
    struct tm* ti;
  
    time(&tt);
  
    ti = localtime(&tt);
  
    return DeleteNext((string) asctime(ti));
  }

  void Info(string message) {
    cout << "[" << PURPLE_COLOR << "INFO" << RESET_COLOR << ", " << CurrentTime() << "]: " << message << endl;
  }

  void Found(string message) {
    cout << "[" << RED_COLOR << "CRITICAL" << RESET_COLOR << ", " << CurrentTime() << "]: " << message << endl;
  }
};
