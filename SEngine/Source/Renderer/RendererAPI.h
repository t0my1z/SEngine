#pragma once

namespace SE
{
	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0,
			OpenGL = 1,
			Vulkan = 2
		};

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}

