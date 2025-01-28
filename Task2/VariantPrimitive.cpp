#include "VariantPrimitive.h"

#include <stdexcept>
#include <format>

VariantPrimitive& VariantPrimitive::operator=(const VariantPrimitive& other)
{
	if (this != &other)
	{
		m_type = other.m_type;
		CopyUnion(other);
	}
	return *this;
}

VariantPrimitive& VariantPrimitive::operator=(const bool& other)
{
	m_type = Type::BOOL;
	m_bool = other;
	return *this;
}

VariantPrimitive& VariantPrimitive::operator=(const char& other)
{
	m_type = Type::CHAR;
	m_char = other;
	return *this;
}

VariantPrimitive& VariantPrimitive::operator=(const int& other)
{
	m_type = Type::INT;
	m_int = other;
	return *this;
}

VariantPrimitive& VariantPrimitive::operator=(const float& other)
{
	m_type = Type::FLOAT;
	m_float = other;
	return *this;
}

VariantPrimitive& VariantPrimitive::operator=(const double& other)
{
	m_type = Type::DOUBLE;
	m_double = other;
	return *this;
}

const char* VariantPrimitive::get_type(const Type& type) const
{
	switch (type) {
	case Type::INT: return "INT";
	case Type::FLOAT: return "FLOAT";
	case Type::DOUBLE: return "DOUBLE";
	case Type::CHAR: return "CHAR";
	case Type::BOOL: return "BOOL";
	default: return "UNDEFINED";
	}
}

std::variant<int, float, double, char, bool> VariantPrimitive::get_value() const
{
	switch (m_type)
	{
	case VariantPrimitive::Type::INT:
		return m_int;
	case VariantPrimitive::Type::FLOAT:
		return m_float;
	case VariantPrimitive::Type::DOUBLE:
		return m_double;
	case VariantPrimitive::Type::CHAR:
		return m_char;
	case VariantPrimitive::Type::BOOL:
		return m_bool;
	case VariantPrimitive::Type::UNDEFINED:
		throw std::runtime_error("Undefined type");
	}
}

int VariantPrimitive::ToInt() const
{
	CheckType(Type::INT);
	return m_int;
}

float VariantPrimitive::ToFloat() const
{
	CheckType(Type::FLOAT);
	return m_float;
}

double VariantPrimitive::ToDouble() const
{
	CheckType(Type::DOUBLE);
	return m_double;
}

char VariantPrimitive::ToChar() const
{
	CheckType(Type::CHAR);
	return m_char;
}

bool VariantPrimitive::ToBool() const
{
	CheckType(Type::BOOL);
	return m_bool;
}

void VariantPrimitive::Swap(VariantPrimitive& other)
{
	std::swap(m_type, other.m_type);
	std::swap(m_int, other.m_int);
}

void VariantPrimitive::Reset()
{
	m_type = Type::UNDEFINED;
	m_double = 0.0; // As double is the largest type, it will be enough to reset the union
}

void VariantPrimitive::CheckType(Type expected) const
{
	if (m_type != expected)
	{
		throw std::runtime_error(std::format("Type mismatch: expected {}, got {}", get_type(m_type), get_type(expected)));
	}
}

void VariantPrimitive::CopyUnion(const VariantPrimitive& other)
{
	switch (m_type)
	{
	case Type::BOOL: m_bool = other.m_bool; break;
	case Type::CHAR: m_char = other.m_char; break;
	case Type::INT: m_int = other.m_int; break;
	case Type::FLOAT: m_float = other.m_float; break;
	case Type::DOUBLE: m_double = other.m_double; break;
	}
}

