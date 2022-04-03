#ifndef CHtmlParser_H
#define CHtmlParser_H

#include <CHtmlTypes.h>
#include <CFile.h>
#include <CSafeIndex.h>

#include <string>
#include <vector>
#include <memory>

class CHtml;
class CHtmlTag;
class CHtmlToken;

class CHtmlParserTokens {
 public:
  CHtmlParserTokens();
 ~CHtmlParserTokens();

  void add(CHtmlToken *token);

  size_t size() const { return tokens_.size(); }

  bool empty() const { return tokens_.empty(); }

  const CHtmlToken *operator[](int i) const { return CUtil::safeIndex(tokens_, i); }

  void clear();

  CHtmlTokenArray::iterator begin() { return tokens_.begin(); }
  CHtmlTokenArray::iterator end  () { return tokens_.end  (); }

 private:
  CHtmlTokenArray tokens_;
};

//------

class CHtmlParser {
 public:
  explicit CHtmlParser(const CHtml &html);
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
  void readScriptText();

  bool matchString(const std::string &str);
  void skipSpaces();

  int lookChar();
  int readChar();

  void unreadChars(const std::string &str);
  void unreadChar(int c);

  void parseError(const char *fmt, ...);
  void parseError(const std::string &str);

  CHtmlTag *currentTag() const;

 private:
  CHtmlParser(const CHtmlParser &rhs);
  CHtmlParser &operator=(const CHtmlParser &rhs);

 private:
  using Buffer   = std::vector<char>;
  using TagStack = std::vector<CHtmlTag *>;
  using FileP =   std::unique_ptr<CFile>;

  const CHtml&       html_;
  FileP              file_;
  CHtmlParserTokens* tokens_   { nullptr };
  TagStack           tagStack_;
  Buffer             buffer_;
  bool               debug_   { false };
  uint               lineNum_ { 1 };
  uint               charNum_ { 0 };
};

#endif
