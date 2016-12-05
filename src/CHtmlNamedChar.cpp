#include <CHtmlNamedChar.h>
#include <cstring>
#include <iostream>

CHtmlNamedChar
CHtmlNamedCharMgr::
named_chars_[] = {
  CHtmlNamedChar("AElig" , 198, "\u00c6"),
  CHtmlNamedChar("Aacute", 193, "\u00c1"),
  CHtmlNamedChar("Acirc" , 194, "\u00c2"),
  CHtmlNamedChar("Agrave", 192, "\u00c0"),
  CHtmlNamedChar("Aring" , 197, "\u00c5"),
  CHtmlNamedChar("Atilde", 195, "\u00c3"),
  CHtmlNamedChar("Auml"  , 196, "\u00c4"),
  CHtmlNamedChar("Ccedil", 199, "\u00c7"),
  CHtmlNamedChar("ETH"   , 208, "\u00d0"),
  CHtmlNamedChar("Eacute", 201, "\u00c9"),
  CHtmlNamedChar("Ecirc" , 202, "\u00ca"),
  CHtmlNamedChar("Egrave", 200, "\u00c8"),
  CHtmlNamedChar("Euml"  , 203, "\u00cb"),
  CHtmlNamedChar("Iacute", 205, "\u00cd"),
  CHtmlNamedChar("Icirc" , 206, "\u00ce"),
  CHtmlNamedChar("Igrave", 204, "\u00cc"),
  CHtmlNamedChar("Iuml"  , 207, "\u00cf"),
  CHtmlNamedChar("Ntilde", 209, "\u00d1"),
  CHtmlNamedChar("Oacute", 211, "\u00d3"),
  CHtmlNamedChar("Ocirc" , 212, "\u00d4"),
  CHtmlNamedChar("Ograve", 210, "\u00d2"),
  CHtmlNamedChar("Oslash", 216, "\u00d8"),
  CHtmlNamedChar("Otilde", 213, "\u00d5"),
  CHtmlNamedChar("Ouml"  , 214, "\u00d6"),
  CHtmlNamedChar("THORN" , 222, "\u00de"),
  CHtmlNamedChar("Uacute", 218, "\u00da"),
  CHtmlNamedChar("Ucirc" , 219, "\u00db"),
  CHtmlNamedChar("Ugrave", 217, "\u00d9"),
  CHtmlNamedChar("Uuml"  , 220, "\u00dc"),
  CHtmlNamedChar("Yacute", 221, "\u00dd"),
  CHtmlNamedChar("aacute", 225, "\u00e1"),
  CHtmlNamedChar("acute" , 180, "\u00b4"),
  CHtmlNamedChar("acirc" , 226, "\u00e2"),
  CHtmlNamedChar("aelig" , 230, "\u00e6"),
  CHtmlNamedChar("agrave", 224, "\u00e0"),
  CHtmlNamedChar("amp"   ,  38, "&"),
  CHtmlNamedChar("apos"  ,  39, "'"),
  CHtmlNamedChar("aring" , 229, "\u00e5"),
  CHtmlNamedChar("atilde", 227, "\u00e3"),
  CHtmlNamedChar("auml"  , 228, "\u00e4"),
  CHtmlNamedChar("brvbar", 166, "\u00a6"),
  CHtmlNamedChar("ccedil", 231, "\u00e7"),
  CHtmlNamedChar("cedil" , 184, "\u00b8"),
  CHtmlNamedChar("cent"  , 162, "\u00a2"),
  CHtmlNamedChar("copy"  , 169, "\u00a9"),
  CHtmlNamedChar("curren", 164, "\u00a4"),
  CHtmlNamedChar("deg"   , 176, "\u00b0"),
  CHtmlNamedChar("divide", 247, "\u00f7"),
  CHtmlNamedChar("eacute", 233, "\u00e9"),
  CHtmlNamedChar("ecirc" , 234, "\u00ea"),
  CHtmlNamedChar("egrave", 232, "\u00e8"),
  CHtmlNamedChar("eth"   , 240, "\u00f0"),
  CHtmlNamedChar("euml"  , 235, "\u00eb"),
  CHtmlNamedChar("frac12", 189, "\u00bd"),
  CHtmlNamedChar("frac14", 188, "\u00bc"),
  CHtmlNamedChar("frac34", 190, "\u00be"),
  CHtmlNamedChar("gt"    ,  62, ">"),
  CHtmlNamedChar("iacute", 237, "\u00ed"),
  CHtmlNamedChar("icirc" , 238, "\u00ee"),
  CHtmlNamedChar("iexcl" , 161, "\u00a1"),
  CHtmlNamedChar("igrave", 236, "\u00ec"),
  CHtmlNamedChar("iuml"  , 239, "\u00ef"),
  CHtmlNamedChar("iquest", 191, "\u00df"),
  CHtmlNamedChar("laquo" , 171, "\u00ab"),
  CHtmlNamedChar("lt"    ,  60, "<"),
  CHtmlNamedChar("macr"  , 175, "\u00af"),
  CHtmlNamedChar("micro" , 181, "\u00b5"),
  CHtmlNamedChar("middot", 183, "\u00b7"),
  CHtmlNamedChar("nbsp"  , 160, "\u00a0"),
  CHtmlNamedChar("not"   , 172, "\u00ac"),
  CHtmlNamedChar("ntilde", 241, "\u00f1"),
  CHtmlNamedChar("oacute", 243, "\u00f3"),
  CHtmlNamedChar("ocirc" , 244, "\u00f4"),
  CHtmlNamedChar("ograve", 242, "\u00f2"),
  CHtmlNamedChar("ordf"  , 170, "\u00aa"),
  CHtmlNamedChar("ordm"  , 186, "\u00ba"),
  CHtmlNamedChar("oslash", 248, "\u00f8"),
  CHtmlNamedChar("otilde", 245, "\u00f5"),
  CHtmlNamedChar("ouml"  , 246, "\u00f6"),
  CHtmlNamedChar("para"  , 182, "\u00b6"),
  CHtmlNamedChar("plusmn", 177, "\u00b1"),
  CHtmlNamedChar("pound" , 163, "\u00a3"),
  CHtmlNamedChar("quot"  ,  34, "\""),
  CHtmlNamedChar("raquo" , 187, "\u00bb"),
  CHtmlNamedChar("reg"   , 174, "\u00ae"),
  CHtmlNamedChar("sect"  , 167, "\u00a7"),
  CHtmlNamedChar("shy"   , 173, "\u00ad"),
  CHtmlNamedChar("sup1"  , 185, "\u00b9"),
  CHtmlNamedChar("sup2"  , 178, "\u00b2"),
  CHtmlNamedChar("sup3"  , 179, "\u00b3"),
  CHtmlNamedChar("szlig" , 223, "\u00df"),
  CHtmlNamedChar("thorn" , 254, "\u00fe"),
  CHtmlNamedChar("times" , 215, "\u00d7"),
  CHtmlNamedChar("uacute", 250, "\u00fa"),
  CHtmlNamedChar("ucirc" , 251, "\u00fb"),
  CHtmlNamedChar("ugrave", 249, "\u00f9"),
  CHtmlNamedChar("uml"   , 168, "\u00a8"),
  CHtmlNamedChar("uuml"  , 252, "\u00fc"),
  CHtmlNamedChar("yacute", 253, "\u00fd"),
  CHtmlNamedChar("yen"   , 165, "\u00a5"),
  CHtmlNamedChar("yuml"  , 255, "\u00ff"),
};

