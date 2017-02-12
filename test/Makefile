.SILENT:

CC = g++
LD = g++

CDEBUG = -g

CFLAGS = \
-std=c++11 \
$(CDEBUG) \
-I. \
-I$(INC_DIR) \
-I$(INC_DIR)/CHtml \
-I$(INC_DIR)/CCSS \
-I$(INC_DIR)/CXml \
-I$(INC_DIR)/CFile \
-I$(INC_DIR)/CFileType \
-I$(INC_DIR)/CStrUtil \
-I$(INC_DIR)/CAutoPtr \

LDEBUG = -g

LFLAGS = \
$(LDEBUG) \
-L$(LIB_DIR) \
-lCHtml -lCCSS -lCXML -lCStrParse \
-lCFile -lCImageLib -lCGlob -lCUtil -lCStrUtil \
-lCRegExp -lCGlob -lCOSUser -lCOSFile -lCOSTime -lCOSProcess -lCOSSignal \
-lCEnv -lCImageUtil -lCStrNCase -lCPrintF \
-ltre -lpng -ljpeg -lm -lc

SRCS1 = CHtmlTest.cpp
OBJS1 = $(SRCS1:.cpp=.o)

SRCS2 = CHtmlUtilTest.cpp
OBJS2 = $(SRCS2:.cpp=.o)

SRCS3 = CHtmlToWiki.cpp
OBJS3 = $(SRCS3:.cpp=.o)

SRCS4 = CHtmlToMarkdown.cpp
OBJS4 = $(SRCS4:.cpp=.o)

SRCS5 = CHtmlCSSSelect.cpp
OBJS5 = $(SRCS5:.cpp=.o)

EXE1 = $(BIN_DIR)/CHtmlTest
EXE2 = $(BIN_DIR)/CHtmlUtilTest
EXE3 = $(BIN_DIR)/CHtmlToWiki
EXE4 = $(BIN_DIR)/CHtmlToMarkdown
EXE5 = $(BIN_DIR)/CHtmlCSSSelect

.SUFFIXES: .cpp

all: $(EXE1) $(EXE2) $(EXE3) $(EXE4) $(EXE5)

.cpp.o:
	echo "Compiling $<"
	$(CC) -c $< $(CFLAGS)

$(EXE1): $(OBJS1) $(LIB_DIR)/libCHtml.a
	echo "Linking CHtmlTest"
	$(LD) -o $(EXE1) $(OBJS1) $(LFLAGS)

$(EXE2): $(OBJS2) $(LIB_DIR)/libCHtml.a
	echo "Linking CHtmlUtilTest"
	$(LD) -o $(EXE2) $(OBJS2) $(LFLAGS)

$(EXE3): $(OBJS3) $(LIB_DIR)/libCHtml.a
	echo "Linking CHtmlToWiki"
	$(LD) -o $(EXE3) $(OBJS3) $(LFLAGS)

$(EXE4): $(OBJS4) $(LIB_DIR)/libCHtml.a
	echo "Linking CHtmlToMarkdown"
	$(LD) -o $(EXE4) $(OBJS4) $(LFLAGS)

$(EXE5): $(OBJS5) $(LIB_DIR)/libCHtml.a $(LIB_DIR)/libCCSS.a
	echo "Linking CHtmlCSSSelect"
	$(LD) -o $(EXE5) $(OBJS5) $(LFLAGS)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3) $(EXE4) $(EXE5)
