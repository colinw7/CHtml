#ifndef CHtmlParser_H
#define CHtmlParser_H

#include <CHtmlTypes.h>
#include <CAutoPtr.h>
#include <CFile.h>
#include <string>
#include <vector>

class CHtml;
class CHtmlToken;

class CHtmlParserTokens {
 public:
  CHtmlParserTokens();
 ~CHtmlParserTokens();

  void add(CHtmlToken *token);

  int size() { return tokens_.size(); }

  const CHtmlToken *operator[](int i) { return tokens_[i]; }

  void clear();

 private:
  CHtmlTokenArray tokens_;
};

//------

class CHtmlParser {
 public:
  CHtmlParser(const CHtml &html);
 ~CHtmlParser();

  bool read(const std::string &filename, CHtmlParserTokens &tokens);

  bool readString(const std::string &str, CHtmlParserTokens &tokens);

  void setDebug(bool debug) { debug_ = debug; }
  bool getDebug() { return debug_; }

 private:
  bool isComment();
  bool readComment();

  bool isTag();
  bool readTag();
  void readTagOptions(CHtmlTagOptionArray &options);

  std::string replaceNamedChars(const std::string &value);

  void readText();

  bool matchString(const std::string &str);
  void skipSpaces();

  int lookChar();
  int readChar();

  void unreadChars(const std::string &str);
  void unreadChar(int c);

  void parseError(const char *fmt, ...);
  void parseError(const std::string &str);

 private:
  CHtmlParser(const CHtmlParser &rhs);
  CHtmlParser &operator=(const CHtmlParser &rhs);

 private:
  typedef std::vector<char> Buffer;

  const CHtml       &html_;
  CAutoPtr<CFile>    file_;
  CHtmlParserTokens *tokens_ { nullptr };
  Buffer             buffer_;
  bool               debug_ { false };
  uint               line_num_ { 1 };
  uint               char_num_ { 0 };
};

#endif
