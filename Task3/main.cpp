#include "DirectoryProcessor.h"


int main() {
    
	DirectoryProcessor dp;
    dp.ProcessDirectory("D:\\amigos", SAVE_GENERAL_STATS | SAVE_INDIVIDUAL_FILES_STATS);
	dp.WriteStats("D:\\amigos\\bimba.txt");
    return 0;
}
