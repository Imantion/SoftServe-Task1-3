#include <gtest/gtest.h>
#include "VariantPrimitive.h"


TEST(VariantPrimitiveTest, DefaultConstructor)
{
    VariantPrimitive vp;
    VariantPrimitive other;
    ASSERT_THROW(vp.ToInt(), std::runtime_error);
    ASSERT_THROW(vp.ToFloat(), std::runtime_error);
    ASSERT_THROW(vp.ToDouble(), std::runtime_error);
    ASSERT_THROW(vp.ToChar(), std::runtime_error);
    ASSERT_THROW(vp.ToBool(), std::runtime_error);
    ASSERT_THROW(vp = other, std::runtime_error);
    ASSERT_THROW(vp == other, std::invalid_argument);
    ASSERT_THROW(vp.get_value(), std::runtime_error);

    other = 4;
    ASSERT_THROW(vp == other, std::invalid_argument);
}

TEST(VariantPrimitiveTest, ConstructorAssignments)
{
    VariantPrimitive vp_int(42);
    ASSERT_EQ(vp_int.ToInt(), 42);
    ASSERT_EQ(std::get<int>(vp_int.get_value()), 42);

    VariantPrimitive vp_float(3.14f);
    ASSERT_FLOAT_EQ(vp_float.ToFloat(), 3.14f);
    ASSERT_EQ(std::get<float>(vp_float.get_value()), 3.14f);

    VariantPrimitive vp_double(2.718);
    ASSERT_DOUBLE_EQ(vp_double.ToDouble(), 2.718);
    ASSERT_EQ(std::get<double>(vp_double.get_value()), 2.718);

    VariantPrimitive vp_char('A');
    ASSERT_EQ(vp_char.ToChar(), 'A');
    ASSERT_EQ(std::get<char>(vp_char.get_value()), 'A');

    VariantPrimitive vp_bool(true);
    ASSERT_EQ(vp_bool.ToBool(), true);
    ASSERT_EQ(std::get<bool>(vp_bool.get_value()), true);
}

TEST(VariantPrimitiveTest, AssignmentOperators)
{
    VariantPrimitive vp;

    vp = 100;
    ASSERT_EQ(vp.ToInt(), 100);
    ASSERT_EQ(std::get<int>(vp.get_value()), 100);

    vp = 5.5f;
    ASSERT_FLOAT_EQ(vp.ToFloat(), 5.5f);
    ASSERT_EQ(std::get<float>(vp.get_value()), 5.5f);

    vp = 10.01;
    ASSERT_DOUBLE_EQ(vp.ToDouble(), 10.01);
    ASSERT_EQ(std::get<double>(vp.get_value()), 10.01);

    vp = 'Z';
    ASSERT_EQ(vp.ToChar(), 'Z');
    ASSERT_EQ(std::get<char>(vp.get_value()), 'Z');

    vp = false;
    ASSERT_EQ(vp.ToBool(), false);
    ASSERT_EQ(std::get<bool>(vp.get_value()), false);
}

TEST(VariantPrimitiveTest, CopyConstructor)
{
    VariantPrimitive vp1(123);
    VariantPrimitive vp2 = vp1;
    ASSERT_EQ(vp2.ToInt(), 123);
}

TEST(VariantPrimitiveTest, TypeMismatchThrows)
{
    VariantPrimitive vp(3.14);
    ASSERT_THROW(vp.ToInt(), std::runtime_error);
    ASSERT_THROW(vp.ToChar(), std::runtime_error);
    ASSERT_THROW(vp.ToBool(), std::runtime_error);
}

TEST(VariantPrimitiveTest, ResetFunction)
{
    VariantPrimitive vp(42);
    vp.Reset();
    ASSERT_THROW(vp.ToInt(), std::runtime_error);
}

TEST(VariantPrimitiveTest, SwapFunction)
{
    VariantPrimitive vp1(10);
    VariantPrimitive vp2(20.5f);
    vp1.Swap(vp2);

    ASSERT_FLOAT_EQ(vp1.ToFloat(), 20.5f);
    ASSERT_EQ(vp2.ToInt(), 10);
}

class VariantPrimitiveParameterizedTest : public ::testing::TestWithParam<std::tuple<VariantPrimitive::Type, std::variant<int, float, double, char, bool>>> {
};

TEST_P(VariantPrimitiveParameterizedTest, ParameterizedAssignment)
{
    auto [type, value] = GetParam();
    VariantPrimitive vp;

    switch (type) {
    case VariantPrimitive::Type::INT:
        vp = std::get<int>(value);
        ASSERT_EQ(vp.ToInt(), std::get<int>(value));
        break;
    case VariantPrimitive::Type::FLOAT:
        vp = std::get<float>(value);
        ASSERT_FLOAT_EQ(vp.ToFloat(), std::get<float>(value));
        break;
    case VariantPrimitive::Type::DOUBLE:
        vp = std::get<double>(value);
        ASSERT_DOUBLE_EQ(vp.ToDouble(), std::get<double>(value));
        break;
    case VariantPrimitive::Type::CHAR:
        vp = std::get<char>(value);
        ASSERT_EQ(vp.ToChar(), std::get<char>(value));
        break;
    case VariantPrimitive::Type::BOOL:
        vp = std::get<bool>(value);
        ASSERT_EQ(vp.ToBool(), std::get<bool>(value));
        break;
    }
}

INSTANTIATE_TEST_SUITE_P(
    VariantPrimitiveTests,
    VariantPrimitiveParameterizedTest,
    ::testing::Values(
        std::make_tuple(VariantPrimitive::Type::INT, 42),
        std::make_tuple(VariantPrimitive::Type::FLOAT, 3.14f),
        std::make_tuple(VariantPrimitive::Type::DOUBLE, 2.718),
        std::make_tuple(VariantPrimitive::Type::CHAR, 'A'),
        std::make_tuple(VariantPrimitive::Type::BOOL, true)
    )
);

class VariantPrimitiveCopyTest : public ::testing::TestWithParam<VariantPrimitive> {
};

TEST_P(VariantPrimitiveCopyTest, CopyConstuctorTest)
{
    VariantPrimitive vp(GetParam());

    ASSERT_EQ(vp, GetParam());
}

TEST_P(VariantPrimitiveCopyTest, AssigmentTest)
{
    VariantPrimitive vp;
    vp = GetParam();

    ASSERT_EQ(vp, GetParam());
}

TEST_P(VariantPrimitiveCopyTest, CompareTest)
{
    VariantPrimitive vp(4);

    ASSERT_NE(vp, GetParam());
}


INSTANTIATE_TEST_SUITE_P(
    VariantAssigmentTest,
    VariantPrimitiveCopyTest,
    ::testing::Values(VariantPrimitive(2),
                    VariantPrimitive(2.0f),
                    VariantPrimitive(2.0),
                    VariantPrimitive(true),
                    VariantPrimitive('a'))
);