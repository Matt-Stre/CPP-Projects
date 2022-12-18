
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Header
{
public:
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
};

class pixel
{
public:
	unsigned char _blue;
	unsigned char _green;
	unsigned char _red;
};

class newfile
{
public:
	Header _fileheader;
	vector<pixel> _pixelVector;
};

bool testfiles(newfile& tempfile1, newfile& tempfile2)
{
	// comparing headers;
	int headercount = 0;
	if (tempfile1._fileheader.idLength == (int)tempfile2._fileheader.idLength)
		headercount += 1;
	if (tempfile1._fileheader.idLength != tempfile2._fileheader.idLength) cout << "idLength does not match" << endl;
	if (tempfile1._fileheader.colorMapType == tempfile2._fileheader.colorMapType)
		headercount += 1;
	if (tempfile1._fileheader.colorMapType != tempfile2._fileheader.colorMapType) cout << "colormaptype does not match" << endl;
	if (tempfile1._fileheader.dataTypeCode == tempfile2._fileheader.dataTypeCode)
		headercount += 1;
	if (tempfile1._fileheader.dataTypeCode != tempfile2._fileheader.dataTypeCode) cout << "datatypecode does not match" << endl;
	if (tempfile1._fileheader.colorMapOrigin == tempfile2._fileheader.colorMapOrigin)
		headercount += 1;
	if (tempfile1._fileheader.colorMapOrigin != tempfile2._fileheader.colorMapOrigin) cout << "colormaptype does not match" << endl;
	if (tempfile1._fileheader.colorMapLength == tempfile2._fileheader.colorMapLength)
		headercount += 1;
	if (tempfile1._fileheader.colorMapLength != tempfile2._fileheader.colorMapLength) cout << "colormaplength does not match" << endl;
	if (tempfile1._fileheader.colorMapDepth == tempfile2._fileheader.colorMapDepth)
		headercount += 1;
	if (tempfile1._fileheader.colorMapDepth != tempfile2._fileheader.colorMapDepth) cout << "colomapdepth does not match" << endl;
	if (tempfile1._fileheader.xOrigin == tempfile2._fileheader.xOrigin)
		headercount += 1;
	if (tempfile1._fileheader.xOrigin != tempfile2._fileheader.xOrigin) cout << "xOrigin does not match" << endl;
	if (tempfile1._fileheader.yOrigin == tempfile2._fileheader.yOrigin)
		headercount += 1;
	if (tempfile1._fileheader.yOrigin != tempfile2._fileheader.yOrigin) cout << "yOrigin does not match" << endl;
	if (tempfile1._fileheader.width == tempfile2._fileheader.width)
		headercount += 1;
	if (tempfile1._fileheader.width != tempfile2._fileheader.width) cout << "width does not match" << endl;
	if (tempfile1._fileheader.height == tempfile2._fileheader.height)
		headercount += 1;
	if (tempfile1._fileheader.height != tempfile2._fileheader.height) cout << "heighth does not match" << endl;
	if (tempfile1._fileheader.bitsPerPixel == tempfile2._fileheader.bitsPerPixel)
		headercount += 1;
	if (tempfile1._fileheader.bitsPerPixel != tempfile2._fileheader.bitsPerPixel) cout << "bitsperpixel does not match" << endl;
	if (tempfile1._fileheader.imageDescriptor == tempfile2._fileheader.imageDescriptor)
		headercount += 1;
	if (tempfile1._fileheader.imageDescriptor != tempfile2._fileheader.imageDescriptor) cout << "imagedescriptor does not match" << endl;


	if (headercount == 12) // if headers are the same
	{
		int pixelsize1 = tempfile1._fileheader.width * tempfile1._fileheader.height;
		for (int i = 0; i < pixelsize1; i++)
		{
			pixel currentpixel1 = tempfile1._pixelVector[i];
			pixel currentpixel2 = tempfile2._pixelVector[i];
			if (currentpixel1._blue == currentpixel2._blue && currentpixel1._green == currentpixel2._green && currentpixel1._red == currentpixel2._red)
			{

			}
			else
			{
				cout << "Error at index: " << i << endl;
				cout << "Correct BGR: " << (int)currentpixel1._blue << " " << (int)currentpixel1._green << " " << (int)currentpixel1._red << endl;
				cout << "Actual BGR: " << (int)currentpixel2._blue << " " << (int)currentpixel2._green << " " << (int)currentpixel2._red << endl;
				return false;
			}
		}
		return true;
	}
	else
	{
		cout << "Error outside of loop" << endl;
		return false;
	}
}

