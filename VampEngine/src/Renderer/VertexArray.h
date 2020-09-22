#pragma once
#include <vector>
#include "Buffer.h"

namespace VampEngine
{
	class VertexArray
	{
		//Public Static Methods.
		public:
			static VertexArray* Create();


		//Public Methods.
		public:
			VertexArray();

			inline std::vector<VertexBuffer*> GetVertexBuffers() const { return m_vertexBuffers; }
			inline IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

		//Public Virtual Methods.
		public:

			//Virtual Destructor.
			virtual ~VertexArray() = default;

			//Bind and Unbind Methods.
			virtual void Bind()		const = 0;
			virtual void Unbind()	const = 0;

			//Add Buffer and Set Index Buffer Methods.
			virtual void AddBuffer(VertexBuffer* vbo)		= 0;
			virtual void SetIndexBuffer(IndexBuffer* ebo)	= 0;


		//Protected Members.
		protected:
			std::vector<VertexBuffer *>	m_vertexBuffers;
			IndexBuffer*				m_IndexBuffer;

	};

}