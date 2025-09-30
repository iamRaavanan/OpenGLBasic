#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	test::TestClearColor::TestClearColor()
		:mClearColor{0.2f, 0.3f, 0.8f, 1.0f}
	{
	}

	test::TestClearColor::~TestClearColor()
	{
	}

	void test::TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void test::TestClearColor::OnRender()
	{
		GLCall(glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void test::TestClearColor::OnImGUIRender()
	{
		ImGui::ColorEdit4("Clear Color", mClearColor);
	}
}