void readfile(newfile& newfile, ifstream& file)
{
	//reading header
	file.read(&newfile._fileheader.idLength, sizeof(newfile._fileheader.idLength));
	file.read(&newfile._fileheader.colorMapType, sizeof(newfile._fileheader.colorMapType));
	file.read(&newfile._fileheader.dataTypeCode, sizeof(newfile._fileheader.dataTypeCode));
	file.read(reinterpret_cast<char*>(&newfile._fileheader.colorMapOrigin), sizeof(newfile._fileheader.colorMapOrigin));
	file.read(reinterpret_cast<char*>(& newfile._fileheader.colorMapLength), sizeof(newfile._fileheader.colorMapLength));
	file.read(&newfile._fileheader.colorMapDepth, sizeof(newfile._fileheader.colorMapDepth));
	file.read(reinterpret_cast<char*>(& newfile._fileheader.xOrigin), sizeof(newfile._fileheader.xOrigin));
	file.read(reinterpret_cast<char*>(& newfile._fileheader.yOrigin), sizeof(newfile._fileheader.yOrigin));
	file.read(reinterpret_cast<char*>(& newfile._fileheader.width), sizeof(newfile._fileheader.width));
	file.read(reinterpret_cast<char*>(& newfile._fileheader.height), sizeof(newfile._fileheader.height));
	file.read(&newfile._fileheader.bitsPerPixel, sizeof(newfile._fileheader.bitsPerPixel));
	file.read(&newfile._fileheader.imageDescriptor, sizeof(newfile._fileheader.imageDescriptor));
	
	//testing outputs for debugging
	//cout << (int)newfile._fileheader.dataTypeCode << endl;
	//cout << (int)newfile._fileheader.width << endl;
	//cout << (int)newfile._fileheader.height << endl;
	//cout << (int)newfile._fileheader.bitsPerPixel << endl;
	
	//reading pixels
	int pixelsize = newfile._fileheader.width * newfile._fileheader.height;
	for (int i = 0; i < pixelsize; i++)
	{
		pixel currentpixel; 
		file.read((char*)&currentpixel._blue, 1);
		file.read((char*)& currentpixel._green, 1);
		file.read((char*)& currentpixel._red, 1);
		newfile._pixelVector.push_back(currentpixel); 

	}	

}

void writefile(newfile& newfile, ofstream& file)
{
	file.write(reinterpret_cast<char*>(& newfile._fileheader.idLength), sizeof(newfile._fileheader.idLength));
	file.write(reinterpret_cast<char*>(& newfile._fileheader.colorMapType), sizeof(newfile._fileheader.colorMapType));
	file.write(reinterpret_cast<char*>(& newfile._fileheader.dataTypeCode), sizeof(newfile._fileheader.dataTypeCode));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.colorMapOrigin), sizeof(newfile._fileheader.colorMapOrigin));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.colorMapLength), sizeof(newfile._fileheader.colorMapLength));
	file.write(reinterpret_cast<char*>(& newfile._fileheader.colorMapDepth), sizeof(newfile._fileheader.colorMapDepth));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.xOrigin), sizeof(newfile._fileheader.xOrigin));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.yOrigin), sizeof(newfile._fileheader.yOrigin));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.width), sizeof(newfile._fileheader.width));
	file.write(reinterpret_cast<char*>(&newfile._fileheader.height), sizeof(newfile._fileheader.height));
	file.write(reinterpret_cast<char*>(& newfile._fileheader.bitsPerPixel), sizeof(newfile._fileheader.bitsPerPixel));
	file.write(reinterpret_cast<char*>(& newfile._fileheader.imageDescriptor), sizeof(newfile._fileheader.imageDescriptor));


	
	//writing pixels
	int pixelsize = newfile._fileheader.width * newfile._fileheader.height;
	for (int i = 0; i < pixelsize; i++)
	{
		pixel currentpixel = newfile._pixelVector[i];
		file.write(reinterpret_cast<char*>(&currentpixel._blue), sizeof(currentpixel._blue));
		file.write(reinterpret_cast<char*>(&currentpixel._green), sizeof(currentpixel._green));
		file.write(reinterpret_cast<char*>(&currentpixel._red), sizeof(currentpixel._red));
		
	}
	
}

