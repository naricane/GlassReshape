#pragma once

#include <glad/glad.h>
#include <span>

class VertexBuffer
{
private:
	GLuint id;

public:
	VertexBuffer() = default;
	VertexBuffer(std::span<const float> data);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	void bind() const;
	void unbind() const;
};
