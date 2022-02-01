#include <stdio.h>
#include <assert.h>
#include <string.h>

#define ENVIRONMENT_PRODUCTION 	0
#define ENVIRONMENT_TEST 	1

#define ENVIRONMENT ENVIRONMENT_TEST

#define MAJOR_COLOR 0
#define MINOR_COLOR 1

const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

#if(ENVIRONMENT == ENVIRONMENT_TEST)

int Test_index=0;

char Test_Buffer[25][25] =   {" 0 | White  | Blue",
			      " 1 | White  | Orange",
			      " 2 | White  | Green",
			      " 3 | White  | Brown",
			      " 4 | White  | Slate",
			      " 5 | Red    | Blue",
			      " 6 | Red    | Orange",
			      " 7 | Red    | Green",
			      " 8 | Red    | Brown",
			      " 9 | Red    | Slate",
			      "10 | Black  | Blue",
			      "11 | Black  | Orange",
			      "12 | Black  | Green",
			      "13 | Black  | Brown",
			      "14 | Black  | Slate",
			      "15 | Yellow | Blue",
			      "16 | Yellow | Orange",
			      "17 | Yellow | Green",
			      "18 | Yellow | Brown",
			      "19 | Yellow | Slate",
			      "20 | Violet | Blue",
			      "21 | Violet | Orange",
			      "22 | Violet | Green",
			      "23 | Violet | Brown",
			      "24 | Violet | Slate"
			      };
#endif

char buffer[50];

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

int printColorMap(void (*fun_formatonConsole)(const char*, const char*,int,int, void(*)()), const char* (*fun_getMajorMinorcolor[])(int)
					,void (*fun_printOnConsole)()) {
    int i=0,j=0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            fun_formatonConsole(fun_getMajorMinorcolor[MAJOR_COLOR](i), 
            					   fun_getMajorMinorcolor[MINOR_COLOR](i),i,j,fun_printOnConsole);
        }
    }
    return i * j;
}

void printColorMapOnConsole()
{
	printf("%s",buffer);
}

void formatColorMapOnConsole(const char* colorMajor,const char* colorMinor, int index_major, int index_minor,void (*fun_printOnConsole)())
{
	sprintf(buffer,"%d | %s | %s\n", index_major* 5 + index_minor,colorMajor,colorMinor); 
	fun_printOnConsole();
}

#if(ENVIRONMENT == ENVIRONMENT_TEST)
void Test_PrintandFormatOnConsole()
{
	assert(buffer == Test_Buffer[Test_index]);
	Test_index++;
}

const char* Test_getMajorcolor(int index)
{
	return getMajorcolor(index);
}

const char* Test_getMinorcolor(int index)
{
	return getMinorcolor(index);
}

void Test_Environment()
{
    const char* l_testgetMajorcolor = Test_getMajorcolor(0);
    assert(strcmp(l_testgetMajorcolor ,"White") == 0);
    l_testgetMajorcolor = Test_getMajorcolor(3);
    assert(strcmp(l_testgetMajorcolor ,"Yellow") == 0);
    const char* l_testgetMinorcolor = Test_getMinorcolor(1);
    assert(strcmp(l_testgetMinorcolor ,"Orange") == 0);
    l_testgetMinorcolor = Test_getMinorcolor(2);
    assert(strcmp(l_testgetMinorcolor ,"Green")  == 0);

    /* Testing function printColorMap, getMinorcolor, getMajorcolor, formatColorMapOnConsole */
    const char* (*l_testgetMajorMinorcolor[])(int) = {getMajorcolor,getMinorcolor}; 
    void (*l_testformatonConsole)(const char*, const char*,int,int,void (*)()) = formatColorMapOnConsole;
    void (*l_testprintOnConsole)() = Test_PrintandFormatOnConsole;
    int result = printColorMap(l_testformatonConsole, l_testgetMajorMinorcolor,l_testprintOnConsole);
    assert(result == 25);

    printf("All is well (maybe!)\n");
}
#endif

int main() {

    #if(ENVIRONMENT == ENVIRONMENT_PRODUCTION)
    const char* (*l_getMajorMinorcolor[])(int) = {getMajorcolor,getMinorcolor}; 
    void (*l_formatonConsole)(const char*, const char*,int,int,void (*p)()) = formatColorMapOnConsole;
    void (*l_printOnConsole)() = printColorMapOnConsole;
    int result = printColorMap(l_formatonConsole, l_getMajorMinorcolor,l_printOnConsole);
    assert(result == 25);
    #endif
    
    #if(ENVIRONMENT == ENVIRONMENT_TEST)
    Test_Environment();
    #endif
    return 0;
}
