# A Static Function

# Description
Implement the class Exp,with a static varible count. If we constuct an object Exp, count will increse by 1. If we destory an object, count will decrese by 1.  
I will test this class with the following code.

```
cout << "Initial exp : " << Exp::get_Exp() << end;
int n;
cin >> n;
int tot = 0;
for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    if (x == 1) {
	    a[++tot] = new Exp();
    } else {
        if (tot >= 0) {
            delete a[tot];
            tot--;
        }
    }
    cout << "Current exp : " << Exp::get_exp() << endl;
 }
    
```