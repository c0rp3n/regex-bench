#include <array>
#include <regex>
#include <utility>

#include <boost/regex.hpp>
#include <benchmark/benchmark.h>

const std::array<std::tuple<const char*, const char*>, 14> reg_tests = {
    // start with a simple test, this is basically a measure of the minimal overhead
    // involved in calling a regex matcher:
    std::make_tuple("abc", "abc"),
    // these are from the regex docs:
    std::make_tuple("^([0-9]+)(\\-| |$)(.*)$", "100- this is a line of ftp response which contains a message string"),
    std::make_tuple("([[:digit:]]{4}[- ]){3}[[:digit:]]{3,4}", "1234-5678-1234-456"),
    // these are from http://www.regxlib.com/
    std::make_tuple("^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$", "john@johnmaddock.co.uk"),
    std::make_tuple("^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$", "foo12@foo.edu"),
    std::make_tuple("^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$", "bob.smith@foo.tv"),
    std::make_tuple("^[a-zA-Z]{1,2}[0-9][0-9A-Za-z]{0,1} {0,1}[0-9][A-Za-z]{2}$", "EH10 2QQ"),
    std::make_tuple("^[a-zA-Z]{1,2}[0-9][0-9A-Za-z]{0,1} {0,1}[0-9][A-Za-z]{2}$", "G1 1AA"),
    std::make_tuple("^[a-zA-Z]{1,2}[0-9][0-9A-Za-z]{0,1} {0,1}[0-9][A-Za-z]{2}$", "SW1 1ZZ"),
    std::make_tuple("^[[:digit:]]{1,2}/[[:digit:]]{1,2}/[[:digit:]]{4}$", "4/1/2001"),
    std::make_tuple("^[[:digit:]]{1,2}/[[:digit:]]{1,2}/[[:digit:]]{4}$", "12/12/2001"),
    std::make_tuple("^[-+]?[[:digit:]]*\\.?[[:digit:]]*$", "123"),
    std::make_tuple("^[-+]?[[:digit:]]*\\.?[[:digit:]]*$", "+3.14159"),
    std::make_tuple("^[-+]?[[:digit:]]*\\.?[[:digit:]]*$", "-3.14159")
};

const size_t n = 1024;

static void bm_std_regex(benchmark::State& state)
{
    std::array<std::tuple<std::regex, const char*>, 14> test;
    std::transform(reg_tests.begin(), reg_tests.end(), test.begin(),
                   [](const std::tuple<const char*, const char*>& in) -> std::tuple<std::regex, const char*>
                   {
                       auto [t, m] = in;
                       return std::make_tuple(std::regex(t), m);
                   });

    for (auto _ : state)
    {
        for (auto [r, m] : test)
        {
            for (size_t i = 0; i < 1024; ++i)
            {
                std::regex_match(m, r);
            }
        }
    }
}
BENCHMARK(bm_std_regex);

static void bm_boost_regex(benchmark::State& state)
{
    std::array<std::tuple<boost::regex, const char*>, 14> test;
    std::transform(reg_tests.begin(), reg_tests.end(), test.begin(),
                   [](std::tuple<const char*, const char*> in) -> std::tuple<boost::regex, const char*>
                   {
                       auto [t, m] = in;
                       return std::make_tuple(boost::regex(t), m);
                   });

    for (auto _ : state)
    {
        for (auto [r, m] : test)
        {
            for (size_t i = 0; i < 1024; ++i)
            {
                boost::regex_match(m, r);
            }
        }
    }
}
BENCHMARK(bm_boost_regex);

BENCHMARK_MAIN();
