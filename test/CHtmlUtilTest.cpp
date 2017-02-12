#include <CFile.h>
#include <CDir.h>
#include <CHtmlUtil.h>

int
main(int argc, char **argv)
{
  CDir  dir(".");
  CFile output("dir.html");

  CHtmlFileMgr mgr;

  CHtmlUtil::listDirectory(dir, output, mgr);
}
