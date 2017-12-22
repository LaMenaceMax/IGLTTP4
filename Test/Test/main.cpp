#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "testCanal.h"
#include "testImage.h"
#include "testIntegration.h"

TEST(TestFonctionnalite, ModifierUneImage)
{
	Image img = Image(10, 5, 1);
	for (size_t i = 0; i < 10 ; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			img[0](i, j) = i*j;
		}
	}
	
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			EXPECT_EQ(i*j, img[0](i, j));
		}
	}

}

TEST(TestFonctionnalite, read)
{
	Image img = Image(30, 30);
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
			img[0](i, j) = 65;
	}
	fichierIm lecture("p5.pgm");
	lecture.charge();

	EXPECT_EQ(lecture.image(),img);
}

TEST(TestFonctionnalite, save)
{
	Image img = Image(30, 30);
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
			img[0](i, j) = 65;
	}
	
	fichierIm save(img, "test2.pgm");
	save.sauvegarde();

	fichierIm lecture("test2.pgm");
	lecture.charge();

	EXPECT_EQ(lecture.image(), save.image());
	EXPECT_EQ(lecture.image(), img);
}

int main(int argc,char* argv[])
{
	Canal test = Canal();
	test(-1);
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}