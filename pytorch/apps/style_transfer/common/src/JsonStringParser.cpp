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



#include "JsonStringParser.hpp"
#include <iostream>

JsonStringParser::JsonStringParser(std::string &str)
{
  Dom.Parse(str.c_str());
}

JsonStringParser::~JsonStringParser()
{
  // Empty
}

std::string JsonStringParser::GetString(std::string key)
{
  std::string retVal("");
  if ( Dom.HasMember(key.c_str())) {
    retVal = Dom[key.c_str()].GetString();
  }
  else {
    std::cerr << "Invalid Key " << key.c_str() << "\n";
  }
  return retVal;
}

uint64_t JsonStringParser::GetUInt64(std::string key)
{
  uint64_t retVal;
  if ( Dom.HasMember(key.c_str())) {
    retVal = Dom[key.c_str()].GetUint64();
  }
  else {
    std::cerr << "Invalid Key " << key.c_str() << "\n";
  }
  return retVal;
}

bool JsonStringParser::SetString(std::string key, std::string val)
{
  bool retVal(false);
  if ( Dom.HasMember(key.c_str())) {
    Dom[key.c_str()].SetString(val.c_str(),val.length());
    retVal = true;
  }
  else {
    std::cerr << "Invalid Key " << key.c_str() << "\n";
  }
  return retVal;
}

bool JsonStringParser::SetInt(std::string key, uint64_t val)
{
  bool retVal(false);
  if ( Dom.HasMember(key.c_str())) {
    Dom[key.c_str()].SetUint64(val);
    retVal = true;
  }
  else {
    std::cerr << "Invalid Key " << key.c_str() << "\n";
  }
  return retVal;
}

std::string JsonStringParser::GetStrigifiedJson()
{
  //printf("\nModified JSON with reformatting:\n");
  rapidjson::StringBuffer sb;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
  Dom.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
  std::cout << "stringify : " << sb.GetString() << "\n";
  return sb.GetString();
}


