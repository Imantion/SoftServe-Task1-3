#include <gtest/gtest.h>
#include "StringList.h"


class StringListTestFixture : public testing::Test
{
public:
	StringListTestFixture() = default;
	virtual ~StringListTestFixture() = default;

	void SetUp() override
	{
		StringListInit(&m_list);

		// Appending chars to the list
		{
			StringListAdd(m_list, "My");
			StringListAdd(m_list, "name");
			StringListAdd(m_list, "is");
			StringListAdd(m_list, "Kira.");
			StringListAdd(m_list, "Yoshikage");
			StringListAdd(m_list, "I'm");
			StringListAdd(m_list, "33");
			StringListAdd(m_list, "years");
			StringListAdd(m_list, "old.");
			StringListAdd(m_list, "My");
			StringListAdd(m_list, "house");
			StringListAdd(m_list, "is");
			StringListAdd(m_list, "in");
			StringListAdd(m_list, "the");
			StringListAdd(m_list, "northeast");
			StringListAdd(m_list, "section");
			StringListAdd(m_list, "of");
			StringListAdd(m_list, "Morioh,");
			StringListAdd(m_list, "where");
			StringListAdd(m_list, "all");
			StringListAdd(m_list, "the");
			StringListAdd(m_list, "villas");
			StringListAdd(m_list, "are,");
			StringListAdd(m_list, "and");
			StringListAdd(m_list, "I'm");
			StringListAdd(m_list, "not");
			StringListAdd(m_list, "married");
			StringListAdd(m_list, "yeat");
		}
	}

	void TearDown() override
	{
		StringListDestroy(&m_list);
	}

protected:
	StringList m_list = nullptr;
};

TEST(StringListTests, ExceptionsTest)
{
	EXPECT_THROW(StringListReplaceInStrings(nullptr, "before", "after"), std::invalid_argument);
	EXPECT_THROW(StringListSort(nullptr), std::invalid_argument);
	EXPECT_THROW(StringListSize(nullptr), std::invalid_argument);
	EXPECT_THROW(StringListRemoveDuplicates(nullptr), std::invalid_argument);
	EXPECT_THROW(StringListGetElement(nullptr, 0), std::invalid_argument);
	EXPECT_THROW(StringListIndexOf(nullptr, "test"), std::invalid_argument);
	EXPECT_THROW(StringListRemove(nullptr, "test"), std::invalid_argument);
	EXPECT_THROW(StringListAdd(nullptr, "test"), std::invalid_argument);
	EXPECT_THROW(StringListInit(nullptr), std::invalid_argument);

	StringList list;
	StringListInit(&list);
	EXPECT_THROW(StringListGetElement(list, 1), std::out_of_range);
	StringListDestroy(&list);
}

TEST(StringListTests, TestStringListAdd)
{
	StringList list = nullptr;
	StringListInit(&list);
	
	StringListAdd(list, "Apple");
	ASSERT_STREQ("Apple", StringListGetElement(list, 0));

	StringListAdd(list, "Banana");
	ASSERT_STREQ("Banana", StringListGetElement(list, 1));
}

TEST(StringListTests, TestStringListSorting)
{
	StringList list = nullptr;
	StringListInit(&list);
	const char* str[] = { "ca", "ba", "ad", "ab", "da", "dd", "d", "cc" };
	uint8_t amount = sizeof(str) / sizeof(char*);
	for (size_t i = 0; i < amount; i++)
	{
		StringListAdd(list, str[i]);
	}

	StringListSort(&list);

	const char* expected[] = { "ab", "ad", "ba", "ca", "cc", "d", "da", "dd" };

	for (size_t i = 0; i < amount; i++)
	{
		EXPECT_STREQ(expected[i], StringListGetElement(list, (int)i)) << "Mismatch at index " << i;
	}



	StringListDestroy(&list);
}

TEST_F(StringListTestFixture, TestStringListSize)
{
	ASSERT_EQ(28, StringListSize(m_list));
}

TEST_F(StringListTestFixture, TestStingListGetElement)
{
	ASSERT_STREQ("My", StringListGetElement(m_list, 0));
	ASSERT_STREQ("name", StringListGetElement(m_list, 1));
	ASSERT_STREQ("is", StringListGetElement(m_list, 2));
	ASSERT_STREQ("section", StringListGetElement(m_list, 15));
	ASSERT_STREQ("married", StringListGetElement(m_list, 26));
	ASSERT_STREQ("yeat", StringListGetElement(m_list, 27));
}

TEST_F(StringListTestFixture, TestStringListGetIndexOf)
{
	ASSERT_EQ(0, StringListIndexOf(m_list, "My"));
	ASSERT_EQ(1, StringListIndexOf(m_list, "name"));
	ASSERT_EQ(2, StringListIndexOf(m_list, "is"));
	ASSERT_EQ(15, StringListIndexOf(m_list, "section"));
	ASSERT_EQ(26, StringListIndexOf(m_list, "married"));
	ASSERT_EQ(27, StringListIndexOf(m_list, "yeat"));
}

TEST_F(StringListTestFixture, TestStringListAdd)
{
	const char* str[] = { "Erwin", "Smith" };
	uint8_t amount = sizeof(str) / sizeof(void*);

	for (size_t i = 0; i < amount; i++)
	{
		StringListAdd(m_list, str[i]);
		int newSize = StringListSize(m_list);
		ASSERT_EQ(28 + 1 + i, newSize);
		ASSERT_STREQ(str[i], StringListGetElement(m_list, newSize - 1));
	}
}

TEST_F(StringListTestFixture, TestStringListRemove)
{
	StringListRemove(&m_list, "My");
	ASSERT_EQ(26, StringListSize(m_list));
	ASSERT_EQ(-1, StringListIndexOf(m_list, "My"));
}

TEST_F(StringListTestFixture, TestStringListRemoveDuplicates)
{
	StringListRemoveDuplicates(&m_list);
	ASSERT_EQ(24, StringListSize(m_list));
}

TEST_F(StringListTestFixture, TestStringListReplaceInStrings)
{
	StringListReplaceInStrings(m_list, "My", "His");
	ASSERT_STREQ("His", StringListGetElement(m_list, 0));
	ASSERT_STREQ("His", StringListGetElement(m_list, 9));

	StringListReplaceInStrings(m_list, "ea", "amogus");
	ASSERT_STREQ("yamogusrs", StringListGetElement(m_list, 7));
	ASSERT_STREQ("northamogusst", StringListGetElement(m_list, 14));
	ASSERT_STREQ("yamogust", StringListGetElement(m_list, 27));

	StringListReplaceInStrings(m_list, "ya", "bibi");
	ASSERT_STREQ("bibimogusrs", StringListGetElement(m_list, 7));
	ASSERT_STREQ("bibimogust", StringListGetElement(m_list, 27));

	StringListReplaceInStrings(m_list, "srs", "HoI");
	ASSERT_STREQ("bibimoguHoI", StringListGetElement(m_list, 7));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}