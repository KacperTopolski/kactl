#define LOC
#include <bits/stdc++.h>
#define int32_t void
#define main _main_unused
#include "../../content/contest/sol.cpp"
#undef int32_t
#undef main

// for old tests
#define debug(x...) deb(x)

// WSL1 is broken, remove once nobody in the team uses WSL1
#if __has_include (<fpu_control.h>)
#include <fpu_control.h>
namespace wsl {
auto is_wsl = [](){
	ifstream stream("/proc/version");
	string str;
	getline(stream, str);
	for (char &ch : str)
		ch = (char) tolower((unsigned char) ch);
	if (str.find("microsoft") == string::npos)
		return false;
	unsigned short Cw = 0x37f;
	_FPU_SETCW(Cw);
	return true;
}();
}
#endif
