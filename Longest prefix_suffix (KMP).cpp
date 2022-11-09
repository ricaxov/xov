//achar a maior sequencia contigua entre duas strings em que o suffix de uma delas é o prefix da outra!!!
void lps(string str, vector<int>&match){
    int j=0;
    match[0]=0;
    for(int i=1; i<str.size(); i++){
        while(j>0 && str[i]!=str[j]) j=match[j-1];
        if(str[i]==str[j]) j++;
        match[i]=j;
    }
}
int kmp(string word, string pattern, vector<int>&match){
    int j=0;
    for(int i=0; i<word.size(); i++){
        while(j>0 && word[i]!=pattern[j]) j=match[j-1];
        if(word[i]==pattern[j]) j++;
    }
    return j;
}
