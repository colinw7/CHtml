#include <CHtmlTagDef.h>
#include <CStrUtil.h>

namespace {

CHtmlTagDef tagDefs[] = {
  CHtmlTagDef(CHtmlTagId::NONE      , ""          , CHtmlTextType::NONE   ),
  CHtmlTagDef(CHtmlTagId::A         , "a"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ABBR      , "abbr"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ACRONYM   , "acronym"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ADDRESS   , "address"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::APPLET    , "applet"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::AREA      , "area"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ARTICLE   , "article"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ASIDE     , "aside"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::AUDIO     , "audio"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::B         , "b"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BASE      , "base"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BASEFONT  , "basefont"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BGSOUND   , "bgsound"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BIG       , "big"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BLINK     , "blink"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BLOCKQUOTE, "blockquote", CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BODY      , "body"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BUTTON    , "button"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::BR        , "br"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CANVAS    , "canvas"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CAPTION   , "caption"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CENTER    , "center"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CITE      , "cite"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::CODE      , "code"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DETAILS   , "details"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DD        , "dd"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DEL       , "del"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DFN       , "dfn"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DIR       , "dir"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DIV       , "div"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DL        , "dl"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::DT        , "dt"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::EM        , "em"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FIELDSET  , "fieldset"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FONT      , "font"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FORM      , "form"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FOOTER    , "footer"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FRAME     , "frame"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::FRAMESET  , "frameset"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H1        , "h1"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H2        , "h2"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H3        , "h3"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H4        , "h4"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H5        , "h5"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::H6        , "h6"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HEAD      , "head"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HEADER    , "header"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HGROUP    , "hgroup"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HR        , "hr"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::HTML      , "html"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::I         , "i"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::IFRAME    , "iframe"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::IMG       , "img"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::INPUT     , "input"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::INS       , "ins"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::ISINDEX   , "isindex"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::KBD       , "kbd"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LABEL     , "label"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LEGEND    , "legend"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LI        , "li"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LINK      , "link"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::LISTING   , "listing"   , CHtmlTextType::LITERAL),
  CHtmlTagDef(CHtmlTagId::MAP       , "map"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::MARQUEE   , "marquee"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::MENU      , "menu"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::META      , "meta"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NAV       , "nav"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NEXTID    , "nextid"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOBR      , "nobr"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOFRAMES  , "noframes"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::NOSCRIPT  , "noscript"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::OL        , "ol"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::OPTION    , "option"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::OUTPUT    , "output"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::P         , "p"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PARAM     , "param"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PRE       , "pre"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::PLAINTEXT , "plaintext" , CHtmlTextType::RAW    ),
  CHtmlTagDef(CHtmlTagId::S         , "s"         , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SAMP      , "samp"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SCRIPT    , "script"    , CHtmlTextType::STYLE  ),
  CHtmlTagDef(CHtmlTagId::SECTION   , "section"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SELECT    , "select"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SMALL     , "small"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SPAN      , "span"      , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STRIKE    , "strike"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STRONG    , "strong"    , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::STYLE     , "style"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SUB       , "sub"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SUMMARY   , "summary"   , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::SUP       , "sup"       , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TABLE     , "table"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TBODY     , "tbody"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TD        , "td"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TEXTAREA  , "textarea"  , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TFOOT     , "tfoot"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TH        , "th"        , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::THEAD     , "thead"     , CHtmlTextType::PLAIN  ),
  CHtmlTagDef(CHtmlTagId::TIME      , "time"      , CHtmlTextType::PLAIN  ),
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
  inlineTags_ = {{ CHtmlTagId::B      , CHtmlTagId::BIG     , CHtmlTagId::I     ,
                   CHtmlTagId::SMALL  , CHtmlTagId::TT      , CHtmlTagId::ABBR  ,
                   CHtmlTagId::ACRONYM, CHtmlTagId::CITE    , CHtmlTagId::CODE  ,
                   CHtmlTagId::DFN    , CHtmlTagId::EM      , CHtmlTagId::KBD   ,
                   CHtmlTagId::STRONG , CHtmlTagId::SAMP    , CHtmlTagId::TIME  ,
                   CHtmlTagId::VAR    , CHtmlTagId::A       , CHtmlTagId::BDO   ,
                   CHtmlTagId::BR     , CHtmlTagId::IMG     , CHtmlTagId::MAP   ,
                   CHtmlTagId::OBJECT , CHtmlTagId::Q       , CHtmlTagId::SCRIPT,
                   CHtmlTagId::SPAN   , CHtmlTagId::SUB     , CHtmlTagId::SUP   ,
                   CHtmlTagId::BUTTON , CHtmlTagId::INPUT   , CHtmlTagId::LABEL ,
                   CHtmlTagId::SELECT , CHtmlTagId::TEXTAREA }};

  emptyTags_ = {{ CHtmlTagId::AREA, CHtmlTagId::BR, CHtmlTagId::HR, CHtmlTagId::IMG,
                  CHtmlTagId::INPUT, CHtmlTagId::LINK, CHtmlTagId::META, CHtmlTagId::WBR }};

  metaTags_ = {{ CHtmlTagId::BASE  , CHtmlTagId::LINK , CHtmlTagId::META    , CHtmlTagId::NOSCRIPT,
                 CHtmlTagId::SCRIPT, CHtmlTagId::STYLE, CHtmlTagId::TEMPLATE, CHtmlTagId::TITLE }};

  // CHtmlTagId::AREA (if it is a descendant of a map element)
  flowTags_ = {{ CHtmlTagId::A, CHtmlTagId::ABBR, CHtmlTagId::ADDRESS, CHtmlTagId::AREA,
                 CHtmlTagId::ARTICLE, CHtmlTagId::ASIDE, CHtmlTagId::AUDIO, CHtmlTagId::B,
                 CHtmlTagId::BDI, CHtmlTagId::BDO, CHtmlTagId::BLOCKQUOTE, CHtmlTagId::BR,
                 CHtmlTagId::BUTTON, CHtmlTagId::CANVAS, CHtmlTagId::CITE, CHtmlTagId::CODE,
                 CHtmlTagId::DATA, CHtmlTagId::DATALIST, CHtmlTagId::DEL, CHtmlTagId::DFN,
                 CHtmlTagId::DIV, CHtmlTagId::DL, CHtmlTagId::EM, CHtmlTagId::EMBED,
                 CHtmlTagId::FIELDSET, CHtmlTagId::FIGURE, CHtmlTagId::FOOTER,
                 CHtmlTagId::FORM, CHtmlTagId::H1, CHtmlTagId::H2, CHtmlTagId::H3,
                 CHtmlTagId::H4, CHtmlTagId::H5, CHtmlTagId::H6, CHtmlTagId::HEADER,
                 CHtmlTagId::HR, CHtmlTagId::I, CHtmlTagId::IFRAME, CHtmlTagId::IMG,
                 CHtmlTagId::INPUT, CHtmlTagId::INS, CHtmlTagId::KBD, CHtmlTagId::KEYGEN,
                 CHtmlTagId::LABEL, CHtmlTagId::MAIN, CHtmlTagId::MAP, CHtmlTagId::MARK,
                 CHtmlTagId::MATH, CHtmlTagId::METER, CHtmlTagId::NAV, CHtmlTagId::NOSCRIPT,
                 CHtmlTagId::OBJECT, CHtmlTagId::OL, CHtmlTagId::OUTPUT, CHtmlTagId::P,
                 CHtmlTagId::PRE, CHtmlTagId::PROGRESS, CHtmlTagId::Q, CHtmlTagId::RUBY,
                 CHtmlTagId::S, CHtmlTagId::SAMP, CHtmlTagId::SCRIPT, CHtmlTagId::SECTION,
                 CHtmlTagId::SELECT, CHtmlTagId::SMALL, CHtmlTagId::SPAN, CHtmlTagId::STRONG,
                 CHtmlTagId::SUB, CHtmlTagId::SUP, CHtmlTagId::SVG, CHtmlTagId::TABLE,
                 CHtmlTagId::TEMPLATE, CHtmlTagId::TEXTAREA, CHtmlTagId::TIME,
                 CHtmlTagId::U, CHtmlTagId::UL, CHtmlTagId::VAR, CHtmlTagId::VIDEO,
                 CHtmlTagId::WBR, CHtmlTagId::TEXT }};

  sectionTags_ = {{ CHtmlTagId::ARTICLE, CHtmlTagId::ASIDE, CHtmlTagId::NAV,
                    CHtmlTagId::SECTION }};

  headingTags_ = {{ CHtmlTagId::H1, CHtmlTagId::H2, CHtmlTagId::H3,
                    CHtmlTagId::H4, CHtmlTagId::H5, CHtmlTagId::H6 }};

  // CHtmlTagId::AREA (if it is a descendant of a map element)
  phrasingTags_ = {{ CHtmlTagId::A, CHtmlTagId::ABBR, CHtmlTagId::AUDIO, CHtmlTagId::B,
                     CHtmlTagId::BDI, CHtmlTagId::BDO, CHtmlTagId::BR, CHtmlTagId::BUTTON,
                     CHtmlTagId::CANVAS, CHtmlTagId::CITE, CHtmlTagId::CODE, CHtmlTagId::DATA,
                     CHtmlTagId::DATALIST, CHtmlTagId::DEL, CHtmlTagId::DFN, CHtmlTagId::EM,
                     CHtmlTagId::EMBED, CHtmlTagId::I, CHtmlTagId::IFRAME, CHtmlTagId::IMG,
                     CHtmlTagId::INPUT, CHtmlTagId::INS, CHtmlTagId::KBD, CHtmlTagId::KEYGEN,
                     CHtmlTagId::LABEL, CHtmlTagId::MAP, CHtmlTagId::MARK, CHtmlTagId::MATH,
                     CHtmlTagId::METER, CHtmlTagId::NOSCRIPT, CHtmlTagId::OBJECT,
                     CHtmlTagId::OUTPUT, CHtmlTagId::PROGRESS, CHtmlTagId::Q, CHtmlTagId::RUBY,
                     CHtmlTagId::S, CHtmlTagId::SAMP, CHtmlTagId::SCRIPT, CHtmlTagId::SELECT,
                     CHtmlTagId::SMALL, CHtmlTagId::SPAN, CHtmlTagId::STRONG, CHtmlTagId::SUB,
                     CHtmlTagId::SUP, CHtmlTagId::SVG, CHtmlTagId::TEMPLATE,
                     CHtmlTagId::TEXTAREA, CHtmlTagId::TIME, CHtmlTagId::U, CHtmlTagId::VAR,
                     CHtmlTagId::VIDEO, CHtmlTagId::WBR, CHtmlTagId::TEXT }};

  embedTags_ = {{ CHtmlTagId::AUDIO, CHtmlTagId::CANVAS, CHtmlTagId::EMBED,
                  CHtmlTagId::IFRAME, CHtmlTagId::IMG, CHtmlTagId::MATH,
                  CHtmlTagId::OBJECT, CHtmlTagId::SVG, CHtmlTagId::VIDEO }};

  // CHtmlTagId::AUDIO (if the controls attribute is present),
  // CHtmlTagId::IMG (if the usemap attribute is present),
  // CHtmlTagId::INPUT (if the type attribute is not in the Hidden state)
  // CHtmlTagId::OBJECT (if the usemap attribute is present),
  // CHtmlTagId::VIDEO (if the controls attribute is present)
  interactiveTags_ = {{ CHtmlTagId::A, CHtmlTagId::BUTTON, CHtmlTagId::EMBED,
                        CHtmlTagId::IFRAME, CHtmlTagId::KEYGEN, CHtmlTagId::LABEL,
                        CHtmlTagId::SELECT, CHtmlTagId::TEXTAREA }};

  //---

  for (uint i = 1; i < numTagDefs; i++) {
    CHtmlTagDef &tagDef = tagDefs[i];

    nameToTag_[tagDef.getName()] = &tagDef;
    idToTag_  [tagDef.getId  ()] = &tagDef;

    if (inlineTags_.find(tagDef.getId()) != inlineTags_.end())
      tagDef.setInline(true);

    if (emptyTags_.find(tagDef.getId()) != emptyTags_.end())
      tagDef.setEmpty(true);

    if (metaTags_.find(tagDef.getId()) != metaTags_.end())
      tagDef.setMeta(true);

    if (flowTags_.find(tagDef.getId()) != flowTags_.end())
      tagDef.setFlow(true);

    if (sectionTags_.find(tagDef.getId()) != sectionTags_.end())
      tagDef.setSection(true);

    if (headingTags_.find(tagDef.getId()) != headingTags_.end())
      tagDef.setHeading(true);

    if (phrasingTags_.find(tagDef.getId()) != phrasingTags_.end())
      tagDef.setPhrasing(true);

    if (embedTags_.find(tagDef.getId()) != embedTags_.end())
      tagDef.setEmbed(true);

    if (interactiveTags_.find(tagDef.getId()) != interactiveTags_.end())
      tagDef.setInteractive(true);
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
