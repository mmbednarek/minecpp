#include "membuf.h"

namespace Utils {

MemBuf::MemBuf(char *ptr, size_t size) {
	setg(ptr, ptr, ptr + size);
}

}
