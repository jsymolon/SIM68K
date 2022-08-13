#include "PropertiesTest.h"

#include <climits>

//----------------------------------------------------------------------------------
TEST_F(PropertiesTest,TestStrPropRead) {
	std::unique_ptr<Properties> p = std::make_unique<Properties>();
	p->load("sim68k.toml");
	std::string item = p->getString(PROPERTIES::TABLE_SOURCE, PROPERTIES::SOURCE_FONT_NAME, "");
	EXPECT_EQ(item.compare("Courier"), 0) << "Prop Font Name";
}

//----------------------------------------------------------------------------------
TEST_F(PropertiesTest,TestIntPropRead) {
	std::unique_ptr<Properties> p = std::make_unique<Properties>();
	p->load("sim68k.toml");
	int item = p->getInt(PROPERTIES::TABLE_SOURCE, PROPERTIES::SOURCE_FONT_SIZE, 0);
	EXPECT_EQ( item, 10) << "Prop Font Name Size";
}
