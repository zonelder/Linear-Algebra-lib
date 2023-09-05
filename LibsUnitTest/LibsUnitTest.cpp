#include "pch.h"
#include "CppUnitTest.h"
#include "../libs/Vec2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define MSG(msg) [&]{ std::wstringstream _s; _s << msg; return _s.str(); }().c_str()

namespace LibsUnitTest
{
	TEST_CLASS(Vec2UnitTest)
	{
	public:
		
		TEST_METHOD(createShortCuts)
		{
			Assert::AreEqual(Vec2::Up.ToString(), Vec2(0.0, 1.0f).ToString(), MSG("up shortcut is not equal to (0,1)"));
			Assert::AreEqual(Vec2::Down.ToString(), Vec2(0.0, -1.0f).ToString(), MSG("up shortcut is not equal to (0,-1)"));
			Assert::AreEqual(Vec2::Left.ToString(), Vec2(-1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (-1,0)"));
			Assert::AreEqual(Vec2::Right.ToString(), Vec2(1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (1,0)"));
			Assert::AreEqual(Vec2::Zero.ToString(), Vec2(0.0, 0.0f).ToString(), MSG("up shortcut is not equal to (0,0)"));

			Assert::AreEqual(Vec2::One.ToString(), Vec2(1.0, 1.0f).ToString(), MSG("up shortcut is not equal to (1,1)"));
		}

		TEST_METHOD(VectorEqual)
		{
			Vec2 a = Vec2::One;

			Vec2 b(2.0f + 0.4f - 1.4f, 2 * 2 - 3);
			Vec2 c(15.0f, 22.0f);

			Assert::IsFalse(a == c, MSG(" operator ==  return true with big diffence of component"));
			Assert::IsTrue(a == b, MSG(" operator == does not work well on small values"));

			Vec2 big1(100000000000.9f, 100000000.9f);
			Vec2 big2(110000000000.9f - 10000000000.0f, 110000000.9f - 10000000.9f);
			Assert::IsTrue(big1 == big2, MSG(" operator == does not work well on big(10^10) values"));
		}

		TEST_METHOD(VectorAlgebra)
		{
			Vec2 a = Vec2::One;
			Vec2 b = Vec2::Down;
			Assert::IsTrue((a + b) == Vec2::Right, MSG("(1,1)+(0,-1) != (1,0). operator's + work is not corrent"));
			Assert::IsTrue((-a) == Vec2(-1, -1), MSG(" -(1,1) != (-1,-1).work of  unar minus operator is incorrent"));

			Assert::IsTrue((b - a) == Vec2(-1, -2), MSG("(0,-1) - (1,1) != (-1,-2).work of  minus operator is incorrent"));

			Assert::IsTrue((2*a) == Vec2(2,2),MSG("work of LHS multiplication is incorrent"));
			Assert::IsTrue((a * 2) == Vec2(2, 2), MSG("work of RHS multiplication is incorrent"));
			Assert::IsTrue((2 * a) == (a * 2), MSG("RHS mult equal to LHS mult"));

			Assert::IsTrue((a / 2) == Vec2(0.5, 0.5), MSG("dividing vector by number is incorrent"));
		}

		TEST_METHOD(parenthesisTest)
		{
			Vec2 a(1, 2);
			Assert::AreEqual(a[0], 1.0f, MSG("parenthesis return incorrent value at index 0"));
			Assert::AreEqual(a[1], 2.0f, MSG("parenthesis return incorrent value at index 1"));
		}

		TEST_METHOD(MagnitudeCalc)
		{
			Vec2 a(4, 3);
			Assert::AreEqual(a.SqrMagnitude(), 25.0f, MSG("sqr magnitude calc incorrect"));
			Assert::AreEqual(a.Magnitude(), 5.0f, MSG("magnitude calc incorrect"));
			Assert::AreEqual(Vec2::Distance(a, Vec2(0, 0)), 5.0f, MSG("distance calc incorrect"));
		}

		TEST_METHOD(Lerps)
		{
			Vec2 a(0, 0);
			Vec2 b(20, 12);
			Assert::IsTrue(Vec2::Lerp(a,b,1.5f) == b, MSG("clamp above incorect in lerp method"));
			Assert::IsTrue(Vec2::Lerp(a, b, -1.5f) == a, MSG("clamp below incorect in lerp method"));
			Assert::IsTrue(Vec2::Lerp(a, b, 0.25f) == Vec2(5,3), MSG("incorect uotput in lerp method"));

			Assert::IsTrue(Vec2::LerpUnclamped(a, b, 1.5f) == Vec2(30,18), MSG("unclamp above output incorect in lerp method"));
		}

		TEST_METHOD(Scales)
		{
			Vec2 a(2, 5);
			Vec2 b(6, 2);
			Assert::IsTrue(Vec2::Scale(a,b) == Vec2(12,10), MSG("Scale calc incorrect"));
		}


	};
}
