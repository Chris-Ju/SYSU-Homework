#include "ModifyUserScene.h"
#include "Utils.h"
#include "network\HttpClient.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
#include "Utils.h"
#include <string>


using namespace rapidjson;
using namespace cocos2d::network;

cocos2d::Scene * ModifyUserScene::createScene() {
  return ModifyUserScene::create();
}

bool ModifyUserScene::init() {
  if (!Scene::init()) return false;
  
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  auto postDeckButton = MenuItemFont::create("Post Deck", CC_CALLBACK_1(ModifyUserScene::putDeckButtonCallback, this));
  if (postDeckButton) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + postDeckButton->getContentSize().height / 2;
    postDeckButton->setPosition(Vec2(x, y));
  }

  auto backButton = MenuItemFont::create("Back", [](Ref* pSender) {
    Director::getInstance()->popScene();
  });
  if (backButton) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - backButton->getContentSize().height / 2;
    backButton->setPosition(Vec2(x, y));
  }

  auto menu = Menu::create(postDeckButton, backButton, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  deckInput = TextField::create("Deck json here", "arial", 24);
  if (deckInput) {
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - 100.0f;
    deckInput->setPosition(Vec2(x, y));
    this->addChild(deckInput, 1);
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

void ModifyUserScene::putDeckButtonCallback(Ref * pSender) {
  // Your code here
  HttpRequest* request = new HttpRequest();
  request->setUrl("127.0.0.1:8000/users");
  request->setRequestType(HttpRequest::Type::PUT);
  request->setResponseCallback(CC_CALLBACK_2(ModifyUserScene::onHttpComplete, this));

  rapidjson::Document document;
  document.SetObject();
  rapidjson::Value array(rapidjson::kArrayType);
  rapidjson::Value object(rapidjson::kObjectType);
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

  std::string _data = deckInput->getString();

  rapidjson::Document k;
  k.Parse(_data.c_str());

  for (int i = 0; i < k.Size(); i++) {
    auto f = k[i].GetObjectW();
    object.Clear();
    for (auto iter = f.begin(); iter != f.end(); iter++) {
      object.AddMember(iter->name, iter->value, allocator);
    }
    array.PushBack(object, allocator);
  }
  
  document.AddMember("deck", array, allocator);
  

  StringBuffer buffer;
  rapidjson::Writer<StringBuffer> writer(buffer);
  document.Accept(writer);

  request->setRequestData(buffer.GetString(), buffer.GetSize());
  request->setTag("PUT");

  HttpClient::getInstance()->send(request);
  request->release();
}

void ModifyUserScene::onHttpComplete(HttpClient * sender, HttpResponse * data) {
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
  messageBox->setString(d["msg"].GetString());
}
