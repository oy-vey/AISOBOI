#include <cstdio>
#include <cinttypes>
 
int main()
{
    std::printf("%zu\n", sizeof(std::int64_t));
    std::printf("%s\n", PRId64);
    std::printf("%+" PRId64 "\n", INT64_MIN);
    std::printf("%+" PRId64 "\n", INT64_MAX);
 
    std::int64_t n = 7;
    std::printf("%+" PRId64 "\n", n);
}