newfile multiplyfile(newfile& top, newfile& bottom)
{
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		float tempblue = ((((float)top._pixelVector[i]._blue) * (((float)bottom._pixelVector[i]._blue)))/255.0f+0.5f);
		float tempgreen = ((((float)top._pixelVector[i]._green) * (((float)bottom._pixelVector[i]._green)))/255.0f+0.5f);
		float tempred = ((((float)top._pixelVector[i]._red) * (((float)bottom._pixelVector[i]._red)))/255.0f+0.5f);

		if (tempblue > 255)
			tempblue = 255;
		if (tempgreen > 255)
			tempgreen = 255;
		if (tempred > 255)
			tempred = 255;

		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		(unsigned char)tempred; 
		top._pixelVector[i]._blue = tempblue;
		top._pixelVector[i]._green = tempgreen;
		top._pixelVector[i]._red = tempred;
	}
	return top;
}

newfile subtractfile(newfile& top, newfile& bottom)
{
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		float tempblue = ((((float)bottom._pixelVector[i]._blue) - (((float)top._pixelVector[i]._blue))));
		float tempgreen = ((((float)bottom._pixelVector[i]._green) - (((float)top._pixelVector[i]._green))));
		float tempred = ((((float)bottom._pixelVector[i]._red) - (((float)top._pixelVector[i]._red))));

		if (tempblue < 0)
			tempblue = 0;
		if (tempgreen < 0)
			tempgreen = 0;
		if (tempred < 0)
			tempred = 0;
		tempblue += 0.5f;
		tempgreen += 0.5f;
		tempred += 0.5f;
		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		(unsigned char)tempred;
		top._pixelVector[i]._blue = tempblue;
		top._pixelVector[i]._green = tempgreen;
		top._pixelVector[i]._red = tempred;
	}
	return top;
}

newfile screenfiles(newfile& top, newfile& bottom)
{
	// invert each value, multiply them and then invert that value - should likely 0-1
	for (int i = 0; i < top._pixelVector.size(); i++)
	{

		
		float tempblue = 255-(((255- top._pixelVector[i]._blue)*(255- bottom._pixelVector[i]._blue))/255.0f-0.5f);
		float tempgreen = 255 - (((255 - top._pixelVector[i]._green) * (255 - bottom._pixelVector[i]._green)) / 255.0f - 0.5f);
		float tempred = 255 - (((255 - top._pixelVector[i]._red) * (255 - bottom._pixelVector[i]._red)) / 255.0f - 0.5f);

		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		(unsigned char)tempred;
		top._pixelVector[i]._blue = tempblue;
		top._pixelVector[i]._green = tempgreen;
		top._pixelVector[i]._red = tempred;
	}
	return top;

}

