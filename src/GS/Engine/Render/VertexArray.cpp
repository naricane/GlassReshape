#include "VertexArray.hpp"
#include "GS/Engine/Core/Error.hpp"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &id));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &id));
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: id(other.id)
{
	other.id = 0;
}

VertexArray&
VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other) {
		GLCall(glDeleteVertexArrays(1, &id));

		id = other.id;
		other.id = 0;
	}
	return *this;
}

void
VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.bind();

	const auto& layoutElements = layout.get_elements();
	unsigned char* offset = nullptr;

	for (GLuint i = 0; i < layoutElements.size(); i++) {
		const auto& element = layoutElements[i];

		add_vertex_attribute(
			i, element.count, element.type, element.normalized, layout.get_stride(), offset
		);

		offset += element.count * VertexBufferElement::get_size_of_type(element.type);
	}
}

void
VertexArray::bind() const
{
	GLCall(glBindVertexArray(id));
}

void
VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void
VertexArray::add_vertex_attribute(
	GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	const void* pointer
)
{
	GLCall(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
	GLCall(glEnableVertexAttribArray(index));
}
