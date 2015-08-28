// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 INLINEHOOKLIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// INLINEHOOKLIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef INLINEHOOKLIB_EXPORTS
#define INLINEHOOKLIB_API __declspec(dllexport)
#else
#define INLINEHOOKLIB_API __declspec(dllimport)
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class INLINEHOOKLIB_API InlineHook {
public:
	InlineHook();
	~InlineHook();
	bool install(PVOID pfunc, PVOID jmpPfunc);
	bool uninstall();
	bool suspend();
	bool resume();
private:
	static const int JMP_LEN = 5;
	enum STATUS { NOTHING, WORKING, SUSPEEDED };
	PVOID _addrFunc;
	BYTE _oldBytes[JMP_LEN];
	BYTE _jmpBytes[JMP_LEN];
	STATUS _status;
};