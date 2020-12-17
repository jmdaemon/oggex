//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
//#define DOCTEST_CONFIG_DISABLE
#include "../doctest-main.cpp"
//#include "doctest.h"

#include "EmbedAudio.h"
#include <string>
#include <sstream>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

//#define ASSERT_EXCEPTION_THROWN(std::tuple <filesystem::path, filesystem::path> parseOptions(int argc, char** argv), e) {\

//#define ASSERT_EXCEPTION_THROWN(parseOptions(int argc, char** argv), e) {\

//#define ASSERT_EXCEPTION_THROWN(parseOptions, argc, argv, e) {\

#define ASSERT_EXCEPTION_THROWN(parseOptions, e) {\
    try {\
        parseOptions(argc, argv);\
    } catch (std::exception &e) {\
      return true;\
    }

  //TEST(Exception, HasCertainMessage ) {
    //// this tests _that_ the expected exception is thrown
    //EXPECT_THROW({
        //try
        //{
            ////thisShallThrow();
        //parseOptions(0, "");
        //}
        ////catch( const MyException& e )
        //catch( const exception& e )
        //{
            //// and this tests that it has the correct message
            //EXPECT_STREQ( "Cucumber overflow", e.what() );
            //throw;
        //}
    //}, exception );
//}


TEST_CASE("Audio files can be embedded into image files") {

  SUBCASE("Test toLowerCase()") {
    cout << "Testing toLowerCase()" << endl;
    INFO("Current outPut of toLowerCase(): ");

    REQUIRE(toLowerCase("ABC") == "abc");
    REQUIRE(toLowerCase(".JPG") == ".jpg");
    CHECK(toLowerCase(".JPEG") == ".jpeg");
    CHECK(toLowerCase(".PNG") == ".png");
  }

  SUBCASE("Testing parseOptions()") {
    //cout << "Testing parseOptions()" << endl;
    //CHECK(ASSERT_EXCEPTION_THROWN(parseOptions(0, "")) == true);
    //const char *erroneous[2] = { "test1", "test2" };
    //char** input = new char[255][255];
    //char** input;
    //string test_input("test1", "test2");
    //input = **test_input;
    //char** input[2] = {"test1", "test2"};
    //char** input = nullptr;
    //string testInput[] = {"testing", "parseOptions()"};

    //char input[2][5] = {{"test1", "test2"}, "test3"};

    //char input[255][255];
    //char** inputPtr = **input;
    //typedef char Char2dArray[2][2];
    //Char2dArray a = {{'a', 'b'}, {'c','d'}}; // array
    //Char2dArray* aptr = &a; // pointer to array
    //char* input;
    //char a[2][2]={{'a','b'},{'c','d'}};
    //input = *&a;
    string inputString = "Test_parseOptions()";
    //char* inputptr = inputString.c_str();
    //char** inputpptr = &inputptr;

    std::vector<char> writable(inputString.begin(), inputString.end());
    writable.push_back('\0');
    char* inputptr = &writable[0];
    char** inputpptr = &inputptr;

    CHECK_THROWS_AS(parseOptions(0, inputpptr), std::exception);
    //TEST_CASE(Exception, HasCertainMessage ) {
      //// this tests _that_ the expected exception is thrown
      //EXPECT_THROW({
          //try
          //{
              ////thisShallThrow();
          //parseOptions(0, "");
          //}
          ////catch( const MyException& e )
          //catch( const exception& e )
          //{
              //// and this tests that it has the correct message
              //EXPECT_STREQ( "Cucumber overflow", e.what() );
              //throw;
          //}
      //}, exception );
  //} 

  } 
}
