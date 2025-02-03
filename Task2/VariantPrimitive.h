#pragma once

#include <variant>

class VariantPrimitive
{
public:
	enum class Type { INT, FLOAT, DOUBLE, CHAR, BOOL, UNDEFINED };

	VariantPrimitive() : m_type(Type::UNDEFINED) {}

	VariantPrimitive(int val) : m_int(val), m_type(Type::INT) {}
	VariantPrimitive(float val) : m_float(val), m_type(Type::FLOAT) {}
	VariantPrimitive(double val) : m_double(val), m_type(Type::DOUBLE) {}
	VariantPrimitive(char val) : m_char(val), m_type(Type::CHAR) {}
	VariantPrimitive(bool val) : m_bool(val), m_type(Type::BOOL) {}

	VariantPrimitive(const VariantPrimitive& other) : m_type(other.m_type) { CopyUnion(other); }

	~VariantPrimitive() = default;

	VariantPrimitive& operator=(const VariantPrimitive& other);
	VariantPrimitive& operator=(const bool& other);
	VariantPrimitive& operator=(const char& other);
	VariantPrimitive& operator=(const int& other);
	VariantPrimitive& operator=(const float& other);
	VariantPrimitive& operator=(const double& other);
	bool operator==(const VariantPrimitive& other) const;

	
	std::variant<int, float, double, char, bool> get_value() const;
	const char* get_type() const { return get_type(m_type); }

	int ToInt() const;
	float ToFloat() const;
	double ToDouble() const;
	char ToChar() const;
	bool ToBool() const;

	void Swap(VariantPrimitive& other);
	void Reset();


private:

	void CheckType(Type expected) const;
	void CopyUnion(const VariantPrimitive& other);
	const char* get_type(const Type& type) const;

private:

	Type m_type;

	union
	{
		bool m_bool;
		char m_char;
		int m_int;
		float m_float;
		double m_double;
	};
};