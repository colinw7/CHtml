#ifndef CHtmlNamedChar_H
#define CHtmlNamedChar_H

#include <string>
#include <map>
#include <sys/types.h>

#define CHtmlNamedCharMgrInst CHtmlNamedCharMgr::getInstance()

struct CHtmlNamedChar {
  CHtmlNamedChar(const char *name_, uint value_, const char *str_) :
   name(name_), value(value_), str(str_) {
  }

  const char *name  { nullptr };
  uint        value { 0 };
  const char *str   { nullptr };
};

//------

class CHtmlNamedCharMgr {
 private:
  using NameValueMap = std::map<std::string,CHtmlNamedChar *>;
  using ValueNameMap = std::map<uint       ,CHtmlNamedChar *>;

 public:
  static CHtmlNamedCharMgr *getInstance();

  CHtmlNamedCharMgr();

  bool lookup(const std::string &name, CHtmlNamedChar **named_char) const;
  bool lookup(int value, CHtmlNamedChar **named_char) const;

  std::string encodeString(const std::string &str) const;
  bool        decodeString(const std::string &istr, std::string &ostr) const;

 private:
  static CHtmlNamedChar namedChars_[];
  static uint           numNamedChars_;

  NameValueMap nameValueMap_;
  ValueNameMap valueNameMap_;
};

#endif
