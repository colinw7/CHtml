#include <CHtmlLib.h>
#include <CStrUtil.h>

static bool processFile(const std::string &filename, const std::string &match);

int
main(int argc, char **argv)
{
  std::string match;
  std::string filename;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'm') {
        ++i;

        if (i < argc)
          match = argv[i];
      }
      else {
        continue;
      }
    }
    else {
      filename = argv[i];
    }
  }

  if (filename != "")
    processFile(filename, match);

  return 0;
}

static bool
processFile(const std::string &filename, const std::string &match)
{
  CHtml             html;
  CHtmlParserTokens tokens;

  bool inside = (match != "" ? false : true);

  html.read(filename, tokens);

  int num_tokens = tokens.size();

  for (int i = 0; i < num_tokens; ++i) {
    const CHtmlToken *token = tokens[i];

    if      (token->isText()) {
      if (inside) {
        CHtmlText *text = token->getText();

        std::string str = text->getText();

        std::cout << str << std::endl;
      }
    }
    else if (token->isTag()) {
      CHtmlTag *tag = token->getTag();

      const CHtmlTagDef &tag_def = tag->getTagDef();

      std::string tagName = tag_def.getName();

      if (tag->isStartTag()) {
        if (inside) {
          std::cout << "<" << tagName;

          int num_options = tag->getNumOptions();

          for (int j = 0; j < num_options; j++) {
            const CHtmlTagOption *option = tag->getOption(j);

            std::string name  = option->getName ();
            std::string value = option->getValue();

            std::cout << " " << name << "=\"" << value << "\"";
          }

          std::cout << ">";
        }

        if (match != "" && tagName == match)
          inside = true;
      }
      else {
        if (match != "" && tagName == match)
          inside = false;

        if (inside)
          std::cout << "</" << tagName << ">";
      }
    }
  }

  return true;
}
