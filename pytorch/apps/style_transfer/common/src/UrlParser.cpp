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


#include "UrlParser.hpp"

UrlParser::UrlParser(std::string &url) : Url(url),
  IsValid(false)
{
  Parse();
}

UrlParser::~UrlParser()
{
  // Empty.
}

void UrlParser::Parse()
{
  std::string http("http://");
  std::string https("https://");
  if (Url.compare(0,7,http)) {
    IsValid = true;
  }
  else if (Url.compare(0,8,https)) {
    IsValid = true;
  }
  else {
    IsValid = false;
  }
  if (IsValid) {
    IsValid = IsImageUrl();
  }
}

bool UrlParser::IsImageUrl()
{
//https://www.publicdomainpictures.net/pictures/30000/velka/numbers.jpg
  auto pos = Url.find_last_of('.');
  auto val(false);
  const auto extension = Url.substr(pos+1);
  if (extension.compare("jpg") == 0) {
    val = true;
  }
  else if (extension.compare("jpeg") == 0) {
    val = true;
  }
  else if (extension.compare("png") == 0) {
    val = true;
  }
  return val;
}

bool UrlParser::IsValidUrl() const
{
  return IsValid;
}
