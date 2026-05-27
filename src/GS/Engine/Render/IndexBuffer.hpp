#pragma once

#include <glad/glad.h>
#include <span>

class IndexBuffer
{
private:
	GLuint id;
	unsigned int count;

public:
	IndexBuffer() = default;
	IndexBuffer(std::span<const unsigned int> data);
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	IndexBuffer(IndexBuffer&& other) noexcept;
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;

	void bind() const;
	void unbind() const;
	unsigned int get_count() const;
};
