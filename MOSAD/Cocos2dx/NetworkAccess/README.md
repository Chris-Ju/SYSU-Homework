# Cocos2d-x Week17

## 作业要求

- 实现 输入用户名和密码进行注册、登录。注册、登录后应有信息回显 (显示成功/失败，和服务端返回的信息)
- 实现 获取用户信息
- (加分项) 实现 修改个人信息
  - 修改个人信息只是修改“卡组”信息，输入框中直接输入“卡组”的json
  - 这一功能需要通过cookie认证身份，即在登录后需要记录cookie (enableCookies)
  - 使用enableCookies非常简单，因此需要在报告中体现 “思考enableCookies的作用” 才能加分

## 实现过程

- 登录与注册的实现还是很简单的，只需将账号与密码发送一个POST即可

```cpp
void LoginRegisterScene::registerButtonCallback(Ref * pSender) {
  // Your code here
  HttpRequest* request = new HttpRequest();
  request->setUrl("127.0.0.1:8000/users");
  request->setRequestType(HttpRequest::Type::POST);
  request->setResponseCallback(CC_CALLBACK_2(LoginRegisterScene::onHttpComplete, this));

  rapidjson::Document document;
  document.SetObject();
  rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

  document.AddMember("username", rapidjson::Value(usernameInput->getString().c_str(), allocator), allocator);
  document.AddMember("password", rapidjson::Value(passwordInput->getString().c_str(), allocator), allocator);
  
  StringBuffer buffer;
  rapidjson::Writer<StringBuffer> writer(buffer);
  document.Accept(writer);

  request->setRequestData(buffer.GetString(), buffer.GetSize());
  request->setTag("REGISTER");
  HttpClient::getInstance()->enableCookies(nullptr);
  HttpClient::getInstance()->send(request);
  request->release();

}


void LoginRegisterScene::onHttpComplete(HttpClient* sender, HttpResponse *data) {
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
```

- **EnableCookie**的作用:
  - 查看该方法的源码，nullptr是创建一个默认的名为cookieFile的文件，将服务端传回的session保存在此处

![](https://github.com/Chris-Ju/Picture/blob/master/CocosCookie.png?raw=true)

```cpp
void HttpClient::enableCookies(const char* cookieFile)
{
  std::lock_guard<std::mutex> lock(_cookieFileMutex);
  if (cookieFile)
  {
      _cookieFilename = std::string(cookieFile);
  }
  else
  {
      _cookieFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
  }
}
```

- 修改个人信息，这个 json 的处理调试了好久

```cpp
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
    //object.Clear();
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
```

- 获取用户信息，json格式拿输出一点一点测试。

```cpp
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
```