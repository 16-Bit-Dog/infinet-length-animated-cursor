// made by Ariel Glasroth
// video in the tutorial is mine... 
// this is under the appache liscene 2.0 and all that legal stuff:
// yes this is not fully efficent in any way; just works with low overhead for what it needs to do

#define _CRT_SECURE_NO_WARNINGS
#define ERROR
#define OEMRESOURCE 
#include <windows.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <libavcodec/avcodec.h>
#include <fstream>

#define INBUF_SIZE 4096


char check = 'y';

std::string fileNameS;
std::string fileName;
int filesToRead;
int cursorType;
std::pair<DWORD, std::string> value;
int delay = 0;

std::pair<DWORD,std::string> convertType(int a) { // 14 cursors
	std::pair<DWORD,std::string> result;

	switch (a) {

	case 1:

		result.first = 32650;
		result.second = "Small hourglass + pointer";
		
		return result;
		break;
	case 2:
		result.first = 32512;
		result.second = "Standard arrow";

		return result;
		break;
	case 3:
		result.first = 32515;
		result.second = "Crosshair";

		return result;
		break;
	case 4:
		result.first = 32649;
		result.second = "Hand";

		return result;
		break;
	case 5:
		result.first = 32651;
		result.second = "Question mark";

		return result;
		break;
	case 6:
		result.first = 32513;
		result.second = "I-beam pointer: the 'I' shaped thing that shows when your mouse is over text";

		return result;
		break;
	case 7:
		result.first = 32648;
		result.second = "Slashed circle/no symbol";

		return result;
		break;
	case 8:
		result.first = 32646;
		result.second = "Four-pointed arrow pointing north, south, east, and west";

		return result;
		break;
	case 9:
		result.first = 32643;
		result.second = "Double-pointed arrow pointing northeast and southwest";

		return result;
		break;
	case 10:
		result.first = 32645;
		result.second = "Double-pointed arrow pointing north and south";

		return result;
		break;
	case 11:
		result.first = 32642;
		result.second = "Double-pointed arrow pointing northwest and southeast";

		return result;
		break;
	case 12:
		result.first = 32644;
		result.second = "Double-pointed arrow pointing west and east";

		return result;		
		break;
	case 13:
		result.first = 32516;
		result.second = "Vertical arrow";

		return result;
		break;
	case 14:
		result.first = 32514;
		result.second = "Hourglass";

		return result;
		break;
	}
}

void ImageToCursor(){



	std::cout << "NOTE; restarting your computer resets any changed cursors (you can also use method 'r'/'R'). \n\nto use the program (multipule can be open at once):\n1. fill a folder with the images you want to be rotated through (name example, 1.CUR)\n2. drag and drop the folder in this window\n3. click enter \n4. chose which cursor you want to animate (ex: hand arrow) - and number of images to cycle through (putting a impossible value will result in a crash)\n5. the cursor will animate\n";

	std::cin >> fileNameS;

	for (auto i : fileNameS) {
		if (i != '"') {
			fileName += i;
		}
	}

	std::cout << "\nenter the image count\n";

	std::cin >> filesToRead;

	std::vector<HCURSOR> cursorList;

	for (int i = 1; i <= filesToRead; i++) {
		std::string fileNameRevised = (fileName + "\\" + std::to_string(i) + ".CUR");

		cursorList.push_back(LoadCursorFromFileA(fileNameRevised.c_str()));

		if (cursorList[i - 1] == NULL) {

			std::cout << "\n fileName was incorrect";

		}

	}

	for (int i = 0; i < filesToRead; i++) {

		if (cursorList[i] == NULL) {
			std::cout << "oof";
		}

	}

	for (int i = 1; i < 15; i++) {
		value.first = convertType(i).first;
		value.second = convertType(i).second;
		std::cout << "\nType " << i << " :" << value.first << "\n";
		std::cout << "\nInfo :" << value.second << "\n\n\n";

	}


	std::cout << "\nEnter the cursor type to modify:";
	std::cin >> cursorType;
	std::cout << "\n";

	DWORD cursorID = convertType(cursorType).first;

	SetSystemCursor(LoadCursor(0, IDC_ARROW), cursorID); // reset cursor

	std::cout << "enter the delay until each cursor picture changes (miliseconds)\n";

	std::cin >> delay;

	std::cout << "\n";


		for (int i = 0; i < filesToRead; i++) {
			Sleep(delay);
			SetSystemCursor(cursorList[i], cursorID);


			//SystemParametersInfoA(SPI_SETCURSORS, 0, NULL, 0); // reload cursors
			if (i + 1 >= filesToRead) {

				i = (filesToRead == 1) ? -1 : 0;



				for (int x = 1; x <= filesToRead; x++) {

					std::string fileNameRevised = (fileName + "\\" + std::to_string(x) + ".CUR");

					cursorList[x - 1] = (LoadCursorFromFileA(fileNameRevised.c_str()));

					if (cursorList[x - 1] == NULL) {

						std::cout << "\n invalid handle made";

					}

				}




		}
			//	std::cout << i;

	}

}

