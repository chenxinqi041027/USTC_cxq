#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Replace(char *text, char *s1, char *s2, char *text2)
{
	int cnt = 0, L = strlen(text), l1 = strlen(s1), l2 = strlen(s2);
	int i, j, pos = 0;
	for(i = 0; i < L; i++)
	{
		if(text[i] == s1[0])
		{
			int flag = 1;
			for(j = 1; j < l1; j++)
			{
				if(text[i + j] != s1[j])
				{
					flag = 0; break;
				}
			}
			if(flag)
			{
				cnt++;
				for(int k = 0; k < l2; k++)
				{
					text2[pos++] = s2[k];
				}
				i += l1 - 1;
			}
			else text2[pos++] = text[i];
		}
		else text2[pos++] = text[i];
	}
	return cnt;
}


int main()
{
	char text[1000] = "I wish to wish the wish you wish to wish.";
	char s1[1000], s2[1000], text2[1000];
	int N;
	printf("S1 = ");
	scanf("%s", s1);
	printf("S2 = ");
	scanf("%s", s2);
	N = Replace(text, s1, s2, text2);
	printf("%d items replaced!\n", N);
	printf("Replaced text = %s", text2);
	return 0;
} 
