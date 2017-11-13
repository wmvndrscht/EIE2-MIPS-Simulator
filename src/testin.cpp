#include <iostream>     
#include <fstream>
#include <cstdint>



int main (int argc, char* argv[]) {

	std::streampos size;

	std::string binin;
	binin = argv[1];
	std::cout << binin << std::endl;

  std::ifstream file (binin, std::ios::in|std::ios::binary|std::ios::ate);


  if (file.is_open()){

  	size = file.tellg();
  	std::cout << "file size: " << size << std::endl; //prints size
  	// may need to include size constraint for too large binaries

    file.seekg(0, std::ios::beg);

    memblock = new char [size];

    file.read( (char*) &ADDR_INSTR, size);

    // file.read( (char*) &ADDR_INSTR, size);
    // fin.read((char*) &A[0], 4);
	
    file.close();

    delete[] memblock;


    uint32_t instruction1 = (ADDR_INSTR[0] << 24 | ADDR_INSTR[1] << 16| ADDR_INSTR[2] << 8| ADDR_INSTR[3]);

    std::cout << instruction1 << std::endl;

    std::cout << "the entire file content is in memory" << std::endl;

  }
  else{ 
  	std::cout << "Unable to open file" << std::endl;
  }
  return 0;
}