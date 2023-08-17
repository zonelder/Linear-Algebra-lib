#include "pch.h"
#include "CppUnitTest.h"
#include "../libs/Vec2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define MSG(msg) [&]{ std::wstringstream _s; _s << msg; return _s.str(); }().c_str()

namespace LibsUnitTest
{
	TEST_CLASS(LibsUnitTest)
	{
	public:
		
		TEST_METHOD(createShortCuts)
		{
			Assert::AreEqual(Vec2::Up().ToString(), Vec2(0.0, 1.0f).ToString(), MSG("up shortcut is not equal to (0,1)"));
			Assert::AreEqual(Vec2::Down().ToString(), Vec2(0.0, -1.0f).ToString(), MSG("up shortcut is not equal to (0,-1)"));
			Assert::AreEqual(Vec2::Left().ToString(), Vec2(-1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (-1,0)"));
			Assert::AreEqual(Vec2::Right().ToString(), Vec2(1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (1,0)"));
			Assert::AreEqual(Vec2::Zero().ToString(), Vec2(0.0, 0.0f).ToString(), MSG("up shortcut is not equal to (0,0)"));

			Assert::AreEqual(Vec2::One().ToString(), Vec2(1.0, 1.0f).ToString(), MSG("up shortcut is not equal to (1,1)"));
		}

		TEST_METHOD(VectorEquil)
		{
			Vec2 a = Vec2::One();

			Vec2 b(2.0f + 0.4f - 1.4f, 2 * 2 - 3);
			Vec2 c(15.0f, 22.0f);

			Assert::IsFalse(a == c, MSG(" operator ==  return true with big diffence of component"));
			Assert::IsTrue(a == b, MSG(" operator == does not work well on small values"));

			Vec2 big1(100000000000.9f, 100000000.9f);
			Vec2 big2(110000000000.9f - 10000000000.0f, 110000000.9f - 10000000.9f);
			Assert::IsTrue(big1 == big2, MSG(" operator == does not work well on big(10^10) values"));
		}
	};
}
