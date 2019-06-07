#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

bool debug = true;

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

/**
 * @brief Ela vai gerar o codigo haming a partir dos bits originais
 * @param bits byte original do arquivo
 * @return char* Retorna um vetor de char's com 13 elementos no total
 */
char *gera_haming(char bits[8]) {
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

/**
 * @brief Transforma o haming 
 * @param bits 
 * @return unsigned char* 
 */
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

unsigned char transforma_em_char_normal(char bits[]) {
    char valor_char = 0;
			for(int i =0; i< 13; i++) {
				switch(i) {
					
					case 3:
						valor_char += pow(2,0)*bits[3];
						break;
					case 5:
						valor_char += pow(2,1)*bits[5];
						break;
					case 6:
						valor_char += pow(2,2)*bits[6];
						break;
					case 7:
						valor_char += pow(2,3)*bits[7];
						break;
					case 9:
						valor_char += pow(2,4)*bits[9];
						break;
					case 10:
						valor_char += pow(2,5)*bits[10];
						break;
					case 11:
						valor_char += pow(2,6)*bits[11];
						break;
					case 12:
						valor_char += pow(2,7)*bits[12];
						break;
				}
			}
			return valor_char;
}

/**
 * @brief Cria o codigo haming e converte ele para char para gravar em um arquivo
 * 
 * @param bits É o byte original do arquivo convertido em uma lista de char's
 * @return unsigned char* Retorna os dois char's os quais serão gravados no arquivo haming
 */
unsigned char *haming(char bits[8]) {
    char *codigo_haming = gera_haming(bits);
    return transforma_em_char(codigo_haming);
}

/**
 * @brief Verificação se o codigo haming armazenado é compativel com o codigo haming gerado pelo arquivo original,e se não tenta consertar
 * 
 * @param bytes_arquivo_haming Bytes do arquivo original, eles vem em formato de char e são dois, pois o codigo haming gera 13 bits
 * @param byte_arquivo_original Byte do arquivo original, é apenas um e em formato char
 * @param local_byte Diz o local do byte no buffer
 * @return unsigned char Retorna um char o qual será gravado no arquivo original
 */
void verification(unsigned char *bytes_arquivo_haming, int local_byte, ofstream *output_haming, ofstream *output_original) {
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

    char *bits_originais = new char[8];
    bits_originais[0] = bits_haming_arquivo[3];
    bits_originais[1] = bits_haming_arquivo[5];
    bits_originais[2] = bits_haming_arquivo[6];
    bits_originais[3] = bits_haming_arquivo[7];
    bits_originais[4] = bits_haming_arquivo[9];
    bits_originais[5] = bits_haming_arquivo[10];
    bits_originais[6] = bits_haming_arquivo[11];
    bits_originais[7] = bits_haming_arquivo[12];

    char *bits_haming = gera_haming(bits_originais);

    char c1 = bits_haming[1]^bits_haming_arquivo[1];
    char c2 = bits_haming[2]^bits_haming_arquivo[2];
    char c4 = bits_haming[4]^bits_haming_arquivo[4];
    char c8 = bits_haming[8]^bits_haming_arquivo[8];

    if(c1 == 0 && c2 == 0 && c4 == 0 && c8 == 0) {
        output_haming->write((char *)bytes_arquivo_haming,2);
        output_original->put((char)transforma_em_char_normal(bits_haming));
    }
    else {
        int posicao_mudar = (int)pow(2,0)*c1 + (int)pow(2, 1)*c2 
                            + (int)pow(2, 2)*c4 + (int)pow(2,3)*c8;

        if(posicao_mudar > 12) {
            cout << "Posicão maior que tamanho do codigo haming gerado!" << endl;
            //return byte_arquivo_original;
        }
        else {
            cout << endl << "Posicao a ser alterada e " << posicao_mudar 
            << " do byte " <<  local_byte <<endl;
			
            if(bits_haming[posicao_mudar] == 0) {
                bits_haming[posicao_mudar] = 1;
            }
            else {
                bits_haming[posicao_mudar] = 0;
            }
	        bits_haming[1] = bits_haming[3]^bits_haming[5]^bits_haming[7]^bits_haming[9]^bits_haming[11];

	        bits_haming[2] = bits_haming[3]^bits_haming[6]^bits_haming[7]^bits_haming[10]^bits_haming[11];

	        bits_haming[4] = bits_haming[5]^bits_haming[6]^bits_haming[7]^bits_haming[12];

	        bits_haming[8]= bits_haming[9]^bits_haming[10]^bits_haming[11]^bits_haming[12];
	        
            char g = bits_haming[1]^bits_haming[2]^bits_haming[3]^bits_haming[4]
                    ^bits_haming[5]^bits_haming[6]^bits_haming[7]^bits_haming[8]
                    ^bits_haming[9]^bits_haming[10]^bits_haming[11]^bits_haming[12];

            
            if(g == bits_haming_arquivo[0]) {
				cout << "byte arrumado com sucesso!" << endl;
				output_haming->write((char *)transforma_em_char(bits_haming),2);
				/*
				output_haming << transforma_em_char(bits_haming);
				output_original<< transforma_em_char_normal(bits_haming);
				*/
				output_original->put(transforma_em_char_normal(bits_haming));
                //return byte_arquivo_original + valor_somado;
            }
            else {
                cout << "Incosistencia detectada, não é possivel consertar o byte: " << local_byte + 1 << endl;
				cout << posicao_mudar << endl;
				/*
                output_haming << bytes_arquivo_haming;
                output_original<< transforma_em_char_normal(bits_haming);
                */
                output_haming->write((char *)bytes_arquivo_haming,2);
                output_original->put(transforma_em_char_normal(bits_haming));
            }
        }
    }
}

/**
 * @brief Lê o arquivo original gera o haming e grava no arquivo destino
 * 
 * @param path_src Caminho do arquivo original
 * @param path_dest Caminho do arquivo destino
 */
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
    cout << "Gravação feita com sucesso!" << endl;
    output.close();
    input.close();
}

