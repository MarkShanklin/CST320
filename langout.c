#include <stdio.h>
#define MEM_SIZE  10000
char Memory[MEM_SIZE];
int Frame_Pointer = 0;
int Stack_Pointer = 0;
int Temp = 0;
double Temp_F = 0.0;
int main() {
*(int *)&Memory[Frame_Pointer+ 0 ]= 1 ;
*(int *)&Memory[Stack_Pointer]= Frame_Pointer;
Stack_Pointer += 4 ;
*(int *)&Memory[Stack_Pointer] = *(int *)&Memory[Frame_Pointer+ 0 ];
Stack_Pointer += 4 ;
Frame_Pointer = Stack_Pointer;
Frame_Pointer -=  4 ;
plus_plus();
Stack_Pointer -= 4 ;
Stack_Pointer -= 4 ;
Frame_Pointer = *(int *)&Memory[Stack_Pointer];
*(int *)&Memory[Frame_Pointer+ 4 ] = Temp;
Temp = *(int *)&Memory[Frame_Pointer+ 0 ];
printf("%d\n", Temp);
return 0;
 }
int plus_plus()
{
Temp = *(int *)&Memory[Frame_Pointer+ 0 ];
printf("%d\n", Temp);
*(int *)&Memory[Frame_Pointer+ 0 ]=*(int *)&Memory[Frame_Pointer+ 0 ]+ 1 ;
Temp = *(int *)&Memory[Frame_Pointer+ 0 ];
printf("%d\n", Temp);
Temp= *(int *)&Memory[Frame_Pointer+ 0 ];
goto LABEL_$2;
LABEL_$2:
return 0;
}
