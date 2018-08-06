//Xin Song -- BoyerMoore
//https://www.geeksforgeeks.org/pattern-searching-set-7-boyer-moore-algorithm-bad-character-heuristic/
#include<iostream>
#include<vector>
using namespace std;

// fast target first ocurrence index in source string
int BoyerMoore(string& source, string& target){
	int m = target.size();
	int n = search.size();
	if(m == 0) return 0;
        if(m > n) return -1;
        
        // Boyer Moore's 预处理table, 未出现的全是-1，target里出现的字符，table里依次赋值i
        vector<int> table(256, -1);
        for(int i = 0; i < m; ++i) {
            table[target[i]] = i;
        }
        
        // s为要求的初次匹配索引号，j=m-1从target尾巴开始匹配
        int s = 0; 
        while(s <= (n-m)) {
            int j = m - 1;
	    // 当source target一直匹配时,j--，直至<0，证明找到了，返回s
            while(j >= 0 && source[s + j] == target[j])  {
                j--;
            }
            if(j < 0) {
                return s;
		//  s += (s+m < n)? m-badchar[txt[s+m]] : 1;   (如果要求多次匹配的地方，加这行进行下次匹配)
            }
            else {
		// 当一旦有不match的，s就跳j - table[source[s+j]], 保证source中的该坏字符
        	// 对齐target里该字符最后一次出现的地方，max(1)是确保我们get a positive shift
                s += max(1, j - table[source[s+j]]);
            }
        }
        return -1;
}

int main(){
	string search = "This is my string";
	string target = "Ng";
	cout << BoyerMoore(search, target) << endl;

	string s = "here is a simple example";
	string t = "simple";
	int res = BoyerMoore(s, t);
	cout << res << endl;
	string s1 = "hello";
	string t1 = "ll";
	int res2 = BoyerMoore(s1, t1);
	cout << res2 << endl;
	return 0;

}
