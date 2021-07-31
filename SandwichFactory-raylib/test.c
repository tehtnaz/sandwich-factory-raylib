#include <stdio.h>
#include <math.h>
int main(void){
    for(;;){
        int og = 10;
        float temp = og;
        float friction = 0.5f;
        float fps;
        //int num = ceilf(fps/60.00f);
        scanf("%f", &fps);
        float nums[(int)ceilf(fps/60.00f)];

        for(int i = 0; i < ceilf(fps/60.00f) && og - temp < 6; i++){
            temp -= (temp - (temp * friction)) * 60 / fps;
            nums[i] = (temp - (temp * friction)) * 60 / fps;
            printf("%f\n", temp);
        }

        temp = nums[0];
        for(int i = 0; i < (int)ceilf(fps/60.00f); i++){
            temp += nums[i];
        }
        printf("    %f\n", temp);
    }
}