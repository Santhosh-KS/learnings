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

#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>

#include <sys/stat.h>

// system() cmd related.
#include <stdlib.h>
#include <signal.h>

#include <Wt/WMessageBox.h>
#include <Wt/WAnchor.h>
#include <Wt/WTable.h>
#include <Wt/WLength.h>

#include "ClientUi.hpp"
#include "UrlParser.hpp"
#include "TcpClient.hpp"
#include "JsonFileParser.hpp"
#include "JsonStringParser.hpp"
#include "Utils.hpp"


// Sets up the theme. Wt supports Bootstap (https://getbootstrap.com/)
// Setup Wt to use Boosstrap 3.
void ClientUiApplication::SetupTheme()
{
  useStyleSheet(Wt::WLink("css/styleSheet.css"));
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));
}

void ClientUiApplication::SetupHeader()
{
  Wt::WContainerWidget *HeaderDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDiv->setId("header");
  Wt::WContainerWidget *HeaderDivTextDiv = HeaderDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  HeaderDivTextDiv->setId("h3");
  // Header text to be displayed
  Wt::WText *HeaderText = HeaderDivTextDiv->addWidget(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("Style Transfer with Pytorch")));
}

void ClientUiApplication::SetupImageSearchBar(Wt::WContainerWidget *mainLeft)
{
  Wt::WContainerWidget *rowDiv = mainLeft->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");

  Wt::WContainerWidget *columnLeftDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnLeftDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  Wt::WContainerWidget *SearchStyleDiv = columnLeftDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  SearchStyleDiv->setStyleClass("input-group");
  Wt::WContainerWidget *SearchStyleDivLineEditDiv = SearchStyleDiv->addWidget(std::make_unique<Wt::WContainerWidget>());

  /*SearchStyleLineEdit = SearchStyleDivLineEditDiv->addWidget(
      std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me a style image to be transferred")));*/
  SearchStyleLineEdit = SearchStyleDivLineEditDiv->addWidget(
      std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("https://i.pinimg.com/originals/a5/05/44/a50544a29cce4bf5e1b3b1680b727bf8.jpg")));
  SearchStyleLineEdit->setStyleClass("form-control");

  // As soon as the page loads; mouse/cursor should be focused on search window.
  SearchStyleLineEdit->setFocus();

  Wt::WContainerWidget *StyleButtonDiv = SearchStyleDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  StyleButtonDiv->setStyleClass("input-group-btn");
  SearchStyleButton = StyleButtonDiv->addWidget(std::make_unique<Wt::WPushButton>("Style-Image"));
  SearchStyleButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));


  Wt::WContainerWidget *ColumnRightDiv= rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnRightDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  Wt::WContainerWidget *SearchContentDiv = ColumnRightDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  SearchContentDiv->setStyleClass("input-group");
  Wt::WContainerWidget *SearchContentDivLineEditDiv = SearchContentDiv->addWidget(std::make_unique<Wt::WContainerWidget>());

  /*SearchContentLineEdit = SearchContentDivLineEditDiv->addWidget(
      std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me a Content image to be Used")));*/
  SearchContentLineEdit = SearchContentDivLineEditDiv->addWidget(
      std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("https://cbsnews2.cbsistatic.com/hub/i/r/2014/03/30/da73ee19-a578-4192-bfe4-1f4a94320e09/thumbnail/1200x630/ac2fcbe08a81db308e5d2d22aa85086f/colbie-smulders-cbs-news.jpg")));
  SearchContentLineEdit->setStyleClass("form-control");

  Wt::WContainerWidget *ContentButtonDiv = SearchContentDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ContentButtonDiv->setStyleClass("input-group-btn");
  SearchContentButton = ContentButtonDiv->addWidget(std::make_unique<Wt::WPushButton>("Content-Image"));
  SearchContentButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchStyleLineEdit->enterPressed().connect
    (std::bind(&ClientUiApplication::OnSearchStyleButtonPressed, this));

  SearchStyleButton->clicked().connect(this, &ClientUiApplication::OnSearchStyleButtonPressed);

  SearchContentLineEdit->enterPressed().connect
    (std::bind(&ClientUiApplication::OnSearchContentButtonPressed, this));

  SearchContentButton->clicked().connect(this, &ClientUiApplication::OnSearchContentButtonPressed);
}


void ClientUiApplication::SetupFooter()
{
  FooterDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  FooterDiv->setId("footer");
  Wt::WContainerWidget *FooterDivTextDiv = FooterDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  // Footer Text to display
  Wt::WText *Text = FooterDivTextDiv->addWidget(
      std::make_unique<Wt::WText>(
        Wt::WString::fromUTF8("© santhoshachar08@gmail.com All Rights Reserved.")));
}


void ClientUiApplication::SetupStyleImageWindow(Wt::WContainerWidget *mainImgDiv)
{
  Wt::WContainerWidget *rowDiv = mainImgDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");


  Wt::WContainerWidget *columnLeftDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnLeftDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  Wt::WContainerWidget *StyleImageDiv =columnLeftDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  StyleImageDiv->setStyleClass("center-block");

  if (!StyleImageUrl.empty()) {
    StyleImage = StyleImageDiv->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(StyleImageUrl.c_str())));
    StyleImage->setStyleClass("img-responsive center-block");
  }

  Wt::WContainerWidget *ColumnRightDiv= rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ColumnRightDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  Wt::WContainerWidget *ContentImageDiv = ColumnRightDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  ContentImageDiv->setStyleClass("center-block");

  if (!ContentImageUrl.empty()) {
    ContentImage = ContentImageDiv->addWidget(std::make_unique<Wt::WImage>(Wt::WLink(ContentImageUrl.c_str())));
    ContentImage->setStyleClass("img-responsive center-block");
  }
}

