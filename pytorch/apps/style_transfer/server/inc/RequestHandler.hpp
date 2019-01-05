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



#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>
#include "NotCopyable.hpp"
#include "JsonStringParser.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>
#include <memory>

class RequestHandler : public NotCopyable
{
  private:
    std::vector<std::string> ModelsVector;
    std::string ModelFile;
    std::string RespTemplateFile;
    std::string ResponseTemplate;

    Utils CmdUtil;

    struct RequestElements {
      std::string SessionId;
      std::string ImageUrl;
      uint64_t ModelId;
    };

    inline bool HaveModelsToWork() { return ModelsVector.empty(); }

    bool GetSupportedModels();
    void GetResponseTemplate();
    RequestElements ReadRequest(std::string &req);
    std::string ResponseCreator(std::string &sessionId);
  public:
    RequestHandler(std::string &modelFile, std::string &respFile);
    ~RequestHandler();
    std::string ProcessRequest(std::string &req);
};

#endif // REQUEST_HANDLER_HPP
