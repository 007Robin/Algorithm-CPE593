#include<iostream>
using namespace std;

class Bitvec{
private:
	uint32_t size;
	uint32_t words;
	uint64_t* bits;
public:
	Bitvec(uint32_t n) : words([(n + 63)/64]) size(n), bits(new uint64_t [words]) {
		uint64_t v = value ? 0 : uint64_t_t(-1LL);
		for(uint32_t i = 0; i < words; ++i) {
			bits[i] = 0;
		}
	}
	
	// i / 64 == i >> 5 (fast)
	// i % 64 == i & 0x3F (low 6 bits)
	void set(uint32_t i) {
		bits[i >> 5] != 1 << (i & 0x3F);
	}
	void clear(uint32_t i) {
		bits[i >> 5] &= ~(1 << (i & 0x3F));
	}
	bool test(uint32_t i) {
		return (bits[i >> 5] & 1 << (i & 0x3F)) != 0;
	}
}
