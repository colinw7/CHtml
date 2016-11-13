#ifndef CHtmlTypes_H
#define CHtmlTypes_H

#include <vector>

enum class CHtmlTagId {
  NONE,
  A,
  ADDRESS,
  APPLET,
  AREA,
  B,
  BASE,
  BASEFONT,
  BGSOUND,
  BIG,
  BLINK,
  BLOCKQUOTE,
  BODY,
  BR,
  CANVAS,
  CAPTION,
  CENTER,
  CITE,
  CODE,
  DD,
  DFN,
  DIR,
  DIV,
  DL,
  DT,
  EM,
  FONT,
  FORM,
  FRAME,
  FRAMESET,
  H1,
  H2,
  H3,
  H4,
  H5,
  H6,
  HEAD,
  HR,
  HTML,
  I,
  IMG,
  INPUT,
  ISINDEX,
  KBD,
  LI,
  LINK,
  LISTING,
  MAP,
  MARQUEE,
  MENU,
  META,
  NEXTID,
  NOBR,
  NOFRAMES,
  NOSCRIPT,
  OL,
  OPTION,
  P,
  PARAM,
  PLAINTEXT,
  PRE,
  S,
  SAMP,
  SCRIPT,
  SELECT,
  SMALL,
  SPAN,
  STRIKE,
  STRONG,
  STYLE,
  SUB,
  SUP,
  TABLE,
  TD,
  TEXTAREA,
  TH,
  TITLE,
  TR,
  TT,
  U,
  UL,
  VAR,
  WBR,
  XMP,
  COMMENT,
  DOCTYPE
};

enum class CHtmlTextType {
  NONE,
  PLAIN,
  STYLE,
  LITERAL,
  RAW,
};

class CHtmlParserTokens;
class CHtmlParser;
class CHtmlNamedChar;
class CHtmlTagDef;
class CHtmlTagOption;
class CHtmlToken;

typedef std::vector<CHtmlToken *>     CHtmlTokenArray;
typedef std::vector<CHtmlTagOption *> CHtmlTagOptionArray;

#endif
