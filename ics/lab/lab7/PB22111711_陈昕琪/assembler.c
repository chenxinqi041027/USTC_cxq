#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Function prototypes
void read_asm_file(const char *filename, char lines[][MAX_LINE_LENGTH], int *num_lines);
void write_output_file(const char *filename, const char *output[], int num_lines);
void assemble(char lines[][MAX_LINE_LENGTH], int num_lines, char *output[], int* num);
void translate_instruction(const char *instruction, char *machine_code, int* locate, char labellist[][MAX_LINE_LENGTH], int pc);

// TODO: Define any additional functions you need to implement the assembler, e.g. the symbol table.
char instructions[29][9] = {"ADD ", "AND ", "BR ", "JMP ", "JSR ", "JSRR ", "LD ", "LDI ", "LDR ", "LEA ", "NOT ", "RET ", "RTI ", "ST ", "STI ", "STR ", "TRAP ", 
                            ".ORIG ", ".END", ".FILL ", ".BLKW ", ".STRINGZ ", 
                            "BRN ", "BRZ ", "BRP ", "BRZP ", "BRNP ", "BRNZ ", "BRNZP "};//将语句存入数组
int findins(char lines[][MAX_LINE_LENGTH], int num_lines, char* string);
char* getPCoffset9(int pc, const char* label, char labellist[][MAX_LINE_LENGTH], int* locate);
char* getPCoffset11(int pc, const char* label, char labellist[][MAX_LINE_LENGTH], int* locate);
int is_label(const char* string);
char* get_register(char number);
char* getoff6(const char* number);
char* getbinary(char number);
char* gethx_5(const char* string);
char* getde_5(const char* string);

int main(int argc, char *argv[])
{
    // Command-line argument parsing
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input_file.asm> <output_file.txt>\n", argv[0]);
        return 1;
    }

    char input_filename[100];
    char output_filename[100];
    strcpy(input_filename, argv[1]);
    strcpy(output_filename, argv[2]);

    char lines[100][MAX_LINE_LENGTH]; // Assuming a maximum of 100 lines
    int num_lines = 0;
    read_asm_file(input_filename, lines, &num_lines);

    char *output[100]; // Output array of strings
    for (int i = 0; i < 100; i++)
    {
        output[i] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
        output[i][0] = '\0';
    }

    assemble(lines, num_lines, output, &num_lines);
    write_output_file(output_filename, (const char **)output, num_lines);

    // Free allocated memory
    for (int i = 0; i < 100; i++)
    {
        free(output[i]);
    }

    return 0;
}

void read_asm_file(const char *filename, char lines[][MAX_LINE_LENGTH], int *num_lines)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        strcpy(lines[*num_lines], line);
        if(strncmp(lines[*num_lines], ".END", strlen(".END")) == 0){
            lines[*num_lines][4] = '\0';
        }else{
            for(int i = 0; i < MAX_LINE_LENGTH; i++){
                if(lines[*num_lines][i] == '\n'){
                    lines[*num_lines][i] = '\0';
                    break;
                }
            }
        }
        (*num_lines)++;
    }
    fclose(file);
}

void write_output_file(const char *filename, const char *output[], int num_lines)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < num_lines; i++)
    {
        if(output[i][0] == '\0'){
            continue;
        }
        fprintf(file, "%s\n", output[i]);
    }

    fclose(file);
}

