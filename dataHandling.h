#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "levelStructs.h"
#include "exponent.h"
#include "compareString.h"
#pragma once

//File Structure
//    data;data;data;...;!
//    ! = terminates the file

int parseInt(char input[11], int arraySize){ // Sometimes while parsing garbage data could be given (input: "128;ns" however still outputs to 128)
    char ch = '?';
    int output = 0;
    int i = 0;

    bool isEnd = false;

    if(arraySize == 0){
        perror("Warning parsing - tried to parse 0 characters");
        return 0;
    }
    if(arraySize > 10){
        perror("Error parsing - output int would exceed 32bit number limit");
        return 0;
    }

    for(; i < 11 && !isEnd && i < arraySize; i++){ // Warning: I left this as a for statement while not declaring a variable because I'm a lazy bastard
        ch = input[i];

        switch(ch){
            case '0':
                output = output * 10;
                break;
            case '1':
                output = (output * 10) + 1;
                break;
            case '2':
                output = (output * 10) + 2;
                break;
            case '3':
                output = (output * 10) + 3;
                break;
            case '4':
                output = (output * 10) + 4;
                break;
            case '5':
                output = (output * 10) + 5;
                break;
            case '6':
                output = (output * 10) + 6;
                break;
            case '7':
                output = (output * 10) + 7;
                break;
            case '8':
                output = (output * 10) + 8;
                break;
            case '9':
                output = (output * 10) + 9;
                break;
            case '!':
            case ';':
            case ',':
                isEnd = true;
                break;
            case '.':
                perror("Received \'.\' as input. This will fail because the parser checks for integers. Ending function...");
                isEnd = true;
                output = 0;
                break;
        }
        //printf("%c + %d\n", ch, output);
    }
    //printf("final char + output: %c + %d\n", ch, output);
    if(!isEnd && i != arraySize){
        perror("Reached end of parse before termination");
        printf("Given Max size: %d\n", arraySize);
        
    }
    printf("Given string: %s", input);
    printf(" - Output: %d\n", output);
    return output;
}

float parseFloat(char input[12]){
    char ch;
    float output = 0;

    int decimal = 0;
    bool isEnd = false;

    for(int i = 0; i < 12 && !isEnd; i++){
        ch = input[i];

        if(decimal != 0 && ch != '!' && ch != ';' && ch != ')' && ch != ','){
            decimal++;
        }
        switch(ch){
            case '0':
                output = output * 10;
                break;
            case '1':
                output = (output * 10) + 1;
                break;
            case '2':
                output = (output * 10) + 2;
                break;
            case '3':
                output = (output * 10) + 3;
                break;
            case '4':
                output = (output * 10) + 4;
                break;
            case '5':
                output = (output * 10) + 5;
                break;
            case '6':
                output = (output * 10) + 6;
                break;
            case '7':
                output = (output * 10) + 7;
                break;
            case '8':
                output = (output * 10) + 8;
                break;
            case '9':
                output = (output * 10) + 9;
                break;
            case '!':
            case ';':
            case ',':
            case ')':
                isEnd = true;
                break;
            case '.':
                decimal++;
                break;
        }
        //printf("%c + %f\n", ch, output);
    }
    for(int i = 0; i < decimal - 1; i++){
        output /= 10;
        printf("0.1 ^ %d * %f\n", i, output);
    }
    

    if(!isEnd){
        perror("Reached end of parse before termination");
        
    }
    printf("Given string: %s - Output: %f. Watch out for float precision issues\n", input, output);
    return output;
}

//Input structure (data,data) or data,data) aka: does not require starting bracket
Vector2 readVector2(char input[20]){
    char ch;
    int inputSelect = 0;
    Vector2 output;
    char sendToParse[11];
    int i;

    printf("readVector2 = Reading \"%s\"\n", input);

    ch = input[inputSelect];

    if(ch == '('){
        inputSelect++;
        ch = input[inputSelect];
    }

    if(ch == ',' || ch == ')'){
        inputSelect++;
        ch = input[inputSelect];
        output.x = 0;
    }else{
        i = 0;
        while(ch != ','){
            sendToParse[i] = ch;
            inputSelect++;
            ch = input[inputSelect];
            i++;
            printf("%d-", i);
        }
        sendToParse[i] = ';';
        printf("%d\n", i);
        output.x = parseInt(sendToParse, i + 1);
        inputSelect++;
        ch = input[inputSelect];
    }

    if(ch == ')'){
        inputSelect++;
        ch = input[inputSelect];
        output.y = 0;
    }else{
        i = 0;
        while(ch != ')'){
            sendToParse[i] = ch;
            inputSelect++;
            ch = input[inputSelect];
            i++;
            printf("%d-", i);
        }
        sendToParse[i] = ';';
        printf("%d\n", i);
        output.y = parseInt(sendToParse, i + 1);
        inputSelect++;
        ch = input[inputSelect];
    }

    return output;
}

