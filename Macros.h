#pragma once

#define GET_LAST_ERROR printf("%s::%d %d", __FILE__, __LINE__, GetLastError())
#define MS_PER_UPDATE (double)1.0 / 60.0