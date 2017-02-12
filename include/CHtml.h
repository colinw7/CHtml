#ifndef CHtml_H
#define CHtml_H

#include <string>

class CHtmlParserTokens;

class CHtml {
 public:
  CHtml();

  bool isDebug() const { return debug_; }
  void setDebug(bool b) { debug_ = b; }

  bool read(const std::string &filename, CHtmlParserTokens &tokens);

  bool readString(const std::string &str, CHtmlParserTokens &tokens);

 private:
  bool debug_ { false };
};

#endif
