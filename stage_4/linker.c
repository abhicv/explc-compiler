#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABELS 1200
unsigned int labelAddrTable[MAX_LABELS];
unsigned int labelCount = 0;

unsigned int startAddress = 2048 + 8;

int main(int argc, char *argv[])
{
    FILE *in = fopen("out.xsm", "r");
    
    if(in)
    {
        int currentAddress = startAddress;

        char line[100] = {0};
        while(fgets(line, 100, in) != NULL)
        {
            int len = strlen(line);

            if(len > 3)
            {
                if(line[0] == 'L' && (line[1] >= '0' && line[1] <= '9'))
                {
                    int index = line[1] - '0';
                    labelAddrTable[index] = currentAddress;
                    labelCount++;
                }
                else if(!(line[0] >= '0' && line[0] <= '9') && line[0] != '\n')
                {
                    printf("%d -> %s", currentAddress, line);
                    currentAddress += 2;
                }
            }
            memset(line, 0, 100);
        }
    }
    else
    {
        printf("Failed to load input file!\n");
    }

    printf("\nAddress Table:\n");
    for(int n = 0; n < labelCount; n++)   
    {
        printf("L%d -> %d\n", n, labelAddrTable[n]);
    }

    fseek(in, 0, SEEK_SET);

    //second pass
    FILE *out = fopen("out_linked.xsm", "w");

    if(out)
    {
        char line[100] = {0};
        while(fgets(line, 100, in) != NULL)
        {
            int len = strlen(line);

            if(len > 3)
            {
                if(line[0] == 'L' && (line[1] >= '0' && line[1] <= '9'))
                {
                    continue;
                }
                else if(line[0] == 'J' && line[len-3] == 'L')
                {
                    line[len-3] = 0;
                    fprintf(out, "%s%d\n", line, labelAddrTable[(line[len-2]) - '0']);
                    continue;
                }
            }
            fprintf(out, "%s", line);
            memset(line, 0, 100);
        }
    }
    else
    {
        printf("Failed to open output file!\n");
    }
    
    fclose(out);
    fclose(in);

    return 0;
}