void assemble(char lines[][MAX_LINE_LENGTH], int num_lines, char *output[], int* num)
{
    // TODO: Implement the assembly process
    // Implement the 2-pass process described in textbook.
    //首先找到起始地址的位置
    int start = findins(lines, num_lines, ".ORIG ");
    int i = 0, j = 0, count = 0;
    int start_address= 0;
    while(lines[start][i] != 'x' && lines[start][i] != '#'){//判断是不是十六进制和十进制
        i++;
    }if(lines[start][i] == '#'){//十进制
        i++;
        for(; i < (int)strlen(lines[start]); i++){
            start_address = 10 * start_address;
            start_address += lines[start][i] - '0';
        }
    }else if(lines[start][i] == 'x'){//十六进制
        i++;
        for(; i < (int)strlen(lines[start]); i++){
            start_address = 16 * start_address;
            start_address += lines[start][i] - '0';
        }
    }
    //找到结尾的位置
    int end = findins(lines, num_lines, ".END");
    char labellist[100][MAX_LINE_LENGTH];//创建符号表
    int locate[100] = {0};
    //先遍历一遍，创建符号表
    for(i = start; i <= end; i++){
        if(is_label(lines[i])){
            j = strchr(lines[i], ' ') - lines[i] + 1;//发现label
            strncpy(labellist[count], lines[i], j);//进行标记
            labellist[count][j] = '\0';
            locate[count] = i + start_address - 1 - start;
            count++;
        }
    }

    //第二次扫描输出机器码
    int number = 0;
    int tempt = 0, left;
    char* leftstring;
    count = 0;
    for (int i = start; i < end; i++)
    {
        leftstring = lines[i];
        if(is_label(leftstring)){//判断label
            leftstring = strchr(leftstring, ' ') + 1;//跳过label
        }
        //.BLKW
        if(strncmp(leftstring, ".BLKW ", strlen(".BLKW ")) == 0){//判断出.BLKW
            leftstring = strchr(leftstring, ' ') + 1;
            if(leftstring[0] == 'x'){//十六进制
                for(int k = 1; leftstring[k] != '\0'; k++){
                    number *= 16;
                    if(leftstring[k] <= '9'){
                        number = leftstring[k] - '0';
                    }else if(leftstring[k] >= 'a'){
                        number = leftstring[k] - 'a' + 10;
                    }else{
                        number = leftstring[k] - 'A' + 10;
                    }
                }
                for(int j = 0; j < number; j++){
                    strcpy(output[i - start + count + j], "0000000000000000");
                    tempt++;
                    *num = *num + 1;
                }
            }
            else if(leftstring[0] == '#'){//十进制
                for(int k = 1; leftstring[k] != '\0'; k++){
                    number *= 10;
                    number += leftstring[k] - '0';
                }
                for(int j = 0; j < number; j++){
                    strcpy(output[i - start + count + j], "0000000000000000");
                    tempt++;
                    *(num)++;
                }
            }number = 0;
            count += (tempt - 1);
            tempt = 0;
            continue;
        }
        else if(strncmp(leftstring, ".STRINGZ ", strlen(".STRINGZ ")) == 0){//判断出.STRINGZ
            leftstring = strchr(leftstring, ' ') + 2;//到达string
            for(int j = 0; leftstring[j] != '\0'; j++){
                number = leftstring[j];
                if(number == '"'){
                    strcpy(output[i - start + count + j], "0000000000000000");//.STRING最后是结束
                    count++;
                    break;
                }for(int k = 0; k < 16; k++){
                    left = number % 2;
                    if(left == 0){
                        output[i - start + count + j][15 - k] = '0';
                    }else{
                        output[i - start + count + j][15 - k] = '1';
                    }number = number / 2;
                }output[i - start + count + j][16] = '\0';
                tempt++;
                *num = *num + 1;
            }count += (tempt - 1);
            number = 0;
            tempt = 0;
            continue;
        }
        translate_instruction(lines[i], output[i - start + count], locate, labellist, i + start_address - start);
    }
}

