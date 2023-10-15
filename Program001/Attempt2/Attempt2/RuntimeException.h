#ifndef RuntimeException_h
#define RuntimeException_h

#include <string>

using std::string;

// Source code provided in Sec. 2.4.3, Page 97, of Textbook
// Michael T. Goodrich, Roberto Tamassia, and David Mount. Data Structures and Algorithms in C++. Second Edition. 2011. Wiley

class RuntimeException {  // generic run-time exception
private:
  string errorMsg;
public:
  RuntimeException(const string& err) { errorMsg = err; }
  string getMessage() const { return errorMsg; }
};

#endif 
