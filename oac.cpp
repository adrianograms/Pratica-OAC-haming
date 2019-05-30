#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

// function to convert decimal to binary 
char *decToBinary(unsigned char n) 
{ 
    // array to store binary number 
    char *binaryNum = new char[8]; 

    for(int i =0; i< 8; i++) {
        binaryNum[i] = 0;
    }
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    /*
    if(aux == 15) {
    for(int i =0; i<8; i++) {
        cout << (int)binaryNum[i];
    }
    cout << endl;
    }
    */
    return binaryNum;
} 

char *haming2(char bits[8]) {
    char c1 = bits[0]^bits[1]^bits[3]^bits[4]^bits[6];

	char c2 = bits[0]^bits[2]^bits[3]^bits[5]^bits[6];

	char c4 = bits[1]^bits[2]^bits[3]^bits[7];

	char c8 = bits[4]^bits[5]^bits[6]^bits[7];

	char g = bits[0]^bits[1]^bits[2]^bits[3]^bits[4]^bits[5]
	^bits[6]^bits[7]^c1^c2^c4^c8;

    char *codigo_haming = new char[13];
    for(int i =0; i< 13; i++) {
        if(i == 0) {
            codigo_haming[i] = g;
        }
        else if(i == 1) {
            codigo_haming[i] = c1;
        }
        else if(i == 2) {
            codigo_haming[i] = c2;
        }
        else if(i == 3) {
            codigo_haming[i] = bits[0];
        }
        else if(i == 4) {
            codigo_haming[i] = c4;
        }
        else if(i == 8) {
            codigo_haming[i] = c8;
        }
        else if(i < 8) {
            codigo_haming[i] = bits[i-4];
        }
        else if(i > 8) {
            codigo_haming[i] = bits[i-5];
        }
    }
    for(int i =0; i<13; i++) {
        cout << (int)codigo_haming[i];
    }
    cout << endl;

    return codigo_haming;
}

unsigned char *transforma_em_char(char bits[]) {
    unsigned char *bytes = new unsigned char[2];
    bytes[0] = bytes[1] =0;
    for(int i =0; i< 13; i++) {
        if(i < 8) {
            bytes[0] += (unsigned char)pow(2,i)*bits[i];
        }
        else {
            bytes[1] += (unsigned char)pow(2,i-8)*bits[i];
        }
    }
    //cout << (int) bytes[0] << " " << (int) bytes[1] << endl;
    return bytes;
}

unsigned char *haming(char bits[8]) {
    
	char c1 = bits[0]^bits[1]^bits[3]^bits[4]^bits[6];

	char c2 = bits[0]^bits[2]^bits[3]^bits[5]^bits[6];

	char c4 = bits[1]^bits[2]^bits[3]^bits[7];

	char c8 = bits[4]^bits[5]^bits[6]^bits[7];

	char g = bits[0]^bits[1]^bits[2]^bits[3]^bits[4]^bits[5]
	^bits[6]^bits[7]^c1^c2^c4^c8;

    unsigned char *byte_arruamdo  = new unsigned char[2];

    char *teste = haming2(bits);
    unsigned char *teste2 = transforma_em_char(teste);

    cout << (int)teste2[0] << " " << (int)teste2[1] << " " << "trasforma em char" << endl;

    /*
    for(int i =0; i<8; i++) {
        cout << (int)bits[i];
    }
    
    cout << endl;
    */
    //cout << (int)c1 << (int)c2 << (int)c4 << (int)c8 << (int)g << endl;

    byte_arruamdo[0] = byte_arruamdo[1] = 0;

    for(int i =0; i< 13; i++) {
        if(i < 8) {
            if(i == 0) {
                byte_arruamdo[0] += (unsigned char)pow(2, i)*g;
            }
            else if(i == 1) {
                byte_arruamdo[0] += (unsigned char)pow(2, i)*c1;
            }
            else if(i == 2) {
                byte_arruamdo[0] += (unsigned char)pow(2, i)*c2;
            }
            else if(i == 3)
                    byte_arruamdo[0] += (unsigned char)pow(2, i)*bits[0];

            else if(i == 4)
                    byte_arruamdo[0] += (unsigned char)pow(2, i)*c4;
            else
                byte_arruamdo[0] += (unsigned char)pow(2, i)*bits[i-4];
        } 
        else if(i == 8) {
            byte_arruamdo[1] += (unsigned char)pow(2, i-8)*c8;
        }
        else {
            byte_arruamdo[1] += (unsigned char)pow(2 , i-8)*bits[i-5];
        }
    }
    cout << (int) byte_arruamdo[0] << " " << (int) byte_arruamdo[1] << endl;
	return byte_arruamdo;
}

