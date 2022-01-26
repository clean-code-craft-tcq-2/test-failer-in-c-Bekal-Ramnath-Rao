#include <stdio.h>
#include <assert.h>
#include <string.h>

#define ENVIRONMENT_PRODUCTION 	0
#define ENVIRONMENT_TEST 	   	1

#define ENVIRONMENT ENVIRONMENT_TEST

#define MAJOR_COLOR 0
#define MINOR_COLOR 1

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
            fun_printonConsole(fun_getMajorMinorcolor[MAJOR_COLOR](i), 
            					   fun_getMajorMinorcolor[MINOR_COLOR](i),i,j);
        }
    }
    return i * j;
}


void printColorMapOnConsole(const char* colorMajor,const char* colorMinor, int index_major, int index_minor)
{
	printf("%d | %s | %s\n", index_major* 5 + index_minor,colorMajor,colorMinor); 
}

#if(ENVIRONMENT == ENVIRONMENT_TEST)
void Test_printColorMapOnConsole(const char* colorMajor,const char* colorMinor,int index_major, int index_minor)
{
	assert(colorMajor == majorColor[index_major]);
	assert(colorMinor == minorColor[index_minor]);
}

const char* Test_getMajorcolor(int index)
{
	return getMajorcolor(index);
}

const char* Test_getMinorcolor(int index)
{
	return getMinorcolor(index);
}
#endif

int main() {
	const char* (*l_getMajorMinorcolor[])(int) = {getMajorcolor,getMinorcolor}; 
	void (*l_printonConsole)(const char*, const char*,int,int) = printColorMapOnConsole;	
    int result = printColorMap(l_printonConsole, l_getMajorMinorcolor);
    assert(result == 25);

	#if(ENVIRONMENT == ENVIRONMENT_TEST)
    /* Testing function printColorMap, getMinorcolor, getMajorcolor */
    void (*l_testprintonConsole)(const char*, const char*,int,int) = Test_printColorMapOnConsole;
    const char* l_testgetMajorcolor = Test_getMajorcolor(0);
    assert(strcmp(l_testgetMajorcolor ,"White") == 0);
    l_testgetMajorcolor = Test_getMajorcolor(3);
    assert(strcmp(l_testgetMajorcolor ,"Yellow") == 0);
    const char* l_testgetMinorcolor = Test_getMinorcolor(1);
    assert(strcmp(l_testgetMinorcolor ,"Orange") == 0);
    l_testgetMinorcolor = Test_getMinorcolor(2);
    assert(strcmp(l_testgetMinorcolor ,"Green")  == 0);
    result = printColorMap(l_testprintonConsole, l_getMajorMinorcolor);
    assert(result == 25);
    printf("All is well (maybe!)\n");
    #endif
    return 0;
}