bool ClientUiApplication::ValidateUrl(std::string &url)
{
  std::string sessId(sessionId());
  std::string cmd("curl --head --silent --fail " + url);
  Utils cmdUtil;
  bool retVal(false);

  UrlParser parse(url);
  if (parse.IsValidUrl()) {
    int ret = cmdUtil.ExecuteCommand(cmd);
    if (ret == 0) {
      retVal = true;
      std::cout << "URL: " << url.c_str() << "\n";
    }
  }
  else {
    Wt::WMessageBox::show("Information", "Please give Valid URL with .jpg or .jpeg or .png extension.", Wt::StandardButton::Ok);
  }
  return retVal;
}

void ClientUiApplication::SendRequest()
{
  std::string serverIp("localhost");

  int port(5678);
  std::string jsonFile("/opt/pytorch/data/Request.json");
  std::string sessIdKey("SessionId");

  JsonFileParser parser(jsonFile);
  TcpClient client(serverIp, port);

  std::string sessIdVal(sessionId());
  std::string contentImgUrl("ContentImageUrl");
  std::string styleImgUrl("StyleImageUrl");

  parser.SetString(sessIdKey, sessIdVal);
  parser.SetString(contentImgUrl, ContentImageUrl);
  parser.SetString(styleImgUrl, StyleImageUrl);
  std::string req(parser.GetStrigifiedJson());
  std::string resp(client.Connect(req));
  std::cout << "Before parser resp = " << resp.c_str() << "\n";
  ParseResponse(resp);
}

void ClientUiApplication::ParseResponse(std::string resp)
{
  std::string sessIdKey("SessionId");
  std::string statusKey("Status");
  std::string predKey("Prediction");

  std::cout << " resp = " << resp.c_str() << "\n";
  std::string err("ERROR");
  // Handle the error when connection to TCP socket is having some problem.
  if(resp.find(err) != std::string::npos) {
    Wt::WMessageBox::show("Information", resp.c_str(), Wt::StandardButton::Ok);
    return;
  }
  else {
    std::unique_ptr<JsonStringParser> respParser =  std::make_unique<JsonStringParser>(resp);;
    std::string sessId(respParser->GetString(sessIdKey));
    std::string status(respParser->GetString(statusKey));
    uint64_t prediction(respParser->GetUInt64(predKey));
   if (sessId.compare(sessionId()) == 0) {
      //if (status.compare("200 OK") == 0) {

      //}
      //else {
        std::string msg("Got Status ");
        msg += status + " from server";
        Wt::WMessageBox::show("Information", msg.c_str(), Wt::StandardButton::Ok);
      //}
    }
    else {
      Wt::WMessageBox::show("Information", "Invalid Session ID." , Wt::StandardButton::Ok);
    }
  }
}

void ClientUiApplication::SetupImgs()
{
  root()->removeWidget(MainImageDiv);
  root()->removeWidget(FooterDiv);
  MainImageDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  SetupStyleImageWindow(MainImageDiv);
  if (!StyleImageUrl.empty() && !ContentImageUrl.empty()) {
    SetupTransferButton();
  }
  SetupFooter();
}

void ClientUiApplication::SetupTransferButton()
{
  root()->removeWidget(MainBtnDiv);

  MainBtnDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainBtnDiv->setId("main_left");

  Wt::WContainerWidget *rowDiv = MainBtnDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  rowDiv->setStyleClass("row");

  Wt::WContainerWidget *columnLeftDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnLeftDiv->setStyleClass("col-md-3  col-xs-3 col-sm-3");

  Wt::WContainerWidget *columnMidDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnMidDiv->setStyleClass("col-md-6  col-xs-3 col-sm-3");

  TransferImageButton = columnMidDiv->addWidget(std::make_unique<Wt::WPushButton>("Abraca Dabra"));
  TransferImageButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label btn-block"));

  Wt::WContainerWidget *columnRightDiv = rowDiv->addWidget(std::make_unique<Wt::WContainerWidget>());
  columnRightDiv->setStyleClass("col-md-3  col-xs-3 col-sm-3");

  TransferImageButton->clicked().connect(this, &ClientUiApplication::OnTransferButtonPressed);

  if (ContentImageUrl.empty() || StyleImageUrl.empty()) {
    TransferImageButton->setEnabled(false);
  }
  else {
    TransferImageButton->setEnabled(true);
  }
}

// Event and button click handlers.
void ClientUiApplication::OnTransferButtonPressed()
{
  SendRequest();
}

void ClientUiApplication::OnSearchContentButtonPressed()
{
  auto url(SearchContentLineEdit->text().toUTF8());
  if (ValidateUrl(url)) {
    std::cout << "URL: " << url.c_str() << "\n";
    ContentImageUrl = url;
    SetupImgs();
  }
}

void ClientUiApplication::OnSearchStyleButtonPressed()
{
  auto url(SearchStyleLineEdit->text().toUTF8());
  if (ValidateUrl(url)) {
    std::cout << "URL: " << url.c_str() << "\n";
    StyleImageUrl = url;
    SetupImgs();
  }
}

ClientUiApplication::ClientUiApplication(const Wt::WEnvironment& env)
  : WApplication(env),
  StyleImageUrl(""),
  ContentImageUrl("")
{
  setTitle("Style Transfer using Pytorch"); // application title
  SetupTheme();
  SetupHeader();
  MainSearchDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  MainSearchDiv->setId("main_left");
  SetupImageSearchBar(MainSearchDiv);
  MainImageDiv = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  SetupStyleImageWindow(MainImageDiv);
  MainImageDiv->hide();
  MainBtnDiv= root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  SetupFooter();
}

ClientUiApplication::~ClientUiApplication()
{
  // Empty;
}
