#ifndef CHtmlTag_H
#define CHtmlTag_H

#include <CHtmlTypes.h>
#include <string>
#include <vector>
#include <sys/types.h>

class CHtmlTagOption {
 public:
  CHtmlTagOption(const std::string &name, const std::string &value);

  const std::string &getName () const { return name_ ; }
  const std::string &getValue() const { return value_; }

 private:
  std::string name_;
  std::string value_;
};

//------

class CHtmlTag {
 public:
  typedef std::vector<CHtmlTagOption *> OptionArray;
  typedef std::vector<CHtmlToken *>     Children;

 public:
  CHtmlTag(const std::string &name, const OptionArray &options, bool end_tag);

  const std::string &getName() const { return name_; }

  uint getNumOptions() const { return options_.size(); }

  const OptionArray &getOptions() const { return options_; }

  const CHtmlTagOption *getOption(int i) const { return options_[i]; }

  bool hasOptionName(const std::string &name) const;

  bool hasOptionNameValue(const std::string &name, const std::string &value) const;

  bool hasOptionNameSubValue(const std::string &name, const std::string &value) const;

  bool hasOptionNameStart(const std::string &name, const std::string &value) const;

  std::string getOptionValue(const std::string &name) const;

  bool isEndTag  () const { return   endTag_; }
  bool isStartTag() const { return ! endTag_; }

  bool isInline() const;

  std::string getTagName() const;

  bool isEmpty() const;

  const CHtmlTagDef &getTagDef() const { return tagDef_; }

  const CHtmlTagId &getTagId() const;

  const Children &children() const { return children_; }

  CHtmlTag *parent() { return parent_; }
  void setParent(CHtmlTag *parent) { parent_ = parent; }

  void addChild(CHtmlToken *child);

 private:
  CHtmlTag*          parent_ { nullptr };
  std::string        name_;
  OptionArray        options_;
  bool               endTag_ { false };
  const CHtmlTagDef& tagDef_;
  Children           children_;
};

#endif
