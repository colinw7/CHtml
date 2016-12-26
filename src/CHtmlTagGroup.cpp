#include <CHtmlTagGroup.h>

CHtmlTagGroup::
CHtmlTagGroup(const CHtmlTokenArray &tokens, int *i)
{
  subGroup_ = new CHtmlTagSubGroup(tokens, i);
}

CHtmlTagSubGroup::
CHtmlTagSubGroup(CHtmlToken *token)
{
  CHtmlTagSubGroupToken *subValue = new CHtmlTagSubGroupToken(token);

  subValues_.push_back(subValue);
}

CHtmlTagSubGroup::
CHtmlTagSubGroup(const CHtmlTokenArray &tokens, int *i)
{
  int num_tokens = tokens.size();

  if (*i >= num_tokens)
    return;

  CHtmlToken *token = tokens[(*i)++];

  if (! token->isTag()) {
    CHtmlTagSubGroupToken *subValue = new CHtmlTagSubGroupToken(token);

    subValues_.push_back(subValue);

    return;
  }

  CHtmlTag *tag = token->getTag()->getTag();

  if (tag->getIsEndTag()) {
    CHtmlTagSubGroupToken *subValue = new CHtmlTagSubGroupToken(token);

    subValues_.push_back(subValue);

    return;
  }

  CHtmlTagSubGroup *subGroup = new CHtmlTagSubGroup(token);

  while (*i < num_tokens) {
    token = tokens[(*i)++];

    if (! token->isTag()) {
      subGroup->add(token);

      continue;
    }

    CHtmlTag *tag1 = token->getTag()->getTag();

    if (tag->getName() != tag1->getName() || ! tag1->getIsEndTag())
      CHtmlTagSubGroup *subGroup1 = CHtmlTagSubGroup(tokens, i);

      subGroup->add(subGroup1);

      continue;
    }

    break;
  }

  CHtmlTagSubGroupSubGroup *subValue = new CHtmlTagSubGroupSubGroup(subGroup);

  subValues_.push_back(subValue);
}
