#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "fonctions.h"


TEST(UnitTestCanal, Constructor)
{
	Canal test1 = Canal();		
	EXPECT_TRUE(test1.GetPixel()==NULL&&test1.GetWidth()==0&& test1.GetHeight()==0);
	
	Canal test2 = Canal(2,2);
	PIXTYPE *pixel = new PIXTYPE[2 * 2];
	PIXTYPE pixel2[2 * 2] = { 0,0,0,1 };	
	EXPECT_TRUE(*test2.GetPixel()== *pixel && test2.GetWidth() == 2 && test2.GetHeight() == 2);
	pixel = pixel2;
	EXPECT_FALSE(*test2.GetPixel() == *pixel && test2.GetWidth() == 2 && test2.GetHeight() == 2);

	Canal test3 = Canal(-2, 2);
	EXPECT_TRUE(test3.GetPixel() == NULL && test3.GetWidth() == 0 && test3.GetHeight() == 0);
	
}
TEST(UnitTestCanal, SetPixel)
{

	Canal test1 = Canal(2, 2);
	PIXTYPE *pixel = new PIXTYPE[2 * 2];
	pixel[2] = 1;
	test1.SetPixel(pixel);	
	EXPECT_TRUE(*test1.GetPixel() == *pixel );
	EXPECT_EQ(test1(2), 1);

	test1(1) = 3;
	pixel[1] = 3;
	EXPECT_EQ(test1(1), 3);
	EXPECT_TRUE(*test1.GetPixel() == *pixel);

	test1(1, 1) = 50;
	pixel[3] = 50;
	EXPECT_EQ(test1(3), 50);
	EXPECT_TRUE(*test1.GetPixel() == *pixel);

}

TEST(UnitTestCanal, Operatorequal)
{
	Canal test1 = Canal(2, 2);
	Canal test2= Canal(2, 2);
	PIXTYPE *pixel = new PIXTYPE[2 * 2];
	pixel[1] = test1(1) = test2(1) = 9;	
	EXPECT_TRUE(test1 == pixel);
	EXPECT_TRUE(test1 == test2);

	pixel[1]=test1(2) = 1;
	EXPECT_FALSE(test1 == test2);
	EXPECT_FALSE(test2 == pixel);
}

TEST(UnitTestCanal, InitWith)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	test1.InitWith(5);
	test2(1) = test2(2) = test2(3) = test2(4) = 5;
	EXPECT_TRUE(test1 == test2);

}




TEST(UnitTestCanal, Affector)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	test1.InitWith(5);
	test2 = test1;
	EXPECT_TRUE(test1 == test2);
	EXPECT_FALSE(test1 == test3);

}

TEST(UnitTestCanal, MultiplicationByCanal)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1*test2 == test3);
	EXPECT_FALSE(test1*test3 == test2);
}
TEST(UnitTestCanal, MultiplicationByScalaire)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	int scalaire = 3;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1*scalaire == test3);
	EXPECT_FALSE(test2*scalaire == test3);
}

TEST(UnitTestCanal, DivisionByCanal)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test3 /test2 == test1);
	EXPECT_FALSE(test3/test3 == test1);
}
TEST(UnitTestCanal, DivisionByScalaire)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	int scalaire = 3;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test3/scalaire == test1);
	EXPECT_FALSE(test3 /scalaire == test2);
}
TEST(UnitTestCanal, AdditionByCanal)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	test1.InitWith(2);
	test2.InitWith(4);
	test3.InitWith(6);
	EXPECT_TRUE(test1+test2 == test3);
	EXPECT_FALSE(test2+ test3 == test1);
}
TEST(UnitTestCanal, AdditionByScalaire)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	int scalaire = 4;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1 + scalaire == test3);
	EXPECT_FALSE(test2 + scalaire == test3);
}

TEST(UnitTestCanal, substractionByCanal)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	test1.InitWith(2);
	test2.InitWith(4);
	test3.InitWith(6);
	EXPECT_TRUE(test3 - test2 == test1);
	EXPECT_FALSE(test2- test3 == test1);
}

TEST(UnitTestCanal, substractionByScalaire)
{
	Canal test1 = Canal(2, 2);
	Canal test2 = Canal(2, 2);
	Canal test3 = Canal(2, 2);
	int scalaire = 4;
	test1.InitWith(2);
	test2.InitWith(3);
	test3.InitWith(6);
	EXPECT_TRUE(test1 + scalaire == test3);
	EXPECT_FALSE(test2 + scalaire == test3);
}

TEST(UnitTestCanal, GetHeight)
{
	Canal c = Canal(5, 10);
	int x = c.GetHeight();
	EXPECT_EQ(10, x);
	EXPECT_FALSE(10 != x);
}


TEST(UnitTestCanal, CanalGetWidth)
{
	Canal c = Canal(5, 10);
	int x = c.GetWidth();
	EXPECT_EQ(5, x);
	EXPECT_FALSE(5 != x);
}