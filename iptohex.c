#include <stdio.h>
#include <string.h>
#include <math.h>

int fun(char const *);
int hextoint(char*);
char* inttohex(int x, int z, int a, int b, char *s);
//input string maximum length
#define N 20
/*
 *version: 1.2.1_x86
 *Date: 2017/12/25 23:56
 *location: Tangshan
 *aim: To cover the int format ip address and hex format ip address.
 */
int main(int argc, char const *argv[]) 
{
	int info, n = 0;
	//The command line mode
	if (argc > 1) {
		for (n=1;n<argc;n++)
			fun(argv[n]);
		return 0;
	}
	//The normal mode
	printf("To cover ip address from int to hex or hex to int.\nIf you want to quit, enter q.\nversion: 1.2_x86\n\n");
	while (1)
		if      ((info = fun(NULL)) == -1) 	//invalid input
			printf("Enter again.\n");
		else if (info == -2)							//input quit
			break;

	return 0;
}

int fun(char const *w)
{
	int a, b, c, d;//four part of ip address
	int t;//integer format ip address
	char s[N], s1[N], lc;//input str, return str, 

	s[0] = s1[0] = '\0';
	
	if (w == NULL) {
		printf("> ");
		scanf("%19s", s);
	} else strncpy(s, w, N);

	if (*s == 'q')
		return -2;

	if (sscanf(s, "%d.%d.%d.%d%c", &a, &b, &c, &d, &lc) >= 4) {
		if (lc != '\0')
			return -1;
		printf("0x%s\n",inttohex(a, b, c, d, s1));
		return 0;
	}

	if ((t = hextoint(s)) == -3)
		return -1;
	else if ( t == -1)
		a = b = c = d = 255;
	else {

		d =  t & 0xff;
		c = (t & 0xff00) >> 8;
		b = (t & 0xff0000) >> 16;
		a = (t & 0xff000000) >> 24;
	}
	printf("%d.%d.%d.%d\n", a, b, c, d);
	return 0;
}

int hextoint(char *s)
{
	int n = -1, i;//length of variable s,
	int temp = 0;// return integer format ip address
	char a, b;
	
	n = 0;
	while( s[n] != '\0')
		++n;
	if (n == 0 || n > 8)
		return -3;

	for (i=n-1;i>=0;i--) {
		a = s[i];
		if      (a >= '0' && a <= '9')
			b = '0';
		else if (a >= 'a' && a <= 'f')
			b = 'a' - 10;
		else if (a >= 'A' && a <= 'F')
			b = 'A' - 10;
		else
			return -3;
		
		temp += (s[i] - b)*(int)pow(16,n-i-1);
	}
	return temp;
}

char* inttohex(int x, int z, int a, int b, char *s)
{
	int i;
	char q[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	if (x < 0 || x > 255 ||
		z < 0 || z > 255 ||
		a < 0 || z > 255 ||
		b < 0 || b > 255) {
		*s = '\0';
		return s;
	}
	s[0] = q[x/16];
	i = x/16==0?0:1;
	s[0+i] = q[x&0xf];
	s[++i] = q[z/16];
	s[++i] = q[z&0xf];
	s[++i] = q[a/16];
	s[++i] = q[a&0xf];
	s[++i] = q[b/16];
	s[++i] = q[b&0xf];
	s[++i] = '\0';
	return s;
}

/* test data
B7D5F101
183.213.241.1
*/
