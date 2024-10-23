#include <gtest/gtest.h>
#include <allocator.h>

TEST(AllocatorTest, usual) {
	Allocator allocator;
	allocator.makeAllocator(100);
	char* ptr = allocator.alloc(50);
	ptr[11] = 'f';
	EXPECT_EQ(ptr[11], 'f');
}

TEST(AllocatorTest1, zero) {
	Allocator allocator;
	allocator.makeAllocator(0);
	EXPECT_EQ(allocator.alloc(1), nullptr);
}

TEST(AllocatorTest2, outof) {
	Allocator allocator;
	allocator.makeAllocator(1);
	char* ptr = allocator.alloc(1);
	EXPECT_EQ(allocator.alloc(1), nullptr);
	allocator.reset();
	ptr = allocator.alloc(1);
	*(ptr) = 'e';
	EXPECT_EQ(*(ptr), 'e');
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}