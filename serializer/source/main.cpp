#include "serializer.h"
#include <sstream>

struct Data {
	uint64_t a;
	bool b;
	uint64_t c;

	template<typename Serializer>
	Error serialize(Serializer& serializer) {
		return serializer(a, b, c);
	}
};

int main()
{
    Data x{ 1, true, 2 };
    std::stringstream stream{};

    Serializer<Data> serializer(stream);
    serializer.save(x);

    Data y{ 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    std::cout << (err == Error::NoError) << (x.a == y.a) << (x.b == y.b) << (x.c == y.c);

    return 0;
}