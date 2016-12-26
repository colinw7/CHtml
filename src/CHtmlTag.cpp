#include <CHtmlTag.h>
#include <CHtmlTagDef.h>

CHtmlTag::
CHtmlTag(const std::string &name, const CHtmlTagOptionArray &options, bool endTag) :
 name_(name), options_(options), endTag_(endTag), tagDef_(CHtmlTagDefLookupInst->lookup(name_))
{
}

CHtmlTagOption::
CHtmlTagOption(const std::string &name, const std::string &value) :
 name_(name), value_(value)
{
}
