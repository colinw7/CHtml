#ifndef CHtmlToken_H
#define CHtmlToken_H

enum class CHtmlTokenType {
  NONE,
  COMMENT,
  TAG,
  TEXT
};

class CHtmlComment;
class CHtmlTag;
class CHtmlText;

class CHtmlToken {
 public:
  CHtmlToken(CHtmlTokenType type);

  virtual ~CHtmlToken();

  CHtmlTokenType getType() const { return type_; }

  bool isComment() const { return type_ == CHtmlTokenType::COMMENT; }
  bool isTag    () const { return type_ == CHtmlTokenType::TAG    ; }
  bool isText   () const { return type_ == CHtmlTokenType::TEXT   ; }

  virtual CHtmlComment *getComment() const { return nullptr; }
  virtual CHtmlTag     *getTag    () const { return nullptr; }
  virtual CHtmlText    *getText   () const { return nullptr; }

 protected:
  CHtmlTokenType type_ { CHtmlTokenType::NONE };
};

//------

class CHtmlCommentToken : public CHtmlToken {
 public:
  CHtmlCommentToken(CHtmlComment *comment);

  CHtmlComment *getComment() const override { return comment_; }

 private:
  CHtmlComment *comment_ { nullptr };
};

//------

class CHtmlTagToken : public CHtmlToken {
 public:
  CHtmlTagToken(CHtmlTag *tag);

  CHtmlTag *getTag() const override { return tag_; }

 private:
  CHtmlTag *tag_ { nullptr };
};

//------

class CHtmlTextToken : public CHtmlToken {
 public:
  CHtmlTextToken(CHtmlText *text);

  CHtmlText *getText() const override { return text_; }

 private:
  CHtmlText *text_ { nullptr };
};

#endif
