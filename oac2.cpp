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
	return byte_arruamdo;
}

unsigned char verification(unsigned char *bytes_arquivo_haming, unsigned char bytes_arquivo_original, int local_byte) {
    char *inferior = decToBinary(bytes_arquivo_haming[0]);
    char *superior = decToBinary(bytes_arquivo_haming[1]);

    char *bits_haming_arquivo = new char[13];

    for(int i =0; i<13; i++) {
        if(i < 8) {
            bits_haming_arquivo[i] = inferior[i];
        }
        else {
            bits_haming_arquivo[i] = superior[i-8];
        }
    }

    char *bits_originais = decToBinary(bytes_arquivo_original);

    char *bits_haming = haming2(bits_originais);

    char c1 = bits_haming[1]^bits_haming_arquivo[1];
    char c2 = bits_haming[2]^bits_haming_arquivo[2];
    char c4 = bits_haming[4]^bits_haming_arquivo[4];
    char c8 = bits_haming[8]^bits_haming_arquivo[8];

    if(c1 == 0 && c2 == 0 && c4 == 0 && c8 == 0) {
        //cout << "Tudo certo!" << endl;
        return bytes_arquivo_original;
    }
    else {
        int posicao_mudar = (int)pow(2,0)*c1 + (int)pow(2, 1)*c2 
                            + (int)pow(2, 2)*c4 + (int)pow(2,3)*c8;

        //cout << posicao_mudar << endl;
        if(posicao_mudar >= 12) {
            cout << "Posicão maior que tamanho do codigo haming gerado!" << endl;
            return bytes_arquivo_original;
        }
        else {
			int valor_somado = 0;
			switch(posicao_mudar) {
				
				case 3:
					valor_somado = pow(2,0);
					break;
				case 5:
					valor_somado = pow(2,1);
					break;
				case 6:
					valor_somado = pow(2,2);
					break;
				case 7:
					valor_somado = pow(2,3);
					break;
				case 9:
					valor_somado = pow(2,4);
					break;
				case 10:
					valor_somado = pow(2,5);
					break;
				case 11:
					valor_somado = pow(2,6);
					break;
				case 12:
					valor_somado = pow(2,7);
					break;
			}
            if(bits_haming[posicao_mudar] == 0) {
                bits_haming[posicao_mudar] = 1;
            }
            else {
                bits_haming[posicao_mudar] = 0;
                valor_somado = -valor_somado;
            }

            char g = bits_haming[1]^bits_haming[2]^bits_haming[3]^bits_haming[4]
                    ^bits_haming[5]^bits_haming[6]^bits_haming[7]^bits_haming[8]
                    ^bits_haming[9]^bits_haming[10]^bits_haming[11]^bits_haming[12];
            
            if(g == bits_haming_arquivo[0]) {
				cout << "byte arrumado: " << local_byte + 1 << endl;
                return bytes_arquivo_original + valor_somado;
            }
            else {
                cout << "Incosistencia detectada, não é possivel consertar o byte: " << local_byte + 1 << endl;
                return bytes_arquivo_original;
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
        
    }
    output.close();
    input.close();
}

void reading_teste(string path_haming,string path_original) {
    ifstream input_haming(path_haming, std::ios::binary);
    ifstream input_original(path_original, std::ios::binary);

    vector<unsigned char> buffer_haming(istreambuf_iterator<char>(input_haming), {});
    vector<unsigned char> buffer_original(istreambuf_iterator<char>(input_original), {});
    
    input_original.close();
    input_haming.close();
    
    ofstream output_original;
    output_original.open(path_original, ios::binary);
    
    int j;
    for(int i = 0, j= 0; i< buffer_haming.size(), j < buffer_original.size(); i=i+2, j++) {
        unsigned char *bytes_arquivo_haming = new unsigned char[2];
        bytes_arquivo_haming[0]  =buffer_haming[i];
        bytes_arquivo_haming[1] = buffer_haming[i+1];
        unsigned char bytes_arquivo_original = buffer_original[j];
        output_original << verification(bytes_arquivo_haming, bytes_arquivo_original,j);
    }
}

int main(int argc, char *argv[]) {
	if(argc >= 2) {
		if(argv[2][1] == 'w')
		{
			reading_char(argv[1], "qlq.bin");
			reading_teste("qlq.bin", argv[1]);
		}
		else if(argv[2][1] == 'r') {
				reading_teste("qlq.bin",argv[1]);
		}
	}
    return 0; 
	
}
