#include <stdio.h>

#include "archs.h"
#include "defs.h"

void uci()
{
  printf("%s %s %s by %s\n", PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_ARCH, PROGRAM_AUTHOR);
}
