#include <iostream>
#include <vector>

using namespace std;

// function to convert decimal to binary 
char *decToBinary(unsigned char n) 
{ 
    // array to store binary number 
    char *binaryNum = new char[8];; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
	for (int j = 7; j >= 0; j--) 
        cout << (int)binaryNum[j]; 
    // printing binary array in reverse order 
    cout << endl;
    return binaryNum;
} 

char binaryToDecimal(int n) 
{ 
    int num = n; 
    char dec_value = 0; 
  
    // Initializing base value to 1, i.e 2^0 
    int base = 1; 
  
    int temp = num; 
    while (temp) { 
        char last_digit = temp % 10; 
        temp = temp / 10; 
  
        dec_value += last_digit * base; 
  
        base = base * 2; 
    } 
  
    return dec_value; 
} 

char chor(char bit1, char bit2) {
	if(bit1 == bit2)
		return '0';
	else
		return '1';
}

char haming(char bits[8]) {
	char c1 = bits[0]^bits[1]^bits[3]^bits[4]^bits[6];
	cout << (int)c1 << endl;
	char c2 = bits[0]^bits[2]^bits[3]^bits[5]^bits[6];
	cout << (int)c2 << endl;
	char c4 = bits[1]^bits[2]^bits[3]^bits[7];
	cout << (int)c4 << endl;
	char c8 = bits[4]^bits[5]^bits[6]^bits[7];
	cout << (int)c8 << endl;
	char g = bits[0]^bits[1]^bits[2]^bits[3]^bits[4]^bits[5]
	^bits[6]^bits[7]^c1^c2^c4^c8;
	cout << (int) g << endl;
	return '0';
}

int main() {
	
	char n = 17; 
    haming(decToBinary(n)); 
    return 0; 
	
}
