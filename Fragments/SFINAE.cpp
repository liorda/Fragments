#include <stdio.h>
#include <type_traits>

#include <vector>

// SFINAE for user provided de/serialization
#include <iostream>

struct A {};

std::string to_string(const A&)
{
	return "I am a A!";
}

// Type B with a serialize method.
struct B
{
	virtual std::string serialize() const
	{
		return "I am a B!";
	}
};

// Type C with a "wrong" serialize member (not a method) and a to_string overload.
struct C
{
	std::string serialize;
};

std::string to_string(const C&)
{
	return "I am a C!";
}

struct D : A
{
	std::string serialize() const
	{
		return "I am a D!";
	}
};

struct E
{
	struct Functor
	{
		std::string operator()() {
			return "I am a E!";
		}
	};

	Functor serialize;
};

struct F : B
{
	std::string serialize() const
	{
		return "I am a F!";
	}
};

template <class T> struct hasSerialize
{
	// We test if the type has serialize using decltype and declval.
	template <typename C> static constexpr decltype(std::declval<C>().serialize(), bool()) test(int)
	{
		// We can return values, thanks to constexpr instead of playing with sizeof.
		return true;
	}

	template <typename C> static constexpr bool test(...)
	{
		return false;
	}

	// int is used to give the precedence!
	static constexpr bool value = test<T>(int());
};

template <typename T> typename std::enable_if<hasSerialize<T>::value, std::string>::type serialize(T& obj)
{
	return obj.serialize();
}

template <typename T> typename std::enable_if<!hasSerialize<T>::value, std::string>::type serialize(T& obj)
{
	return to_string(obj);
}

void SFINAE()
{
	A a;
	B b;
	C c;
	D d;
	E e;
	F f;
	B* fb = new B();

	printf("%s\n", serialize(a).c_str());
	printf("%s\n", serialize(b).c_str());
	printf("%s\n", serialize(c).c_str());
	printf("%s\n", serialize(d).c_str());
	printf("%s\n", serialize(e).c_str());
	printf("%s\n", serialize(f).c_str());
	printf("%s\n", serialize(*fb).c_str());

	delete fb;

}