/**
 * @brief Lê o arquivo original e verifica com o arquivo haming
 * 
 * @param path_haming Caminho do arquivo haming
 * @param path_original Caminho do arquivo original
 */
void reading_verification(string path_haming,string path_original) {
    ifstream input_haming(path_haming, std::ios::binary);
    //ifstream input_original(path_original, std::ios::binary);

    vector<unsigned char> buffer_haming(istreambuf_iterator<char>(input_haming), {});
    //vector<unsigned char> buffer_original(istreambuf_iterator<char>(input_original), {});
    
    //input_original.close();
    input_haming.close();
    
    ofstream output_original;
    output_original.open(path_original, ios::binary);
    
    ofstream output_haming;
    output_haming.open(path_haming, ios::binary);
    
    for(int i = 0; i< buffer_haming.size(); i=i+2) {
        unsigned char *bytes_arquivo_haming = new unsigned char[2];
        bytes_arquivo_haming[0]  =buffer_haming[i];
        bytes_arquivo_haming[1] = buffer_haming[i+1];
        //unsigned char byte_arquivo_original = buffer_original[j];
        verification(bytes_arquivo_haming,i,&output_haming, &output_original);
    }
}

/**
 * @brief Gera o nome do arquivo que vai ser o arquivo haming
 * 
 * @param nome_original Nome do arquivo original
 * @return string Retorna o nome do arquivo com o codigo haming
 */
string gerando_nome_arquivo(char *nome_original) {
    string aux = nome_original;
    string terminacao = ".sotw";
    for(int i = 0; i< aux.size(); i++) {
        if(aux[i] == '.') {
            return (aux.substr(0,i) + terminacao);
        }
    }

}

int main(int argc, char *argv[]) {
	if(argc >= 2) {
        string arquivo_haming = gerando_nome_arquivo(argv[1]);
		if(argv[2][1] == 'w')
		{
			reading_char(argv[1], arquivo_haming);
			reading_verification(arquivo_haming, argv[1]);
		}
		else if(argv[2][1] == 'r') {
			reading_verification(argv[1],argv[1]);
		}
	}
    return 0; 
	
}
