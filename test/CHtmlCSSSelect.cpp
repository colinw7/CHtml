#include <CHtmlLib.h>
#include <CCSS.h>
#include <CStrUtil.h>
#include <cstring>
#include <cassert>

class CHtmlCSSTagData : public CCSSTagData {
 public:
  typedef std::vector<CHtmlTag *> Children;

 public:
  CHtmlCSSTagData(CHtmlTag *tag) :
   tag_(tag) {
  }

  CHtmlTag *tag() const { return tag_; }

  bool isElement(const std::string &name) const override {
    return (name == tag_->getName());
  }

  bool isClass(const std::string &name) const override {
    return (name == tag_->getOptionValue("class"));
  }

  bool isId(const std::string &name) const override {
    return (name == tag_->getOptionValue("id"));
  }

  bool hasAttribute(const std::string &name, CCSSAttributeOp op,
                    const std::string &value) const override {
    if      (op == CCSSAttributeOp::NONE)
      return tag_->hasOptionName(name);
    else if (op == CCSSAttributeOp::EQUAL)
      return tag_->hasOptionNameValue(name, value);
    else if (op == CCSSAttributeOp::PARTIAL)
      return tag_->hasOptionNameSubValue(name, value);
    else if (op == CCSSAttributeOp::STARTS_WITH)
      return tag_->hasOptionNameStart(name, value);
    else
      return false;
  }

  CCSSTagDataP getParent() const override {
    if (! tag_->parent())
      return CCSSTagDataP();

    return CCSSTagDataP(new CHtmlCSSTagData(tag_->parent()));
  }

  void getChildren(TagDataArray &children) const override {
    const CHtmlTag::Children &children1 = tag_->children();

    for (const auto &child : children1) {
      CHtmlTag *childTag = child->getTag();
      if (! childTag) continue;

      if (! childTag->isStartTag())
        continue;

      CCSSTagDataP dataP(new CHtmlCSSTagData(childTag));

      children.push_back(dataP);
    }
  }

  CCSSTagDataP getPrevSibling() const override {
    if (! tag_->parent())
      return CCSSTagDataP();

    const CHtmlTag::Children &children = tag_->parent()->children();

    CHtmlTag *lastChildTag = nullptr;

    for (const auto &child : children) {
      CHtmlTag *childTag = child->getTag();
      if (! childTag) continue;

      if (! childTag->isStartTag())
        continue;

      if (childTag == tag_) {
        if (lastChildTag)
          return CCSSTagDataP(new CHtmlCSSTagData(lastChildTag));
      }

      lastChildTag = childTag;
    }

    return CCSSTagDataP();
  }

  CCSSTagDataP getNextSibling() const override {
    if (! tag_->parent())
      return CCSSTagDataP();

    bool nextChild = false;

    const CHtmlTag::Children &children = tag_->parent()->children();

    for (const auto &child : children) {
      CHtmlTag *childTag = child->getTag();
      if (! childTag) continue;

      if (! childTag->isStartTag())
        continue;

      if (nextChild)
        return CCSSTagDataP(new CHtmlCSSTagData(childTag));

      if (childTag == tag_)
        nextChild = true; // return next child
    }

    return CCSSTagDataP();
  }

 private:
  CHtmlTag *tag_ { nullptr };
};

//------

static bool processFile(const std::string &htmlFile, const std::string &cssFile, bool debug);
static bool checkMatch(const CCSS &css, const CCSSTagDataP &cssTagData);
static void printTag(CHtmlTag *tag);

//------

int
main(int argc, char **argv)
{
  std::string htmlFile;
  std::string cssFile;

  bool debug = false;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(&argv[i][1], "debug") == 0)
        debug = true;
      else {
        std::cerr << "Invalid option '" << argv[i] << "'" << std::endl;
        exit(1);
      }
    }
    else {
      if      (htmlFile == "")
        htmlFile = argv[i];
      else if (cssFile == "")
        cssFile = argv[i];
      else {
        std::cerr << "Invalid arg '" << argv[i] << "'" << std::endl;
        exit(1);
      }
    }
  }

  if (htmlFile == "" || cssFile == "") {
    std::cerr << "Missing html or css arg" << std::endl;
    exit(1);
  }

  processFile(htmlFile, cssFile, debug);

  return 0;
}

static bool
processFile(const std::string &htmlFile, const std::string &cssFile, bool debug)
{
  // process css
  CCSS css;

  css.setDebug(debug);

  css.processFile(cssFile);

  //----

  // process html
  CHtml             html;
  CHtmlParserTokens tokens;

  html.read(htmlFile, tokens);

  int num_tokens = tokens.size();

  for (int i = 0; i < num_tokens; ++i) {
    const CHtmlToken *token = tokens[i];

    if (! token->isTag())
      continue;

    CHtmlTag *tag = token->getTag();

    if (! tag->isStartTag())
      continue;

    CCSSTagDataP cssTagData(new CHtmlCSSTagData(tag));

    if (! checkMatch(css, cssTagData))
      continue;
  }

  return true;
}

static bool
checkMatch(const CCSS &css, const CCSSTagDataP &cssTagData)
{
  bool match = false;

  std::vector<CCSS::SelectorList> selectorListArray;

  css.getSelectors(selectorListArray);

  for (const auto &selectorList : selectorListArray) {
    const CCSS::StyleData &styleData = css.getStyleData(selectorList);

    if (! styleData.checkMatch(cssTagData))
      continue;

    if (! match) {
      CHtmlCSSTagData *dataP = dynamic_cast<CHtmlCSSTagData *>(cssTagData.get());

      printTag(dataP->tag());
    }

    match = true;

    std::cerr << "  " << styleData << std::endl;
  }

  return match;
}

static void
printTag(CHtmlTag *tag)
{
  std::cout << "<" << tag->getName();

  for (int j = 0; j < tag->getNumOptions(); j++) {
    const CHtmlTagOption *option = tag->getOption(j);

    std::cout << " " << option->getName() << "=\"" << option->getValue() << "\"";
  }

  std::cout << ">" << std::endl;
}
