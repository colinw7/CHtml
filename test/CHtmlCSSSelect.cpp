#include <CHtmlLib.h>
#include <CHtmlCSSTagData.h>
#include <CCSS.h>
#include <CStrUtil.h>
#include <cstring>
#include <cassert>

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
