#include "std_c++.h"
#include "CHtml/CHtmlLib.h"
#include "CStrUtil/CStrUtil.h"

static bool processFile
             (const char *file);
static void output_string
             (const string &str);
static void output
             (const string &str);
static void newline
             (int num=1);

static int    new_line  = 1;
static bool   non_space = false;
static bool   format    = true;
static string buffer    = "";

int
main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-')
      continue;

    processFile(argv[i]);
  }

  return 0;
}

enum ListType {
  ORDERED    = 1,
  UNORDERED  = 2,
  DEFINITION = 3
};

typedef vector<ListType> ListTypeList;

static bool
processFile(const char *file)
{
  CHtml html;

  CHtmlParserTokens tokens;

  html.read(file, tokens);

  bool in_body      = false;
  bool in_script    = false;
  int  in_table     = 0;
  int  in_table_row = 0;
  int  table_split  = false;

  ListTypeList list_type_list;

  int num_tokens = tokens.size();

  for (int i = 0; i < num_tokens; ++i) {
    const CHtmlToken *token = tokens[i];

    if      (token->isText()) {
      if (in_script || ! in_body) continue;

      CHtmlText *text = token->getText();

      string str = text->getText();

      str = CStrUtil::translate(str, "\r", "\n");
      str = CStrUtil::translate(str, "\x85", "...");
      str = CStrUtil::translate(str, "\x91\x92", "''");
      str = CStrUtil::translate(str, "\x93\x94", "\"\"");
      str = CStrUtil::translate(str, "\x96", "-");
      str = CStrUtil::translate(str, "\xa0", " ");

      string ostr;

      if (format) {
        vector<string> lines;

        CStrUtil::addLines(str, lines);

        uint num_lines = lines.size();

        for (uint j = 0; j < num_lines; ++j) {
          CHtmlNamedCharMgrInst->decodeString(lines[j], ostr);

          ostr = CStrUtil::stripSpaces(ostr);

          output_string(ostr);
        }
      }
      else {
        CHtmlNamedCharMgrInst->decodeString(str, ostr);

        ostr = CStrUtil::translate(ostr, "\n", " ");

        output_string(ostr);
      }
    }
    else if (token->isTag()) {
      CHtmlTag *tag = token->getTag();

      const CHtmlTagDef &tag_def = tag->getTagDef();

      CHtmlTagId id = tag_def.getId();

      //------

      if      (id == CHtmlTagId::BODY) {
        if (tag->isStartTag())
          in_body = true;
        else
          in_body = false;
      }
      else if (id == CHtmlTagId::H1) {
        if (tag->isStartTag()) {
          newline(2);

          output("====== ");
        }
        else {
          output(" ======");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::H2) {
        if (tag->isStartTag()) {
          newline(2);

          output("===== ");
        }
        else {
          output(" =====");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::H3) {
        if (tag->isStartTag()) {
          newline(2);

          output("==== ");
        }
        else {
          output(" ====");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::H4) {
        if (tag->isStartTag()) {
          newline(2);

          output("=== ");
        }
        else {
          output(" ===");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::H5) {
        if (tag->isStartTag()) {
          newline(2);

          output("== ");
        }
        else {
          output(" ==");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::H6) {
        if (tag->isStartTag()) {
          newline(2);

          output("== ");
        }
        else {
          output(" ==");

          newline(2);
        }
      }
      else if (id == CHtmlTagId::OL) {
        if (tag->isStartTag()) {
          if (list_type_list.empty())
            newline(2);

          list_type_list.push_back(ORDERED);
        }
        else
          list_type_list.pop_back();
      }
      else if (id == CHtmlTagId::UL) {
        if (tag->isStartTag()) {
          if (list_type_list.empty())
            newline(2);

          list_type_list.push_back(UNORDERED);
        }
        else
          list_type_list.pop_back();
      }
      else if (id == CHtmlTagId::DL) {
        if (tag->isStartTag()) {
          if (list_type_list.empty())
            newline(2);

          list_type_list.push_back(DEFINITION);
        }
        else
          list_type_list.pop_back();
      }
      else if (id == CHtmlTagId::TABLE) {
        if (tag->isStartTag()) {
          newline(2);

          ++in_table;
        }
        else
          --in_table;

        table_split = false;
      }
      else if (id == CHtmlTagId::TR) {
        if (tag->isStartTag()) {
          newline();

          ++in_table_row;
        }
        else
          --in_table_row;

        table_split = false;
      }
      else if (id == CHtmlTagId::LI ||
               id == CHtmlTagId::DT ||
               id == CHtmlTagId::DD) {
        if (tag->isStartTag()) {
          if (! in_table_row)
            newline();

          int num = list_type_list.size();

          if (num == 0)
            num = 1;

          for (int i = 0; i < num; ++i)
            output("  ");

          if (! list_type_list.empty() && list_type_list.back() == ORDERED)
            output("- ");
          else
            output("* ");
        }
      }
      else if (id == CHtmlTagId::TH) {
        if (tag->isStartTag()) {
          if (! table_split)
            output("^ ");
          else
            output(" ");
        }
        else {
          output(" ^");

          table_split = true;
        }
      }
      else if (id == CHtmlTagId::TD) {
        if (tag->isStartTag()) {
          if (! table_split)
            output("| ");
          else
            output(" ");
        }
        else {
          output(" |");

          table_split = true;
        }
      }
      else if (id == CHtmlTagId::A) {
        if (tag->isStartTag()) {
          const CHtmlTag::OptionArray &options = tag->getOptions();

          CHtmlTag::OptionArray::const_iterator p1 = options.begin();
          CHtmlTag::OptionArray::const_iterator p2 = options.end  ();

          string link_href = "";
          string link_name = "";

          for ( ; p1 != p2; ++p1) {
            const string &name = (*p1)->getName();

            if      (name == "href")
              link_href = (*p1)->getValue();
            else if (name == "name")
              link_name = (*p1)->getValue();
          }

          if (link_href != "")
            output("[[" + link_href + "|");
          else
            output("[[" + link_name + "|");
        }
        else
          output("]]");
      }
      else if (id == CHtmlTagId::SCRIPT) {
        if (tag->isStartTag())
          in_script = true;
        else
          in_script = false;
      }
      else if (id == CHtmlTagId::IMG) {
        if (! tag->isStartTag())
          continue;

        const CHtmlTag::OptionArray &options = tag->getOptions();

        CHtmlTag::OptionArray::const_iterator p1 = options.begin();
        CHtmlTag::OptionArray::const_iterator p2 = options.end  ();

        string src, al, ar;

        for ( ; p1 != p2; ++p1) {
          const string &name = (*p1)->getName();

          if      (name == "src")
            src = (*p1)->getValue();
          else if (name == "align") {
            if      ((*p1)->getValue() == "left")
              al = " ";
            else if ((*p1)->getValue() == "right")
              ar = " ";
            else if ((*p1)->getValue() == "center") {
              al = " "; ar = " ";
            }
          }
        }

        output("{{" + al + src + ar + "}}");
      }
      else if (id == CHtmlTagId::P) {
        if (! in_table) {
          if (tag->isStartTag()) {
            newline(2);

            const CHtmlTag::OptionArray &options = tag->getOptions();

            CHtmlTag::OptionArray::const_iterator p1 = options.begin();
            CHtmlTag::OptionArray::const_iterator p2 = options.end  ();

            string src, al, ar;

            for ( ; p1 != p2; ++p1) {
              const string &name = (*p1)->getName();

              if (name == "class") {
                if ((*p1)->getValue() == "MsoPlainText")
                  format = false;
                else
                  format = true;
              }
            }
          }
          else {
            newline(2);

            format = true;
          }
        }
      }
      else if (id == CHtmlTagId::B) {
        if (tag->isStartTag())
          output("**");
        else
          output("**");
      }
      else if (id == CHtmlTagId::I) {
        if (tag->isStartTag())
          output("//");
        else
          output("//");
      }
      else if (id == CHtmlTagId::U) {
        if (tag->isStartTag())
          output("__");
        else
          output("__");
      }
      else if (id == CHtmlTagId::HR) {
        if (tag->isStartTag()) {
          newline(2);

          output("____");

          newline(2);
        }
      }
    }
  }

  newline();

  return true;
}

static void
output_string(const string &str)
{
  if (str != "") {
    if (new_line && ! format)
      cout << "  ";

    if (buffer != "") {
      cout << buffer;

      buffer = "";
    }

    if (format && non_space)
      cout << " ";

    cout << str;

    new_line  = 0;
    non_space = true;
  }
}

static void
output(const string &str)
{
  buffer += str;
}

static void
newline(int num)
{
  if (buffer != "") {
    cout << buffer;

    buffer = "";
  }

  while (new_line < num) {
    if (new_line && ! format)
      cout << "  ";

    cout << endl;

    ++new_line;

    non_space = false;
  }
}
