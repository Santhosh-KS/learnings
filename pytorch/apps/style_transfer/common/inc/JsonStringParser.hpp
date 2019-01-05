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



#ifndef JSON_STRING_PARSER_HPP
#define JSON_STRING_PARSER_HPP

#include "rapidjson/document.h"
#include "NotCopyable.hpp"
#include "rapidjson/prettywriter.h"

class  JsonStringParser: public NotCopyable
{
  private:
    rapidjson::Document Dom;
    JsonStringParser() = delete;
  public:
    explicit JsonStringParser(std::string &str);
    ~JsonStringParser();
    std::string GetString(std::string key);
    uint64_t GetUInt64(std::string key);
    bool SetInt(std::string key, uint64_t val);
    bool SetString(std::string key, std::string val);
    std::string GetStrigifiedJson();
};

#endif // JSON_STRING_PARSER_HPP
