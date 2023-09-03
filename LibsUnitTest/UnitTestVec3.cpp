#include "pch.h"
#include "CppUnitTest.h"
#include "../libs/Vec3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define MSG(msg) [&]{ std::wstringstream _s; _s << msg; return _s.str(); }().c_str()

namespace LibsUnitTest
{
	TEST_CLASS(Vec3UnitTest)
	{
	public:

		TEST_METHOD(createShortCuts)
		{
			Assert::AreEqual(Vec3::Up().ToString(), Vec3(0.0, 1.0f).ToString(), MSG("up shortcut is not equal to (0,1)"));
			Assert::AreEqual(Vec3::Down().ToString(), Vec3(0.0, -1.0f).ToString(), MSG("up shortcut is not equal to (0,-1)"));
			Assert::AreEqual(Vec3::Left().ToString(), Vec3(-1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (-1,0)"));
			Assert::AreEqual(Vec3::Right().ToString(), Vec3(1.0, 0.0f).ToString(), MSG("up shortcut is not equal to (1,0)"));
			Assert::AreEqual(Vec3::Zero().ToString(), Vec3(0.0, 0.0f).ToString(), MSG("up shortcut is not equal to (0,0)"));

			Assert::AreEqual(Vec3::One().ToString(), Vec3(1.0, 1.0f).ToString(), MSG("up shortcut is not equal to (1,1)"));
		}

		TEST_METHOD(VectorEqual)
		{
			Vec3 a = Vec3::One();

			Vec3 b(2.0f + 0.4f - 1.4f, 2 * 2 - 3);
			Vec3 c(15.0f, 22.0f);

			Assert::IsFalse(a == c, MSG(" operator ==  return true with big diffence of component"));
			Assert::IsTrue(a == b, MSG(" operator == does not work well on small values"));

			Vec3 big1(100000000000.9f, 100000000.9f);
			Vec3 big2(110000000000.9f - 10000000000.0f, 110000000.9f - 10000000.9f);
			Assert::IsTrue(big1 == big2, MSG(" operator == does not work well on big(10^10) values"));
		}

		TEST_METHOD(VectorAlgebra)
		{
			Vec3 a = Vec3::One();
			Vec3 b = Vec3::Down();
			Assert::IsTrue((a + b) == Vec3::Right(), MSG("(1,1)+(0,-1) != (1,0). operator's + work is not corrent"));
			Assert::IsTrue((-a) == Vec3(-1, -1), MSG(" -(1,1) != (-1,-1).work of  unar minus operator is incorrent"));

			Assert::IsTrue((b - a) == Vec3(-1, -2), MSG("(0,-1) - (1,1) != (-1,-2).work of  minus operator is incorrent"));

			Assert::IsTrue((2 * a) == Vec3(2, 2), MSG("work of LHS multiplication is incorrent"));
			Assert::IsTrue((a * 2) == Vec3(2, 2), MSG("work of RHS multiplication is incorrent"));
			Assert::IsTrue((2 * a) == (a * 2), MSG("RHS mult equal to LHS mult"));

			Assert::IsTrue((a / 2) == Vec3(0.5, 0.5), MSG("dividing vector by number is incorrent"));
		}

		TEST_METHOD(parenthesisTest)
		{
			Vec3 a(1, 2);
			Assert::AreEqual(a[0], 1.0f, MSG("parenthesis return incorrent value at index 0"));
			Assert::AreEqual(a[1], 2.0f, MSG("parenthesis return incorrent value at index 1"));
		}

		TEST_METHOD(MagnitudeCalc)
		{
			Vec3 a(4, 3);
			Assert::AreEqual(a.SqrMagnitude(), 25.0f, MSG("sqr magnitude calc incorrect"));
			Assert::AreEqual(a.Magnitude(), 5.0f, MSG("magnitude calc incorrect"));
			Assert::AreEqual(Vec3::Distance(a, Vec3(0, 0)), 5.0f, MSG("distance calc incorrect"));
		}

		TEST_METHOD(Lerps)
		{
			Vec3 a(0, 0);
			Vec3 b(20, 12);
			Assert::IsTrue(Vec3::Lerp(a, b, 1.5f) == b, MSG("clamp above incorect in lerp method"));
			Assert::IsTrue(Vec3::Lerp(a, b, -1.5f) == a, MSG("clamp below incorect in lerp method"));
			Assert::IsTrue(Vec3::Lerp(a, b, 0.25f) == Vec3(5, 3), MSG("incorect uotput in lerp method"));

			Assert::IsTrue(Vec3::LerpUnclamped(a, b, 1.5f) == Vec3(30, 18), MSG("unclamp above output incorect in lerp method"));
		}

		TEST_METHOD(Scales)
		{
			Vec3 a(2, 5);
			Vec3 b(6, 2);
			Assert::IsTrue(Vec3::Scale(a, b) == Vec3(12, 10), MSG("Scale calc incorrect"));
		}


	};
}
