#include <CHtmlTagDef.h>
#include <CStrUtil.h>

namespace {

CHtmlTagDef tagDefs[] = {
  CHtmlTagDef(CHtmlTagId::NONE      , ""          , CHtmlTextType::NONE   ),
  CHtmlTagDef(CHtmlTagId::A         , "a"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ADDRESS   , "address"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::APPLET    , "applet"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::AREA      , "area"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::B         , "b"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BASE      , "base"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BASEFONT  , "basefont"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BGSOUND   , "bgsound"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BIG       , "big"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BLINK     , "blink"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BLOCKQUOTE, "blockquote", CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BODY      , "body"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BR        , "br"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CANVAS    , "canvas"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CAPTION   , "caption"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CENTER    , "center"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CITE      , "cite"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CODE      , "code"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DD        , "dd"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DFN       , "dfn"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DIR       , "dir"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DIV       , "div"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DL        , "dl"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DT        , "dt"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::EM        , "em"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FONT      , "font"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FORM      , "form"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FRAME     , "frame"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FRAMESET  , "frameset"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H1        , "h1"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H2        , "h2"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H3        , "h3"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H4        , "h4"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H5        , "h5"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H6        , "h6"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HEAD      , "head"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HR        , "hr"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HTML      , "html"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::I         , "i"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::IMG       , "img"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::INPUT     , "input"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ISINDEX   , "isindex"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::KBD       , "kbd"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LI        , "li"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LINK      , "link"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LISTING   , "listing"   , CHtmlTextType::LITERAL),
  CHtmlTagDef(CHtmlTagId::MAP       , "map"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::MARQUEE   , "marquee"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::MENU      , "menu"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::META      , "meta"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NEXTID    , "nextid"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOBR      , "nobr"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOFRAMES  , "noframes"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOSCRIPT  , "noscript"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::OL        , "ol"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::OPTION    , "option"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::P         , "p"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PARAM     , "param"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PRE       , "pre"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PLAINTEXT , "plaintext" , CHtmlTextType::RAW    ),
  CHtmlTagDef(CHtmlTagId::S         , "s"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SAMP      , "samp"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SCRIPT    , "script"    , CHtmlTextType::STYLE  ),
  CHtmlTagDef(CHtmlTagId::SELECT    , "select"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SMALL     , "small"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SPAN      , "span"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STRIKE    , "strike"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STRONG    , "strong"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STYLE     , "style"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SUB       , "sub"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SUP       , "sup"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TABLE     , "table"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TD        , "td"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TEXTAREA  , "textarea"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TH        , "th"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TITLE     , "title"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TR        , "tr"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TT        , "tt"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::U         , "u"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::UL        , "ul"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::VAR       , "var"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::WBR       , "wbr"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::XMP       , "xmp"       , CHtmlTextType::LITERAL),
  CHtmlTagDef(CHtmlTagId::COMMENT   , "!--"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DOCTYPE   , "!doctype"  , CHtmlTextType::PLAIN  ),
};

uint numTagDefs = sizeof(tagDefs)/sizeof(CHtmlTagDef);

}

CHtmlTagDefLookup *
CHtmlTagDefLookup::
instance()
{
  static CHtmlTagDefLookup *inst;

  if (! inst)
    inst = new CHtmlTagDefLookup;

  return inst;
}

CHtmlTagDefLookup::
CHtmlTagDefLookup()
{
  for (uint i = 1; i < numTagDefs; i++) {
    const CHtmlTagDef &tagDef = tagDefs[i];

    nameToTag_[tagDef.getName()] = &tagDef;
    idToTag_  [tagDef.getId  ()] = &tagDef;
  }
}

const CHtmlTagDef &
CHtmlTagDefLookup::
lookup(const std::string &name) const
{
  std::string name1 = CStrUtil::toLower(name);

  auto p = nameToTag_.find(name1);

  if (p != nameToTag_.end())
    return *(*p).second;

  return tagDefs[0];
}

const CHtmlTagDef &
CHtmlTagDefLookup::
lookup(CHtmlTagId id) const
{
  auto p = idToTag_.find(id);

  if (p != idToTag_.end())
    return *(*p).second;

  return tagDefs[0];
}
