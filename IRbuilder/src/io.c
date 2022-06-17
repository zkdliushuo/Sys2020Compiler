#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


int getint()
{
    int i;
    scanf("%d", &i);
    return i; 
}

int getch()
{
    char c;
    scanf("%c", &c);
    return (int)c;
}

int getarray(int a[])
{
    int n;
    scanf("%d", &n);
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%d", a+i);
    }
    return n;
}

void putint(int a)
{
    printf("%d",a);
}

void putch(int a)
{
    char c = a % 256;
    printf("%c",c);
}

void putarray(int n,int a[])
{
    int i;
    printf("%d: ",n);
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
}

void putf(char *fmt, ...)
{
    va_list ap;
    char *ptr;
    int len = 10*strlen(fmt);
	ptr = (char *)malloc(len * sizeof(char));
	if(ptr == NULL)
	{
		fprintf(stderr, "malloc failed\n");
		return;
	}
    memset(ptr, 0, len);

    va_start(ap, fmt);
	vsprintf(ptr, fmt, ap);
	va_end(ap);
 
	ptr[len-1] = '\0';
    printf("%s",ptr);
}

void starttime()
{

}

void stoptime()
{

}
