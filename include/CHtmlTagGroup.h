#ifndef CHtmlTagGroup_H
#define CHtmlTagGroup_H

#include <vector>

class CHtmlTagSubGroup;
class CHtmlTokenArray;

class CHtmlTagGroup {
 public:
  CHtmlTagGroup(const CHtmlTokenArray &tokens, int *i);

 private:
  CHtmlTagSubGroup *subGroup_ { nullptr };
};

//------

class CHtmlTagSubGroup {

 public:
  CHtmlTagSubGroup(CHtmlToken *token);
  CHtmlTagSubGroup(const CHtmlTokenArray &tokens, int *i);

  void add(CHtmlToken *token);
  void add(CHtmlTagSubGroup *subGroup);

 private:
  std::vector<CHtmlTagSubGroupValue *> subValues_;
};

//------

class CHtmlTagSubGroupValue {
};

//------

class CHtmlTagSubGroupToken : public CHtmlTagSubGroupValue {
 public:
  CHtmlTagSubGroupToken(CHtmlToken *token);

 private:
  CHtmlToken *token_ { nullptr };
};

//------

class CHtmlTagSubGroupSubGroup : public CHtmlTagSubGroupValue {
 public:
  CHtmlTagSubGroupToken(CHtmlTagSubGroup *subGroup);

 private:
  CHtmlTagSubGroup *subGroup_ { nullptr };
};

#endif
