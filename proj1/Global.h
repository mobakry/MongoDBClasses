#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define BYTE_ORDER_MARK 0xFEFF

void CopyString(char *_Dest, char *_Source, int MaxDestSize);
void ConcatString(char *_Dest, char *_Source, int MaxDestSize);

void ConvertUtf8ToAnsi(char *inputBuffer, char* OutputBuffer);

void ConvertAnsiToUtf8(char *inputBuffer, char* OutputBuffer);


#define		MAX_VARIABLE_SIZE						128

template <int MaxNofRecords, int SizeOfRec>
void	Split(char *Input, char *Delimiter, int &NumberOfWordToken, char(&TokenArry)[MaxNofRecords][SizeOfRec], int MaxNofWordTokens, int SizeOfRec)
{
	int i, stringIdx = 0;
	bool DelimeterState = false;

	for (i = 0; i < MaxNofRecords; i++)
		memset(TokenArry[i], 0, sizeof(char)*SizeOfRec);

	if (strcmp(Input, "") == 0)
	{
		NumberOfWordToken = 0;
		return;
	}

	NumberOfWordToken = 0;

	i = 0;

	while (Input[i] != '\0' && NumberOfWordToken<MaxNofRecords)
	{
		if (strncmp(&Input[i], Delimiter, strlen(Delimiter)) != 0)
		{
			if (Input[i] != '\n' && Input[i] != '\r' && stringIdx < SizeOfRec - 1)
			{
				TokenArry[NumberOfWordToken][stringIdx] = Input[i];
				stringIdx++;
			}
			DelimeterState = false;
			i++;
			continue;
		}
		else
		{
			if (stringIdx == 0)
			{
				i++;
				continue;
			}

			TokenArry[NumberOfWordToken][stringIdx] = 0;
			stringIdx = 0;
			i += strlen(Delimiter);
			NumberOfWordToken++;
			DelimeterState = true;
		}
	}

	if (!DelimeterState || (Delimiter[strlen(Delimiter) - 1] != Input[strlen(Input) - 1] && NumberOfWordToken<MaxNofRecords))
	{
		TokenArry[NumberOfWordToken][stringIdx] = 0;
		NumberOfWordToken++;
	}
}



#endif //__GLOBAL_H__

