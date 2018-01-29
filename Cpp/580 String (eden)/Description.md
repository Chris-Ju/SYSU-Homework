# String (eden)

## Descrption
**【The point of problem is deep copy】**

Now we have such a class String as follow:

``` cpp
class String {  
public:  
String();  
explicit String(const char *src);  
String(const String &src);

~String();

String& operator =(const String& src);  
const char* c_str() const; //return _buff  
inline char& operator[](int i);

friend ostream& operator <<(ostream& os, const String& src);

private:  
char *_buff;  
int _size;  
};
```
please finish this class.

*出题人：黄浩然*
