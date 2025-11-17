#include <stdio.h>
#include <string.h>

int find_match(char str[], char pat[], char rep[], char ans[]);

int main()
{
    char str[100], pat[100], rep[100], ans[100];
    int flag;

    printf("Enter the main string:\n");
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = 0;

    printf("Enter the pattern string to be searched:\n");
    fgets(pat, 100, stdin);
    pat[strcspn(pat, "\n")] = 0;

    printf("Enter the replacement string:\n");
    fgets(rep, 100, stdin);
    rep[strcspn(rep, "\n")] = 0;

    flag = find_match(str, pat, rep, ans);

    if (flag)
    {
        printf("\nPattern found.\n");
        printf("The string after replacement is: %s\n", ans);
    }
    else
    {
        printf("\nPattern not found.\n");
    }

    return 0;
}

int find_match(char str[], char pat[], char rep[], char ans[])
{
    int i, j, k, m, flag;
    i = k = 0;
    flag = 0;

    int pat_len = strlen(pat);

    if (pat_len == 0) {
        strcpy(ans, str);
        return 0;
    }

    while (str[i] != '\0')
    {
        m = i;
        j = 0;
        while (str[m] == pat[j] && pat[j] != '\0') {
            m++;
            j++;
        }

        if (j == pat_len)
        {
            flag = 1;
            for (int l = 0; rep[l] != '\0'; l++) {
                ans[k++] = rep[l];
            }
            i += pat_len;
        }
        else
        {
            ans[k++] = str[i++];
        }
    }
    ans[k] = '\0';
    return flag;
}