uint CHtmlNamedCharMgr::num_named_chars_ =
  sizeof(CHtmlNamedCharMgr::named_chars_)/sizeof(CHtmlNamedCharMgr::named_chars_[0]);

CHtmlNamedCharMgr *
CHtmlNamedCharMgr::
getInstance()
{
  static CHtmlNamedCharMgr *instance_ = NULL;

  if (instance_ == NULL)
    instance_ = new CHtmlNamedCharMgr();

  return instance_;
}

CHtmlNamedCharMgr::
CHtmlNamedCharMgr() :
 name_value_map_(), value_name_map_()
{
  for (uint i = 1; i < num_named_chars_; ++i) {
    name_value_map_[named_chars_[i].name ] = &named_chars_[i];
    value_name_map_[named_chars_[i].value] = &named_chars_[i];
  }
}

bool
CHtmlNamedCharMgr::
lookup(const std::string &name, CHtmlNamedChar **named_char) const
{
  auto p = name_value_map_.find(name);

  if (p == name_value_map_.end())
    return false;

  *named_char = p->second;

  return true;
}

bool
CHtmlNamedCharMgr::
lookup(int value, CHtmlNamedChar **named_char) const
{
  auto p = value_name_map_.find(value);

  if (p == value_name_map_.end())
    return false;

  *named_char = p->second;

  return true;
}

std::string
CHtmlNamedCharMgr::
encodeString(const std::string &str) const
{
  static const char *encode_chars = "\'\"&";

  CHtmlNamedChar *named_char;

  std::string str1;

  uint len = str.size();

  for (uint i = 0; i < len; ++i) {
    if (strchr(encode_chars, str[i]) != NULL) {
      lookup(int(str[i]), &named_char);

      str1 += "&";
      str1 += named_char->name;
      str1 += ";";
    }
    else
      str1 += str[i];
  }

  return str1;
}

bool
CHtmlNamedCharMgr::
decodeString(const std::string &istr, std::string &ostr) const
{
  ostr = "";

  uint len = istr.size();

  for (uint i = 0; i < len; ++i) {
    if (istr[i] == '&') {
      uint j1 = i + 1;
      uint j2 = j1;

      while (j2 < len && istr[j2] != ';')
        ++j2;

      if (istr[j2] == ';') {
        std::string name = istr.substr(j1, j2 - j1);

        CHtmlNamedChar *named_char;

        if (lookup(name, &named_char))
          ostr += (*named_char).str;
        else
          ostr += istr.substr(j1 - 1, j2 - j1 + 2);
      }
      else
        ostr += istr.substr(i);

      i = j2;
    }
    else {
      int c1 = istr[i];

      if (c1 > 127)
        std::cerr << "Invalid char value " << c1 << std::endl;

      ostr += istr[i];
    }
  }

  return true;
}
