#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

#include <string_view>

namespace taixu {
	constexpr char         OPENGL_VERSION[] = "#version 410";
	constexpr std::int32_t OPENGL_MAJOR_VERSION = 4;
	constexpr std::int32_t OPENGL_MINOR_VERSION = 1;
}// namespace taixu::core

enum class status {
	//Define status enum
	OK,
	PERMISSION_FAILED,
	NO_SUCH_FILE_FAILED
};
//namespace taixu: :core
#endif /* ENGINE_RUNTIME_CORE_BASE_MACRO */
