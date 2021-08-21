#pragma once
int exponentInt(int base, int power){
    if (power == 0){
        return 1;
    }else if(power == 1){
        return base;
    }else{
        int temp = base;
        for(int i = 0; i < power - 1; i++){
            temp *= base;
        }
        return temp;
    }
}

float exponentFloat(float base, int power){
    if (power == 0){
        return 1;
    }else if(power == 1){
        return base;
    }else{
        int temp = base;
        for(int i = 0; i < power - 1; i++){
            temp *= base;
        }
        return temp;
    }
}

// 10 * 10 = ex(10, 2)