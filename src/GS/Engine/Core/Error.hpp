#pragma once

#include <SDL3/SDL_messagebox.h>
#include <expected>
#include <iostream>

namespace error {

void
clear_gl_error();

void
log_gl_error(const char* function, const char* file, int line);

#define GLCall(x) \
	error::clear_gl_error(); \
	x; \
	error::log_gl_error(#x, __FILE__, __LINE__);

struct ErrorMessage
{
	std::string message;
};

}

template<typename... Args>
void
panic(std::string_view message, const Args&... args)
{
	std::string str = std::vformat("{}", std::make_format_args(args...));
	std::cerr << str.data() << "\n";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", str.data(), nullptr);
	std::abort();
}

template<typename T, typename E>
T
unwrap(std::expected<T, E>&& exp)
{
	if (!exp) {
		panic("{}", exp.error());
	}
	return std::forward<T>(*exp);
}

template<>
struct std::formatter<error::ErrorMessage> : std::formatter<std::string>
{
	auto format(error::ErrorMessage error, format_context& ctx) const
	{
		return formatter<string>::format(std::format("{}", error.message), ctx);
	}
};
