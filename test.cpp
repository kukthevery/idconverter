#include <iostream>
#include "cpptest.h"
#include "idconverter.h"

class idTest : public Test::Suite
{

    void test_length();
    void test_symbols();
    void test_convert();

public:
    idTest()
    {
        TEST_ADD (idTest::test_length);
        TEST_ADD (idTest::test_symbols);
        TEST_ADD (idTest::test_convert);
    }
};

void idTest::test_length()
{
    IdConverter converter;
    std::string id = "A1A2A3A4A5A6A7A8A9B1B2", id_out;
    int rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 2, "FAILED CHECK OF INVALID LENGTH");
}

void idTest::test_symbols()
{
    IdConverter converter;
    std::string id = "a1a2", id_out;
    int rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 1, "FAILED CHECK OF WRONG SYMBOLS");
    id = "D1F9G0";
    rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 1, "FAILED CHECK OF WRONG SYMBOLS");
    id = "!@#$%";
    rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 1, "FAILED CHECK OF WRONG SYMBOLS");
    id = "Z9-Z9";
    rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 3, "FAILED CHECK OF WRONG SYMBOLS");
}

void idTest::test_convert()
{
    IdConverter converter;
    std::string id = "A1A9Z9A1-A9A1-Z9", id_out;
    int rc = converter.Convert(id, id_out);
    TEST_ASSERT_MSG(rc == 0, "FAILED CONVERT VALID IDENTIFIER");
}


int main ( )
{
  idTest tests;
  Test::TextOutput output(Test::TextOutput::Verbose);
  return tests.run(output);
}
