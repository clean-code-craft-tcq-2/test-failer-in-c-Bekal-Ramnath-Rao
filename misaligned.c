#include <stdio.h>
#include <assert.h>
#include <string.h>

const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

void printColorMapOnConsole(const char*,const char*,int,int);

const char* getMajorcolor(int);
const char* getMinorcolor(int);

const char* getMajorcolor(int index)
{
	return majorColor[index];
}

const char* getMinorcolor(int index)
{
	return minorColor[index];
}

int printColorMap(void (*fun_printonConsole)(const char*, const char*,int,int), const char* (*fun_getMajorMinorcolor[])(int)) {
	int i=0,j=0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            fun_printonConsole(fun_getMajorMinorcolor[0](i), 
            					   fun_getMajorMinorcolor[1](i),i,j);
        }
    }
    return i * j;
}


void printColorMapOnConsole(const char* colorMajor,const char* colorMinor, int index_major, int index_minor)
{
	printf("%d | %s | %s\n", index_major* 5 + index_minor,colorMajor,colorMinor); 
}

void Test_printColorMapOnConsole(const char* colorMajor,const char* colorMinor,int index_major, int index_minor)
{
	assert(colorMajor == majorColor[index_major]);
	assert(colorMinor == minorColor[index_minor]);
}

int main() {
	const char* (*l_getMajorMinorcolor[])(int) = {getMajorcolor,getMinorcolor}; 
	void (*l_printonConsole)(const char*, const char*,int,int) = printColorMapOnConsole;	
    int result = printColorMap(l_printonConsole, l_getMajorMinorcolor);
    assert(result == 25);

    /* Testing function printColorMap */
    void (*l_testprintonConsole)(const char*, const char*,int,int) = Test_printColorMapOnConsole;	
    result = printColorMap(l_testprintonConsole, l_getMajorMinorcolor);
    assert(result == 25);
    printf("All is well (maybe!)\n");
    return 0;
}