void VideoToCursor() {

	std::cout << "NOTE 1: once you do this operation, you can use them again with method y/Y (you need to look at the largest image name minus 1 to get the number of images). This method also may take more time depending on your computers speed \n\nNOTE; restarting your computer resets any changed cursors (you can also use method 'r'/'R'). You also need ffmpeg.exe to use this feature of the program; download it from their official website and when extracting the archive it should be in ffmpeg/bin/'ffmpeg' \n\nto use the program(multipule can be open at once) :\n1.fill a folder with the video you want to be rotated through(name must be 'video.mp4' -make sure the folder does not have spaces (and is just lowercase letters)   -- > yes you need a mp4, make a github issue request if someone - for some reason - wants this change)\n2.drag and drop the folder in this window\n3.click enter (sometimes you need to do it twice) \n4.chose which cursor you want to animate(ex: hand arrow) - and number of images to cycle through(putting a impossible value will result in a crash)\n5.the cursor will animate\n";



	std::cin >> fileNameS;
	std::cin.sync();

	for (auto i : fileNameS) {
		if (i != '"') {
			fileName += i; // this is were files will be saved...
		}
	}
	
	std::string VideoFileType = "mp4";

	std::cout << "\n enter your video file type. For example, if your video is video.mp4, write down 'mp4' and click 'enter'   ---> if video.avi, write down 'avi' and click 'enter'";

	std::cin >> VideoFileType;         // --> if someone really cares I'll make a second version that supports more than just whats here, this is bassically all the code I need
	
	std::string fileNameExtension = fileName + "\\video."+ VideoFileType; // file and vid


	std::string ffmpegLocation;
	
	std::cout << "drag and drop the ffmpeg program into this command line and click enter\n\n" << std::endl;

	
	
	std::cin>> ffmpegLocation;
	std::cin.sync();



	std::string command;

	if (system(ffmpegLocation.c_str()) == 0) { // system outputs cmd commands, so I need to output a command to open and put commands in ffmpeg here

		std::cout << "wrong path to ffmpeg.exe, or the file was renamed";

	}

	std::string fileNameChanged = fileName + "\\%d.jpg"; //lots of pictures... --> you may hit a maximum one day... I think the max is a long long int...

	command = ffmpegLocation +" -r 1 -i "+ fileNameExtension+ " -r 1 "+ fileNameChanged;

	system(command.c_str());
	
	std::string nameUnchanged;
	std::string nameChanged;
	
	int count = 0; // number of images
	
	
	while (true) {
		count += 1; // interate through all items

		fileNameChanged = fileName + "\\" + std::to_string(count)+".jpg";

		nameUnchanged = fileName + "\\" + std::to_string(count) + ".ico";

		nameChanged = fileName + "\\" + std::to_string(count) + ".cur";
		

		command = ffmpegLocation + " -i " + fileNameChanged + " -vf scale=32:32 "+ nameUnchanged;

		std::ifstream ifile(fileNameChanged.c_str());

		if (!ifile) {

			break;

		}

		ifile.close();

		
		system(command.c_str());
		
		while (true) {//wait until deletes; ffmpeg may not be synced with move file and delete file (its a external cmd process), not allowing delete or renaming (from file use)

			if (DeleteFileA(fileNameChanged.c_str())) {

				break;

			}

		}

		//.cur and .ico are almost always interchangable

		while (true) { // wait until renames; ffmpeg may not be synced with move file and delete file (its a external cmd process), not allowing delete or renaming (from file use)
		
			if ((rename((nameUnchanged.c_str()), (nameChanged.c_str())))) {

				break;

			}
		
		}
	}

	count -= 1; // I add one before operations --> number of images


	//////////////////////////////////////////



	std::vector<HCURSOR> cursorList;

	for (int i = 1; i <= count; i++) {
		std::string fileNameRevised = (fileName + "\\" + std::to_string(i) + ".cur");

		cursorList.push_back(LoadCursorFromFileA(fileNameRevised.c_str()));

		if (cursorList[i - 1] == NULL) {

			std::cout << "\n fileName was incorrect";

		}

	}

	for (int i = 0; i < count; i++) { // make sure you have all images

		if (cursorList[i] == NULL) {
			std::cout << "oof";
		}

	}

	for (int i = 1; i < 15; i++) {
		value.first = convertType(i).first;
		value.second = convertType(i).second;
		std::cout << "\nType " << i << " :" << value.first << "\n";
		std::cout << "\nInfo :" << value.second << "\n\n\n";

	}


	std::cout << "\nEnter the cursor type to modify:";
	std::cin >> cursorType;
	std::cout << "\n";

	DWORD cursorID = convertType(cursorType).first;


	std::cout << "enter the delay until each cursor picture changes (this value is miliseconds) --> I reccomend making this the fps of the video; math would be INPUT = 1000/fpsOfVideo --> ex: if video is 24fps,  INPUT = 1000/24, INPUT = 42  --> also as a side note; your cursor pointer is pointing at the very left and middle of the square\n";

	std::cin >> delay;

	std::cout << "\n";


	for (int i = 0; i < count; i++) {
		Sleep(delay);
		SetSystemCursor(cursorList[i], cursorID);

		//SystemParametersInfoA(SPI_SETCURSORS, 0, NULL, 0); // reload cursors
		if (i + 1 >= count) {

			i = (count == 1) ? -1 : 0;



			for (int x = 1; x <= count; x++) {

				std::string fileNameRevised = (fileName + "\\" + std::to_string(x) + ".cur");

				cursorList[x - 1] = (LoadCursorFromFileA(fileNameRevised.c_str()));

				if (cursorList[x - 1] == NULL) {

					std::cout << "\n invalid handle made";

				}

			}




		}
		//	std::cout << i;

	}


	///////////////////////////////////////////




}

