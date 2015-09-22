
// Primitive BMP to ASCII art generator
// Reads source.bmp and outputs art.txt
// Source must be 24-bit .bmp
// http://www.dreamincode.net/code/snippet957.htm
// Modified Sept 2010 Bill Thibault to make standalone, platform-indep.
// only works on 24-bit uncompressed BMP files. some of them anyway.

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef struct bmp_file_header {
	uint16		filetype; // BM
	uint32		filesize; // in 32-bit integers
	uint32		reserved; // must be 0
	uint32		offset;	  // byte offset to start of data
	uint32		bytesInHeader;	// 40
	uint32		width;			// in pixels
	uint32		height;			// in pixels
	uint16		planes;			// 1
	uint16		bitsPerPixel;	// 1,4,8, or 24
	uint32		compression;	// 0 = none, 1 = 8bit RLE, 2 = 4 bit RLE
	uint32		size;			// of image, in bytes
	uint32		horizRes;		// in pixels/m
	uint32		vertRes;		//      "
	uint32		indicesUsed;	// # color indices used by the bitmap
	uint32		indicesImportant; // # important indices (0=all)
} BMPFileHeader;




#define MAX_SHADES 10
#define DEBUG 1

uint16 extractShort ( ifstream &f )
{
  char buf[2];
  f.read ( buf, 2 );
  uint16 value = buf[0] | (buf[1] << 8);
  return value;
}

uint32 extractInt ( ifstream &f )
{
  char buf[4];
  f.read ( buf, 4 );
  uint32 value = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
  return value;
}


void readHeader ( ifstream& f, BMPFileHeader& header )
{
  header.filetype = extractShort ( f );
  header.filesize = extractInt ( f );
  header.reserved = extractInt ( f );
  header.offset = extractInt ( f );
  header.bytesInHeader = extractInt ( f );
  header.width = extractInt ( f );
  header.height = extractInt ( f );
  header.planes = extractShort ( f );
  header.bitsPerPixel = extractShort ( f );
  header.compression = extractInt ( f );
  header.size = extractInt ( f );
  header.horizRes = extractInt ( f );
  header.vertRes = extractInt ( f );
  header.indicesUsed = extractInt ( f );
  header.indicesImportant = extractInt ( f );

#ifdef DEBUG
  cout << "filetype " << header.filetype << endl;
  cout << "filesize " << header.filesize << endl;
  cout << "reserved " << header.reserved << endl;
  cout << "offset " << header.offset << endl;
  cout << "bytesInHeader " << header.bytesInHeader << endl;
  cout << "width " << int(header.width) << endl;
  cout << "height " << int(header.height) << endl;
  cout << "planes " << header.planes << endl;
  cout << "bitsPerPixel " << header.bitsPerPixel << endl;
  cout << "compression " << header.compression << endl;
  cout << "size " << header.size << endl;
  cout << "horizRes " << header.horizRes << endl;
  cout << "vertRes " << header.vertRes << endl;
  cout << "indicesUsed " << header.indicesUsed << endl;
  cout << "indicesImportant " << header.indicesImportant << endl;
#endif

}



int main()
{
  int width, height;
  unsigned char *image;
  char shades[MAX_SHADES] = {'#','$','O','=','+','|','-','^','.',' '};
  //  char shades[MAX_SHADES] = {'0','1','2','3','4','5','6','7','8','9'};
  int average_color = 0;

  ifstream bmpfile;
  ofstream txtfile;
  BMPFileHeader header;

  // Open the image file
  bmpfile.open ( "source.bmp", ios::in | ios::binary );
  if ( ! bmpfile ) {
    cout << "cannot open source.bmp" << endl;
    return 1;
  }

  // Read header
  readHeader ( bmpfile, header );

  // Read image
  width = int(header.width);
  if ( width < 0 )
    width *= -1;
  height = int(header.height);
  if ( height < 0 )
    height *= -1;

  int rowsize = width * 3;

  image = new unsigned char [ rowsize * height ];

  bmpfile.seekg ( header.offset, ios::beg );
  bmpfile.read ( (char *)image, 3*width*height );
  bmpfile.close();

  // write the output file
  txtfile.open ( "art.txt", ios::out );

  for(int y = height-1; y >= 0; y--) {

    for(int x = 0; x < width; x++) {

      // Get the average color
      average_color = ( image[x*3     + y*rowsize] +
                        image[x*3 + 1 + y*rowsize] +
                        image[x*3 + 2 + y*rowsize] ) / 3;

      // Convert to a shade
      average_color /= (256/MAX_SHADES);
      if(average_color >= MAX_SHADES)
        average_color = MAX_SHADES-1;

      // Output
      txtfile << shades[average_color];

    }

    txtfile << endl;

  }

  txtfile.close();
  return 0;
}
