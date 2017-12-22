#include "gtest/gtest.h"
#include <fstream>
#include <vector>
#include "fichierIm.h"

TEST(TestIntegration, Image)
{
	Image i = Image(10, 5, 2);
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
	int x = imFile.image().GetNumBands();
	EXPECT_EQ(2, x);
	int y = imFile.image().GetHeight();
	EXPECT_EQ(5, y);
	int z = imFile.image().GetWidth();
	EXPECT_EQ(10, z);
	string nom = imFile.nom();
	EXPECT_EQ(nom, "bidon");
}