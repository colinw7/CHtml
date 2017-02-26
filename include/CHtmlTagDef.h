#ifndef CHtmlTagDef_H
#define CHtmlTagDef_H

#include <CHtmlTypes.h>
#include <string>
#include <map>
#include <set>
#include <sys/types.h>

enum class CHtmlTagDisplay {
  INVALID,
  NONE,
  BLOCK,
  INLINE,
  TABLE,
  TABLE_ROW,
  TABLE_CELL,
  TABLE_CAPTION,
  LIST_ITEM
};

//---

#define CHtmlTagDefLookupInst CHtmlTagDefLookup::instance()

class CHtmlTagDef;

class CHtmlTagDefLookup {
 public:
  static CHtmlTagDefLookup *instance();

 ~CHtmlTagDefLookup() { }

  const CHtmlTagDef &lookup(const std::string &name) const;
  const CHtmlTagDef &lookup(CHtmlTagId id) const;

 private:
  CHtmlTagDefLookup();

 private:
  typedef std::map<std::string, const CHtmlTagDef *> NameToTag;
  typedef std::map<CHtmlTagId , const CHtmlTagDef *> IdToTag;
  typedef std::set<CHtmlTagId>                       TagSet;
  typedef std::map<CHtmlTagId , CHtmlTagDisplay>     IdToDisplay;

  NameToTag   nameToTag_;
  IdToTag     idToTag_;
  IdToDisplay idToDisplay_;
  TagSet      inlineTags_;
  TagSet      emptyTags_;
  TagSet      metaTags_;
  TagSet      flowTags_;
  TagSet      sectionTags_;
  TagSet      headingTags_;
  TagSet      phrasingTags_;
  TagSet      embedTags_;
  TagSet      interactiveTags_;
};

//---

class CHtmlTagDef {
 public:
  CHtmlTagDef(CHtmlTagId id, const std::string &name, CHtmlTextType textType) :
   id_(id), name_(name), textType_(textType) {
  }

  const CHtmlTagId    &getId      () const { return id_; }
  const std::string   &getName    () const { return name_; }
  const CHtmlTextType &getTextType() const { return textType_; }

  bool isInline() const { return inline_; }
  void setInline(bool b) { inline_ = b; }

  bool isEmpty() const { return empty_; }
  void setEmpty(bool b) { empty_ = b; }

  bool isMeta() const { return meta_; }
  void setMeta(bool b) { meta_ = b; }

  bool isFlow() const { return flow_; }
  void setFlow(bool b) { flow_ = b; }

  bool isSection() const { return section_; }
  void setSection(bool b) { section_ = b; }

  bool isHeading() const { return heading_; }
  void setHeading(bool b) { heading_ = b; }

  bool isPhrasing() const { return phrasing_; }
  void setPhrasing(bool b) { phrasing_ = b; }

  bool isEmbed() const { return embed_; }
  void setEmbed(bool b) { embed_ = b; }

  bool isInteractive() const { return interactive_; }
  void setInteractive(bool b) { interactive_ = b; }

  bool isValid() const { return id_ != CHtmlTagId::NONE; }

 private:
  CHtmlTagId    id_;
  std::string   name_;
  CHtmlTextType textType_ { CHtmlTextType::NONE };
  bool          inline_ { false };
  bool          empty_ { false };
  bool          meta_ { false };
  bool          flow_ { false };
  bool          section_ { false };
  bool          heading_ { false };
  bool          phrasing_ { false };
  bool          embed_ { false };
  bool          interactive_ { false };
};

#endif
