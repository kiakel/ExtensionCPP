#include "useStatic.h"

static const int cc_static_const_int = 21; // 只能在当前文件使用
static int cc_static_int = 22; // 只能在当前文件使用

int useStatic::m_static_int = 15;
const int useStatic::m_static_const;