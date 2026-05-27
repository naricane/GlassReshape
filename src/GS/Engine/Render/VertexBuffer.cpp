#include "VertexBuffer.hpp"
#include "GS/Engine/Core/Error.hpp"
#include <span>

VertexBuffer::VertexBuffer(std::span<const float> data)
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size_bytes(), data.data(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &id));
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: id(other.id)
{
	other.id = 0;
}

VertexBuffer&
VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other) {
		GLCall(glDeleteBuffers(1, &id));

		id = other.id;
		other.id = 0;
	}
	return *this;
}

void
VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}
void
VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
