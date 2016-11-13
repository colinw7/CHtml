CC = g++
AR = ar
RM = rm

CDEBUG = -g
LDEBUG = -g

INC_DIR = ../include
OBJ_DIR = ../obj
LIB_DIR = ../lib

all: $(LIB_DIR)/libCHtml.a

SRC = \
CHtmlComment.cpp \
CHtml.cpp \
CHtmlNamedChar.cpp \
CHtmlParser.cpp \
CHtmlTag.cpp \
CHtmlTagDef.cpp \
CHtmlText.cpp \
CHtmlToken.cpp \
CHtmlUtil.cpp \

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

CPPFLAGS = \
-std=c++11 \
-I. \
-I$(INC_DIR) \
-I../../CFile/include \
-I../../CStrUtil/include \
-I../../CRegExp/include \
-I../../COS/include \
-I../../CUtil/include \

clean:
	$(RM) -f $(OBJ_DIR)/*.o
	$(RM) -f $(LIB_DIR)/libCHtml.a

$(OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $< -o $(OBJ_DIR)/$*.o $(CPPFLAGS)

.SUFFIXES: .cpp

$(LIB_DIR)/libCHtml.a: $(OBJS)
	$(AR) crv $(LIB_DIR)/libCHtml.a $(OBJS)
