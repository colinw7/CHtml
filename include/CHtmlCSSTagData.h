#ifndef CHtmlCSSTagData_H
#define CHtmlCSSTagData_H

#include <CHtmlLib.h>
#include <CCSS.h>

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

  bool isNthChild(int n) const override {
    if (! tag_->parent())
      return false;

    const CHtmlTag::Children &children = tag_->parent()->children();

    int i = 1;

    for (const auto &child : children) {
      CHtmlTag *childTag = child->getTag();
      if (! childTag) continue;

      if (childTag == tag_)
        return (i == n);

      ++i;
    }

    return false;
  }

  bool isInputValue(const std::string &) const override {
    //TODO
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

#endif
