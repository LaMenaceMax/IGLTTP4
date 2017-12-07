#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "fonctions.h"


TEST(UnitTestCanal, CanalConstructor)
{
	Canal test1 = Canal();	
	EXPECT_TRUE(test1.GetPixel()==NULL&&test1.GetWidth()==0&& test1.GetHeight()==0);
	Canal test2 = Canal(2,2);
	PIXTYPE *pixel = new PIXTYPE[2 * 2];
	PIXTYPE pixel2[2 * 2] = { 0,0,0,1 };	
	EXPECT_TRUE(*test2.GetPixel()== *pixel && test2.GetWidth() == 2 && test2.GetHeight() == 2);
	pixel = pixel2;
	EXPECT_FALSE(*test2.GetPixel() == *pixel && test2.GetWidth() == 2 && test2.GetHeight() == 2);
	
}
TEST(UnitTestCanal, CanalSetPixel)
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

TEST(UnitTestCanal, CanalOperatorequal)
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


TEST(UnitTestCanal, CanalGetHeight)
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