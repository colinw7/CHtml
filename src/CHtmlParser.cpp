#include <CHtmlParser.h>
#include <CHtmlComment.h>
#include <CHtmlToken.h>
#include <CHtmlTag.h>
#include <CHtmlTagDef.h>
#include <CHtmlNamedChar.h>
#include <CHtmlText.h>
#include <CRegExp.h>
#include <CStrUtil.h>
#include <CThrow.h>
#include <CUtf8.h>
#include <cstdio>

CHtmlParser::
CHtmlParser(const CHtml &html) :
 html_(html)
{
}

CHtmlParser::
~CHtmlParser()
{
}

bool
CHtmlParser::
read(const std::string &filename, CHtmlParserTokens &tokens)
{
  if (! CFile::exists(filename)) {
    CTHROW("File " + filename + " does not exist");
    return false;
  }

  tokens_ = &tokens;

  file_ = std::make_unique<CFile>(filename);

  while (lookChar() != EOF) {
    if      (isComment())
      readComment();
    else if (isTag())
      readTag();
    else
      readText();
  }

  file_ = nullptr;

  return true;
}

bool
CHtmlParser::
readString(const std::string &str, CHtmlParserTokens &tokens)
{
  unreadChars(str);

  tokens_ = &tokens;

  file_ = nullptr;

  while (lookChar() != EOF) {
    if      (isComment())
      readComment();
    else if (isTag())
      readTag();
    else
      readText();
  }

  return true;
}

bool
CHtmlParser::
isComment()
{
  std::string str;

  if (! matchString("<!--"))
    return false;

  unreadChars("<!--");

  return true;
}

bool
CHtmlParser::
readComment()
{
  std::string str;

  if (! matchString("<!--"))
    return false;

  str += "<!--";

  //------

  int c = lookChar();

  while (c != EOF) {
    if (matchString("-->")) {
      str += "-->";
      break;
    }

    str += char(readChar());

    c = lookChar();
  }

  if (c == EOF) {
    unreadChars(str);

    return false;
  }

  //---

  auto *comment = new CHtmlComment(str);

  auto *token = new CHtmlCommentToken(comment);

  if (debug_)
    std::cerr << "Comment: " << str << std::endl;

  tokens_->add(token);

  //---

  CHtmlTag *currentTag = this->currentTag();

  if (currentTag) {
    if (debug_)
      std::cerr << "Add <comment> to " << currentTag->getTagName() << std::endl;

    currentTag->addChild(token);
  }

  return true;
}

bool
CHtmlParser::
isTag()
{
  int c = lookChar();

  if (c != '<')
    return false;

  std::string str;

  str += char(readChar());

  c = lookChar();

  if (c == '/')
    str += char(readChar());

  c = lookChar();

  if (! isalpha(c) && c != '!') {
    unreadChars(str);

    return false;
  }

  unreadChars(str);

  return true;
}

bool
CHtmlParser::
readTag()
{
  int c = readChar();

  if (c != '<') {
    CTHROW("readTag: internal error");
    return false;
  }

  //------

  bool end_tag = false;

  c = readChar();

  if (c == '/') {
    end_tag = true;

    c = readChar();
  }

  if (c != EOF)
    unreadChar(c);

  //------

  c = readChar();

  if (c != EOF && ! isalpha(c) && c != '!') {
    CTHROW("readTag: internal error");
    return false;
  }

  std::string name;

  name += char(c);

  c = readChar();

  while (c != EOF && ! isspace(c) && c != '/' && c != '>') {
    name += char(c);

    c = readChar();
  }

  if (c != EOF)
    unreadChar(c);

  //------

  skipSpaces();

  std::vector<CHtmlTagOption *> options;

  readTagOptions(options);

  //------

  bool start_end_tag = false;

  skipSpaces();

  c = readChar();

  if (c == '/') {
    c = readChar();

    if (end_tag)
      parseError("Bad close /> on end tag: " + name);

    start_end_tag = true;
  }

  if (c != '>') {
    parseError("Bad close > on tag: " + name);

    while (c != EOF && c != '>')
      c = readChar();
  }

  //------

  auto *tag = new CHtmlTag(name, options, end_tag);

  tag->setLineNum(int(lineNum_));
  tag->setCharNum(int(charNum_));

  //---

  auto *token = new CHtmlTagToken(tag);

  if (debug_)
    parseError(std::string("Tag: ") + tag->getTagName() +
               (! tag->getTagDef().isValid() ? " <unknown>" : ""));

  tokens_->add(token);

  //---

  CHtmlTag *currentTag = this->currentTag();

  //------

  // start tag only
  if      (! end_tag && ! start_end_tag) {
    if (currentTag) {
      if (debug_)
        std::cerr << "Add Start " << tag->getTagName() << " to " <<
          currentTag->getTagName() << std::endl;

      currentTag->addChild(token);
    }

    tagStack_.push_back(tag);
  }
  // end tag
  else if (end_tag) {
    if      (! currentTag) {
      if (debug_)
        parseError("No current tag for end tag " + tag->getName());
    }
    else if (currentTag->getName() != tag->getName()) {
      if (debug_)
        parseError("Current open tag " + currentTag->getName() +
                   " doesn't match end tag " + tag->getName());
    }
    else {
      tagStack_.pop_back();

      //CHtmlTag *currentTag = this->currentTag();

      if (currentTag) {
        if (debug_)
          std::cerr << "Add End " << tag->getTagName() << " to " <<
            currentTag->getTagName() << std::endl;

        currentTag->addChild(token);
      }
    }
  }
  // start end tag
  else {
    if (currentTag) {
      if (debug_)
        std::cerr << "Add Start of Start/End " << tag->getTagName() << " to " <<
          currentTag->getTagName() << std::endl;

      currentTag->addChild(token);
    }
  }

  //---

  // auto add end tag for start end tag
  if (! end_tag && start_end_tag) {
    std::vector<CHtmlTagOption *> options1;

    auto *tag1 = new CHtmlTag(name, options1, true);

    auto *token1 = new CHtmlTagToken(tag1);

    if (debug_)
      parseError(std::string("Tag: ") + "/" + tag1->getName() +
                 (! tag1->getTagDef().isValid() ? " <unknown>" : ""));

    tokens_->add(token1);

    //---

    if (tag) {
      if (debug_)
        std::cerr << "Add End of Start/End " << tag1->getTagName() <<
            " to " << tag->getTagName() << std::endl;

      tag->addChild(token1);
    }
  }

  return true;
}

