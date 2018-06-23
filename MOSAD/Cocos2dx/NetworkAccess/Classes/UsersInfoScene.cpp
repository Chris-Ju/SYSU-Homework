#include "UsersInfoScene.h"
#include "network\HttpClient.h"
#include "json\document.h"
#include "Utils.h"

using namespace cocos2d::network;
using namespace rapidjson;

cocos2d::Scene * UsersInfoScene::createScene() {
  return UsersInfoScene::create();
}

bool UsersInfoScene::init() {
  if (!Scene::init()) return false;

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  auto getUserButton = MenuItemFont::create("Get User", CC_CALLBACK_1(UsersInfoScene::getUserButtonCallback, this));
  if (getUserButton) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + getUserButton->getContentSize().height / 2;
    getUserButton->setPosition(Vec2(x, y));
  }

  auto backButton = MenuItemFont::create("Back", [](Ref* pSender) {
    Director::getInstance()->popScene();
  });
  if (backButton) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - backButton->getContentSize().height / 2;
    backButton->setPosition(Vec2(x, y));
  }

  auto menu = Menu::create(getUserButton, backButton, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  limitInput = TextField::create("limit", "arial", 24);
  if (limitInput) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - 100.0f;
    limitInput->setPosition(Vec2(x, y));
    this->addChild(limitInput, 1);
  }

  messageBox = Label::create("", "arial", 30);
  if (messageBox) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    messageBox->setPosition(Vec2(x, y));
    this->addChild(messageBox, 1);
  }

  return true;
}

void UsersInfoScene::getUserButtonCallback(Ref * pSender) {
  // Your code here
  HttpRequest* request = new HttpRequest();
  std::string url = "127.0.0.1:8000/users?limit=" + limitInput->getString();
  request->setUrl(url);
  request->setRequestType(HttpRequest::Type::GET);
  request->setResponseCallback(CC_CALLBACK_2(UsersInfoScene::onHttpComplete, this));

  request->setTag("GETUSERS");

  HttpClient::getInstance()->send(request);
  request->release();
}

void UsersInfoScene::onHttpComplete(HttpClient* sender, HttpResponse *data) {
  HttpResponse *response = (HttpResponse*)data;
  if (!response) {
    return;
  }
  if (!response->isSucceed()) {
    CCLOG("response failed");
    return;
  }
  std::vector<char> * buffer = response->getResponseData();
  std::string temp;
  for (auto i = 0; i < buffer->size(); i++) {
    temp += (*buffer)[i];
  }
  rapidjson::Document d;
  d.Parse<0>(temp.c_str());
  if (!d["status"].GetBool()) {
    messageBox->setString(d["msg"].GetString());
    return;
  }
  std::string result;
  result.clear();
  auto _data = d["data"].GetArray();
  
  for (int i = 0; i < _data.Size(); i++) {
    result = result + "Username:" + _data[i]["username"].GetString() + "\n";
    result = result + "Deck:" + "\n";
    auto _deck = _data[i]["deck"].GetArray();
    
    for (int j = 0; j < _deck.Size(); j++) {
      auto f = _deck[j].GetObjectW();
      
      for (auto iter = f.MemberBegin(); iter != f.MemberEnd(); iter++) {
        result = result + "  " + (iter->name).GetString() + ":" + std::to_string((iter->value).GetInt()) + "\n";
      }
      
      result = result + "  ---" + "\n";
    }
    result = result + "---\n";
  }

  messageBox->setString(result);
}
