#include <CHtmlTag.h>
#include <CHtmlTagDef.h>

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

//------

CHtmlTagOption::
CHtmlTagOption(const std::string &name, const std::string &value) :
 name_(name), value_(value)
{
}