void revertCursor() {
	HCURSOR cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\wait_im.cur");
	
	for (int i = 1; i < 15; i++) {
		value.first = convertType(i).first;
		value.second = convertType(i).second;
		std::cout << "\nType " << i << " :" << value.first << "\n";
		std::cout << "\nInfo :" << value.second << "\n\n\n";

	}


	std::cout << "\nEnter the cursor type to revert (only works if windows is in c: drive, and cursors folder is inside the windows folder [this is default for windows])  --> C:\\Windows\\Cursors is the position of the default:";
	std::cin >> cursorType;
	std::cout << "\n";

	
	DWORD cursorID = convertType(cursorType).first;

	switch (cursorID) { 

		//C:\\Windows\\Cursors\\   
	case 32650:
		cursor =LoadCursorFromFileA("C:\\Windows\\Cursors\\size4_m.cur");
		break;
	case 32512:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_arrow.cur");
		break;
	case 32515:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\cross_il.cur");
		break;
	case 32649:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_link_l.cur");
		break;
	case 32651:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_helpsel_l.cur");
		break;
	case 32513:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\beam_l.cur");
		break;
	case 32648:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_unavail_l.cur");
		break;
	case 32646:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_move_l.cur");
		break;
	case 32643:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_nesw_l.cur");
		break;
	case 32645:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_ns_l.cur");
		break;
	case 32642:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_nwse_l.cur");
		break;
	case 32644:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_ew_l.cur");
		break;
	case 32516:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\aero_up_l.cur");
		break;
	case 32514:
		cursor = LoadCursorFromFileA("C:\\Windows\\Cursors\\wait_il.cur");
		break;
	}

	SetSystemCursor(cursor, cursorID);

}


int main() { // yes a switch case is better for this, but I really dont care, this is not active runtime check for 99.999% of the program
	
	std::cout << "click 'Y' or 'y' and enter for 'image to cursor', or 'r' (and 'R') to revert a cursor to default... any other letter turns on 'video to cursor' mode\n\n\n\n\n";
	std::cin >> check;
	
	std::cout << "\n\n\n";

	if (check == 'y' || check == 'Y') {
		ImageToCursor();
	}

	else if(check == 'r' || check == 'R') {

		revertCursor();

	}

	else {

		VideoToCursor();

	}



	return 0;
}
