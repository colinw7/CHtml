#include <CHtmlTag.h>
#include <CHtmlTagDef.h>
#include <CHtmlToken.h>
#include <CStrUtil.h>

CHtmlTag::
CHtmlTag(const std::string &name, const CHtmlTagOptionArray &options, bool endTag) :
 name_(name), options_(options), endTag_(endTag), tagDef_(CHtmlTagDefLookupInst->lookup(name_))
{
}

bool
CHtmlTag::
isInline() const
{
  return tagDef_.isInline();
}

std::string
CHtmlTag::
getTagName() const
{
  if (isStartTag())
    return "<" + getName() + ">";
  else
    return "</" + getName() + ">";
}

bool
CHtmlTag::
isEmpty() const
{
  return tagDef_.isEmpty();
}

const CHtmlTagId &
CHtmlTag::
getTagId() const
{
  return tagDef_.getId();
}

void
CHtmlTag::
addChild(CHtmlToken *child)
{
  children_.push_back(child);

  CHtmlTag *tag = child->getTag();

  if (tag)
    tag->setParent(this);
}

bool
CHtmlTag::
hasOptionName(const std::string &name) const
{
  for (const auto &option : options_) {
    if (option->getName() == name)
      return true;
  }

  return false;
}

bool
CHtmlTag::
hasOptionNameValue(const std::string &name, const std::string &value) const
{
  for (const auto &option : options_) {
    if (option->getName() == name)
      return (option->getValue() == value);
  }

  return false;
}

bool
CHtmlTag::
hasOptionNameSubValue(const std::string &name, const std::string &value) const
{
  for (const auto &option : options_) {
    if (option->getName() != name)
      continue;

    std::vector<std::string> words;

    CStrUtil::toWords(option->getValue(), words);

    for (const auto &word : words) {
      if (word == value)
        return true;
    }
  }

  return false;
}

bool
CHtmlTag::
hasOptionNameStart(const std::string &name, const std::string &value) const
{
  for (const auto &option : options_) {
    if (option->getName() != name)
      continue;

    auto p = option->getValue().find(value);

    if (p != std::string::npos)
      return true;
  }

  return false;
}

std::string
CHtmlTag::
getOptionValue(const std::string &name) const
{
  for (const auto &option : options_) {
    if (option->getName() == name)
      return option->getValue();
  }

  return "";
}

//------

CHtmlTagOption::
CHtmlTagOption(const std::string &name, const std::string &value) :
 name_(name), value_(value)
{
}
