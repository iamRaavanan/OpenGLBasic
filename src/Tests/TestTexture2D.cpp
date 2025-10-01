#include "TestTexture2D.h"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	test::TestTexture2D::TestTexture2D() 
		:mTranslationA(200, 200, 0), mTranslationB(400, 200, 0),
		mProj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		mView(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		mIo(ImGui::GetIO())
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		mVAO = std::make_unique<VertexArray>();
		mIB = std::make_unique<IndexBuffer>(indices, 6);

		mVB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		mVAO->AddBuffer(*mVB, layout);

		mShader = std::make_unique<Shader>("resource/shaders/Basic.shader");
		mShader->Bind();
		mShader->SetUniform("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		float r = 0.0f;
		float increment = 0.05f;

		mTexture = std::make_unique<Texture>("resource/profile.png");
		mShader->SetUniform1i("u_Texture", 0);

		mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	}

	test::TestTexture2D::~TestTexture2D()
	{
	}

	void test::TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void test::TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;

		mTexture->Bind();
		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationA);
			glm::mat4 mvp = mProj * mView * model;
			mShader->Bind();
			//shader.SetUniform("u_Color", r, 0.3f, 0.8f, 1.0f);
			mShader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*mVAO, *mIB, *mShader);
		}

		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationB);
			glm::mat4 mvp = mProj * mView * model;
			mShader->Bind();
			//shader.SetUniform("u_Color", r, 0.3f, 0.8f, 1.0f);
			mShader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*mVAO, *mIB, *mShader);
		}
	}

	void test::TestTexture2D::OnImGUIRender()
	{
		//ImGui::Begin("OpenGL- World");
		ImGui::SliderFloat3("Translation-A", &mTranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation-B", &mTranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / mIo.Framerate, mIo.Framerate);
		//ImGui::End();
	}
}