void translate_instruction(const char *instruction, char *machine_code, int* locate, char labellist[][MAX_LINE_LENGTH], int pc)//pc指向下一条指令的地址
{
    const char* ins_string;
    int i;
    if(is_label(instruction)){//发现label
        ins_string = strchr(instruction, ' ') + 1;//跳过label
    }else{
        ins_string = instruction;//继续判断语句
    }for(i = 0; ins_string[i] == ' '; i++);
    ins_string = &ins_string[i];
     //NOT
    if(strncmp(ins_string, "NOT ", strlen("NOT ")) == 0){
        strcpy(machine_code, "1001");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//SR
        strcat(machine_code, "111111");
        return ;
    }//endNOT
    //ADD
    else if(strncmp(ins_string, "ADD ", strlen("ADD ")) == 0){
        strcpy(machine_code, "0001");//条件码
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//SR1
        ins_string = strchr(ins_string, ' ') + 1;
        if(ins_string[0] == 'R'){//寄存器
            strcat(machine_code, "000");
            strcat(machine_code, get_register(ins_string[1]));
            return ;
        }//立即数
        else if(ins_string[0] == 'x'){//十六进制
            strcat(machine_code, "1");
            char* hex = gethx_5(ins_string + 1);//五位补码
            strcat(machine_code, hex);
            free(hex);
            return ;
        }else{//十进制
            strcat(machine_code, "1");
            char* dec = getde_5(ins_string + 1);
            strcat(machine_code, dec);
            free(dec);
            return ;
        }
    }//endadd
    //AND，与ADD类似
    else if(strncmp(ins_string, "AND ", strlen("AND ")) == 0){
        strcpy(machine_code, "0101");//条件码
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//SR1
        ins_string = strchr(ins_string, ' ') + 1;
        if(ins_string[0] == 'R'){//SR2
            strcat(machine_code, "000");
            strcat(machine_code, get_register(ins_string[1]));
            return ;
        }else if(ins_string[0] == 'x'){
            strcat(machine_code, "1");
            char* hex = gethx_5(ins_string + 1);
            strcat(machine_code, hex);
            free(hex);
            return ;
        }else{
            strcat(machine_code, "1");
            char* dec = getde_5(ins_string + 1);
            strcat(machine_code, dec);
            free(dec);
            return ;
        }
    }//endAND
    //BR跳转指令
    else if(strncmp(ins_string, "BR ", strlen("BR ")) == 0 || 
            strncmp(ins_string, "BRN ", strlen("BRN ")) == 0 || 
            strncmp(ins_string, "BRZ ", strlen("BRZ ")) == 0 ||
            strncmp(ins_string, "BRP ", strlen("BRP ")) == 0 || 
            strncmp(ins_string, "BRZP ", strlen("BRZP ")) == 0 || 
            strncmp(ins_string, "BRNP ", strlen("BRNP ")) == 0 || 
            strncmp(ins_string, "BRNZ ", strlen("BRNZ ")) == 0 || 
            strncmp(ins_string, "BRNZP ", strlen("BRNZP ")) == 0){
        strcpy(machine_code, "0000");//条件码
        ins_string = strchr(ins_string, 'R') + 1;
        if(ins_string[0] == 'n' || ins_string[0] == 'N'){//N
            strcat(machine_code, "1");
            ins_string = ins_string + 1;
        }else{
            strcat(machine_code, "0");
        }if(ins_string[0] == 'z' || ins_string[0] == 'Z'){//Z
            strcat(machine_code, "1");
            ins_string = ins_string + 1;
        }else{
            strcat(machine_code, "0");
        }if(ins_string[0] == 'p' || ins_string[0] == 'P'){//P
            strcat(machine_code, "1");
            ins_string = ins_string + 1;
        }else{
            strcat(machine_code, "0");
        }if(strncmp(machine_code, "0000000", 7) == 0){//判断BR
            strcpy(machine_code, "0000111");
        }ins_string++;
        char* dis = getPCoffset9(pc, ins_string, labellist, locate);
        strcat(machine_code, dis);
        free(dis);
        return ;
    }//endBR
    //JMP
    else if(strncmp(ins_string, "JMP ", strlen("JMP ")) == 0){
        strcpy(machine_code, "1100000");//条件码
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));
        strcat(machine_code, "000000");
        return ;
    }//endJMP
    //RET,直接输出
    else if(strncmp(ins_string, "RET ", strlen("RET ")) == 0){
        strcpy(machine_code, "1100000111000000");
        return ;
    }//endRET
    //RTI,直接输出
    else if(strncmp(ins_string, "RTI ", strlen("RTI ")) == 0){
        strcat(machine_code, "1000");
        strcat(machine_code, "000000000000");
        return ;
    }//endRTI
    //JSRR
    else if(strncmp(ins_string, "JSRR ", strlen("JSRR ")) == 0){
        strcpy(machine_code, "0100000");
        ins_string = strchr(ins_string, ' ') + 2;
        strcat(machine_code, get_register(ins_string[0]));
        strcat(machine_code, "000000");
        return ;
    }//endJSRR
    //JSR,判断完JSRR才能判断JSR
    else if(strncmp(ins_string, "JSR ", strlen("JSR ")) == 0){
        strcpy(machine_code, "01001");
        ins_string = strchr(ins_string, ' ') + 1;
        char* dis = getPCoffset11(pc, ins_string, labellist, locate);
        strcat(machine_code, dis);
        free(dis);
        return ;
    }//endJSRR
    //LDI
    else if(strncmp(ins_string, "LDI ", strlen("LDI ")) == 0){
        strcpy(machine_code, "1010");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));
        ins_string = strchr(ins_string, ' ') + 1;
        char* dis = getPCoffset9(pc, ins_string, labellist, locate);
        strcat(machine_code, dis);
        free(dis);
        return ;
    }//endLDI
    //LDR
    else if(strncmp(ins_string, "LDR ", strlen("LDR ")) == 0){
        strcpy(machine_code, "0110");
        ins_string = strchr(ins_string, ' ') + 2;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//BaseR
        ins_string = strchr(ins_string, ' ') + 1;//offset6
        char* distance = getoff6(ins_string);
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endLDR
    //LD
    else if(strncmp(ins_string, "LD ", strlen("LD ")) == 0){
        strcpy(machine_code, "0010");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));
        ins_string = strchr(ins_string, ' ') + 1;
        char* distance = getPCoffset9(pc, ins_string, labellist, locate);
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endLD
    //LEA
    else if(strncmp(ins_string, "LEA ", strlen("LEA ")) == 0){
        strcpy(machine_code, "1110");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, ' ') + 1;//label
        char* distance = getPCoffset9(pc, ins_string, labellist, locate);
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endLEA
    //STI
    else if(strncmp(ins_string, "STI ", strlen("STI ")) == 0){
        strcat(machine_code, "1011");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//DR
        ins_string = strchr(ins_string, ' ') + 1;
        char* distance = getPCoffset9(pc, ins_string, labellist, locate);//
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endSTI
    //STR
    else if(strncmp(ins_string, "STR ", strlen("STR ")) == 0){
        strcat(machine_code, "0111");
        ins_string = strchr(ins_string, ' ') + 2;//SR
        strcat(machine_code, get_register(ins_string[0]));
        ins_string = strchr(ins_string, 'R') + 1;//BaseR
        strcat(machine_code, get_register(ins_string[0]));
        ins_string = strchr(ins_string, ' ') + 1;//offset6
        char* distance =  getoff6(ins_string);
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endSTR
    //ST
    else if(strncmp(ins_string, "ST ", strlen("ST ")) == 0){
        strcpy(machine_code, "0011");
        ins_string = strchr(ins_string, 'R') + 1;
        strcat(machine_code, get_register(ins_string[0]));//SR
        ins_string = strchr(ins_string, ' ') + 1;
        char* distance = getPCoffset9(pc, ins_string, labellist, locate);//PCoffset9
        strcat(machine_code, distance);
        free(distance);
        return ;
    }//endST
    //TRAP
    else if(strncmp(ins_string, "TRAP ", strlen("TRAP ")) == 0){
        strcpy(machine_code, "11110000");
        ins_string = strchr(ins_string, 'x') + 1;
        char* b_number;
        b_number = getbinary(ins_string[0]);
        strcat(machine_code, b_number);
        free(b_number);
        b_number = getbinary(ins_string[1]);
        strcat(machine_code, b_number);
        free(b_number);
        return ;
    }//endTRAP
    //.ORIG
    else if(strncmp(ins_string, ".ORIG ", strlen(".ORIG ")) == 0){
        ins_string = strchr(ins_string, ' ') + 1;
        int start_address = 0, left;
        if(ins_string[0] == 'x'){
            for(int i = 1; ins_string[i] != '\0'; i++){
                start_address *= 16;
                start_address += ins_string[i] - '0';
            }
        }else{
            for(int i = 1; ins_string[i] != '\0'; i++){
                start_address *=  10;
                start_address += ins_string[i] - '0';
            }
        }for(int i = 0; i < 16; i++){
            left = start_address % 2;
            if(left == 0){
                machine_code[15 - i] = '0';
            }else{
                machine_code[15 - i] = '1';
            }start_address = start_address / 2;
        }machine_code[16] = '\0';
        return ;
    }//end.ORIG
    //.END
    else if(strncmp(ins_string, ".END ", strlen(".END ")) == 0){//.END伪操作
        strcpy(machine_code, "\0");
        return ;
    }
    //.FILL，看后面的内容
    else if(strncmp(ins_string, ".FILL ", strlen(".FILL ")) == 0){//.FILL伪操作
        ins_string = strchr(ins_string, ' ') + 1;
        char* distance;
        if(ins_string[0] == 'x'){//十六进制
            int count = 0;
            for(int i = 1; ins_string[i] != '\0'; i++){
                count++;
                distance = getbinary(ins_string[i]);
                strcat(machine_code, distance);
            }for(int i = 0; i + count <= 4; i++){
                strcat(machine_code, "0000");
            }
        }else if(ins_string[0] == '#'){
            int number = 0, left;
            for(int i = 1; ins_string[i] != '\0'; i++){
                number *= 10;
                number += ins_string[i] - '0';
            }for(int i = 0; i < 16; i++){
                left = number % 2;
                if(left == 0){
                    machine_code[15 - i] = '0';
                }else{
                    machine_code[15 - i] = '1';
                }number = number / 2;
            }
        }machine_code[16] = '\0';
        return ;
    }
}

//辅助函数
//返回距离pc位置为pcoffset的九位补码
char* getPCoffset9(int pc, const char* label, char labellist[][MAX_LINE_LENGTH], int* locate){
    char* dis = (char*)malloc(sizeof(char) * 10);
    int left;
    for(int i = 0; i < 100; i++){
        if(strncmp(label, labellist[i], strlen(label)) == 0 && labellist[i][strlen(label)] ==' '){//找到了label
            int des = locate[i];
            int distance = des - pc, sign = 0;
            dis[0] = '0';
            if(distance < 0){
                sign = 1;
                dis[0] = '1';
                distance = 256 + distance;//寻找对应的二进制补码对应的数
            }for(int i = 0; i < 8; i++){
                left = distance % 2;
                if(left == 0){
                    dis[8 - i] = '0';
                }else{
                    dis[8 - i] = '1';
                }distance = distance / 2;
            }dis[9] = '\0';
            return dis;
        }
    }
}
//返回距离pc位置为pcoffset的十一位补码
char* getPCoffset11(int pc, const char* label, char labellist[][MAX_LINE_LENGTH], int* locate){
    char* dis = (char*)malloc(sizeof(char) * 12);
    int left;
    for(int i = 0; i < 100; i++){
        if(strncmp(label, labellist[i], strlen(label)) == 0 && labellist[i][strlen(label)] ==' '){//找到label
            int des = locate[i];
            int distance = des - pc, sign = 0;
            dis[0] = '0';
            if(distance < 0){
                sign = 1;
                dis[0] = '1';
                distance = 1024 + distance;//求的对应的补码对应的数值
            }for(int i = 0; i < 10; i++){
                left = distance % 2;
                if(left == 0){
                    dis[10 - i] = '0';
                }else{
                    dis[10 - i] = '1';
                }distance = distance / 2;
            }dis[11] = '\0';//字符串结束标志
            return dis;
        }
    }
}
//将十六进制转换为二进制
char* getbinary(char number){
    int real, left;
    if(number <= '9'){
        real = number - '0';
    }else if(number >= 'a'){
        real = number - 'a' + 10;
    }else{
        real = number - 'A' + 10;
    }char* dis = (char*)malloc(sizeof(char) * 5);
    for(int i = 0; i < 4; i++){
        left = real % 2;
        if(left == 0){
            dis[3 - i] = '0';
        }else{
            dis[3 - i] = '1';
        }real = real / 2;
    }dis[4] = '\0';
    return dis;
}

//寻找前缀匹配
int findins(char lines[][MAX_LINE_LENGTH], int num_lines, char* string){
    int length = (int)strlen(string);
    for(int i = 0; i < num_lines; i++){
        if(strncmp(lines[i], string, length) == 0){
            return i;
        }
    }return -1;
}

//判断当前语句中是否有label
int is_label(const char* string){
    for(int i = 0; i < 29; i++){
        if(strncmp(instructions[i], string, (int)strlen(instructions[i])) == 0){
            return 0;
        }
    }return 1;
}

//寄存器
char* get_register(char number){
    switch(number){
        case '0':
        return "000";
        case '1':
        return "001";
        case '2':
        return "010";
        case '3':
        return "011";
        case '4':
        return "100";
        case '5':
        return "101";
        case '6':
        return "110";
        case '7':
        return "111";
        default:
        return "error";
    }
}
//获取五位十六进制补码
char* gethx_5(const char* string){
    char* result;
    int number, left;
    result = (char*)malloc(sizeof(char) * 6);
    int sign = 0;
    if(string[0] == '-'){
        sign = 1;
    }if(sign == 0){
        if(string[0] <= '9'){
            number = string[0] - '0';
        }else if(string[0] >= 'a'){
            number = string[0] - 'a' + 10;
        }else{
            number = string[0] - 'A' + 10;
        }
    }else{
        if(string[1] <= '9'){
            number = string[1] - '0';
        }else if(string[1] >= 'a'){
            number = string[1] - 'a' + 10;
        }else{
            number = string[1] - 'A' + 10;
        }number = 16 - number;//补码对应的数字
    }if(string[2] != '\0' && sign == 1){//对于-16特殊考虑
        strcpy(result, "10000");
        return result;
    }for(int i = 0; i < 4; i++){
        left = number % 2;
        if(left == 0){
            result[4 - i] = '0';
        }else{
            result[4 - i] = '1';
        }number = number / 2;
    }if(sign == 0){
        result[0] = '0';
    }else{
        result[0] = '1';
    }result[5] = '\0';//补上字符串结尾的标志
    return result;
}
//获取五位十进制补码
char* getde_5(const char* string){
    char* result;
    result = (char*)malloc(sizeof(char) * 6);
    int sign = 0, i = 0, number = 0, left;
    if(string[0] == '-'){
        sign = 1;
        i = 1;
    }for(; string[i] != '\0'; i++){
        number *= 10;
        number += string[i] - '0';
    }if(number == 16){
        strcpy(result, "10000");
        return result;
    }else{
        if(sign == 1){//求对应的补码对应数
            number = 16 - number;
            result[0] = '1';
        }else{
            result[0] = '0';
        }for(i = 0; i < 4; i++){
            left = number % 2;
            if(left == 0){
                result[4 - i] = '0';
            }else{
                result[4 - i] = '1';
            }number = number / 2;
        }result[5] = '\0';
        return result;
    }
}
////将10进制或16进制转换成对应的6位补码
char* getoff6(const char* number){
    int sign = 0, wait = 0, start = 1, left;//start对应的是数字部分的开始地址
    char* dis = (char*)malloc(sizeof(char) * 7);
    dis[0] = '0';
    if(number[0] == 'x'){
        if(number[1] == '-'){
            sign = 1;
            start = 2;
        }while(number[start] != '\0'){//读入数字
            wait *= 16;
            if(number[start] <= '9'){
                wait += number[start] - '0';
            }else if(number[start] >= 'a'){
                wait += number[start] - 'a' + 10;
            }else{
                wait += number[start] - 'A' + 10;
            }
            start++;
        }if(sign == 1){//变成对应的负数的补码对应的数字的形式
            wait = 32 - wait;
            dis[0] = '1';
        }for(int i = 0; i < 5; i++){//书写0，1
            left = wait % 2;
            if(left == 0){
                dis[5 - i] = '0';
            }else{
                dis[5 - i] = '1';
            }
        }
    }else{
        if(number[1] == '-'){
            sign = 1;
            start = 2;
        }while(number[start] != '\0'){//读入数字
            wait *= 10;
            wait += number[start] - '0';
            start++;
        }if(sign == 1){//变成对应的负数的补码对应的数字的形式
            wait = 32 - wait;
            dis[0] = '1';
        }for(int i = 0; i < 5; i++){//书写0，1
            left = wait % 2;
            if(left == 0){
                dis[5 - i] = '0';
            }else{
                dis[5 - i] = '1';
            }
        }
    }dis[6] = '\0';
    return dis;
}
