#pragma once
#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "fonctions.h"

TEST(UnitTestImage, Constructor)
{
	Canal CanalTest1 = Canal();
	Image ImageTest1 = Image();
	EXPECT_TRUE(ImageTest1[0] == CanalTest1 && ImageTest1[1] == CanalTest1 && ImageTest1[2] == CanalTest1);
	Canal CanalTest2 = Canal(3,3);
	Image ImageTest3 = Image(3,3);
	EXPECT_TRUE(ImageTest1[0] == CanalTest2 && ImageTest1[1] == CanalTest2 && ImageTest1[2] == CanalTest2);

}


TEST(UnitTestImage, Operatorequal)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	EXPECT_TRUE(test1 == test2);
	test1[1](1) = test2[1](1) = 9;	
	EXPECT_TRUE(test1 == test2);

	test2[0](1) = 11;
	EXPECT_FALSE(test1 == test2);
	
}

TEST(UnitTestImage, InitWith)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	test1.InitWith(5);	
	EXPECT_FALSE(test1 == test2);

	test2[0](1) = test2[0](2) = test2[0](3) = test2[0](0) = 5;
	test2[1](1) = test2[1](2) = test2[1](3) = test2[1](0) = 5;
	test2[2](1) = test2[2](2) = test2[2](3) = test2[2](0) = 5;
	EXPECT_TRUE(test1 == test2);
}




TEST(UnitTestImage, Affector)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	test1.InitWith(5);
	test2 = test1;
	EXPECT_TRUE(test1 == test2);
	EXPECT_FALSE(test1 == test3);

}

TEST(UnitTestImage, MultiplicationByCanal)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1*test2 == test3);
	EXPECT_FALSE(test1*test3 == test2);
}
TEST(UnitTestImage, MultiplicationByScalaire)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	int scalaire = 3;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1*scalaire == test3);
	EXPECT_FALSE(test2*scalaire == test3);
}

TEST(UnitTestImage, DivisionByCanal)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test3 / test2 == test1);
	EXPECT_FALSE(test3 / test3 == test1);
}
TEST(UnitTestImage, DivisionByScalaire)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	int scalaire = 3;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test3 / scalaire == test1);
	EXPECT_FALSE(test3 / scalaire == test2);
}
TEST(UnitTestImage, AdditionByCanal)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	test1.InitWith(2);
	test2.InitWith(4);
	test3.InitWith(6);
	EXPECT_TRUE(test1 + test2 == test3);
	EXPECT_FALSE(test2 + test3 == test1);
}
TEST(UnitTestImage, AdditionByScalaire)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	int scalaire = 4;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1 + scalaire == test3);
	EXPECT_FALSE(test2 + scalaire == test3);
}

TEST(UnitTestImage, substractionByCanal)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	test1.InitWith(2);
	test2.InitWith(4);
	test3.InitWith(6);
	EXPECT_TRUE(test3 - test2 == test1);
	EXPECT_FALSE(test2 - test3 == test1);
}

TEST(UnitTestImage, substractionByScalaire)
{
	Image test1 = Image(2, 2);
	Image test2 = Image(2, 2);
	Image test3 = Image(2, 2);
	int scalaire = 4;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1 + scalaire == test3);
	EXPECT_FALSE(test2 + scalaire == test3);
}

TEST(UnitTestImage, ExtractSubImage)
{
	
	Image test1 = Image(10, 10);
	test1[1](0) = 9;
	Image test2 = Image(2, 2);
	test2[1](0) = 9;
	Image test3 = test1.ExtractSubImage(2, 2, 0, 0);

	EXPECT_TRUE(test2 == test3);
	EXPECT_FALSE(test1 == test3);
}


TEST(UnitTestImage, GetHeight)
{
	Image c = Image(5, 10);
	int x = c.GetHeight();
	EXPECT_EQ(10, x);
	EXPECT_FALSE(10 != x);
}


TEST(UnitTestImage, CanalGetWidth)
{
	Image c = Image(5, 10);
	int x = c.GetWidth();
	EXPECT_EQ(5, x);
	EXPECT_FALSE(5 != x);
}