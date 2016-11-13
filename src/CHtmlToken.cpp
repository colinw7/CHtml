#include <CHtmlToken.h>

CHtmlToken::
CHtmlToken(CHtmlTokenType type) :
 type_(type)
{
}

CHtmlToken::
~CHtmlToken()
{
}

CHtmlCommentToken::
CHtmlCommentToken(CHtmlComment *comment) :
 CHtmlToken(CHtmlTokenType::COMMENT), comment_(comment)
{
}

CHtmlTagToken::
CHtmlTagToken(CHtmlTag *tag) :
 CHtmlToken(CHtmlTokenType::TAG), tag_(tag)
{
}

CHtmlTextToken::
CHtmlTextToken(CHtmlText *text) :
 CHtmlToken(CHtmlTokenType::TEXT), text_(text)
{
}