newfile overlayfiles(newfile& top, newfile& bottom)
{
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		float tempblue;
		float tempgreen;
		float tempred;
		
		
		if (bottom._pixelVector[i]._blue > 127.5)
		{
			tempblue = 255 - ((2 * (255 - top._pixelVector[i]._blue) * (255 - bottom._pixelVector[i]._blue)) / 255.0f);
		}
		else
		{
			tempblue = ((2*(bottom._pixelVector[i]._blue * top._pixelVector[i]._blue))/ 255.0f);
		}

		if (bottom._pixelVector[i]._green > 127.5)
		{
			tempgreen = 255 - ((2 * (255 - top._pixelVector[i]._green) * (255 - bottom._pixelVector[i]._green)) / 255.0f);
		}
		else
		{
			tempgreen = (2 * (bottom._pixelVector[i]._green * top._pixelVector[i]._green)) / 255.0f;
		} 

		if (bottom._pixelVector[i]._red > 127.5)
			{
			tempred = 255 - ((2 * (255 - top._pixelVector[i]._red) * (255 - bottom._pixelVector[i]._red)) / 255.0f);
			}
		else
		{
			tempred = (2 * (bottom._pixelVector[i]._red * top._pixelVector[i]._red)) / 255.0f;
		}
		tempblue += 0.5f;
		tempgreen += 0.5f;
		tempred += 0.5f;
		if (tempblue < 0)
			tempblue = 0;
		if (tempgreen < 0)
			tempgreen = 0;
		if (tempred < 0)
			tempred = 0;
		if (tempblue > 255)
			tempblue = 255;
		if (tempgreen > 255)
			tempgreen = 255;
		if (tempred > 255)
			tempred = 255;
		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		(unsigned char)tempred;
		top._pixelVector[i]._blue = tempblue;
		top._pixelVector[i]._green = tempgreen;
		top._pixelVector[i]._red = tempred;
	}
	return top;
}

newfile addgreen(newfile& top)
{
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		float tempgreen = (float)top._pixelVector[i]._green + 200;
		if (tempgreen > 255)
			tempgreen = 255;

		(unsigned char)tempgreen;
		top._pixelVector[i]._green = tempgreen;

	}
	return top;
}

newfile multiplyredzeroblue(newfile& top)
{
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		float tempblue = 0;
		float tempgreen = (float)top._pixelVector[i]._green;
		float tempred = (float)top._pixelVector[i]._red * 4;
		if (tempred > 255)
			tempred = 255;

		(unsigned char)tempred;
		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		top._pixelVector[i]._red = tempred;
		top._pixelVector[i]._blue = 0;
		top._pixelVector[i]._green = tempgreen;

	}
	return top;
}

newfile flipfile(newfile& top)
{
	vector <pixel> tempvector(top._pixelVector.size());
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		pixel temppixel;
		float tempblue = (float)top._pixelVector[i]._blue;
		float tempgreen = (float)top._pixelVector[i]._green;
		float tempred = (float)top._pixelVector[i]._red;




		(unsigned char)tempred;
		(unsigned char)tempblue;
		(unsigned char)tempgreen;
		temppixel._red = tempred;
		temppixel._blue = tempblue;
		temppixel._green = tempgreen;
		tempvector.insert(tempvector.begin(), temppixel);
	}
	//swap values
	for (int i = 0; i < top._pixelVector.size(); i++)
	{
		top._pixelVector[i]._red = tempvector[i]._red;
		top._pixelVector[i]._blue = tempvector[i]._blue;
		top._pixelVector[i]._green = tempvector[i]._green;
	}

	return top;
}

newfile extractpixel(newfile& top, string color)
{
	if (color == "red")
	{
		for (int i = 0; i < top._pixelVector.size(); i++)
		{
			top._pixelVector[i]._blue = top._pixelVector[i]._red;
			top._pixelVector[i]._green = top._pixelVector[i]._red;
			top._pixelVector[i]._red = top._pixelVector[i]._red;
		}
	}
	if (color == "green")
	{
		for (int i = 0; i < top._pixelVector.size(); i++)
		{
			top._pixelVector[i]._blue = top._pixelVector[i]._green;
			top._pixelVector[i]._green = top._pixelVector[i]._green;
			top._pixelVector[i]._red = top._pixelVector[i]._green;
		}
	}
	if (color == "blue")
	{
		for (int i = 0; i < top._pixelVector.size(); i++)
		{
			top._pixelVector[i]._blue = top._pixelVector[i]._blue;
			top._pixelVector[i]._green = top._pixelVector[i]._blue;
			top._pixelVector[i]._red = top._pixelVector[i]._blue;
		}
	}
	return top;
}

