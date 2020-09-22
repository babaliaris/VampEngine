#pragma once
#include "VampAssert.h"
#include <vector>
#include <string>

namespace VampEngine
{

	enum class BufferDataType
	{
		NONE,
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		INT, INT2, INT3, INT4,
		BOOL, BOOL2, BOOL3, BOOL4,
		MAT3, MAT4
	};
	unsigned int GetBufferDataTypeCount(BufferDataType type);
	unsigned int GetBufferDataTypeSize(BufferDataType type);



	struct LayoutAttribute
	{
		BufferDataType	type;
		std::string		name;
		unsigned int	count;
		unsigned int	size;
		unsigned int	offset;

		LayoutAttribute(BufferDataType type, const std::string& name);
	};




	class BufferLayout
	{

		//Public Methods.
		public:

			//Constructor.
			BufferLayout(const std::initializer_list<LayoutAttribute>& attributes);

			//Get Stride.
			unsigned int GetStride() const { return m_stride; }

			//Vector Iterators.
			std::vector<LayoutAttribute>::iterator			begin();
			std::vector<LayoutAttribute>::iterator			end();
			std::vector<LayoutAttribute>::const_iterator	begin() const;
			std::vector<LayoutAttribute>::const_iterator	end()	const;


		//Private Methods.
		private:
			void CalculateAttributes();


		//Private Members
		private:
			std::vector<LayoutAttribute> m_attributes;
			unsigned int m_stride = 0;
	};



	class VertexBuffer
	{

		//Public Static Methods.
		public:
			static VertexBuffer* Create(const void *data, unsigned int size, BufferLayout& layout);


		//Public Methods.
		public:

			//Constructor.
			VertexBuffer(BufferLayout& layout);

			//Set Layout.
			void SetLayout(const BufferLayout& layout);

			//Get Layout.
			inline const BufferLayout& GetLayout() { return m_layout; }


		//Public Virtual Methods.
		public:

			//Virtual Decontructor.
			virtual ~VertexBuffer() = default;

			//Bind and Unbind Methods.
			virtual void Bind()		const = 0;
			virtual void Unbind()	const = 0;

		//Private Members.
		protected:
			BufferLayout m_layout;
			

	};




	class IndexBuffer
	{

		//Public Static Methods.
		public:

			//Create METHOD.
			static IndexBuffer* Create(const void* data, unsigned int size);


		//Public Methods.
		public:
			IndexBuffer() = default;

		//Public Virtual Methods.
		public:

			//Default Virtual Deconstructor.
			virtual ~IndexBuffer() = default;

			//Bind and Unbind.
			virtual void Bind()		const = 0;
			virtual void Unbind()	const = 0;

			//Get Count.
			virtual unsigned int GetCount() const = 0;
	};
}