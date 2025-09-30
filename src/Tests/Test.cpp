#include "Test.h"
#include "imgui/imgui.h"
namespace test
{
	TestMenu::TestMenu(Test*& currentTestPtr)
		:mCurrentTest(currentTestPtr)
	{

	}

	void TestMenu::OnImGUIRender()
	{
		for (auto& test : mTests)
		{
			if (ImGui::Button(test.first.c_str()))
				mCurrentTest = test.second();
		}
	}
}