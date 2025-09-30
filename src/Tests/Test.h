#pragma once
#include<functional>
#include <vector>
#include <string>
#include<iostream>

namespace test 
{
	class Test
	{
	public:
		Test()
		{
		}
		virtual ~Test()
		{

		}

		virtual void OnUpdate(float deltaTime){}
		virtual void OnRender(){}	
		virtual void OnImGUIRender(){}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPtr);

		void OnImGUIRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout<< "Registering Test for " << name << std::endl;
			mTests.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& mCurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> mTests;

	};
}