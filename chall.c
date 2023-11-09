
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(){
    char input[512]={0};
    printf("Please input your product key: ");
    fgets(input, 512, stdin);
    if(input[strlen(input)-1]=='\n'){
        input[strlen(input)-1]='\0';
    }
    if(strncmp(input, "ptm{", 4)!=0 || input[strlen(input)-1]!='}' || (strlen(input)-5)%2!=0 || (int)((strlen(input)-5)/2)%3!=0){
        puts("Wrong product key, please send an email to mister96@m0lecon.xato for purchase options.");
        exit(-1);
    }

    size_t size = (int)((strlen(input)-5)/2);
    __m512i *rows = malloc(sizeof(__m512i)*size);

    for(int counter=4; counter<(strlen(input)-1); counter+=2){
        uint32_t data[4] = {input[counter]&1, input[counter]>>1&1, input[counter]>>2&1, input[counter]>>3&1};
        uint32_t data2[4] = {input[counter]>>4&1, input[counter]>>5&1, input[counter]>>6&1, input[counter]>>7&1};
        uint32_t data3[4] = {input[counter+1]&1, input[counter+1]>>1&1, input[counter+1]>>2&1, input[counter+1]>>3&1};
        uint32_t data4[4] = {input[counter+1]>>4&1, input[counter+1]>>5&1, input[counter+1]>>6&1, input[counter+1]>>7&1};
        __m128i matrix[4] = {_mm_load_epi32(data), _mm_load_epi32(data2), _mm_load_epi32(data3), _mm_load_epi32(data4)};
        //TODO fast exp
        __m128i output[4] = {matrix[0], matrix[1], matrix[2], matrix[3]};
        __m512i output512 = _mm512_castps128_ps512(output[0]);
        output512 = _mm512_insertf32x4(output512, output[1], 1);
        output512 = _mm512_insertf32x4(output512, output[2], 2);
        output512 = _mm512_insertf32x4(output512, output[3], 3);
        rows[(int)((counter-4)/2)]=output512;
    }

    for(int i=0; i<size; i++){
        __m512i conflicts = _mm512_conflict_epi32(rows[i]);
        if(conflicts!=0){
            
        }
    }



    uint8_t tmp[64]={0x56, 0x39, 0x1b, 0x4c, 0xc2, 0x49, 0x69, 0x24, 0x7d, 0x52, 0xea, 0x8a, 0x39, 0x78, 0x19, 0xf8, 0x7d, 0x14, 0x5d, 0x87, 0x33, 0x26, 0x5, 0x75, 0x70, 0x8, 0x5, 0x48, 0xca, 0xb6, 0xc5, 0x71, 0x13, 0x9, 0x93, 0xd0, 0x59, 0xfc, 0x56, 0x3d, 0x88, 0xe9, 0xb3, 0x11, 0x16, 0xe2, 0xe9, 0xed, 0x7a, 0x55, 0x4f, 0x24, 0xfc, 0x38, 0x67, 0x1c, 0x5d, 0x48, 0x22, 0x54, 0x80, 0xc3, 0xcf, 0x1d};
    __m512i test = _mm512_load_si512(tmp);
    __m512i output = _mm512_conflict_epi32(test);
}