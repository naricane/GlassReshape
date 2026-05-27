#include "Mesh.hpp"

Mesh::Mesh(
	std::span<const float> vertices,
	const VertexBufferLayout& layout,
	std::span<const unsigned int> indices
)
	: vb(vertices)
	, ib(indices)
{
	va.bind();
	va.add_buffer(vb, layout);
	va.unbind();
}

void
Mesh::bind() const
{
	va.bind();
	ib.bind();
}

void
Mesh::unbind() const
{
	va.unbind();
	ib.unbind();
}
