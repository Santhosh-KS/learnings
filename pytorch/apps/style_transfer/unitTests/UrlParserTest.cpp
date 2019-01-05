/*
   MIT License

   Copyright (c) 2018 santhoshachar08@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/


#include "gtest/gtest.h"
#include "UrlParser.hpp"
#include <string>

class UrlParserTest: public ::testing::Test {
  protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
      // Code here will be called immediately after each test
      // (right before the destructor).
    }
};

TEST_F(UrlParserTest, ValidPngUrl) {
  std::string testUrl("http://luisvalesilva.com/datasimple/images/digitre/b64_2_preprocessing_3.png");
  UrlParser parser(testUrl);
  EXPECT_EQ(true,parser.IsValidUrl());
}

TEST_F(UrlParserTest, ValidJpgUrl){
  std::string testUrl("http://luisvalesilva.com/datasimple/images/digitre/b64_2_preprocessing_3.jpg");
  UrlParser parser(testUrl);
  EXPECT_EQ(true,parser.IsValidUrl());
}

TEST_F(UrlParserTest, ValidJpegUrl){
  std::string testUrl("http://luisvalesilva.com/datasimple/images/digitre/b64_2_preprocessing_3.jpeg");
  UrlParser parser(testUrl);
  EXPECT_EQ(true,parser.IsValidUrl());
}

TEST_F(UrlParserTest, InvalidUrl){
  std::string testUrl("http://luisvalesilva.com/datasimple/images/digitre/b64_2_preprocessing_3");
  UrlParser parser(testUrl);
  EXPECT_EQ(false,parser.IsValidUrl());
}

TEST_F(UrlParserTest, GarbageUrl){
  std::string testUrl("htp:/xx");
  UrlParser parser(testUrl);
  EXPECT_EQ(false,parser.IsValidUrl());
}

TEST_F(UrlParserTest, FtpUrl){
  std::string testUrl("ftp://xx");
  UrlParser parser(testUrl);
  EXPECT_EQ(false,parser.IsValidUrl());
}

TEST_F(UrlParserTest, BlankUrl){
  std::string testUrl("");
  UrlParser parser(testUrl);
  EXPECT_EQ(false,parser.IsValidUrl());
}

TEST_F(UrlParserTest, NotAnUrl){
  std::string testUrl("abcdef");
  UrlParser parser(testUrl);
  EXPECT_EQ(false,parser.IsValidUrl());
}