void verification(unsigned char *bytes_arquivo_haming, unsigned char bytes_arquivo_original) {
    cout << (int)bytes_arquivo_haming[0] << " " << (int)bytes_arquivo_haming[1] << endl;
    char *inferior = decToBinary(bytes_arquivo_haming[0]);
    char *superior = decToBinary(bytes_arquivo_haming[1]);

    for(int i =0; i<5; i++) {
        cout << (int)superior[i];
    }
    cout << endl;

    char *bits_haming_arquivo = new char[13];

    for(int i =0; i<13; i++) {
        if(i < 8) {
            if(inferior[i] > 1)
                cout << (int)inferior[i] << " " << i <<  endl;
            bits_haming_arquivo[i] = inferior[i];
        }
        else {
            if(superior[i-8] > 1)
                cout << (int)superior[i-8] << " " << i - 8 <<  endl;
            bits_haming_arquivo[i] = superior[i-8];
        }
    }

    for(int i =0; i<13; i++) {
        cout << (int)bits_haming_arquivo[i];
    }
    cout << "haming" << endl;
    cout << endl;

    char *bits_originais = decToBinary(bytes_arquivo_original);

    for(int i =0; i<8; i++) {
        cout << (int)bits_haming_arquivo[i];
    }
    cout << endl;
    char *bits_haming = haming2(bits_originais);

    char c1 = bits_haming[1]^bits_haming_arquivo[1];
    char c2 = bits_haming[2]^bits_haming_arquivo[2];
    char c4 = bits_haming[4]^bits_haming_arquivo[4];
    char c8 = bits_haming[8]^bits_haming_arquivo[8];

    if(c1 == 0 && c2 == 0 && c4 == 0 && c8 == 0) {
        cout << "Tudo certo!" << endl;
    }
    else {
        int posicao_mudar = (int)pow(2,0)*c1 + (int)pow(2, 1)*c2 
                            + (int)pow(2, 2)*c4 + (int)pow(2,3)*c8;

        cout << posicao_mudar << endl;
        if(posicao_mudar > 12) {
            cout << "Algo esta muito errado!!" << endl;
        }
        else {
            if(bits_haming[posicao_mudar] == 0) {
                bits_haming[posicao_mudar] = 1;
            }
            else {
                bits_haming[posicao_mudar] = 0;
            }

            char g = bits_haming[1]^bits_haming[2]^bits_haming[3]^bits_haming[4]
                    ^bits_haming[5]^bits_haming[6]^bits_haming[7]^bits_haming[8]
                    ^bits_haming[9]^bits_haming[10]^bits_haming[11]^bits_haming[12];
            
            if(g == bits_haming_arquivo[0]) {
                cout << "Deu certo poar!" << endl;
            }
            else {
                cout << "Vish de merda em!!" << endl;
            }
        }
    }
}

void reading_char(string path_src,string path_dest) {
    ofstream output;
    output.open(path_dest, ios::binary);
    ifstream input(path_src, std::ios::binary);

    vector<unsigned char> buffer(istreambuf_iterator<char>(input), {});
    for(unsigned char elemento : buffer) {
        unsigned char *aux =  haming(decToBinary(elemento));

        output << aux[0];
        output << aux[1];

        cout << (int)aux[0] << " " << (int)aux[1] << endl;
        
       /*
       output.write((char *) &aux[0], sizeof(char));
       output.write((char *) &aux[1], sizeof(char));
       */
    }
    output.close();
    input.close();
}

void reading_teste(string path_haming,string path_original) {
    ifstream input_haming(path_haming, std::ios::binary);
    ifstream input_original(path_original, std::ios::binary);

    vector<unsigned char> buffer_haming(istreambuf_iterator<char>(input_haming), {});
    cout << (int)buffer_haming[4] << endl;
    vector<unsigned char> buffer_original(istreambuf_iterator<char>(input_original), {});
    cout << buffer_haming.size() << endl;
    int j;
    for(int i = 0, j= 0; j< buffer_original.size(); i=i+2, j++) {
        unsigned char *bytes_arquivo_haming = new unsigned char[2];
        bytes_arquivo_haming[0]  =buffer_haming[i];
        bytes_arquivo_haming[1] = buffer_haming[i+1];
        unsigned char bytes_arquivo_original = buffer_original[j];
        verification(bytes_arquivo_haming, bytes_arquivo_original);
    }
}

bool deshaming(char bits[8], bool primeiro_byte) {
    if(primeiro_byte == true) {

    }
}

int main() {
	
    //reading_char(R"(teste.txt)", "qlq.bin");
    reading_teste("qlq.bin", "teste.txt");
	char n = 17; 
    //haming(decToBinary(n)); 
    return 0; 
	
}
