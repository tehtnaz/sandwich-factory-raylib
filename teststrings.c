//MUST terminate string with semicolon
#include <stdbool.h>
#include <stdio.h>
bool strEquals(char str1[32], char str2[32]){
    int i = 0;
    while(i < 32 && str1[i] != ';' && str2[i] != ';' && str1[i] == str2[i]){
        i++;
    }
    if(i == 32 || str1[i] != str2[i]){
        return false;
    }else{
        return true;
    }
}

int main(){
    char str[32];
    sprintf(str, "joe;");
    char str2[32];
    str2[0] = 'i';
    printf("%d, %d, %d, %d, %d, %d", strEquals("Big popa;", "Joe popa;"), strEquals("Joe;", "Joe;"), strEquals("Bruh", "Bruh"), strEquals("hey;", "vsauce;"), strEquals(str, "joe;"), strEquals(str2, "i"));
}