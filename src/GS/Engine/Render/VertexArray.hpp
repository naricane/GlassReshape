#pragma once

#include "GS/Engine/Render/VertexBuffer.hpp"
#include <vector>

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	GLboolean normalized;

	static GLuint get_size_of_type(GLuint type)
	{
		switch (type) {
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	GLsizei stride = 0;

public:
	VertexBufferLayout() = default;

	template<typename T>
	void push(GLuint count)
	{
		static_assert(sizeof(T) == 0, "Unsupported type for VertexBufferLayout!");
	}

	const std::vector<VertexBufferElement>& get_elements() const { return elements; }
	GLsizei get_stride() const { return stride; }
};

template<>
inline void
VertexBufferLayout::push<float>(GLuint count)
{
	elements.push_back({ GL_FLOAT, count, GL_FALSE });
	stride += count * sizeof(GLfloat);
}

template<>
inline void
VertexBufferLayout::push<unsigned int>(GLuint count)
{
	elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	stride += count * sizeof(GLuint);
}

template<>
inline void
VertexBufferLayout::push<unsigned char>(GLuint count)
{
	elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	stride += count * sizeof(GLubyte);
}

class VertexArray
{
private:
	GLuint id = 0;

public:
	VertexArray();
	~VertexArray();

	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray(const VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;

	void add_vertex_attribute(
		GLuint index,
		GLint size,
		GLenum type,
		GLboolean normalized,
		GLsizei stride,
		const void* pointer
	);
};
