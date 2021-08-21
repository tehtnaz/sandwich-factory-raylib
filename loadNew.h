#include "dataHandling.h"
#include "levelVariables.h"
#include <stdio.h>
int loadNew(int selectedLevel, bool choice, char levelImagePath[64]){
    char str[100];
    char custom = ' ';
    int temp = 1;
    if(choice){
        while(temp == 1 && choice){
            printf("Enter path to .sf file(must be placed in custom_levels folder): ");
            char temp2[73];
            scanf("%s", temp2);
            sprintf(str, "custom_levels/%s", temp2);
            temp = readFileSF(str, true, &isDoor, &isLever, levelImagePath, &disableCam, &startingPos, &camera, Col, ladderCol, levelText, crate, &levelTexts, &levelCol, &ladderNum, &objectCol);
            if(temp == 1){
                printf("File could not be opened. Try another file.");
            }
        }
    }else{
        isLever = false;
        isDoor = false;
        sprintf(str, "resources/levels/%d.sf", selectedLevel + 1);
        temp = readFileSF(str, false, &isDoor, &isLever, levelImagePath, &disableCam, &startingPos, &camera, Col, ladderCol, levelText, crate, &levelTexts, &levelCol, &ladderNum, &objectCol);
    }
    return temp;
}