#include <CHtmlLib.h>
#include <CStrUtil.h>

static bool processFile(const std::string &filename, const std::string &match,
                        bool hier, bool text, bool debug);
static void printToken(const CHtmlToken *token, const std::string &match, bool text, bool &inside);
static void printHierToken(const CHtmlToken *token, bool text, int depth=0, bool newline=true);
static void printStartTag(CHtmlTag *tag, bool text, int depth=0);
static void printEndTag(CHtmlTag *tag, bool text, int depth=0);
static void printDepthSpaces(int depth=0);
static bool hasChildTags(CHtmlTag *tag);

int
main(int argc, char **argv)
{
  std::string match;
  std::string filename;
  bool        hier = false;
  bool        text = false;
  bool        debug = false;

  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);

    if (! arg.empty() && arg[0] == '-') {
      std::string opt = arg.substr(1);

      if      (opt == "m" || opt == "match") {
        ++i;

        if (i < argc)
          match = argv[i];
      }
      else if (opt == "hier") {
        hier = true;
      }
      else if (opt == "text") {
        text = true;
      }
      else if (opt == "debug") {
        debug = true;
      }
      else {
        std::cerr << "Invalid option '" << arg << "'\n";
        exit(1);
      }
    }
    else {
      filename = argv[i];
    }
  }

  if (filename != "")
    processFile(filename, match, hier, text, debug);

  return 0;
}

bool
processFile(const std::string &filename, const std::string &match,
            bool hier, bool text, bool debug)
{
  CHtml             html;
  CHtmlParserTokens tokens;

  html.setDebug(debug);

  bool inside = (match != "" ? false : true);

  html.read(filename, tokens);

  if (tokens.empty())
    return true;

  if (hier) {
    int depth = 0;

    const CHtmlToken *token = tokens[0];

    printHierToken(token, text, depth);
  }
  else {
    for (int i = 0; i < tokens.size(); ++i) {
      const CHtmlToken *token = tokens[i];

      printToken(token, match, text, inside);
    }
  }

  return true;
}

void
printToken(const CHtmlToken *token, const std::string &match, bool text, bool &inside)
{
  if      (token->isText()) {
    if (inside) {
      CHtmlText *ttext = token->getText();

      std::string str = ttext->getText();

      std::string sstr = CStrUtil::stripSpaces(str);

      if (sstr != "")
        std::cout << sstr << "\n";
    }
  }
  else if (token->isTag()) {
    CHtmlTag *tag = token->getTag();

    const CHtmlTagDef &tag_def = tag->getTagDef();

    std::string tagName = tag_def.getName();

    if (tag->isStartTag()) {
      if (inside)
        printStartTag(tag, text, 0);

      if (match != "" && tagName == match)
        inside = true;
    }
    else {
      if (match != "" && tagName == match)
        inside = false;

      if (inside)
        printEndTag(tag, text, 0);
    }
  }
}

void
printHierToken(const CHtmlToken *token, bool text, int depth, bool newline)
{
  if      (token->isText()) {
    CHtmlText *ttext = token->getText();

    std::string str = ttext->getText();

    std::string sstr = CStrUtil::stripSpaces(str);

    if (sstr != "") {
      std::cout << sstr;

      if (text)
        std::cout << "\n";
    }
  }
  else if (token->isTag()) {
    CHtmlTag *tag = token->getTag();

    if (tag->isStartTag())
      printStartTag(tag, text, depth);
    else {
      if (! text) {
        if (newline) {
          std::cout << "\n";

          printDepthSpaces(depth - 1);
        }
      }

      printEndTag(tag, text, depth - 1);
    }
  }
}

void
printStartTag(CHtmlTag *tag, bool text, int depth)
{
  bool isInline = tag->isInline();

  //---

  if (! text) {
    const CHtmlTagDef &tag_def = tag->getTagDef();

    std::string tagName = tag_def.getName();

    if (! isInline) {
      std::cout << "\n";

      printDepthSpaces(depth);
    }

    std::cout << "<" << tagName;

    //---

    int num_options = tag->getNumOptions();

    for (int j = 0; j < num_options; j++) {
      const CHtmlTagOption *option = tag->getOption(j);

      std::string name  = option->getName ();
      std::string value = option->getValue();

      std::cout << " " << name << "=\"" << value << "\"";
    }

    std::cout << ">";
  }

  //---

  bool childTags = hasChildTags(tag);

  const CHtmlTag::Children &children = tag->children();

  for (const auto &child : children) {
    printHierToken(child, text, depth + 1, childTags);
  }
}

void
printEndTag(CHtmlTag *tag, bool text, int depth)
{
  if (! text) {
    const CHtmlTagDef &tag_def = tag->getTagDef();

    std::string tagName = tag_def.getName();

    std::cout << "</" << tagName << ">";
  }
}

void
printDepthSpaces(int depth)
{
  for (int i = 0; i < depth; ++i)
    std::cout << " ";
}

bool
hasChildTags(CHtmlTag *tag)
{
  const CHtmlTag::Children &children = tag->children();

  for (const auto &child : children) {
    CHtmlTag *childTag = child->getTag();

    if (childTag && childTag->isStartTag() && ! childTag->isInline())
      return true;
  }

  return false;
}
