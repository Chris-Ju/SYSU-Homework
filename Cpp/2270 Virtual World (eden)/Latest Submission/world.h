 #ifndef WORLD
#define WORLD

#include <iostream>

using std::cout;
using std::endl;


struct person{
	static int number;
	int fship[50] = {-1};
	int friendnum;
	person(){id = number; number++; friendnum = 0;}
	int id;

};

int person::number = 0;

void sort(int* m, int n)
{
    int tmp;
    if(n == 1)
        return;
    for(int i = 0; i < n; i++)
    {
        for(int j = n - 1; j > i; j --)
        {
            if(m[j] < m[j - 1])
            {
                tmp = m[j];
                m[j] = m[j - 1];
                m[j - 1] = tmp;
            }
        }
    }
}


class group
{
public:
    group(int i)
    {
    	fid = i;
    	k = 0;
    }
    void displayGroup()
    {

        char c;
        for(int i = 0; i < k; i++)
        {
            if(member[i].id == -1)
                continue;
            c = ',';
            cout << "Person_" << member[i].id << ":";
            if(member[i].friendnum == 0)
            {
                cout << " null" << endl;
                continue;
            }
            for(int j = 0; j < member[i].friendnum; j++)
            {
                sort(member[i].fship, member[i].friendnum);
                if(j == member[i].friendnum - 1)
                    c = '\n';
                cout << " " << member[i].fship[j] << c;
            }
        }
    }
    bool addMember(person &p)
    {
    	for(int i = 0; i < k; i++)
    	{
    		if(member[i].id == p.id)
    			return false;
    	}
    	member[k].id = p.id;
    	k++;
    	if(fid)
    	{
    		for(int i = 0; i < k - 1; i++)
    			makeFriend(member[k - 1], member[i]);
    	}

    	return true;
    }
    bool deleteMember(person &p)
    {
    	int i = 0, j = 0;
    	for(i = 0; i < k; i++)
    	{
    		if(member[i].id == p.id)
    		{
    			j = i;
    			break;
    		}
    	}
    	if(i == k)
    		return false;
    	/*for(i = 0; i < k; i++)
    	{
    		if(i == j)
    			continue;
    		breakRelation(member[j], member[i]);
    	}*/
    	/*for(i = j; i < k; i++)
    	{
    		member[j].friendnum = member[j + 1].friendnum;
    		member[j].id = member[j + 1].id;
    		for(int m = 0; m < member[j + 1].friendnum; m++)
                member[j].fship[m] = member[j + 1].fship[m];
    	}*/
    	member[j].id = -1;
    	return true;
    }
    bool makeFriend(person &p1, person &p2)
    {
    	int a = -1, b = -1;
    	for(int i = 0; i < k; i++)
        {
            if(p1.id == member[i].id)
                a = i;
            if(p2.id == member[i].id)
                b = i;
        }
    	if(a == -1 || b == -1)
            return false;
    	for(int i = 0; i < member[a].friendnum; i++)
        {
            if(member[a].fship[i] == member[b].id)
                return false;
        }
    	member[b].fship[member[b].friendnum] = member[a].id;
    	member[a].fship[member[a].friendnum] = member[b].id;
    	member[a].friendnum++;
    	member[b].friendnum++;
    	return true;
    }
    bool breakRelation(person &p1, person &p2)
    {
        int i = 0, j = 0;
        int a = -1, b = -1;
    	for(int i = 0; i < k; i++)
        {
            if(p1.id == member[i].id)
                a = i;
            if(p2.id == member[i].id)
                b = i;
        }
    	if(a == -1 || b == -1)
            return false;
        for(i = 0; i < member[a].friendnum; i++)
        {
            if(member[a].fship[i] == member[b].id)
            {
                break;
            }
        }
        if(i == member[a].friendnum)
            return false;
        member[a].fship[i] = member[a].fship[member[a].friendnum - 1];
        member[a].friendnum--;
        for(i = 0; i < member[b].friendnum; i++)
        {
            if(member[b].fship[i] == member[a].id)
                break;
        }
        member[b].fship[i] = member[b].fship[member[b].friendnum - 1];
        member[b].friendnum--;
        return true;
    }

private:
	int fid;
	person member[50];
	int k;
};


#endif
