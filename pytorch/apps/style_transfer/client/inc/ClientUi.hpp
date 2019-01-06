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


#ifndef CLIENT_UI_WT_HPP
#define CLIENT_UI_WT_HPP


#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WComboBox.h>
#include <memory>
#include <vector>

class ClientUiApplication : public Wt::WApplication
{
private:
  Wt::WLineEdit *SearchStyleLineEdit;
  Wt::WLineEdit *SearchContentLineEdit;
  Wt::WPushButton *SearchStyleButton;
  Wt::WPushButton *SearchContentButton;
  Wt::WPushButton *PredictButton;
  Wt::WContainerWidget *MainSearchDiv;
  Wt::WContainerWidget *FooterDiv;
  Wt::WContainerWidget *MainImageDiv;
  Wt::WContainerWidget *MainComboDiv;
  Wt::WImage *StyleImage;
  Wt::WImage *ContentImage;
  Wt::WComboBox *ModelComboBox;
  std::vector<std::string> ModelsVector;
  std::string StyleImageUrl;
  std::string ContentImageUrl;

  void SetupTheme();
  void SetupHeader();
  void SetupMainBody();
  void SetupImageSearchBar(Wt::WContainerWidget *mainLeft);
  void SetupFooter();
  void SetupStyleImageWindow(Wt::WContainerWidget *mainImgDiv);
  void OnSearchStyleButtonPressed();
  void OnSearchContentButtonPressed();
  bool CheckFileExists(std::string &file);
  int ExecuteCommand(std::string &cmd);
  bool GetModelsFromJson();
  void ParseResponse(std::string resp);
  bool ValidateUrl(std::string &url);
  void SetupImgs();
  void SendRequest();
public:
  ClientUiApplication(const Wt::WEnvironment& env);
  ~ClientUiApplication();
};

#endif // CLIENT_UI_WT_HPP
