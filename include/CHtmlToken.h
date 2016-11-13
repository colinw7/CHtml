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

  virtual CHtmlComment *getComment() const { return 0; }
  virtual CHtmlTag     *getTag    () const { return 0; }
  virtual CHtmlText    *getText   () const { return 0; }

 protected:
  CHtmlTokenType type_ { CHtmlTokenType::NONE };
};

//------

class CHtmlCommentToken : public CHtmlToken {
 public:
  CHtmlCommentToken(CHtmlComment *comment);

  CHtmlComment *getComment() const { return comment_; }

 private:
  CHtmlComment *comment_ { nullptr };
};

//------

class CHtmlTagToken : public CHtmlToken {
 public:
  CHtmlTagToken(CHtmlTag *tag);

  CHtmlTag *getTag() const { return tag_; }

 private:
  CHtmlTag *tag_ { nullptr };
};

//------

class CHtmlTextToken : public CHtmlToken {
 public:
  CHtmlTextToken(CHtmlText *text);

  CHtmlText *getText() const { return text_; }

 private:
  CHtmlText *text_ { nullptr };
};

#endif
