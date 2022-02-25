#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int startAddress = 2048 + 8 + 10;

#define MAX_LABELS 200
unsigned int labelAddrTable[MAX_LABELS];
unsigned int labelCount = 0;

bool entryPointFound = false;
int entryPointIndex = -1;

char *functionLabels[MAX_LABELS];
int functionAddress[MAX_LABELS];
unsigned int functionLabelCount = 0;

unsigned int stackOffset = 0;

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
                else if(line[0] == '#')
                {
                    char functionLabel[100];
                    int n = 1;
                    while(line[n] != '\n')
                    {
                        functionLabel[n-1] = line[n];
                        n++;
                    }
                    functionLabel[n-1] = 0;

                    if(!strcmp("main", functionLabel))
                    {
                        entryPointFound = true;
                        entryPointIndex = functionLabelCount;
                    }

                    functionLabels[functionLabelCount] = strdup(functionLabel);
                    functionAddress[functionLabelCount] = currentAddress;
                    functionLabelCount++;
                }
                else if(!(line[0] >= '0' && line[0] <= '9') && line[0] != '\n')
                {
                    printf("%d -> %s", currentAddress, line);
                    currentAddress += 2;
                }
            }

            if(len > 1 && line[0] == '$')
            {
                int n = 1;
                while(line[n] != '\n')
                {
                    stackOffset *= 10;
                    stackOffset += (line[n] - '0');
                    n++;
                }
            }
            memset(line, 0, 100);
        }
    }
    else
    {
        printf("[ERROR] failed to load input file!\n");
    }

    if(labelCount > 0)
    {
        printf("\nLabel Address Table:\n");
        for(int n = 0; n < labelCount; n++)   
        {
            printf("L%d -> %d\n", n, labelAddrTable[n]);
        }
    }

    printf("\nFunction Address Table:\n");
    for(int n = 0; n < functionLabelCount; n++)   
    {
        printf("%d -> %s\n", functionAddress[n], functionLabels[n]);
    }

    printf("stack offset : %d\n", stackOffset);

    fseek(in, 0, SEEK_SET);

    //replacing labels with address

    if(entryPointFound)
    {
        FILE *out = fopen("out_linked.xsm", "w");

        fprintf(out, "0\n2056\n0\n0\n0\n0\n0\n0\n");
        fprintf(out, "MOV SP, %d\n", 4096 + stackOffset - 1);
        fprintf(out, "PUSH R0\n");
        fprintf(out, "CALL %d\n", functionAddress[entryPointIndex]);
        fprintf(out, "BRKP\n");
        fprintf(out, "INT 10\n");

        unsigned int instructionCount = 0;
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
                        instructionCount++;
                        line[len-3] = 0;
                        fprintf(out, "%s%d\n", line, labelAddrTable[(line[len-2]) - '0']);
                        continue;
                    }
                    else if(len > 4 && line[0] == 'C' && line[1] == 'A' && line[2] == 'L' && line[3] == 'L')
                    {
                        instructionCount++;
                        if(line[5] >= '0' && line[5] <= '9')
                        {
                            fprintf(out, "%s", line);
                            continue;
                        }

                        char label[100];
                        int n = 5;
                        while(line[n] != '\n')
                        {
                            label[n - 5] = line[n];
                            n++;
                        }
                        label[n - 5] = 0;

                        bool labelFound = false;
                        for(int n = 0; n < functionLabelCount; n++)
                        {
                            if(!strcmp(label, functionLabels[n]))
                            {
                                fprintf(out, "CALL %d\n", functionAddress[n]);
                                labelFound = true;
                                break;
                            }
                        }

                        if(!labelFound)
                        {
                            printf("[ERROR] undefined reference to '%s'\n", label);
                        }

                        continue;
                    }
                    else if(line[0] == '#')
                    {
                        continue;
                    }
                    instructionCount++;
                }

                if(len > 1 && line[0] == '$')
                {
                    continue;
                }

                fprintf(out, "%s", line);
                memset(line, 0, 100);
            }

            printf("instruction count: %u\n", instructionCount);
        }
        else
        {
            printf("[ERROR] failed to open output file!\n");
        }
        fclose(out);
    }
    else
    {
        printf("[ERROR] entry point 'main' undefined !\n");
    }
    
    fclose(in);

    return 0;
}