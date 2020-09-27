#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace VampEngine
{

	//Forward Declerations//
	class VertexArray;
	class Shader;
	//Forward Declerations//



	class Renderer
	{

		friend class Application;

		//Public Static Methods.
		public:

			inline static Renderer* Get() { return s_Instance; }

			static void BeginScene();
			static void EndScene();
			static void Submit();


		//Private Methods.
		private:

			//Create Method.
			static void Create();


		//Private Members.
		private:

			//Render Object.
			struct RenderObject
			{
				VertexArray*			vao;		//Holds the Mesh.
				Shader*					shader;		//The program to render this mesh.
				std::vector<glm::mat4>	models;		//The model transforms. size() = instance rendering count.
			};

			//The instance of this class.
			static Renderer* s_Instance;

			//Objects to be rendered.
			std::vector<RenderObject*> m_opaqueObjects;
			std::vector<RenderObject*> m_transparentObject;


	};
}