newfile combinethreefiles(newfile& blue, newfile& green, newfile& red)
{
	for (int i = 0; i < blue._pixelVector.size(); i++)
	{
		blue._pixelVector[i]._blue = blue._pixelVector[i]._blue;
		blue._pixelVector[i]._green = green._pixelVector[i]._green;
		blue._pixelVector[i]._red = red._pixelVector[i]._red;
	}
	return blue;
}

newfile combinefourfiles(newfile& bottomleft, newfile& bottomright, newfile& topleft, newfile& topright)
{
	newfile final;
	final._fileheader = bottomleft._fileheader;
	final._fileheader.width = 1024;
	final._fileheader.height = 1024;
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			pixel temppixel;
			temppixel._blue = bottomleft._pixelVector[(i*512)+j]._blue;
			temppixel._green = bottomleft._pixelVector[(i * 512) + j]._green;
			temppixel._red = bottomleft._pixelVector[(i * 512) + j]._red;
			final._pixelVector.push_back(temppixel);
		}
		for (int j = 0; j < 512; j++)
		{
			pixel temppixel;
			temppixel._blue = bottomright._pixelVector[(i * 512) + j]._blue;
			temppixel._green = bottomright._pixelVector[(i * 512) + j]._green;
			temppixel._red = bottomright._pixelVector[(i * 512) + j]._red;
			final._pixelVector.push_back(temppixel);
		}

	}
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			pixel temppixel;
			temppixel._blue = topleft._pixelVector[(i * 512) + j]._blue;
			temppixel._green = topleft._pixelVector[(i * 512) + j]._green;
			temppixel._red = topleft._pixelVector[(i * 512) + j]._red;
			final._pixelVector.push_back(temppixel);
		}
		for (int j = 0; j < 512; j++)
		{
			pixel temppixel;
			temppixel._blue = topright._pixelVector[(i * 512) + j]._blue;
			temppixel._green = topright._pixelVector[(i * 512) + j]._green;
			temppixel._red = topright._pixelVector[(i * 512) + j]._red;
			final._pixelVector.push_back(temppixel);
		}

	}
	return final;
}

