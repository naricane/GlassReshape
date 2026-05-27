#include "IndexBuffer.hpp"
#include "GS/Engine/Core/Error.hpp"

IndexBuffer::IndexBuffer(std::span<const unsigned int> data)
	: count(static_cast<unsigned int>(data.size()))
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size_bytes(), data.data(), GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &id));
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	: id(other.id)
	, count(other.count)
{
	other.id = 0;
	other.count = 0;
}

IndexBuffer&
IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
	if (this != &other) {
		GLCall(glDeleteBuffers(1, &id));

		id = other.id;
		count = other.count;

		other.id = 0;
	}
	return *this;
}

void
IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void
IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

GLuint
IndexBuffer::get_count() const
{
	return count;
}
