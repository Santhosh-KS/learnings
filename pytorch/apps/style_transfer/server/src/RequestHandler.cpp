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



#include "RequestHandler.hpp"
#include "JsonStringParser.hpp"
#include "JsonFileParser.hpp"
#include <iostream>

RequestHandler::RequestHandler(std::string &respFile):
  ModelFile(""),
  RespTemplateFile(respFile)
{
  // Empty
}


RequestHandler::RequestHandler(std::string &modelFile, std::string &respFile):
  ModelFile(modelFile),
  RespTemplateFile(respFile)
{
  GetSupportedModels();
}

RequestHandler::~RequestHandler()
{
  // Empty.
}


// We read the "/opt/data/Models.json" file
// and extract the available model information.
// {
//   "Models": ["Logistic Regression", "K-Nearest Neighbours", "CNN"]
// }
// This will help us change/modify/add the new models dynamically,
// without re-compiling the code.
bool RequestHandler::GetSupportedModels()
{
  JsonFileParser parser(ModelFile);
  std::string key("Models");
  if (parser.IsArray(key)) {
    ModelsVector = parser.GetArrayString(key);
  }
  return ModelsVector.empty();
}

// We will read the request message sent by client.
// Request message will have the json format as shown below.
// {
//  "SessionId": "abcd1234",
//  "ImageUrl": "http://someimage.jpg",
//  "ModelId": 1234
// }
// same template should be present in "/opt/data/Request.json"
RequestHandler::RequestElements
RequestHandler::ReadRequest(std::string &req)
{
  std::string sessIdKey("SessionId");
  std::string contentImgUrlKey("ContentImageUrl");
  std::string styleImgUrlKey("StyleImageUrl");

  JsonStringParser reqParser(req);
  RequestHandler::RequestElements elements;
  elements.SessionId = reqParser.GetString(sessIdKey);
  elements.ContentImageUrl = reqParser.GetString(contentImgUrlKey);
  elements.StyleIMageUrl = reqParser.GetString(styleImgUrlKey);

  return elements;
}

std::string RequestHandler::ResponseCreator(std::string &sessionId)
{
  std::string file("/tmp/pytorch/");
  //file += sessionId + "/response.json";
  file += "/response.json";

  JsonFileParser parser(file);
  return parser.GetStrigifiedJson();
}

std::string RequestHandler::ProcessRequest(std::string &req)
{
  RequestHandler::RequestElements reqElements = ReadRequest(req);

/*  if (reqElements.ModelId > ModelsVector.size()) {
    // Models.json file mismatch.
  }
  else {
    std::string python("python");
    std::string modelScript("/opt/pytorch/scripts/modelLoader.py");
    std::string cliOptions(" -u ");
    cliOptions += reqElements.ImageUrl + " -i " +
      std::to_string(reqElements.ModelId) + " -s " + reqElements.SessionId;
    std::string cmd("");
    std::string space(" ");
    cmd = python + space + modelScript + space + cliOptions;
    std::cout << "Ready to rock: " << cmd.c_str() << "\n";
    CmdUtil.ExecuteCommand(cmd);
  }*/
  return ResponseCreator(reqElements.SessionId);
}