int main()
{

	//---TEST 1---
	while (true)
	{
		//loading in files
		ifstream filelayer1;
		filelayer1.open("input/layer1.tga", ios_base::in | ios_base::binary);
		newfile newfilelayer1;
		readfile(newfilelayer1, filelayer1);

		ifstream filepattern1;
		filepattern1.open("input/pattern1.tga", ios_base::in | ios_base::binary);
		newfile newfilepattern1;
		readfile(newfilepattern1, filepattern1);

		//performing operations and outputting
		ifstream fileexample1;
		newfile result1 = multiplyfile(newfilelayer1, newfilepattern1);
		readfile(result1, fileexample1);

		ofstream testfile1;
		testfile1.open("output/part1.tga", ios_base::out | ios_base::binary);
		writefile(result1, testfile1);

		//loading example
		ifstream example1;
		example1.open("examples/EXAMPLE_part1.tga", ios_base::in | ios_base::binary);
		newfile example1a;
		readfile(example1a, example1);

		//testing files
		if (testfiles(example1a, result1))
			cout << " Test #1...... Passed!" << endl;
		else
			cout << " Test #1....... Failed!" << endl;
		break;
	}

	
	//---TEST 2---
	while (true)
	{
		//loading files
		ifstream filelayer2;
		filelayer2.open("input/layer2.tga", ios_base::in | ios_base::binary);
		newfile newfilelayer2;
		readfile(newfilelayer2, filelayer2);

		ifstream filecar2;
		filecar2.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfilecar2;
		readfile(newfilecar2, filecar2);

		//performing operations and outputting
		ifstream fileexample2;
		newfile result2 = subtractfile(newfilelayer2, newfilecar2);
		readfile(result2, fileexample2);

		ofstream testfile2;
		testfile2.open("output/part2.tga", ios_base::out | ios_base::binary);
		writefile(result2, testfile2);

		//loading example
		ifstream example2;
		example2.open("examples/EXAMPLE_part2.tga", ios_base::in | ios_base::binary);
		newfile example2a;
		readfile(example2a, example2);

		//testing files
		if (testfiles(example2a, result2))
			cout << " Test #2...... Passed!" << endl;
		else
			cout << " Test #2...... Failed!" << endl;
		break;
	}


	//---TEST 3---
	while (true)
	{
		//loading files
		ifstream filelayer3;
		filelayer3.open("input/layer1.tga", ios_base::in | ios_base::binary);
		newfile newfilelayer3;
		readfile(newfilelayer3, filelayer3);

		ifstream filepattern3;
		filepattern3.open("input/pattern2.tga", ios_base::in | ios_base::binary);
		newfile newfilepattern3;
		readfile(newfilepattern3, filepattern3);

		ifstream filetext3;
		filetext3.open("input/text.tga", ios_base::in | ios_base::binary);
		newfile newfiletext3;
		readfile(newfiletext3, filetext3);

		//performing operations and outputting
		newfile result3a = multiplyfile(newfilelayer3, newfilepattern3);
		newfile result3b = screenfiles(newfiletext3, result3a);

		ifstream fileexample3;
		readfile(result3b, fileexample3);

		ofstream testfile3;
		testfile3.open("output/part3.tga", ios_base::out | ios_base::binary);
		writefile(result3b, testfile3);

		//loading example
		ifstream example3;
		example3.open("examples/EXAMPLE_part3.tga", ios_base::in | ios_base::binary);
		newfile example3a;
		readfile(example3a, example3);

		//testing files
		if (testfiles(example3a, result3b))
			cout << " Test #3...... Passed!" << endl;
		else
			cout << " Test #3...... Failed!" << endl;
		break;


	}
	

	//---TEST 4---
	while (true)
	{
		//loading files
		ifstream filecircles4;
		filecircles4.open("input/circles.tga", ios_base::in | ios_base::binary);
		newfile newfilecircles4;
		readfile(newfilecircles4, filecircles4);

		ifstream filelayer4;
		filelayer4.open("input/layer2.tga", ios_base::in | ios_base::binary);
		newfile newfilelayer4;
		readfile(newfilelayer4, filelayer4);

		ifstream filepattern4;
		filepattern4.open("input/pattern2.tga", ios_base::in | ios_base::binary);
		newfile newfilepattern4;
		readfile(newfilepattern4, filepattern4);

		//performing operations and outputting
		newfile result4a = multiplyfile(newfilecircles4, newfilelayer4);
		newfile result4b = subtractfile(newfilepattern4, result4a);

		ifstream fileexample4;
		readfile(result4b, fileexample4);

		ofstream testfile4;
		testfile4.open("output/part4.tga", ios_base::out | ios_base::binary);
		writefile(result4b, testfile4);

		//loading example
		ifstream example4;
		example4.open("examples/EXAMPLE_part4.tga", ios_base::in | ios_base::binary);
		newfile example4a;
		readfile(example4a, example4);

		//testing files
		if (testfiles(example4a, result4b))
			cout << " Test #4...... Passed!" << endl;
		else
			cout << " Test #4...... Failed!" << endl;
		break;

	}
	

	//--TEST 5--
	while (true)
	{
		//loading files
		ifstream filelayer5;
		filelayer5.open("input/layer1.tga", ios_base::in | ios_base::binary);
		newfile newfilelayer5;
		readfile(newfilelayer5, filelayer5);

		ifstream filepattern5;
		filepattern5.open("input/pattern1.tga", ios_base::in | ios_base::binary);
		newfile newfilepattern5;
		readfile(newfilepattern5, filepattern5);

		//performing calculation and outputting
		newfile result5 = overlayfiles(newfilelayer5, newfilepattern5);
		ifstream fileexample5;
readfile(result5, fileexample5);

ofstream testfile5;
testfile5.open("output/part5.tga", ios_base::out | ios_base::binary);
writefile(result5, testfile5);

//loading example
ifstream example5;
example5.open("examples/EXAMPLE_part5.tga", ios_base::in | ios_base::binary);
newfile example5a;
readfile(example5a, example5);

//testing files
if (testfiles(example5a, result5))
cout << " Test #5...... Passed!" << endl;
else
cout << " Test #5...... Failed!" << endl;
break;
	}


	//--TEST 6--
	while (true)
	{
		ifstream file6car;
		file6car.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfile6car;
		readfile(newfile6car, file6car);

		ifstream fileexample6;
		newfile result6 = addgreen(newfile6car);
		readfile(result6, fileexample6);

		ofstream testfile6;
		testfile6.open("output/part6.tga", ios_base::out | ios_base::binary);
		writefile(result6, testfile6);

		ifstream example6;
		example6.open("examples/EXAMPLE_part6.tga", ios_base::in | ios_base::binary);
		newfile example6a;
		readfile(example6a, example6);

		if (testfiles(example6a, result6))
			cout << " Test #6...... Passed!" << endl;
		else
			cout << " Test #6...... Failed!" << endl;
		break;
	}


	//--TEST 7--
	while (true)
	{
		//loading file
		ifstream file7car;
		file7car.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfile7car;
		readfile(newfile7car, file7car);

		//performing operations and outputting
		ifstream fileexample7;
		newfile result7 = multiplyredzeroblue(newfile7car);
		readfile(result7, fileexample7);

		ofstream testfile7;
		testfile7.open("output/part7.tga", ios_base::out | ios_base::binary);
		writefile(result7, testfile7);

		//loading example
		ifstream example7;
		example7.open("examples/EXAMPLE_part7.tga", ios_base::in | ios_base::binary);
		newfile example7a;
		readfile(example7a, example7);

		//testing files
		if (testfiles(example7a, result7))
			cout << " Test #7...... Passed!" << endl;
		else
			cout << " Test #7...... Failed!" << endl;
		break;
	}


	//--TEST 8---
	while (true)
	{
		//loading file
		ifstream filecarblue8;
		filecarblue8.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfileblue8;
		readfile(newfileblue8, filecarblue8);

		ifstream filecargreen8;
		filecargreen8.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfilegreen8;
		readfile(newfilegreen8, filecargreen8);

		ifstream filecarred8;
		filecarred8.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfilered8;
		readfile(newfilered8, filecarred8);

		//performing calculations and outputing
		//blue
		newfile resultblue8 = extractpixel(newfileblue8, "blue");
		ifstream fileexampleblue8;
		readfile(resultblue8, fileexampleblue8);

		ofstream testfileblue8;
		testfileblue8.open("output/part8_b.tga", ios_base::out | ios_base::binary);
		writefile(resultblue8, testfileblue8);

		//green
		newfile resultgreen8 = extractpixel(newfilegreen8, "green");
		ifstream fileexamplegreen8;
		readfile(resultgreen8, fileexamplegreen8);

		ofstream testfilegreen8;
		testfilegreen8.open("output/part8_g.tga", ios_base::out | ios_base::binary);
		writefile(resultgreen8, testfilegreen8);

		//red
		newfile resultred8 = extractpixel(newfilered8, "red");
		ifstream fileexamplered8;
		readfile(resultred8, fileexamplered8);

		ofstream testfilered8;
		testfilered8.open("output/part8_r.tga", ios_base::out | ios_base::binary);
		writefile(resultred8, testfilered8);

		//loading examples
		
		//blue
		ifstream exampleblue8;
		exampleblue8.open("examples/EXAMPLE_part8_b.tga", ios_base::in | ios_base::binary);
		newfile exampleblue8a;
		readfile(exampleblue8a, exampleblue8);

		//green
		ifstream examplegreen8;
		examplegreen8.open("examples/EXAMPLE_part8_g.tga", ios_base::in | ios_base::binary);
		newfile examplegreen8a;
		readfile(examplegreen8a, examplegreen8);

		//red
		ifstream examplered8;
		examplered8.open("examples/EXAMPLE_part8_r.tga", ios_base::in | ios_base::binary);
		newfile examplered8a;
		readfile(examplered8a, examplered8);

		//testing files
		if (testfiles(exampleblue8a, resultblue8) && testfiles(examplegreen8a, resultgreen8) && testfiles(examplegreen8a, resultgreen8))
			cout << " Test #8...... Passed!" << endl;
		else
			cout << " Test #8...... Failed!" << endl;
		break;
	}


	//---TEST 9---
	while (true)
	{
		// loading files
		ifstream fileblue9;
		fileblue9.open("input/layer_blue.tga", ios_base::in | ios_base::binary);
		newfile newfileblue9;
		readfile(newfileblue9, fileblue9);

		ifstream filegreen9;
		filegreen9.open("input/layer_green.tga", ios_base::in | ios_base::binary);
		newfile newfilegreen9;
		readfile(newfilegreen9, filegreen9);

		ifstream filered9;
		filered9.open("input/layer_red.tga", ios_base::in | ios_base::binary);
		newfile newfilered9;
		readfile(newfilered9, filered9);

		//performing operations and outputting
		ifstream fileexample9;
		newfile result9 = combinethreefiles(newfileblue9, newfilegreen9, newfilered9);
		readfile(result9, fileexample9);

		ofstream testfile9;
		testfile9.open("output/part9.tga", ios_base::out | ios_base::binary);
		writefile(result9, testfile9);

		//loading example
		ifstream example9;
		example9.open("examples/EXAMPLE_part9.tga", ios_base::in | ios_base::binary);
		newfile example9a;
		readfile(example9a, example9);

		//testing files
		if (testfiles(example9a, result9))
			cout << " Test #9...... Passed!" << endl;
		else
			cout << " Test #9...... Failed!" << endl;
		break;
	}



	//---TEST 10---
	while (true)
	{
		//loading files
		ifstream filetext10;
		filetext10.open("input/text2.tga", ios_base::in | ios_base::binary);
		newfile newfiletext10;
		readfile(newfiletext10, filetext10);

		//performing calculation and outputting
		newfile result10 = flipfile(newfiletext10);
		ifstream fileexample10;
		readfile(result10, fileexample10);

		ofstream testfile10;
		testfile10.open("output/part10.tga", ios_base::out | ios_base::binary);
		writefile(result10, testfile10);

		//loading example
		ifstream example10;
		example10.open("examples/EXAMPLE_part10.tga", ios_base::in | ios_base::binary);
		newfile example10a;
		readfile(example10a, example10);

		//testing files
		if (testfiles(example10a, result10))
			cout << " Test #10...... Passed!" << endl;
		else
			cout << " Test #10...... Failed!" << endl;
		break;
	}


	//---EXTRA CREDIT---
	while (true)
	{
		//loading files
		ifstream fileecbottomleft;
		fileecbottomleft.open("input/text.tga", ios_base::in | ios_base::binary);
		newfile newfileecbottomleft;
		readfile(newfileecbottomleft, fileecbottomleft);

		ifstream fileecbottomright;
		fileecbottomright.open("input/pattern1.tga", ios_base::in | ios_base::binary);
		newfile newfileecbottomright;
		readfile(newfileecbottomright, fileecbottomright);

		ifstream fileectopleft;
		fileectopleft.open("input/car.tga", ios_base::in | ios_base::binary);
		newfile newfileectopleft;
		readfile(newfileectopleft, fileectopleft);

		ifstream fileectopright;
		fileectopright.open("input/circles.tga", ios_base::in | ios_base::binary);
		newfile newfileectopright;
		readfile(newfileectopright, fileectopright);

		//performing calculation and outputting
		newfile resultec = combinefourfiles(newfileecbottomleft, newfileecbottomright, newfileectopleft, newfileectopright);
		ifstream fileexampleec;
		readfile(resultec, fileexampleec);

		ofstream testfileec;
		testfileec.open("output/extracredit.tga", ios_base::out | ios_base::binary);
		writefile(resultec, testfileec);

		//loading example
		ifstream exampleec;
		exampleec.open("examples/EXAMPLE_extracredit.tga", ios_base::in | ios_base::binary);
		newfile exampleeca;
		readfile(exampleeca, exampleec);

		//testing files
		if (testfiles(exampleeca, resultec))
			cout << " Test Extra Credit...... Passed!" << endl;
		else
			cout << " Test Extra Credit...... Failed!" << endl;
		break;



		break;
	}

}
