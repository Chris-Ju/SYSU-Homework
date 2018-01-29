class Exp
{
public:
 Exp(){count++;}
 ~Exp(){count--;}
 static int count;
 static int get_Exp(){
  return count;
 }
};
int Exp::count = 0;