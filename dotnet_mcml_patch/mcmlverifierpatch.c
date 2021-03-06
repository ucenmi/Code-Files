#include <stdio.h>

/*
Media Center SDK MCML Verifier Crash Patch
Oguz Kartal (c) 2009
*/

int main(int argc, char **argv)
{
	FILE *fexe = NULL;
	unsigned char inst;
	int len=5;
	long instruction_offset = 0x2dc + 0xa;

	if (argc < 2)
	{
		printf("dosya adini girmelisiniz.");
		return 1;
	}

	if ((fexe=fopen(argv[1],"r+")) == NULL)
	{
		printf("dosya bulunamadi. dogru dosya adini girin.");
		return 1;
	}

	fseek(fexe,instruction_offset,SEEK_SET);

	inst = (unsigned char)fgetc(fexe);

	if (inst == 0x28) //is this a call instruction?
	{
		fseek(fexe,instruction_offset,SEEK_SET);
		while (len--)
			fputc(0x0,fexe);
	}
	else
	{
		printf("call komutu bulunamadi");
		fclose(fexe);
		return 1;
	}

	fclose(fexe);

	printf("uygulama patch edildi.");
	fflush(stdin);
	getchar();
	return 0;
}