#ifndef CHtmlTagDef_H
#define CHtmlTagDef_H

#include <CHtmlTypes.h>
#include <string>
#include <map>
#include <set>
#include <sys/types.h>

#define CHtmlTagDefLookupInst CHtmlTagDefLookup::instance()

class CHtmlTagDef;

class CHtmlTagDefLookup {
 public:
  static CHtmlTagDefLookup *instance();

 ~CHtmlTagDefLookup() { }

  const CHtmlTagDef &lookup(const std::string &name) const;
  const CHtmlTagDef &lookup(CHtmlTagId id) const;

 private:
  CHtmlTagDefLookup();

 private:
  typedef std::map<std::string, const CHtmlTagDef *> NameToTag;
  typedef std::map<CHtmlTagId , const CHtmlTagDef *> IdToTag;
  typedef std::set<CHtmlTagId>                       InlineTags;

  NameToTag  nameToTag_;
  IdToTag    idToTag_;
  InlineTags inlineTags_;
};

//---

class CHtmlTagDef {
 public:
  CHtmlTagDef(CHtmlTagId id, const std::string &name, CHtmlTextType textType) :
   id_(id), name_(name), textType_(textType) {
  }

  CHtmlTagId         getId      () const { return id_; }
  const std::string &getName    () const { return name_; }
  CHtmlTextType      getTextType() const { return textType_; }

  bool isInline() const { return inline_; }
  void setInline(bool b) { inline_ = b; }

  bool isValid() const { return id_ != CHtmlTagId::NONE; }

 private:
  CHtmlTagId    id_;
  std::string   name_;
  CHtmlTextType textType_ { CHtmlTextType::NONE };
  bool          inline_ { false };
};

#endif