void
CHtmlParser::
readTagOptions(std::vector<CHtmlTagOption *> &options)
{
  while (true) {
    skipSpaces();

    //------

    int c = lookChar();

    if      (c == '>')
      break;
    else if (c == '/') {
      c = readChar();

      int c1 = lookChar();

      if (c1 == '>') {
        unreadChar(c);
        break;
      }

      unreadChar(c);
    }

    //------

    std::string name;

    c = readChar();

    while (c != EOF && ! isspace(c) && c != '=' && c != '>') {
      name += char(c);

      c = readChar();
    }

    if (c != EOF)
      unreadChar(c);

    if (name == "")
      break;

    //------

    skipSpaces();

    //------

    std::string value;

    c = lookChar();

    if (c == '=') {
      c = readChar();

      skipSpaces();

      c = readChar();

      while (c != EOF && ! isspace(c)) {
        if      (c == '\'') {
          c = readChar();

          while (c != EOF) {
            if (c == '\'')
              break;

            value += char(c);

            c = readChar();
          }

          if (c == '\'')
            c = readChar();
        }
        else if (c == '\"') {
          c = readChar();

          while (c != EOF) {
            if (c == '\"')
              break;

            value += char(c);

            c = readChar();
          }

          if (c == '\"')
            c = readChar();
        }
        else if (c == '>') {
          break;
        }
        else if (c == '/') {
          int c1 = lookChar();

          if (c1 == '>')
            break;

          value += char(c);
        }
        else {
          value += char(c);

          c = readChar();
        }
      }

      if (c != EOF)
        unreadChar(c);
    }

    //------

    value = replaceNamedChars(value);

    //------

    auto *option = new CHtmlTagOption(name, value);

    if (debug_)
      std::cerr << "Option: " << name << "," << value << std::endl;

    options.push_back(option);
  }
}

std::string
CHtmlParser::
replaceNamedChars(const std::string &value)
{
  static CRegExp re1("#x[0-9a-fA-F][0-9a-fA-F]");
  static CRegExp re2("#[0-9][0-9]*");

  std::string value1;

  auto len = value.size();

  decltype(len) i = 0;

  while (i < len) {
    char c = value[i];

    if (c == '&') {
      auto j = i++;

      while (i < len) {
        if (value[i] == ';')
          break;

        ++i;
      }

      if (i >= len) {
        value1 += value.substr(j);
        break;
      }

      auto len1 = i - j - 1;

      std::string name = value.substr(j + 1, len1);

      if      (re1.find(name)) {
        std::string hstr = name.substr(2);

        uint h;

        CStrUtil::decodeHexString(hstr, &h);

        value1 += char(h);
      }
      else if (re2.find(name)) {
        std::string dstr = name.substr(1);

        long l;

        CStrUtil::toInteger(dstr, &l);

        value1 += char(l);
      }
      else {
        CHtmlNamedChar *named_char;

        if (CHtmlNamedCharMgrInst->lookup(name, &named_char))
          CUtf8::append(value1, named_char->value);
        else
          value1 += value.substr(j, i - j + 1);
      }

      ++i;
    }
    else {
      value1 += char(c);

      ++i;
    }
  }

  return value1;
}

