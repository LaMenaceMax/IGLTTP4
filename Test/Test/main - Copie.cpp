#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"
#include "fonctions.h"
#include "testCanal.h"
#include "testImage.h"




TEST(TestIntegration, Canal)
{
	Canal c = Canal(10, 5);
	int cy = c.GetHeight();
	EXPECT_EQ(5, cy);
	int cz = c.GetWidth();
	EXPECT_EQ(10, cz);
}

TEST(TestIntegration, Image)
{
	Image i = Image(10, 5, 2);
	Canal c = i[0];
	int cy = c.GetHeight();
	EXPECT_EQ(5, cy);
	int cz = c.GetWidth();
	EXPECT_EQ(10, cz);
	int x = i.GetNumBands();
	EXPECT_EQ(2, x);
	int y = i.GetHeight();
	EXPECT_EQ(5, y);
	int z = i.GetWidth();
	EXPECT_EQ(10, z);
}


TEST(TestIntegration, fichierIm)
{
	Image i = Image(10, 5, 2);
	fichierIm imFile = fichierIm(i, "bidon");
	Canal c = imFile.image[0];
	int cy = c.GetHeight();
	EXPECT_EQ(5, cy);
	int cz = c.GetWidth();
	EXPECT_EQ(10, cz);
	int x = imFile.image().GetNumBands();
	EXPECT_EQ(2, x);
	int y = imFile.image().GetHeight();
	EXPECT_EQ(5, y);
	int z = imFile.image().GetWidth();
	EXPECT_EQ(10, z);
	string nom = imFile.nom();
	EXPECT_EQ(nom, "bidon");
}


TEST(TestFonctionnalite, ModifierUneImage)
{
	Image img = Image(10, 5, 1);
	for (int i = 0; i < 10 ; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			img[0](i, j) = i*j;
		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			EXPECT_EQ(i*j, img[0](i, j));
		}
	}

}


int main(int argc,char* argv[])
{
	Canal test = Canal();
	test(-1);
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}