Vector2 readVector2Float(char input[20]){
    char ch;
    int inputSelect = 0;
    Vector2 output;
    char sendToParse[11];
    int i;

    ch = input[inputSelect];

    if(ch == '('){
        inputSelect++;
        ch = input[inputSelect];
    }

    if(ch == ',' || ch == ')'){
        inputSelect++;
        ch = input[inputSelect];
        output.x = 0;
    }else{
        i = 0;
        while(ch != ','){
            sendToParse[i] = ch;
            inputSelect++;
            ch = input[inputSelect];
            i++;
        }
        sendToParse[i] = ';';
        output.x = parseFloat(sendToParse);
        inputSelect++;
        ch = input[inputSelect];
    }

    if(ch == ')'){
        inputSelect++;
        ch = input[inputSelect];
        output.y = 0;
    }else{
        i = 0;
        while(ch != ')'){
            sendToParse[i] = ch;
            inputSelect++;
            ch = input[inputSelect];
            i++;
        }
        sendToParse[i] = ';';
        output.y = parseFloat(sendToParse);
        inputSelect++;
        ch = input[inputSelect];
    }

    return output;
}

Color parseColor(char input[17], int inputSize){
    int select = 0;
    Color output;
    char sendToParse[3];
    int i;
    int temp;

    if(input[select] == '('){
        select++;
    }

    for(int s = 0; s < 4; s++){
        i = 0;
        while(input[select] != ',' && i < 4 && input[select] != ')'){
            //printf("select: %d, i: %d, char: %c\n", select, i, input[select]);
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        select++;
        if(i > 3){
            perror("parseColor - Value exceeds maximum (Overflowed. Missing comma or parenthesis)");
        }
        temp = parseInt(sendToParse, i);
        if(temp > 255){
            perror("parseColor - Value exceeds maximum (Value largeer than 255)");
            temp = 255;
        }
        switch(s){
            case 0:
                output.r = temp;
                break;
            case 1:
                output.g = temp;
                break;
            case 2:
                output.b = temp;
                break;
            case 3:
                output.a = temp;
                break;
        }
        //printf("i: %s o: %d, s: %d, select: %d\n", sendToParse, temp, s, select);
    }
    return output;

}

void readIntArray(char input[128], int output[16]){
    char ch;
    int inputSelect = 0;
    char sendToParse[11];
    int i;
    int objectSelect = 0;

    ch = input[inputSelect];

    if(ch == '('){
        inputSelect++;
        ch = input[inputSelect];
    }

    while(ch != ')'){
        if(ch == ','){
            inputSelect++;
            ch = input[inputSelect];
            output[objectSelect] = 0;
        }else{
            i = 0;
            while(ch != ',' && ch != ')'){
                sendToParse[i] = ch;
                inputSelect++;
                ch = input[inputSelect];
                i++;
            }
            sendToParse[i] = ';';
            output[objectSelect] = parseInt(sendToParse, i + 1);
            if(ch == ','){
                inputSelect++;
                ch = input[inputSelect];
            }
        }
        objectSelect++;
    }
    printf("readIntArray finished - given string: %s\n", input);
}

int readBoolArray(char input[16], bool output[8]){
    char ch;
    int inputSelect = 0;
    int objectSelect = 0;

    ch = input[inputSelect];

    if(ch == '('){
        inputSelect++;
        ch = input[inputSelect];
    }

    while(ch != ')'){
        if(objectSelect > 8){
            perror("readBoolArray - Too much bools given or array could not be terminated");
            return 1;
        }
        if(ch == ','){
            inputSelect++;
            ch = input[inputSelect];
            output[objectSelect] = false;
        }else{
            if(ch == '0' || ch == 'f' || ch == 'F'){
                output[objectSelect] = false;
            }else if(ch == '1' || ch == 't' || ch == 'T'){
                output[objectSelect] = true;
            }else{
                perror("readBoolArray - input is not bool");
                return 1;
            }
            inputSelect++;
            ch = input[inputSelect];
            if(ch != ','){
                if(ch != ')'){
                    perror("readBoolArray - input is not bool");
                    return 1;
                }
            }else{
                inputSelect++;
                ch = input[inputSelect];
            }
        }
        objectSelect++;
    }
    return 0;
}

bool parseBool(char ch){
    if(ch == '0' || ch == 'f' || ch == 'F'){
        printf("parseBool - Returned false\n");
        return false;
    }else if (ch == '1' || ch == 't' || ch == 'T'){
        printf("parseBool - Returned true\n");
        return true;
    }else{
        perror("parseBool - Input is not bool");
        return false;
    }
}

//Note: Does not read ladder property
//You MUST either give the script a inputSize or terminating character ( chars = ';' and ')' )
//Function accepts '(' as first character
BoxCollider2D parseBoxCollider(char input[128], int inputSize, bool isLadder){
    int select = 0;
    char sendToParse[11];
    int temp;
    int i;
    BoxCollider2D returnedCol;

    if(input[select] == '('){
        select++;
    }

    for(int propertySelect = 0; propertySelect < 4; propertySelect++){
        i = 0;
        temp = 0;
        while(input[select] != ','){
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        select++;
        temp = parseInt(sendToParse, i);
        switch(propertySelect){
            case 0:
                returnedCol.x = temp;
                break;
            case 1:
                returnedCol.y = temp;
                break;
            case 2:
                returnedCol.sizeX = temp;
                break;
            case 3:
                returnedCol.sizeY = temp;
                break;
        }
    }
    returnedCol.trigger = parseBool(input[select]);
    select++;
    if(input[select] == ','){
        select++;
    }else{
        perror("parseBoxCollider2D - Input is not a bool");
    }
    returnedCol.enabled = parseBool(input[select]);
    if(input[select] != ';' && input[select] != ')' && (select < inputSize - 1 || select > inputSize)){
        perror("parseBoxCollider2D - Could not terminate Collider properly...\n\tNote: This is probably because a bool was incorrect\n");
    }
    return returnedCol;
}

//Note: Does not read velocity or isTouchingPlayer
PhysicsObject parsePhysicsObject(char input[128], int inputSize){
    int select = 0;
    char sendToParse[20];
    int temp;
    int i;
    PhysicsObject returnedObj;

    if(input[select] == '('){
        select++;
    }

    if(input[select] == '@'){
        // we have a vector2
        select++;
        i = 0;
        if(input[select] == 'f'){
            temp = 1;
            select++;
        }else{
            temp = 0;
        }
        while(input[select] != ')'){
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        sendToParse[i] = input[select];
        if(temp == 0){
            returnedObj.position = readVector2(sendToParse);
        }else{
            returnedObj.position = readVector2Float(sendToParse);
        }
        
        select++;
        if(input[select] == ','){
            select++;
        }
    }else{
        // we have floats
        i = 0;
        while(input[select] != ','){
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        sendToParse[i] = ';';
        returnedObj.position.x = parseFloat(sendToParse);
        select++;

        i = 0;
        while(input[select] != ','){
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        sendToParse[i] = ';';
        returnedObj.position.y = parseFloat(sendToParse);
        select++;
    }

    i = 0;
    while(input[select] != ','){
        sendToParse[i] = input[select];
        select++;
        i++;
    }
    sendToParse[i] = ';';
    returnedObj.sizeX = parseInt(sendToParse, i);
    select++;

    i = 0;
    while(input[select] != ','){
        sendToParse[i] = input[select];
        select++;
        i++;
    }
    sendToParse[i] = ';';
    returnedObj.sizeY = parseInt(sendToParse, i);
    select++;

    returnedObj.trigger = parseBool(input[select]);
    select++;
    if(input[select] == ','){
        select++;
    }else{
        perror("parsePhysicsObject - Input is not bool");
        printf("given char - %c\n", input[select]);
    }

    returnedObj.enabled = parseBool(input[select]);
    select++;
    printf("hello");
    if(input[select] == ')'){
        select++;
    }else{
        perror("parsePhysicsObject - Input is not bool");
        printf("given char - %c\n", input[select]);
    }
    printf("hello2");
    return returnedObj;
}

TextBox parseTextBox(char input[128], int inputSize){
    int select = 0;
    char sendToParse[17];
    int temp;
    int i;
    TextBox returnedTextBox;

    if(input[select] == '('){
        select++;
    }

    for(int s = 0; s < 3; s++){
        i = 0;
        while(input[select] != ','){
            sendToParse[i] = input[select];
            select++;
            i++;
        }
        temp = parseInt(sendToParse, i);
        select++;
        switch(s){
            case 0:
                returnedTextBox.x = temp;
                break;
            case 1:
                returnedTextBox.y = temp;
                break;
            case 2:
                returnedTextBox.size = temp;
                break;
        }
    }

    i = 0;
    while(input[select] != ',' && i < 40){
        if(input[select] == '\\'){
            temp = 1;
            //printf("-%c\n", input[select]);
        }
        if(temp != 1){
            returnedTextBox.text[i] = input[select];
        }
        //printf("-%c\n", input[select]);
        select++;
        i++;
        if(input[select] == ',' && temp == 1){
            i--;
            returnedTextBox.text[i] = input[select];
            //printf("-%c\n", input[select]);
            select++;
            i++;
            //printf("-%c\n", input[select]);
            temp = 0;
        }
    }
    select++;
    if(i == 40){
        perror("parseTextBox - String was too long. Continuing with shortned string...");
    }else{
        returnedTextBox.text[i] = '\0'; // this is probably a very ghetto way of doing things;   
        //this is because while it may look like the string ends, there is still a bunch of junk data being thorwn around
    }

    if(input[select] == '?'){
        select++;
        if(input[select] == '('){
            select++;
        }
        i = 0;
        //printf("c: %c\n", input[select]);
        while(input[select] != ')' && i < 17){
            //printf("c: %c\n", input[select]);
            sendToParse[i] = input[select];
            select++;
            i++;
            
        }
        sendToParse[i] = ')';
        if(i == 17){
            perror("parseTextBox - Color input was too long. Is input a valid color?");
        }
        printf("cs: %s\n", sendToParse);
        returnedTextBox.colour = parseColor(sendToParse, i);
    }else{
        perror("parseTextBox - Please input an item of type color");
    }

    return returnedTextBox;
}

//SandwichFactory Data structure
//    path to level image is always first ie. levels/1/photo.png;~2323;~2343

//    generic struct array = symbol{(struct1);(struct2)}
//    generic struct       = symbol(property1,2,3,4,5,6)
//        note: structs in arrays only include symbol at beginning
//    bools are stored as 0 or 1
//    ~ = property   = ~propertyname=data;
//    ; seperates each object (if on same line)
//    ! = terminates the file
//
//  Structs
// @  % = level collider  = %{} or %() or %) <- this is not an array
// @  * = ladder collider = *{} or *() or *)
// @  ^ = Physics object  = ^{} or ^() or ^)
//    # = camera     = #(@(pos),@(maxCam),@(minCam),smoothingEnabled, smoothing);
//        note: can have either vec2 int or float
// @  & = textBox       = &{(text1,x,y,colour,size);(text2,x,y,colour,size);etc..}; or&()
//
//  Types
//    @ = vector 2 (int)   = @(x,y);  or @2091,133)
//    @f= vector 2 (float) = @f(x,y); or @f103.198,103.123)
//    ? = colour     = ?(r,g,b,a)
// *  " = string     = "(text) or "text) or "text"

// * = Not finished
// @ = Arrays not implemented

//    example: ~10;~224!
//    example: ~193;~1093;%{(13,31,3,13,34);(1093,13,42,24,24)};*{}

// Structs could be written without inital bracket:   #109,10193,1334,221) instead of #(13013,13,13,345,6,6)
// Vector2 is the same, @219,138) instead of @(1983,13)

//Bools can be given as 0, 1, T, F, t, f

// Note: Structs must be strictly written keeping their structure in mind, however an object can be written at any point

//Reads generic sandwichfactory file type. Returns error code if neededs
//
//int levelTexts, int levelCol, int ladderNum, int objectCol, bool disableCam, Vector2 startingPos
//add these values as you add more features

// ; TERMINATE CURRENT LOOP IF REACHED. DO NOT MAKE THE SEMICOLON MOVE THE OBJECT AS THE LOOP SHOULD BE DOING IT

// Property names
// ~sp=     (startingPosition)
// ~img=

// TODO actually make it so the game can start (loadNew may be fine)


int readFileSF(char path[100], bool readLevelImagePath, bool* isLever, bool* isDoor, char levelImagePath[64], bool* disableCam, Vector2* startingPos, s_Camera* camera, BoxCollider2D levelCol[15], BoxCollider2D ladders[2], TextBox texts[2], PhysicsObject physobjects[2], int* levelTexts, int* levelColNum, int* ladderNum, int* physObjNum){
    FILE* fp;
    fp = fopen(path, "r");
    if(fp == NULL){
        perror("Error opening. File may not exist");
        printf("Could not open: %s", path);
        return 1;
    }
    
    char input[1024]; // Defines how much text is stored (ie. how big a level can be)
    char sendToParse[128];
    char propertyName[8];
    char ch; // character selected
    int levelColID = 0;
    int ladderID = 0;
    int physObjID = 0;
    int textBoxID = 0;
    bool isEnd = false; // do we end read?
    bool isVector = false;
    int temp = 0;
    bool subFor = false;

    *disableCam = true;
    bool lever = false;
    bool door = false;

    //Note: This means only 1024 characters can be stored per line
    for(int i = 0; i < 1024 && !isEnd; i++){
        input[i] = fgetc(fp);
        if(input[i] == '\n' || input[i] == EOF){
            isEnd = true;
        }
        if(input[i] == '\n'){
            printf("\\n`\n");
        }else{
            printf("%c`", input[i]);
        }
    }
    isEnd = false;
    
    for(int charSelect = 0; charSelect < 1024 && !isEnd; charSelect++){
        if(subFor){
            subFor = false;
            charSelect--;
        }
        ch = input[charSelect];
        if(ch == '\n'){
            printf("\\n  \n");
        }else{
            printf("%c` ", ch);
        }
        if(ch == '!' || ch == '\0' || ch == EOF){
            isEnd = true;
        }else if(ch == '~'){
            charSelect++;
            ch = input[charSelect];
            for(int i = 0; ch != '=' && i < 32 && ch != '\n' && ch != '\0'; i++){
                propertyName[i] = ch;
                charSelect++;
                ch = input[charSelect];
                if(ch == '='){
                    propertyName[i + 1] = ';';
                }
            }
            if(ch != '='){
                perror("parseProperty - Property name was too long or invald");
                printf("Given name: %s\n", propertyName);
                printf("ch = %c\n", ch);
            }else{
                charSelect++;
                ch = input[charSelect];
                if(strEquals(propertyName, "sp;")){
                    if(ch == '@'){
                        charSelect++;
                        ch = input[charSelect];
                        if(ch == 'f'){
                            //float vector
                            charSelect++;
                            ch = input[charSelect];
                            temp = 0;
                            while(ch != ')' && temp < 20){
                                sendToParse[temp] = ch;
                                charSelect++;
                                ch = input[charSelect];
                                temp++;
                            }
                            if(temp == 20){
                                perror("parseProperty - Reached end of startingPos before expected");
                            }else{
                                sendToParse[temp] = ')';
                                *startingPos = readVector2Float(sendToParse);
                            }
                        }else{
                            //int vector
                            temp = 0;
                            while(ch != ')' && temp < 20){
                                sendToParse[temp] = ch;
                                charSelect++;
                                ch = input[charSelect];
                                temp++;
                            }
                            if(temp == 20){
                                perror("parseProperty - Reached end of startingPos before expected");
                            }else{
                                sendToParse[temp] = ')';
                                *startingPos = readVector2(sendToParse);
                            }
                        }
                    }else{
                        perror("parseProperty - Please provide a vector2 for the sp input");
                    }
                }else if(strEquals(propertyName, "img;")){
                    temp = 0;
                    while(ch != ';' && ch != '\n' && ch != '\0' && temp < 64){
                        levelImagePath[temp] = ch;
                        charSelect++;
                        ch = input[charSelect];
                        temp++;
                    }
                    if(temp == 64){
                        perror("Overflowed allow path size (64 charcters). File missing, forgot to terminate or try renaming the file.");
                    }else{
                        levelImagePath[temp] = '\0';
                    }
                    charSelect--;
                }else if(strEquals(propertyName, "isLever;")){
                    lever = parseBool(ch);
                    charSelect++;
                    ch = input[charSelect];
                }else if(strEquals(propertyName, "isDoor;")){
                    door = parseBool(ch);
                    charSelect++;
                    ch = input[charSelect];
                }else{
                    perror("parseProperty - Invalid property name");
                    printf("Given name: %s\n", propertyName);
                }

                
                if(ch != ';' && ch != '!'&& ch != '\n' && ch != '\0'){
                    perror("SF_File - Error terminating Property");
                }else{
                    charSelect--;
                }
            }

            
        }else if(ch == '#'){
            s_Camera temp_cam;
            charSelect++;
            ch = input[charSelect];
            if(ch == '('){
                charSelect++;
                ch = input[charSelect];
            }
            
            for(int s = 0; s < 3; ){
                if(ch == '@'){
                    charSelect++;
                    ch = input[charSelect];
                    if(ch == 'f'){
                        temp = 1;
                        charSelect++;
                        ch = input[charSelect];
                    }else{
                        temp = 0;   
                    }
                    for(int i = 0; ch != ')'; i++){
                        sendToParse[i] = ch;
                        charSelect++;
                        ch = input[charSelect];
                        if(ch == ')'){
                            sendToParse[i + 1] = ch;
                        }
                    }
                    if(temp == 1){
                        switch(s){
                            case 0:
                                temp_cam.position = readVector2Float(sendToParse);
                                break;
                            case 1:
                                temp_cam.maxCamera = readVector2Float(sendToParse);
                                break;
                            case 2:
                                temp_cam.minCamera = readVector2Float(sendToParse);
                                break;
                        }
                    }else{
                        switch(s){
                            case 0:
                                temp_cam.position = readVector2(sendToParse);
                                break;
                            case 1:
                                temp_cam.maxCamera = readVector2(sendToParse);
                                break;
                            case 2:
                                temp_cam.minCamera = readVector2(sendToParse);
                                break;
                        }
                    }
                    charSelect++;
                    ch = input[charSelect];
                    printf("-%c-", ch);
                    *disableCam = false;
                }else if(ch == ','){
                    s++;
                    charSelect++;
                    ch = input[charSelect];
                }else {
                    printf("Error reading Vector2 - I'm too lazy to do the x/y method please use vector2 import\n");
                }
            }

            if(ch == ','){
                temp_cam.smoothingEnabled = false;
                charSelect++;
                ch = input[charSelect];
            }else{
                temp_cam.smoothingEnabled = parseBool(ch);
                charSelect++;
                ch = input[charSelect];
            }

            if(ch == ','){
                charSelect++;
                ch = input[charSelect];
            }else{
                perror("readFileSF - Camera - Value given for smoothingEnabled is not bool");
            }

            for(int i = 0; ch != ')' && ch != ';'; i++){
                sendToParse[i] = ch;
                charSelect++;
                ch = input[charSelect];
            }
            temp_cam.smoothing = parseFloat(sendToParse);
            *camera = temp_cam;
        }else if(ch == '%'){
            //level collider  = %{} or %()
            charSelect++;
            ch = input[charSelect];
            if(ch == '{'){
                //array
                while(ch != '}'){
                    charSelect++;
                    ch = input[charSelect];
                }
                
            }else{
                //single struct
                if(ch == '('){
                    charSelect++;
                    ch = input[charSelect];
                }
                temp = 0;
                while(ch != ')'){
                    sendToParse[temp] = ch;
                    charSelect++;
                    ch = input[charSelect];
                    temp++;
                }
                sendToParse[temp] = ch;
                levelCol[levelColID] = parseBoxCollider(sendToParse, temp, false);
                printf("uhh this worked");
                levelColID++;
            }
        }else if(ch == '*'){
            //ladder collider = *{} or *()
            charSelect++;
            ch = input[charSelect];
            if(ch == '{'){
                //array
            }else{
                //single struct
                if(ch == '('){
                    charSelect++;
                    ch = input[charSelect];
                }
                temp = 0;
                while(ch != ')'){
                    sendToParse[temp] = ch;
                    charSelect++;
                    ch = input[charSelect];
                    temp++;
                }
                sendToParse[temp] = ch;
                ladders[ladderID] = parseBoxCollider(sendToParse, temp, false); // fix this to be based on input
                ladderID++;
            }
        }else if(ch == '^'){
            //physics object  = ^{} or ^()
            charSelect++;
            ch = input[charSelect];
            if(ch == '{'){
                //array
            }else{
                //single struct
                if(ch == '('){
                    charSelect++;
                    ch = input[charSelect];
                }
                temp = 0;
                isVector = false;
                while(ch != ')'){
                    if(ch == '@'){
                        isVector = true;
                    }
                    sendToParse[temp] = ch;
                    charSelect++;
                    ch = input[charSelect];
                    temp++;
                    if(ch == ')' && isVector){
                        isVector = false;
                        charSelect++;
                        ch = input[charSelect];
                        temp++;
                    }
                }
                sendToParse[temp] = ch;
                physobjects[physObjID] = parsePhysicsObject(sendToParse, temp);
                printf("hello3");
                physObjID++;
            }
        }else if(ch == '&'){
            //textBox         = &{} or &()
            charSelect++;
            ch = input[charSelect];
            if(ch == '{'){
                //array
            }else{
                //single struct
                if(ch == '('){
                    charSelect++;
                    ch = input[charSelect];
                }
                temp = 0;
                isVector = false;
                while(ch != ')'){
                    if(ch == '?'){
                        isVector = true;
                    }
                    sendToParse[temp] = ch;
                    charSelect++;
                    ch = input[charSelect];
                    temp++;
                    if(ch == ')' && isVector){
                        isVector = false;
                        charSelect++;
                        ch = input[charSelect];
                        temp++;
                    }
                }
                sendToParse[temp] = ch;
                texts[textBoxID] = parseTextBox(sendToParse, temp);
                printf("Given text: %s\n", texts[textBoxID].text);
                //printf("hello3");
                textBoxID++;
            }
        }else if(ch == '\n' || ch == '/'){
            charSelect = 0;
            for(int i = 0; i < 1024 && !isEnd; i++){
                input[i] = fgetc(fp);
                if(input[i] == '\n' || input[i] == EOF){
                    isEnd = true;
                    subFor = true; // Because we always do charSelect at the end, we must subtract that value to return to 0 instead of 1
                }
                if(input[i] == '\n'){
                    printf("\\n`\n");
                }else{
                    printf("%c`", input[i]);
                }
            }
            isEnd = false;
            printf("Getting new line\n");
        }
    }
    
    if(door){// fix this once the ID system is integrated
        levelColID--;
    }
    if(lever){// fix this once the ID system is integrated
        levelColID--;
    }
    *isDoor = door;
    *isLever = lever;

    *levelColNum = levelColID;
    *levelTexts = textBoxID;
    *ladderNum = ladderID;
    *physObjNum = physObjID;

    //printf("hello4");
    //printf("input - %s", input);
    fclose(fp);
    //printf("hello5\n");
    return 0;
}





// Reads generic int data 
//   int;int;int!
void readFileInt(char path[40], int inputArray[256], int arraySize, int* outputSize){
    FILE* fp;
    fp = fopen(path, "r");
    if(fp == NULL){
        perror("Error opening");
        return;
    }

    char input[512];
    char ch;
    int inputSelect = 0;

    fgets(input, 512, fp);

    bool isEnd = false;

    for(int i = 0; i < 511 && !isEnd && inputSelect < arraySize; i++){
        ch = input[i];

        switch(ch){
            case '!':
                isEnd = true;
                break;
            case '0':
                inputArray[inputSelect] = inputArray[inputSelect] * 10;
                break;
            case '1':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 1;
                break;
            case '2':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 2;
                break;
            case '3':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 3;
                break;
            case '4':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 4;
                break;
            case '5':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 5;
                break;
            case '6':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 6;
                break;
            case '7':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 7;
                break;
            case '8':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 8;
                break;
            case '9':
                inputArray[inputSelect] = (inputArray[inputSelect] * 10) + 9;
                break;
            case ';':
                inputSelect++;
                break;
        }
    }
    fclose(fp);
    if(!isEnd){
        perror("Reached end of file before file termination");
    }else{
        *outputSize = inputSelect;
    }
    for(int i = 0; i < arraySize; i++){
        printf("%d\n", inputArray[i]);
    }
}


//Writes int array
void writeFileInt(char path[40], int inputArray[256], int arraySize){
    FILE* fp;
    fp = fopen(path, "w");

    char str[40];

    for(int i = 0; i < arraySize; i++){
        sprintf(str, "%d", inputArray[i]);
        fputs(str, fp);
        fputc(';', fp);
    }
    fputc('!', fp);
    fclose(fp);
}