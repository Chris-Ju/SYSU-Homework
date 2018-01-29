# Copy Constructor

# Description

You need to complete the class FUN to make it satisfy the sample output.  

The declaration of class FUN

```
class FUN
{
private:
 
    char *str;
public:
    FUN(char *s);
 
    FUN(const FUN& C);
 
    ~FUN()
    {
        delete[]str;
    }
    void show();
};
```
Output:
```
Good luck!
Good luck!
```