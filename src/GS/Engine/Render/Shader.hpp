#pragma once

#include <expected>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

class Shader
{
private:
	GLuint id;

	static constexpr std::string_view default_vertex_src = R"(
	       #version 330 core
	       layout(location = 0) in vec3 position;
	       layout(location = 1) in vec3 color;
	       out vec3 v_Color;
	       uniform mat4 u_MVP;
	       void main() {
	           gl_Position = u_MVP * vec4(position, 1.0);
	           v_Color = color;
	       }
	   )";

	static constexpr std::string_view default_fragment_src = R"(
        #version 330 core
        in vec3 v_Color;
        layout(location = 0) out vec4 color;
        void main() {
            color = vec4(v_Color, 1.0);
        }
    )";

	std::expected<std::string, std::string> read_file(std::string_view path);
	std::expected<GLuint, std::string> compile_shader(GLenum type, std::string_view source);
	std::expected<GLuint, std::string>
	init_program(std::string_view vertex_src, std::string_view fragment_src);

public:
	Shader();
	Shader(std::string_view vertex_path, std::string_view fragment_path);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void use() const;
	void set_uniform(std::string_view name, bool value) const;
	void set_uniform(std::string_view name, int value) const;
	void set_uniform(std::string_view name, float value) const;
	void set_uniform(std::string_view name, const glm::mat4& value) const;
	void set_uniform(std::string_view name, float x, float y, float z) const;
	void set_uniform(std::string_view name, float x, float y) const;
};
