#include "std_c++.h"
#include "CFile/CFile.h"
#include "CFile/CDir.h"
#include "CHtml/CHtmlUtil.h"

int
main(int argc, char **argv)
{
  CDir  dir(".");
  CFile output("dir.html");

  CHtmlFileMgr mgr;

  CHtmlUtil::listDirectory(dir, output, mgr);
}
