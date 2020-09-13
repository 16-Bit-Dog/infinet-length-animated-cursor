// made by Ariel G.



#define OEMRESOURCE 
#include <windows.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
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


int main() {
	


	std::cout << "NOTE; restarting your computer resets any changed cursors. \n\nto use the program (multipule can be open at once):\n1. fill a folder with the images you want to be rotated through (name example, 1.CUR)\n2. drag and drop the folder in this window\n3. click enter \n4. chose which cursor you want to animate (ex: hand arrow) - and number of images to cycle through (putting a impossible value will result in a crash)\n5. the cursor will animate\n";

	std::cin >> fileNameS;

	for (auto i:fileNameS) {
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
		
		if (cursorList[i-1] == NULL) {

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
		std::cout << "\nType " <<i<<" :"<< value.first << "\n";
		std::cout << "\nInfo :" << value.second << "\n\n\n";

	}
	

	std::cout << "\nEnter the cursor type to modify:";
	std::cin >> cursorType;
	std::cout<<"\n";

	https://www.youtube.com/channel/UCUcexVbcU3qnBY9v8elVCpQ?view_as=subscriber

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

				i = (filesToRead == 1) ?-1:0;



				for (int x = 1; x <= filesToRead; x++) {

					std::string fileNameRevised = (fileName + "\\" + std::to_string(x) + ".CUR");

					cursorList[x-1] = (LoadCursorFromFileA(fileNameRevised.c_str()));

					if (cursorList[x - 1] == NULL) {

						std::cout << "\n invalid handle made";

					}

				}




		}
		//	std::cout << i;
			
		}
		
	
		return 0;
}
