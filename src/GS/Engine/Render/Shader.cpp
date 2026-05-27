#include "Shader.hpp"
#include "GS/Engine/Core/Error.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

std::expected<std::string, std::string>
Shader::read_file(std::string_view path)
{
	std::ifstream file(path.data(), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		return std::unexpected(std::format("Could not open file: {}", path));
	}

	std::stringstream stream;
	stream << file.rdbuf();
	return stream.str();
}

std::expected<GLuint, std::string>
Shader::compile_shader(GLenum type, std::string_view source)
{
	GLCall(GLuint s_id = glCreateShader(type));
	const char* src = source.data();
	GLCall(glShaderSource(s_id, 1, &src, nullptr));
	GLCall(glCompileShader(s_id));

	GLint is_compiled = 0;
	GLCall(glGetShaderiv(s_id, GL_COMPILE_STATUS, &is_compiled));
	if (is_compiled == GL_FALSE) {
		GLint max_length = 0;
		GLCall(glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &max_length));
		std::vector<GLchar> info_log(max_length);
		GLCall(glGetShaderInfoLog(s_id, max_length, &max_length, info_log.data()));
		GLCall(glDeleteShader(s_id));

		return std::unexpected(
			std::format(
				"[GLSL Compile Error] ({}): {}",
				(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"),
				info_log.data()
			)
		);
	}
	return s_id;
}

std::expected<GLuint, std::string>
Shader::init_program(std::string_view vertex_src, std::string_view fragment_src)
{
	auto vs = compile_shader(GL_VERTEX_SHADER, vertex_src);
	if (!vs) {
		return std::unexpected(vs.error());
	}

	auto fs = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
	if (!fs) {
		GLCall(glDeleteShader(*vs));
		return std::unexpected(fs.error());
	}

	GLCall(GLuint prog_id = glCreateProgram());
	GLCall(glAttachShader(prog_id, *vs));
	GLCall(glAttachShader(prog_id, *fs));
	GLCall(glLinkProgram(prog_id));

	GLint is_linked = 0;
	GLCall(glGetProgramiv(prog_id, GL_LINK_STATUS, &is_linked));
	if (is_linked == GL_FALSE) {
		GLint max_length = 0;
		GLCall(glGetProgramiv(prog_id, GL_INFO_LOG_LENGTH, &max_length));
		std::vector<GLchar> info_log(max_length);
		GLCall(glGetProgramInfoLog(prog_id, max_length, &max_length, info_log.data()));

		GLCall(glDeleteProgram(prog_id));
		GLCall(glDeleteShader(*vs));
		GLCall(glDeleteShader(*fs));

		return std::unexpected(std::format("Shader linking failed: {}", info_log.data()));
	}

	GLCall(glDetachShader(prog_id, *vs));
	GLCall(glDetachShader(prog_id, *fs));
	GLCall(glDeleteShader(*vs));
	GLCall(glDeleteShader(*fs));

	return prog_id;
}

Shader::Shader()
	: id(unwrap(init_program(default_vertex_src, default_fragment_src)))
{
}

Shader::Shader(std::string_view vertex_path, std::string_view fragment_path)
{
	auto vertex_res = read_file(vertex_path);
	auto fragment_res = read_file(fragment_path);

	std::string error_message;
	bool success = false;

	if (!vertex_res) {
		error_message = vertex_res.error();
	} else if (!fragment_res) {
		error_message = fragment_res.error();
	} else {
		auto program_res = init_program(*vertex_res, *fragment_res);

		if (program_res) {
			id = *program_res;
			success = true;
		} else {
			error_message = program_res.error();
		}
	}

	if (!success) {
		std::cerr << "[Shader File Compile Error]: " << error_message
				  << "\n-> Falling back to embedded default shader.\n"
				  << std::endl;
		if (id != 0) {
			glDeleteProgram(id);
			id = 0;
		}

		id = unwrap(init_program(default_vertex_src, default_fragment_src));
	}
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(id));
}

Shader::Shader(Shader&& other) noexcept
	: id(other.id)
{
	other.id = 0;
}

Shader&
Shader::operator=(Shader&& other) noexcept
{
	if (this != &other) {
		GLCall(glDeleteProgram(id));
		id = other.id;
		other.id = 0;
	}
	return *this;
}

void
Shader::use() const
{
	GLCall(glUseProgram(id));
}

void
Shader::set_uniform(std::string_view name, bool value) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniform1i(loc, (int)value));
}

void
Shader::set_uniform(std::string_view name, int value) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniform1i(loc, value));
}

void
Shader::set_uniform(std::string_view name, float value) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniform1f(loc, value));
}

void
Shader::set_uniform(std::string_view name, const glm::mat4& value) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)&value[0][0]));
}

void
Shader::set_uniform(std::string_view name, float x, float y, float z) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniform3f(loc, x, y, z));
}

void
Shader::set_uniform(std::string_view name, float x, float y) const
{
	GLCall(GLuint loc = glGetUniformLocation(id, name.data()));
	GLCall(glUniform2f(loc, x, y));
}
