#pragma once

#include "Test.h"
#include "VertexBuffer.h";
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "imgui/imgui.h"

namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;

	private:
		glm::vec3 mTranslationA, mTranslationB;
		std::unique_ptr<VertexArray> mVAO;
		std::unique_ptr<VertexBuffer> mVB;
		std::unique_ptr<IndexBuffer> mIB;
		std::unique_ptr<Shader> mShader;
		std::unique_ptr<Texture> mTexture;
		glm::mat4 mProj, mView;
		ImGuiIO& mIo;
	};
}