void
CHtmlParser::
readText()
{
  CHtmlTag *currentTag = this->currentTag();

  if (currentTag && CStrUtil::toLower(currentTag->getName()) == "script") {
    readScriptText();

    return;
  }

  //---

  int c = readChar();

  if (c == EOF)
    return;

  std::string str;

  str += char(c);

  while (! isComment() && ! isTag()) {
    c = readChar();

    if (c == EOF)
      break;

    str += char(c);
  }

  //---

  str = replaceNamedChars(str);

  auto *text = new CHtmlText(str);

  auto *token = new CHtmlTextToken(text);

  if (debug_)
    std::cerr << "Text: " << str << std::endl;

  tokens_->add(token);

  //---

  if (currentTag) {
    if (debug_)
      std::cerr << "Add <text> to " << currentTag->getTagName() << std::endl;

    currentTag->addChild(token);
  }
}

void
CHtmlParser::
readScriptText()
{
  int c = readChar();

  std::string str;
  std::string tagName;
  bool        inTag = false;
  bool        endFound = false;

  while (c != EOF) {
    if      (c == '<') {
      tagName = "";
      inTag   = true;

      tagName += char(c);
    }
    else if (c == '>') {
      if (inTag)
        tagName += char(c);

      inTag = false;
    }
    else {
      if (inTag)
        tagName += char(tolower(c));
    }

    str += char(c);

    if (tagName == "</script>") {
      endFound = true;
      break;
    }

    c = readChar();
  }

  if (endFound) {
    str = str.substr(0, str.size() - 9);

    unreadChars("</script>");
  }

  auto *text = new CHtmlText(str);

  auto *token = new CHtmlTextToken(text);

  if (debug_)
    std::cerr << "Text: " << str << std::endl;

  tokens_->add(token);

  //---

  CHtmlTag *currentTag = this->currentTag();

  if (currentTag)
    currentTag->addChild(token);
}

bool
CHtmlParser::
matchString(const std::string &str)
{
  std::string str1;

  auto len = str.size();

  for (decltype(len) i = 0; i < len; ++i) {
    int c = lookChar();

    if (c != str[i]) {
      unreadChars(str1);
      return false;
    }

    str1 += char(readChar());
  }

  return true;
}

void
CHtmlParser::
skipSpaces()
{
  int c = readChar();

  while (c != EOF && isspace(c))
    c = readChar();

  if (c != EOF)
    unreadChar(c);
}

int
CHtmlParser::
lookChar()
{
  if (buffer_.size() == 0) {
    int c = EOF;

    if (file_)
      c = file_->getC();

    if (c == EOF)
      return EOF;

    buffer_.push_back(char(c));
  }

  return buffer_[buffer_.size() - 1];
}

int
CHtmlParser::
readChar()
{
  if (buffer_.size() == 0) {
    if (file_) {
      int c = file_->getC();

      if (c == '\n') {
        ++lineNum_;

        charNum_ = 0;
      }
      else
        ++charNum_;

      return c;
    }
    else
      return EOF;
  }

  int c = buffer_[buffer_.size() - 1];

  if (c == '\n') {
    ++lineNum_;

    charNum_ = 0;
  }
  else
    ++charNum_;

  buffer_.pop_back();

  return c;
}

void
CHtmlParser::
unreadChars(const std::string &str)
{
  auto len = str.size();

  while (len > 0) {
    --len;

    if (str[len] == '\n') {
      --lineNum_;

      charNum_ = 256;
    }
    else
      --charNum_;

    buffer_.push_back(str[len]);
  }
}

void
CHtmlParser::
unreadChar(int c)
{
  if (c == '\n')
    --lineNum_;
  else
    --charNum_;

  buffer_.push_back(char(c));
}

void
CHtmlParser::
parseError(const char *fmt, ...)
{
  va_list vargs;

  va_start(vargs, fmt);

  std::cerr << lineNum_ << ":" << charNum_ << "> ";
  std::cerr << CStrUtil::vstrprintf(fmt, &vargs) << std::endl;

  va_end(vargs);
}

void
CHtmlParser::
parseError(const std::string &str)
{
  std::cerr << lineNum_ << ":" << charNum_ << "> " << str << std::endl;
}

CHtmlTag *
CHtmlParser::
currentTag() const
{
  return (! tagStack_.empty() ? tagStack_.back() : 0);
}

//--------------

CHtmlParserTokens::
CHtmlParserTokens()
{
}

CHtmlParserTokens::
~CHtmlParserTokens()
{
  clear();
}

void
CHtmlParserTokens::
add(CHtmlToken *token)
{
  tokens_.push_back(token);
}

void
CHtmlParserTokens::
clear()
{
  auto num_tokens = tokens_.size();

  for (decltype(num_tokens) i = 0; i < num_tokens; i++)
    delete tokens_[i];

  tokens_.clear();
}
