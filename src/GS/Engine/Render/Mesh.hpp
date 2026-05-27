#pragma once

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glm/glm.hpp>
#include <span>

class Mesh
{
private:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

public:
	Mesh(
		std::span<const float> vertices,
		const VertexBufferLayout& layout,
		std::span<const unsigned int> indices
	);

	~Mesh() = default;

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept = default;
	Mesh& operator=(Mesh&& other) noexcept = default;

	void bind() const;
	void unbind() const;

	unsigned int get_index_count() const { return ib.get_count(); }
};
