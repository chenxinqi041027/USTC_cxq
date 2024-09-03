#include <cstdint>
#include <iostream>
#include <fstream>
#include <bitset>

#define LENGTH 1
#define MAXLEN 100
#define STUDENT_ID_LAST_DIGIT 1



int16_t lab1(int16_t n) {
    // initialize
    int16_t cnt = 0;//count zeros
    int16_t rep = 16;
    if(!(n & 1) && n < 0) n = (~n) + 1;//check if n is odd, if yes then turn n into its implement

    // calculation
    while(rep--){
		if(n >= 0) cnt++;
		n = n + n;
	}

    // return value
    return cnt + STUDENT_ID_LAST_DIGIT;
}

int16_t lab2(int16_t n) {
    // initialize
    if(n == 1) return 3;
    int rep = n - 1, mod = 4095, mul = 7;
    int sgn = 2;
    int ans = 3;

    // calculation
    while(rep--){
		if(!(ans & mul)){ // if v_n is a multiple of 7
			if(sgn == 2) sgn = -2;
			else sgn = ~sgn + 1;
		}
		else{ // if the last digit of v_n is 8
			int tmp = ans;
			while(tmp > 0) tmp -= 10;
			if(!(tmp + 2)){
				if(sgn == 2) sgn = -2;
				else sgn = ~sgn + 1;
			}
		}
		ans = ans + ans + sgn;
		ans &= mod; // use & to do modulo
	}
	
    // return value
    return ans;
}

int check(char a){
	if((a - 'a' >= 0 && a - 'z' <= 0) || (a - 'A' >= 0 && a - 'Z' <= 0)) return 1;
	else return 0;
}

int16_t lab3(char s1[], char s2[]) {
    // initialize
    char *p1 = s1, *p2 = s2;
    int cmp = 0;
    
    // calculation
	while(check(*p1) && check(*p2)){
		cmp = *p1 - *p2;
		if(cmp) return cmp;
		p1++;
		p2++;
	}
	
    // return value
    return *p1 - *p2;
}

int16_t remove(int16_t *memory, int16_t n, int16_t &state);

int16_t put(int16_t *memory, int16_t n, int16_t &state);

int16_t lab4(int16_t *memory, int16_t n, int16_t &state) { // stack, n rings, stack index
    // initialize
	
	int16_t run = remove(memory, n, state);
	return run;
    // calculation
	
    // return value
}

int16_t remove(int16_t *memory, int16_t n, int16_t &state){
	
	if(n == 0){
		return 1;
	}
	else if(n == 1){
		memory[state + 1] = memory[state] + 1;
		state++;
		return 1;
	}
	int runR = 0;
	runR = remove(memory, n - 2, state);
	int shifter = n - 1, imp = 1;
	while(shifter--) imp += imp;
	memory[state + 1] = memory[state] + imp;
	state++;
	runR = put(memory, n - 2, state);
	runR = remove(memory, n - 1, state);
	
	return runR;
}

int16_t put(int16_t *memory, int16_t n, int16_t &state){
	if(n == 0){
		return 1;
	}
	else if(n == 1){
		memory[state + 1] = memory[state] - 1;
		state++;
		return 1;
	}
	int runP = 0;
	runP = put(memory, n - 1, state);
	runP = remove(memory, n - 2, state);
	int shifter = n - 1, imp = 1;
	while(shifter--) imp += imp;
	memory[state + 1] = memory[state] - imp;
	state++;
	runP = put(memory, n - 2, state);
	
	return runP;
	
	
}

int main() {
    std::fstream file;
    file.open("test.txt", std::ios::in);
    int16_t n = 0;

    // lab1
    
    std::cout << "===== lab1 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab1(n) << std::endl;
    }

    // lab2
    std::cout << "===== lab2 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab2(n) << std::endl;
    }
   
    // lab3
    std::cout << "===== lab3 =====" << std::endl;
    char s1[MAXLEN]; char s2[MAXLEN];
    for (int i = 0; i < LENGTH; ++i) {
        file >> s1 >> s2;
        std::cout << lab3(s1, s2) << std::endl;
    }
   
    // lab4
    std::cout << "===== lab4 =====" << std::endl;
    int16_t memory[MAXLEN];
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        int16_t state = 0;
        memory[0] = 0;
        int CHECK_RUN = lab4(memory, n, state);
        for(int j = 1; j <= state; ++j){
            std::cout << std::bitset<16>(memory[j]) << std::endl;
        }
    }
  
    file.close();
    return 0;
}
